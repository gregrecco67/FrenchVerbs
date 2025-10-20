#include "App.h"

using namespace visage::dimension;

namespace gwr::frvb
{

VISAGE_THEME_COLOR(WRONG, 0xff991212);
VISAGE_THEME_COLOR(RIGHT, 0xff129912);

App::App() : dbm(":memory:")
{

    setFlexLayout(true);
    layout().setFlexRows(true);
    addChild(header, true);
    addChild(body, true);
    header.setFlexLayout(true);
    header.layout().setDimensions(100_vw, 10_vh);
    header.layout().setFlexRows(false);
    header.layout().setFlexGap(1_vw);
    header.layout().setPadding(8_vh);
    header.outline = false;

    header.addChild(newBtn, true);
    header.addChild(markBtn, true);
    header.addChild(headword, true);
    header.addChild(cmpBtn, true);
    header.addChild(quizUnderway, false);

    newBtn.layout().setDimensions(15_vw, 100_vh);
    markBtn.layout().setDimensions(15_vw, 100_vh);
    headword.layout().setDimensions(35_vw, 100_vh);
    cmpBtn.layout().setDimensions(15_vw, 100_vh);
    quizUnderway.layout().setDimensions(10_vw, 100_vh);
    
    newBtn.setFont(font.withSize(25.f));
    newBtn.onMouseDown() = [&](const visage::MouseEvent &e) { newQuiz(); };

    markBtn.setFont(font.withSize(25.f));
    markBtn.onMouseDown() = [&](const visage::MouseEvent &e) { markQuiz(); };

    cmpBtn.setFont(font.withSize(25.f));
    cmpBtn.onMouseDown() = [&](const visage::MouseEvent &e) { 
        if (cmpBtn.isActive()) { compare(); }
    };
    cmpBtn.setActive(false);

    
    quizUnderway.setText("Quiz underway");
    quizUnderway.setFont(font.withSize(14.f));
    quizUnderway.centered = false;
    quizUnderway.outline = false;

    headword.setFont(font.withSize(25.f));
    headword.onEnterKey() = [this]() { 
        auto head = headword.text().toUtf8();
        newQuiz(head); 
    };
    // ============================

    body.setFlexLayout(true);
    body.layout().setDimensions(100_vw, 90_vh);
    body.layout().setFlexRows(false);
    body.outline = false;
    body.addChild(left, true);
    body.addChild(right, true);

    left.setFlexLayout(true);
    left.layout().setDimensions(49_vw, 100_vh);
    left.layout().setFlexGap(2.f);
    left.layout().setPadding(5.f);

    left.addChild(conjPres, true);
    left.addChild(conjImpf, true);
    left.addChild(conjPs, true);
    left.addChild(conjImper, true);

    conjPres.setFlexLayout(true);
    conjPres.layout().setDimensions(100_vw, 24_vh);
    conjPres.name_ = "Present";
    
    conjImpf.setFlexLayout(true);
    conjImpf.layout().setDimensions(100_vw, 24_vh);
    conjImpf.name_ = "Imperfect";

    conjImper.setFlexLayout(true);
    conjImper.layout().setDimensions(100_vw, 24_vh);
    conjImper.name_ = "Imperative  /  Participles+";
    conjImper.pn1.setText("(tu)");
    conjImper.pn2.setText("(nous)");
    conjImper.pn3.setText("(vous)");
    conjImper.pn4.setText("pres.");
    conjImper.pn5.setText("past");
    conjImper.pn6.setText("aux.");

    conjPs.setFlexLayout(true);
    conjPs.layout().setDimensions(100_vw, 24_vh);
    conjPs.name_ = "Simple Past";

    right.setFlexLayout(true);
    right.layout().setDimensions(49_vw, 100_vh);
    right.layout().setFlexGap(2.f);
    right.layout().setPadding(5.f);

    right.addChild(conjFut, true);
    right.addChild(conjCond, true);
    right.addChild(conjSubjPr, true);
    right.addChild(conjSubjImpf, true);

    conjFut.setFlexLayout(true);
    conjFut.layout().setDimensions(100_vw, 24_vh);
    conjFut.name_ = "Future";

    conjCond.setFlexLayout(true);
    conjCond.layout().setDimensions(100_vw, 24_vh);
    conjCond.name_ = "Conditional";

    conjSubjPr.setFlexLayout(true);
    conjSubjPr.layout().setDimensions(100_vw, 24_vh);
    conjSubjPr.name_ = "Subjunctive Present";

    conjSubjImpf.setFlexLayout(true);
    conjSubjImpf.layout().setDimensions(100_vw, 24_vh);
    conjSubjImpf.name_ = "Subjunctive Imperfect";

    conjs = {&conjPres, &conjImpf, &conjPs, &conjImper, &conjFut, &conjCond, &conjSubjPr, &conjSubjImpf};
}

void App::newQuiz()
{
    std::string dummy;
    newQuiz(dummy);
}

SQLite::Statement App::getRightStatment(std::string &inverb) {
    if (!inverb.empty()) {
        auto likeV = replaceUnaccentedCharacters(inverb);
        auto st = dbm.getStmt("select infinitive from frenchVerbs where infinitive like ?;");
        st.bind(1, likeV);
        std::vector<std::string> infs;
        while (st.executeStep()) {
            infs.push_back(st.getColumn("infinitive").getString());
        }

        std::string finalForm;
        for (auto inf : infs) {
            if (matches(inf, inverb)) {
                finalForm = inf;
            }
        }
        if (!finalForm.empty()) {
            st = dbm.getStmt(
                "select infinitive, present, imperfect, presParticiple, pastParticiple, auxiliary, imperative, future, conditional, passeSimple, "
                "subjunctivePres, subjunctiveImpf from frenchVerbs where infinitive = ?;");
            st.bind(1, finalForm);
            return st;
        }
    }
    auto st = dbm.getStmt(
        "select infinitive, present, imperfect, presParticiple, pastParticiple, auxiliary, imperative, future, conditional, passeSimple, "
        "subjunctivePres, subjunctiveImpf from frenchVerbs order by random() limit 1;");
    return st;
}

void App::newQuiz(std::string &inverb) {
    clearColors();
    clearPronouns();

    auto st = getRightStatment(inverb);

    std::string verb, pres, impf, imperat, pastPart, presPart, aux, fut, cond, ps, subjPres, subjImpf;
    while (st.executeStep())
    {
        verb = st.getColumn("infinitive").getString();
        pres = st.getColumn("present").getString();
        impf = st.getColumn("imperfect").getString();
        imperat = st.getColumn("imperative").getString();
        pastPart = st.getColumn("pastParticiple").getString();
        presPart = st.getColumn("presParticiple").getString();
        aux = st.getColumn("auxiliary").getString();
        fut = st.getColumn("future").getString();
        cond = st.getColumn("conditional").getString();
        ps = st.getColumn("passeSimple").getString();
        subjPres = st.getColumn("subjunctivePres").getString();
        subjImpf = st.getColumn("subjunctiveImpf").getString();
    }
    headword.setText(verb);

    auto presForms = splitForms(pres);
    auto impfForms = splitForms(impf);
    auto imperForms = splitForms(imperat);
    std::vector<std::string> impPartForms;
    impPartForms.push_back(imperForms[1]); // 2nd sg imperat. to first position
    impPartForms.push_back(imperForms[3]); // 1st pl imperat. to second
    impPartForms.push_back(imperForms[4]); // 2nd pl imp. to third
    impPartForms.push_back(presPart);
    impPartForms.push_back(pastPart);
    impPartForms.push_back(aux);
    auto futForms = splitForms(fut);
    auto condForms = splitForms(cond);
    auto psForms = splitForms(ps);
    auto subjPresForms = splitForms(subjPres);
    auto subjImpfForms = splitForms(subjImpf);

    for (size_t i = 0; i < 6; ++i)
    {
        for (auto conj : conjs) {
            conj->es[i]->clear();
        }

        conjPres.dbForms[i] = presForms[i];
        conjImpf.dbForms[i] = impfForms[i];
        conjPs.dbForms[i] = psForms[i];
        conjImper.dbForms[i] = impPartForms[i];
        conjFut.dbForms[i] = futForms[i];
        conjCond.dbForms[i] = condForms[i];
        conjSubjPr.dbForms[i] = subjPresForms[i];
        conjSubjImpf.dbForms[i] = subjImpfForms[i];
    }

    userInputIsShown = true;
    quizIsMarked = false;
    cmpBtn.setActive(false);
    quizUnderway.setVisible(true);
    redraw();
}

void App::markQuiz()
{
    if (!userInputIsShown) return;
    readContents();
    clearColors();

    // compare userForms with dbForms
    for (size_t i = 0; i < 6; ++i)
    {
        for (auto conj : conjs) {
            conj->isCorrect[i] = matches(conj->userForms[i], conj->dbForms[i]);
        }
    }

    // color fields by correctness
    userInputIsShown = true;
    quizIsMarked = true;
    quizUnderway.setVisible(false);
    cmpBtn.setActive(true);
    color();
    redraw();
}

void App::readContents()
{
    for (size_t i = 0; i < 6; ++i)
    {
        for (auto conj : conjs) {
            auto aa = conj->es[i]->text().toUtf8();
            conj->userForms[i] = aa;
        }
    }
}

bool App::matches(std::string &userAnswer, std::string &dbAnswer)
{
    return (replaceAccentedCharacters(userAnswer).compare(replaceAccentedCharacters(dbAnswer)) == 0);
}

void App::draw(visage::Canvas &canvas)
{
    canvas.setColor(0xffbbbbbb);
    canvas.fill(0, 0, width(), height());
}

std::vector<std::string> App::splitForms(std::string entry)
{
    std::vector<std::string> entries;
    size_t pos{0};
    std::string::size_type n;
    n = entry.find(", ");
    if (n != std::string::npos)
    {
        entries.push_back(entry.substr(0, n));
        pos = n + 2;
    }
    n = entry.find(", ", pos);
    if (n != std::string::npos)
    {
        entries.push_back(entry.substr(pos, n - pos));
        pos = n + 2;
    }
    n = entry.find(", ", pos);
    if (n != std::string::npos)
    {
        entries.push_back(entry.substr(pos, n - pos));
        pos = n + 2;
    }
    n = entry.find(", ", pos);
    if (n != std::string::npos)
    {
        entries.push_back(entry.substr(pos, n - pos));
        pos = n + 2;
    }
    n = entry.find(", ", pos);
    if (n != std::string::npos)
    {
        entries.push_back(entry.substr(pos, n - pos));
        pos = n + 2;
    }
    entries.push_back(entry.substr(pos, n));
    return entries;
}

void App::clearColors() {
    for (size_t i = 0; i < 6; ++i)
    {
        for (auto conj : conjs) {
            conj->es[i]->setBackgroundColorId(visage::TextEditor::TextEditorBackground);
        }
    }
    redraw();
}

void App::clearPronouns() {
    for (size_t i = 0; i < 6; ++i) {
        for (auto conj : conjs) {
            conj->pronouns[i]->setColor(visage::Color(0xff000000));
        }
    }
}

void App::red(Label *l) { l->setColor(visage::Color(0xffbb3232)); l->redraw(); }
void App::red(visage::TextEditor *e) { e->setBackgroundColorId(WRONG); e->redraw(); }

void App::grn(Label *l) { l->setColor(visage::Color(0xff32bb32)); l->redraw(); }
void App::grn(visage::TextEditor *e) { e->setBackgroundColorId(RIGHT); e->redraw(); }

void App::blk(Label *l) { l->setColor(visage::Color(0xff000000)); l->redraw(); }
void App::blk(visage::TextEditor *e) { e->setBackgroundColorId(visage::TextEditor::TextEditorBackground); e->redraw();}

void App::color() {
    for (size_t i = 0; i < 6; ++i)
    {
        for (auto conj : conjs) {
            if (conj->isCorrect[i]) { grn(conj->es[i]); grn(conj->pronouns[i]); }
            else { if (!conj->userForms[i].empty()) {red(conj->es[i]); red(conj->pronouns[i]); } }
        }        
    }
    redraw();
}

void App::compare() {
    if (!quizIsMarked) { return; }

    if (userInputIsShown)
    {
        for (size_t i = 0; i < 6; ++i)
        {
            for (auto conj : conjs) {
                conj->es[i]->setText(conj->dbForms[i]);
            }
        }
        clearColors();
    }
    else
    {
        for (size_t i = 0; i < 6; ++i)
        {
            for (auto conj : conjs) {
                conj->es[i]->setText(conj->userForms[i]);
            }
        }
        color();
    }
    userInputIsShown = !userInputIsShown;
    redraw();
}

std::string App::replaceAccentedCharacters(std::string& input) {

    std::string result;
    
    for (size_t i = 0; i < input.size(); ++i) {
        if ((int)input[i] >= 0) { 
            result.append(1, input[i]); 
        }
        else { 
            if ((int)input[i] == -61) { 
                if (((int)input[i+1] >= -96) &&  ((int)input[i+1] <= -90)) {
                    result.append("a");
                }
                if (((int)input[i+1] == -89)) {
                    result.append("c");
                }
                if (((int)input[i+1] >= -88) &&  ((int)input[i+1] <= -85)) {
                    result.append("e");
                }
                if (((int)input[i+1] >= -84) &&  ((int)input[i+1] <= -81)) {
                    result.append("i");
                }
                if (((int)input[i+1] >= -78) &&  ((int)input[i+1] <= -72)) {
                    result.append("o");
                }
                if (((int)input[i+1] >= -71) &&  ((int)input[i+1] <= -68)) {
                    result.append("u");
                }
            }
        }
    }
    return result;
}

std::string App::replaceUnaccentedCharacters(std::string &input) { 
    std::string result;
    for (char ch : input) {
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'u') { result.push_back('_'); }
        else { result.push_back(ch); }
    }
    return result;
}

} // namespace gwr::frvb