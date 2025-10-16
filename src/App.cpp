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
    // markBtn.onMouseDown() = [&](const visage::MouseEvent &e) { newQuiz(); };

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
    left.layout().setFlexGap(5.f);
    left.layout().setPadding(5.f);

    left.addChild(conjPres, true);
    left.addChild(conjImpf, true);
    left.addChild(conjPc, true);

    conjPres.setFlexLayout(true);
    conjPres.layout().setDimensions(100_vw, 30_vh);
    conjPres.name_ = "Present";

    conjImpf.setFlexLayout(true);
    conjImpf.layout().setDimensions(100_vw, 30_vh);
    conjImpf.name_ = "Imperfect";

    conjPc.setFlexLayout(true);
    conjPc.layout().setDimensions(100_vw, 30_vh);
    conjPc.name_ = "Compound Past";

    right.setFlexLayout(true);
    right.layout().setDimensions(49_vw, 100_vh);
    right.layout().setFlexGap(5.f);
    right.layout().setPadding(5.f);

    right.addChild(conjFut, true);
    right.addChild(conjCond, true);
    right.addChild(conjPs, true);

    conjFut.setFlexLayout(true);
    conjFut.layout().setDimensions(100_vw, 30_vh);
    conjFut.name_ = "Future";

    conjCond.setFlexLayout(true);
    conjCond.layout().setDimensions(100_vw, 30_vh);
    conjCond.name_ = "Conditional";

    conjPs.setFlexLayout(true);
    conjPs.layout().setDimensions(100_vw, 30_vh);
    conjPs.name_ = "Simple Past";



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
        // subjunctivePres TEXT
        // );
        

    auto st = dbm.getStmt("select infinitive, present, imperfect, passeCompose, future, conditional, passeSimple from frenchVerbs order by random() limit 1;");
    std::string verb, pres, impf, pc, fut, cond, ps;
    while (st.executeStep())
    {
        verb = st.getColumn("infinitive").getString();
        pres = st.getColumn("present").getString();
        impf = st.getColumn("imperfect").getString();
        pc = st.getColumn("passeCompose").getString();
        fut = st.getColumn("future").getString();
        cond = st.getColumn("conditional").getString();
        ps = st.getColumn("passeSimple").getString();
    }
    headword.setText(verb);
    auto entries = splitForms(pres);
    conjPres.e1.setText(entries[0]);
    conjPres.e2.setText(entries[1]);
    conjPres.e3.setText(entries[2]);
    conjPres.e4.setText(entries[3]);
    conjPres.e5.setText(entries[4]);
    conjPres.e6.setText(entries[5]);
    entries = splitForms(impf);
    conjImpf.e1.setText(entries[0]);
    conjImpf.e2.setText(entries[1]);
    conjImpf.e3.setText(entries[2]);
    conjImpf.e4.setText(entries[3]);
    conjImpf.e5.setText(entries[4]);
    conjImpf.e6.setText(entries[5]);
    entries = splitForms(pc);
    conjPc.e1.setText(entries[0]);
    conjPc.e2.setText(entries[1]);
    conjPc.e3.setText(entries[2]);
    conjPc.e4.setText(entries[3]);
    conjPc.e5.setText(entries[4]);
    conjPc.e6.setText(entries[5]);
    entries = splitForms(fut);
    conjFut.e1.setText(entries[0]);
    conjFut.e2.setText(entries[1]);
    conjFut.e3.setText(entries[2]);
    conjFut.e4.setText(entries[3]);
    conjFut.e5.setText(entries[4]);
    conjFut.e6.setText(entries[5]);
    entries = splitForms(cond);
    conjCond.e1.setText(entries[0]);
    conjCond.e2.setText(entries[1]);
    conjCond.e3.setText(entries[2]);
    conjCond.e4.setText(entries[3]);
    conjCond.e5.setText(entries[4]);
    conjCond.e6.setText(entries[5]);
    entries = splitForms(ps);
    conjPs.e1.setText(entries[0]);
    conjPs.e2.setText(entries[1]);
    conjPs.e3.setText(entries[2]);
    conjPs.e4.setText(entries[3]);
    conjPs.e5.setText(entries[4]);
    conjPs.e6.setText(entries[5]);
    
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