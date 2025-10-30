#include "App2.h"

using namespace visage::dimension;

namespace gwr::frvb
{

VISAGE_THEME_COLOR(WRONG, 0xff991212);
VISAGE_THEME_COLOR(RIGHT, 0xff129912);

App2::App2() : dbm(":memory:")
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
    header.addChild(cmpBtn, true);

    newBtn.layout().setDimensions(15_vw, 100_vh);
    markBtn.layout().setDimensions(15_vw, 100_vh);
    cmpBtn.layout().setDimensions(15_vw, 100_vh);

    newBtn.setFont(font.withSize(25.f));
    newBtn.onMouseDown() = [&](const visage::MouseEvent &e) { newQuiz(); };

    markBtn.setFont(font.withSize(25.f));
    markBtn.onMouseDown() = [&](const visage::MouseEvent &e) { markQuiz(); };

    cmpBtn.setFont(font.withSize(25.f));
    cmpBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
        if (cmpBtn.isActive())
        {
            compare();
        }
    };
    cmpBtn.setActive(false);
    // ============================

    body.setFlexLayout(true);
    body.layout().setDimensions(100_vw, 90_vh);
    body.layout().setFlexRows(true);
    body.layout().setFlexGap(4_vh);
    body.outline = false;
    body.addChild(r1, true);
    body.addChild(r2, true);
    body.addChild(r3, true);
    body.addChild(r4, true);
    body.addChild(r5, true);
    body.addChild(r6, true);
    body.addChild(r7, true);
    body.addChild(r8, true);

    recogs = {&r1, &r2, &r3, &r4, &r5, &r6, &r7, &r8};

    for (auto &recog : recogs)
    {
        recog->layout().setDimensions(100_vw, 6_vh);
    }
}

SQLite::Statement App2::getRightStatment(std::string &inverb)
{
    if (!inverb.empty())
    {
        auto likeV = replaceUnaccentedCharacters(inverb);
        auto st = dbm.getStmt("select infinitive from frenchVerbs where infinitive like ?;");
        st.bind(1, likeV);
        std::vector<std::string> infs;
        while (st.executeStep())
        {
            infs.push_back(st.getColumn("infinitive").getString());
        }

        std::string finalForm;
        for (auto inf : infs)
        {
            if (matches(inf, inverb))
            {
                finalForm = inf;
            }
        }
        if (!finalForm.empty())
        {
            st = dbm.getStmt(
                "select infinitive, present, imperfect, presParticiple, pastParticiple, auxiliary, "
                "imperative, future, conditional, passeSimple, "
                "subjunctivePres, subjunctiveImpf from frenchVerbs where infinitive = ?;");
            st.bind(1, finalForm);
            return st;
        }
    }
    auto st =
        dbm.getStmt("select infinitive, present, imperfect, presParticiple, pastParticiple, "
                    "auxiliary, imperative, future, conditional, passeSimple, "
                    "subjunctivePres, subjunctiveImpf from frenchVerbs order by random() limit 1;");
    return st;
}

void App2::newQuiz()
{
    clearColors();

    std::string str;
    auto st = getRightStatment(str);

    std::string verb, pres, impf, imperat, pastPart, presPart, aux, fut, cond, ps, subjPres,
        subjImpf;
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

    for (auto recog : recogs)
    {
        recog->clearAll();
    }

    userInputIsShown = true;
    quizIsMarked = false;
    cmpBtn.setActive(false);
    redraw();
}

void App2::markQuiz()
{
    if (!userInputIsShown)
        return;
    readContents();
    clearColors();

    // compare userForms with dbForms
    for (auto recog : recogs)
    {
        recog->isCorrect = matches(recog->userForm, recog->dbForm);
    }

    // color fields by correctness
    userInputIsShown = true;
    quizIsMarked = true;
    cmpBtn.setActive(true);
    color();
    redraw();
}

void App2::readContents()
{
    for (auto &recog : recogs)
    {
        auto aa = recog->head.text().toUtf8();
        recog->userForm = aa;
    }
}

bool App2::matches(std::string &userAnswer, std::string &dbAnswer)
{
    return (replaceAccentedCharacters(userAnswer).compare(replaceAccentedCharacters(dbAnswer)) ==
            0);
}

void App2::draw(visage::Canvas &canvas)
{
    canvas.setColor(0xffbbbbbb);
    canvas.fill(0, 0, width(), height());
}

std::vector<std::string> App2::splitForms(std::string entry)
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

void App2::clearColors()
{
    for (size_t i = 0; i < 6; ++i)
    {
        for (auto recog : recogs)
        {
            recog->parse.setBackgroundColorId(visage::TextEditor::TextEditorBackground);
        }
    }
    redraw();
}

void App2::red(Label *l)
{
    l->setColor(visage::Color(0xffbb3232));
    l->redraw();
}
void App2::red(visage::TextEditor *e)
{
    e->setBackgroundColorId(WRONG);
    e->redraw();
}

void App2::grn(Label *l)
{
    l->setColor(visage::Color(0xff32bb32));
    l->redraw();
}
void App2::grn(visage::TextEditor *e)
{
    e->setBackgroundColorId(RIGHT);
    e->redraw();
}

void App2::blk(Label *l)
{
    l->setColor(visage::Color(0xff000000));
    l->redraw();
}
void App2::blk(visage::TextEditor *e)
{
    e->setBackgroundColorId(visage::TextEditor::TextEditorBackground);
    e->redraw();
}

void App2::color() { redraw(); }

void App2::compare()
{
    if (!quizIsMarked)
    {
        return;
    }

    if (userInputIsShown)
    {
        for (auto &recog : recogs)
        {
            recog->head.setText(recog->dbForm);
        }
        clearColors();
    }
    else
    {
        for (auto &recog : recogs)
        {
            recog->head.setText(recog->userForm);
        }
        color();
    }
    userInputIsShown = !userInputIsShown;
    redraw();
}

std::string App2::replaceAccentedCharacters(std::string &input)
{

    std::string result;

    for (size_t i = 0; i < input.size(); ++i)
    {
        if ((int)input[i] >= 0)
        {
            result.append(1, input[i]);
        }
        else
        {
            if ((int)input[i] == -61)
            {
                if (((int)input[i + 1] >= -96) && ((int)input[i + 1] <= -90))
                {
                    result.append("a");
                }
                if (((int)input[i + 1] == -89))
                {
                    result.append("c");
                }
                if (((int)input[i + 1] >= -88) && ((int)input[i + 1] <= -85))
                {
                    result.append("e");
                }
                if (((int)input[i + 1] >= -84) && ((int)input[i + 1] <= -81))
                {
                    result.append("i");
                }
                if (((int)input[i + 1] >= -78) && ((int)input[i + 1] <= -72))
                {
                    result.append("o");
                }
                if (((int)input[i + 1] >= -71) && ((int)input[i + 1] <= -68))
                {
                    result.append("u");
                }
            }
        }
    }
    return result;
}

std::string App2::replaceUnaccentedCharacters(std::string &input)
{
    std::string result;
    for (char ch : input)
    {
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'u')
        {
            result.push_back('_');
        }
        else
        {
            result.push_back(ch);
        }
    }
    return result;
}

} // namespace gwr::frvb