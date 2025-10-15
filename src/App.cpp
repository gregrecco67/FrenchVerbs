#include "App.h"

namespace gwr::frvb {

    App::App() : dbm(":memory:") {
        
        addChild(&newBtn, true);
        newBtn.setFlexLayout(true);
        newBtn.setBounds({10, 10, 180, 70});
        newBtn.setFont(font.withSize(25.f));
        newBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
            redraw(); // later, create new quiz
        };

        addChild(&markBtn, true);
        markBtn.setBounds({210, 10, 180, 70});
        markBtn.setFont(font.withSize(25.f));
        markBtn.setFlexLayout(true);
        markBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
            redraw();
        };

        addChild(&pres1s, true);
        addChild(&pres2s, true);
        addChild(&pres3s, true);
        addChild(&pres1p, true);
        addChild(&pres2p, true);
        addChild(&pres3p, true);
        auto fn = font.withSize(25.f);
        pres1s.setBounds(210, 120, 380, 70);
        pres1s.setFlexLayout(true);
        pres1s.setFont(fn);
        pres2s.setBounds(210, 220, 380, 70);
        pres2s.setFlexLayout(true);
        pres2s.setFont(fn);
        pres3s.setBounds(210, 320, 380, 70);
        pres3s.setFlexLayout(true);
        pres3s.setFont(fn);
        pres1p.setBounds(610, 120, 380, 70);
        pres1p.setFlexLayout(true);
        pres1p.setFont(fn);
        pres2p.setBounds(610, 220, 380, 70);
        pres2p.setFlexLayout(true);
        pres2p.setFont(fn);
        pres3p.setBounds(610, 320, 380, 70);
        pres3p.setFlexLayout(true);
        pres3p.setFont(fn);
    }

    void App::draw(visage::Canvas &canvas) {
        canvas.setColor(0xffffffff);
        canvas.fill(0, 0, 1200, 900);
        auto st = dbm.getStmt("select infinitive from frenchVerbs order by random() limit 1;");
        std::string verb;
        while (st.executeStep()) {
            verb = st.getColumn("infinitive").getString();
        }
        canvas.setColor(0xff000000);

        for (int i = 0; i < 10; ++i)
        {
            canvas.rectangle(0, i * 100, 1200, 1);
            canvas.rectangle(i * 100, 0, 1, 900);
        }

        canvas.text(visage::String(verb), font.withSize(25.f), visage::Font::Justification::kLeft, 217, 5, 194, 35);
        canvas.rectangleBorder(205, 5, 190, 35, 2.0f);
    }
}