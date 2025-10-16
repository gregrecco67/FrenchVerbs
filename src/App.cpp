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
    header.addChild(newBtn, true);
    header.addChild(markBtn, true);
    header.addChild(headword, true);
    newBtn.layout().setDimensions(15_vw, 100_vh);
    markBtn.layout().setDimensions(15_vw, 100_vh);
    headword.layout().setDimensions(35_vw, 100_vh);

    newBtn.setFont(font.withSize(25.f));
    newBtn.onMouseDown() = [&](const visage::MouseEvent &e) { newQuiz(); };

    markBtn.setFont(font.withSize(25.f));
    markBtn.onMouseDown() = [&](const visage::MouseEvent &e) { newQuiz(); };

    headword.setFont(font.withSize(25.f));
    headword.setText("hello");

    // ============================

    body.setFlexLayout(true);
    body.layout().setDimensions(100_vw, 90_vh);
    body.layout().setFlexRows(true);
    body.layout().setFlexGap(5.f);
    body.layout().setPadding(5.f);

    body.addChild(conjPres, true);
    conjPres.setFlexLayout(true);
    conjPres.layout().setDimensions(50_vw, 30_vh);
    conjPres.name_ = "Present";
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

    auto st = dbm.getStmt("select infinitive, present from frenchVerbs order by random() limit 1;");
    std::string verb, pres;
    while (st.executeStep())
    {
        verb = st.getColumn("infinitive").getString();
        pres = st.getColumn("present").getString();
    }
    headword.setText(verb);
    auto entries = splitForms(pres);
    conjPres.e1.setText(entries[0]);
    conjPres.e2.setText(entries[1]);
    conjPres.e3.setText(entries[2]);
    conjPres.e4.setText(entries[3]);
    conjPres.e5.setText(entries[4]);
    conjPres.e6.setText(entries[5]);
    
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