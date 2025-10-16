#include "App.h"

using namespace visage::dimension;

namespace gwr::frvb {

    App::App() : dbm(":memory:") {
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
        newBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
            newQuiz();
        };

        markBtn.setFont(font.withSize(25.f));
        markBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
            newQuiz();
        };

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

    void App::newQuiz() {

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
        while (st.executeStep()) {
            verb = st.getColumn("infinitive").getString();
            pres = st.getColumn("present").getString();
        }
        headword.setText(verb);
        conjPres.e1.setText(pres);
    }

    void App::draw(visage::Canvas &canvas) {
        canvas.setColor(0xffffffff);
        canvas.fill(0, 0, 1200, 900);

        // canvas.setColor(0xff000000);

        // for (int i = 0; i < 10; ++i)
        // {
        //     canvas.rectangle(0, i * 100, 1200, 1);
        //     canvas.rectangle(i * 100, 0, 1, 900);
        // }

        // canvas.text(visage::String(verb), font.withSize(25.f), visage::Font::Justification::kLeft, 217, 5, 194, 35);
        // canvas.rectangleBorder(205, 5, 190, 35, 2.0f);
    }
}