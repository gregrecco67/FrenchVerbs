#include "App.h"

using namespace visage::dimension;

namespace gwr::frvb {

    App::App() : dbm(":memory:") {
        setFlexLayout(true);
        layout().setFlexRows(true);
        // layout().setFlexGap(5.f);
        addChild(header, true);
        addChild(body, true);
        header.setFlexLayout(true);
        header.layout().setDimensions(100_vw, 10_vh);
        header.layout().setFlexRows(false);
        header.layout().setFlexGap(1_vw);
        header.layout().setPadding(10_vh);
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
        body.addChild(present, true);

        present.setFlexLayout(true);
        present.layout().setFlexRows(false);
        present.layout().setDimensions(50_vw, 50_vh);
        present.addChild(pronPresSing, true);
        present.addChild(presSing, true);
        present.addChild(pronPresPl, true);
        present.addChild(presPl, true);
        pronPresSing.setFlexLayout(true);
        pronPresSing.layout().setDimensions(10_vw, 100_vh);
        pronPresPl.layout().setDimensions(10_vw, 100_vh);
        presSing.setFlexLayout(true);
        presSing.layout().setDimensions(40_vw, 100_vh);
        presSing.layout().setFlexRows(true);
        presSing.layout().setFlexGap(5.f);
        presSing.layout().setFlexItemAlignment(visage::Layout::ItemAlignment::Center);
        presPl.setFlexLayout(true);
        presPl.layout().setDimensions(40_vw, 100_vh);
        presPl.layout().setFlexRows(true);
        presPl.layout().setFlexGap(5.f);
        presPl.layout().setFlexItemAlignment(visage::Layout::ItemAlignment::Center);
        presSing.addChild(pres1s, true);
        presSing.addChild(pres2s, true);
        presSing.addChild(pres3s, true);
        presPl.addChild(pres1p, true);
        presPl.addChild(pres2p, true);
        presPl.addChild(pres3p, true);

        for (auto& fr : {&pres1s, &pres2s, &pres3s, &pres1p, &pres2p, &pres3p}) {
            fr->setFlexLayout(true);
            fr->setFont(font.withSize(25.f));
            fr->setDefaultText("...");
            fr->setJustification(visage::Font::Justification::kCenter);
            fr->layout().setDimensions(95_vw, 32_vh);
            fr->setTextFieldEntry();
        }


// 
        // addChild(&pres1s, true);
        // addChild(&pres2s, true);
        // addChild(&pres3s, true);
        // addChild(&pres1p, true);
        // addChild(&pres2p, true);
        // addChild(&pres3p, true);
        // auto fn = font.withSize(25.f);
        // pres1s.setBounds(210, 120, 380, 70);
        // pres1s.setFlexLayout(true);
        // pres1s.setFont(fn);
        // pres2s.setBounds(210, 220, 380, 70);
        // pres2s.setFlexLayout(true);
        // pres2s.setFont(fn);
        // pres3s.setBounds(210, 320, 380, 70);
        // pres3s.setFlexLayout(true);
        // pres3s.setFont(fn);
        // pres1p.setBounds(610, 120, 380, 70);
        // pres1p.setFlexLayout(true);
        // pres1p.setFont(fn);
        // pres2p.setBounds(610, 220, 380, 70);
        // pres2p.setFlexLayout(true);
        // pres2p.setFont(fn);
        // pres3p.setBounds(610, 320, 380, 70);
        // pres3p.setFlexLayout(true);
        // pres3p.setFont(fn);
    }

    void App::newQuiz() {
        auto st = dbm.getStmt("select infinitive from frenchVerbs order by random() limit 1;");
        std::string verb;
        while (st.executeStep()) {
            verb = st.getColumn("infinitive").getString();
        }
        headword.setText(verb);
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