#include "App.h"

namespace gwr::frvb {

    App::App() : dbm(":memory:") {
        addChild(&newBtn);
        newBtn.setBounds(10, 10, 200, 70);
        newBtn.setVisible(true);
        newBtn.setFont(font);
        newBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
            redraw(); // later, create new quiz
        };

        addChild(&newFrm);
        newFrm.setBounds(220, 10, 200, 70);
        newFrm.setVisible(true);
        newFrm.onMouseDown() = [&](const visage::MouseEvent &e) {
            redraw();
        };
        newFrm.onDraw() = [&](visage::Canvas &canvas) {
            std::string msg;
            msg = "New";
            canvas.setColor(0xff000000);
            canvas.text(msg, font, visage::Font::Justification::kLeft, 0, 0, 200, 70);
        };
    }

    void App::draw(visage::Canvas &canvas) {
        canvas.setColor(0xffffffff);
        canvas.fill(0, 0, 1200, 900);
        auto st = dbm.getStmt("select infinitive from frenchVerbs order by random() limit 1;");
        std::string infinitive;
        while (st.executeStep()) {
            infinitive = st.getColumn("infinitive").getString();
        }
        canvas.setColor(0xff000000);
        canvas.text(visage::String(infinitive), font, visage::Font::Justification::kLeft, 50, 0, 500,
                    700);
        canvas.rectangleBorder(50, 250, 800, 200, 2.0f);
    }
}