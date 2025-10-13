#include "App.h"

namespace gwr::frvb {

    App::App() : dbm(":memory:") {}

    void App::draw(visage::Canvas &canvas) {
        canvas.setColor(0xffffffff);
        canvas.fill(0, 0, 1200, 900);
        canvas.setColor(0xffcccccc);
        for (int i = 0; i < 90; ++i)
        {
            canvas.rectangle(0, i * 10, 1200, 1);
        }
        for (int i = 0; i < 120; ++i)
        {
            canvas.rectangle(i * 10, 0, 1, 900);
        }
        canvas.setColor(0xff000000);
        for (int i = 0; i < 10; ++i)
        {
            canvas.rectangle(0, i * 70, 1200, 1);
            canvas.rectangle(i * 90, 0, 1, 900);
        }
        canvas.setColor(0xff000000);
        auto st = dbm.getStmt("select infinitive from frenchVerbs where true limit 1;");
        std::string infinitive;
        while (st.executeStep()) {
            infinitive = st.getColumn("infinitive").getString();
        }
        canvas.text(visage::String(infinitive), font, visage::Font::Justification::kCenter, 50, 0, 500,
                    700);
        canvas.rectangleBorder(50, 250, 800, 200, 2.0f);
        canvas.rectangle(0, 349, 900, 3);
    }
}