#include "App.h"

using namespace visage::dimension;

namespace gwr::frvb
{

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

    newBtn.layout().setDimensions(15_vw, 100_vh);
    markBtn.layout().setDimensions(15_vw, 100_vh);
    headword.layout().setDimensions(35_vw, 100_vh);

    newBtn.setFont(font.withSize(25.f));
    newBtn.onMouseDown() = [&](const visage::MouseEvent &e) { newQuiz(); };

    markBtn.setFont(font.withSize(25.f));
    markBtn.onMouseDown() = [&](const visage::MouseEvent &e) { markQuiz(); };

    headword.setFont(font.withSize(25.f));
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
    left.addChild(conjPc, true);
    left.addChild(conjPs, true);

    conjPres.setFlexLayout(true);
    conjPres.layout().setDimensions(100_vw, 24_vh);
    conjPres.name_ = "Present";

    conjImpf.setFlexLayout(true);
    conjImpf.layout().setDimensions(100_vw, 24_vh);
    conjImpf.name_ = "Imperfect";

    conjPc.setFlexLayout(true);
    conjPc.layout().setDimensions(100_vw, 24_vh);
    conjPc.name_ = "Compound Past";

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





}

void App::newQuiz()
{
    // CREATE TABLE frenchVerbs(
    // verbID INTEGER PRIMARY KEY AUTOINCREMENT,
    // infinitive TEXT,
    // pastParticiple TEXT,
    // presParticiple TEXT,
    // auxiliary TEXT,
    // present TEXT,
    // imperfect TEXT,
    // passeCompose TEXT,
    // passeSimple TEXT,
    // future TEXT,
    // conditional TEXT,
    // subjunctivePres TEXT,
    // subjunctiveImpf TEXT
    // );             

    auto st = dbm.getStmt("select infinitive, present, imperfect, passeCompose, future, conditional, passeSimple, subjunctivePres, subjunctiveImpf from frenchVerbs order by random() limit 1;");
    std::string verb, pres, impf, pc, fut, cond, ps, subjPres, subjImpf;
    while (st.executeStep())
    {
        verb = st.getColumn("infinitive").getString();
        pres = st.getColumn("present").getString();
        impf = st.getColumn("imperfect").getString();
        pc = st.getColumn("passeCompose").getString();
        fut = st.getColumn("future").getString();
        cond = st.getColumn("conditional").getString();
        ps = st.getColumn("passeSimple").getString();
        subjPres = st.getColumn("subjunctivePres").getString();
        subjImpf = st.getColumn("subjunctiveImpf").getString();
    }
    headword.setText(verb);

    auto presForms = splitForms(pres);
    auto impfForms = splitForms(impf);
    auto pcForms = splitForms(pc);
    auto futForms = splitForms(fut);
    auto condForms = splitForms(cond);
    auto psForms = splitForms(ps);
    auto subjPresForms = splitForms(subjPres);
    auto subjImpfForms = splitForms(subjImpf);

    for (size_t i = 0; i < 6; ++i) {
        conjPres.es[i]->clear();
        conjImpf.es[i]->clear();
        conjPc.es[i]->clear();
        conjFut.es[i]->clear();
        conjCond.es[i]->clear();
        conjPs.es[i]->clear();
        conjSubjPr.es[i]->clear();
        conjSubjImpf.es[i]->clear();

        conjPres.forms[i] = presForms[i];
        conjImpf.forms[i] = impfForms[i];
        conjPc.forms[i] = pcForms[i];
        conjFut.forms[i] = futForms[i];
        conjCond.forms[i] = condForms[i];
        conjPs.forms[i] = psForms[i];
        conjSubjPr.forms[i] = subjPresForms[i];
        conjSubjImpf.forms[i] = subjImpfForms[i];
    }
}

void App::markQuiz() {
    for (size_t i = 0; i < 6; ++i) {
        conjPres.ans[i] = conjPres.es[i]->text().toUtf8();
        conjPres.es[i]->setText(conjPres.forms[i]);
        if (matches(conjPres.ans[i], conjPres.forms[i])) {
            // green
        }
        else {
            // red 
        }

        conjImpf.ans[i] = conjImpf.es[i]->text().toUtf8();
        conjImpf.es[i]->setText(conjImpf.forms[i]);

        conjPc.ans[i] = conjPc.es[i]->text().toUtf8();
        conjPc.es[i]->setText(conjPc.forms[i]);

        conjFut.ans[i] = conjFut.es[i]->text().toUtf8();
        conjFut.es[i]->setText(conjFut.forms[i]);
        
        conjCond.ans[i] = conjCond.es[i]->text().toUtf8();
        conjCond.es[i]->setText(conjCond.forms[i]);

        conjPs.ans[i] = conjPs.es[i]->text().toUtf8();
        conjPs.es[i]->setText(conjPs.forms[i]);

        conjSubjPr.ans[i] = conjSubjPr.es[i]->text().toUtf8();
        conjSubjPr.es[i]->setText(conjSubjPr.forms[i]);

        conjSubjImpf.ans[i] = conjSubjImpf.es[i]->text().toUtf8();
        conjSubjImpf.es[i]->setText(conjSubjImpf.forms[i]);
    }
}

bool App::matches(std::string &userAnswer, std::string &dbAnswer) { 
    return false; 
}

void App::draw(visage::Canvas &canvas)
{
    canvas.setColor(0xffffffff);
    canvas.fill(0, 0, 1200, 900);
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
        pos = n+2;
    }
    n = entry.find(", ", pos);
    if (n != std::string::npos)
    {
        entries.push_back(entry.substr(pos, n - pos));
        pos = n+2;
    }
    n = entry.find(", ", pos);
    if (n != std::string::npos)
    {
        entries.push_back(entry.substr(pos, n - pos));
        pos = n+2;
    }
    n = entry.find(", ", pos);
    if (n != std::string::npos)
    {
        entries.push_back(entry.substr(pos, n - pos));
        pos = n+2;
    }
    n = entry.find(", ", pos);
    if (n != std::string::npos)
    {
        entries.push_back(entry.substr(pos, n - pos));
        pos = n+2;
    }
    entries.push_back(entry.substr(pos, n));
    return entries;
}

} // namespace gwr::frvb