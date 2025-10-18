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
    header.addChild(swapBtn, true);

    newBtn.layout().setDimensions(15_vw, 100_vh);
    markBtn.layout().setDimensions(15_vw, 100_vh);
    headword.layout().setDimensions(35_vw, 100_vh);
    swapBtn.layout().setDimensions(15_vw, 100_vh);

    newBtn.setFont(font.withSize(25.f));
    newBtn.onMouseDown() = [&](const visage::MouseEvent &e) { newQuiz(); };

    markBtn.setFont(font.withSize(25.f));
    markBtn.onMouseDown() = [&](const visage::MouseEvent &e) { markQuiz(); };

    swapBtn.setFont(font.withSize(25.f));
    swapBtn.onMouseDown() = [&](const visage::MouseEvent &e) { swap(); };
    swapBtn.setActive(false);

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
    auto st = dbm.getStmt(
        "select infinitive, present, imperfect, passeCompose, future, conditional, passeSimple, "
        "subjunctivePres, subjunctiveImpf from frenchVerbs order by random() limit 1;");
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

    for (size_t i = 0; i < 6; ++i)
    {
        conjPres.es[i]->clear();
        conjImpf.es[i]->clear();
        conjPc.es[i]->clear();
        conjFut.es[i]->clear();
        conjCond.es[i]->clear();
        conjPs.es[i]->clear();
        conjSubjPr.es[i]->clear();
        conjSubjImpf.es[i]->clear();

        conjPres.dbForms[i] = presForms[i];
        conjImpf.dbForms[i] = impfForms[i];
        conjPc.dbForms[i] = pcForms[i];
        conjFut.dbForms[i] = futForms[i];
        conjCond.dbForms[i] = condForms[i];
        conjPs.dbForms[i] = psForms[i];
        conjSubjPr.dbForms[i] = subjPresForms[i];
        conjSubjImpf.dbForms[i] = subjImpfForms[i];
    }

    quizIsMarked = false;
    swapBtn.setActive(false);
}

void App::markQuiz()
{
    // read texteditor contents into userForms fields
    readContents();
    std::cout << "read contents" << std::endl;

    // compare userForms with dbForms
    for (size_t i = 0; i < 6; ++i)
    {
        conjPres.isCorrect[i] = matches(conjPres.userForms[i], conjPres.dbForms[i]);
        std::cout << "checked for match" << std::endl;

        if (conjPres.isCorrect[i])
        {
            conjPres.pronouns[i]->setColor(visage::Color(0xff0ff000));
        }
        else
        {
            conjPres.pronouns[i]->setColor(visage::Color(0xffff0000));
        }
        std::cout << "set color" << std::endl;

        conjImpf.isCorrect[i] = matches(conjImpf.userForms[i], conjImpf.dbForms[i]);
        if (conjImpf.isCorrect[i])
        {
            conjImpf.pronouns[i]->setColor(0xffff0000);
        }
        else
        {
            conjImpf.pronouns[i]->setColor(0xff00ff00);
        }
        conjPc.isCorrect[i] = matches(conjPc.userForms[i], conjPc.dbForms[i]);
        if (conjPc.isCorrect[i])
        {
            conjPc.pronouns[i]->setColor(0xffff0000);
        }
        else
        {
            conjPc.pronouns[i]->setColor(0xff00ff00);
        }
        conjFut.isCorrect[i] = matches(conjFut.userForms[i], conjFut.dbForms[i]);
        if (conjFut.isCorrect[i])
        {
            conjFut.pronouns[i]->setColor(0xffff0000);
        }
        else
        {
            conjPres.pronouns[i]->setColor(0xff00ff00);
        }
        conjCond.isCorrect[i] = matches(conjCond.userForms[i], conjCond.dbForms[i]);
        if (conjCond.isCorrect[i])
        {
            conjCond.pronouns[i]->setColor(0xffff0000);
        }
        else
        {
            conjPres.pronouns[i]->setColor(0xff00ff00);
        }
        conjPs.isCorrect[i] = matches(conjPs.userForms[i], conjPs.dbForms[i]);
        if (conjPs.isCorrect[i])
        {
            conjPs.pronouns[i]->setColor(0xffff0000);
        }
        else
        {
            conjPres.pronouns[i]->setColor(0xff00ff00);
        }
        conjSubjPr.isCorrect[i] = matches(conjSubjPr.userForms[i], conjSubjPr.dbForms[i]);
        if (conjSubjPr.isCorrect[i])
        {
            conjSubjPr.pronouns[i]->setColor(0xffff0000);
        }
        else
        {
            conjPres.pronouns[i]->setColor(0xff00ff00);
        }
        conjSubjImpf.isCorrect[i] = matches(conjSubjImpf.userForms[i], conjSubjImpf.dbForms[i]);
        if (conjSubjImpf.isCorrect[i])
        {
            conjSubjImpf.pronouns[i]->setColor(0xffff0000);
        }
        else
        {
            conjPres.pronouns[i]->setColor(0xff00ff00);
        }
    }

    std::cout << "compared forms, set colors" << std::endl;

    // set quizIsMarked to true
    quizIsMarked = true;

    // when a quiz is marked, then enable the "swap" button
    swapBtn.setActive(true);
    swapState = false;
}

