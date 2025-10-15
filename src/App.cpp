#include "App.h"

namespace gwr::frvb {

    App::App() : dbm(":memory:") {
        addChild(&newBtn);
        newBtn.setBounds(10, 10, 200, 70);
        newBtn.setVisible(true);
        newBtn.setFont(font.withSize(25.f));
        newBtn.setFlexLayout(true);
        newBtn.layout().setPadding(5.f);
        newBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
            redraw(); // later, create new quiz
        };

        addChild(&markBtn);
        markBtn.setBounds(220, 10, 200, 70);
        markBtn.setVisible(true);
        markBtn.setFont(font.withSize(25.f));
        markBtn.setFlexLayout(true);
        markBtn.layout().setPadding(5.f);
        markBtn.onMouseDown() = [&](const visage::MouseEvent &e) {
            redraw();
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