void App::swap()
{
    if (swapState)
    {
        for (size_t i = 0; i < 6; ++i)
        {
            conjPres.es[i]->setText(conjPres.dbForms[i]);
            conjImpf.es[i]->setText(conjImpf.dbForms[i]);
            conjPc.es[i]->setText(conjPc.dbForms[i]);
            conjFut.es[i]->setText(conjFut.dbForms[i]);
            conjCond.es[i]->setText(conjCond.dbForms[i]);
            conjPs.es[i]->setText(conjPs.dbForms[i]);
            conjSubjPr.es[i]->setText(conjSubjPr.dbForms[i]);
            conjSubjImpf.es[i]->setText(conjSubjImpf.dbForms[i]);
        }
    }
    else
    {
        for (size_t i = 0; i < 6; ++i)
        {
            conjPres.es[i]->setText(conjPres.userForms[i]);
            conjImpf.es[i]->setText(conjImpf.userForms[i]);
            conjPc.es[i]->setText(conjPc.userForms[i]);
            conjFut.es[i]->setText(conjFut.userForms[i]);
            conjCond.es[i]->setText(conjCond.userForms[i]);
            conjPs.es[i]->setText(conjPs.userForms[i]);
            conjSubjPr.es[i]->setText(conjSubjPr.userForms[i]);
            conjSubjImpf.es[i]->setText(conjSubjImpf.userForms[i]);
        }
    }
    swapState = !swapState;
}

void App::readContents()
{
    for (size_t i = 0; i < 6; ++i)
    {
        conjPres.userForms[i] = conjPres.es[i]->text().toUtf8();
        conjImpf.userForms[i] = conjImpf.es[i]->text().toUtf8();
        conjPc.userForms[i] = conjPc.es[i]->text().toUtf8();
        conjFut.userForms[i] = conjFut.es[i]->text().toUtf8();
        conjCond.userForms[i] = conjCond.es[i]->text().toUtf8();
        conjPs.userForms[i] = conjPs.es[i]->text().toUtf8();
        conjSubjPr.userForms[i] = conjSubjPr.es[i]->text().toUtf8();
        conjSubjImpf.userForms[i] = conjSubjImpf.es[i]->text().toUtf8();
    }
}

bool App::matches(std::string &userAnswer, std::string &dbAnswer)
{
    return userAnswer.compare(dbAnswer) == 0;
}

void App::draw(visage::Canvas &canvas)
{
    canvas.setColor(0xffffffff);
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

} // namespace gwr::frvb