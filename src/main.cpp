#include <visage/app.h>
#include <visage_app/application_window.h>
#include <visage_file_embed/embedded_file.h>
#include "embedded/example_fonts.h"

int main()
{
    const visage::Font font{800, resources::fonts::Lato_Regular_ttf};
    visage::ApplicationWindow app;

    app.onDraw() = [&app, font](visage::Canvas &canvas) {
        canvas.setColor(0xffffffff);
        canvas.fill(0, 0, 900, 700);
        canvas.setColor(0xffcccccc);
        for (int i = 0; i < 70; ++i)
        {
            canvas.rectangle(0, i * 10, 900, 1);
        }
        for (int i = 0; i < 90; ++i)
        {
            canvas.rectangle(i * 10, 0, 1, 700);
        }
        canvas.setColor(0xff000000);
        for (int i = 0; i < 10; ++i)
        {
            canvas.rectangle(0, i * 70, 900, 1);
            canvas.rectangle(i * 90, 0, 1, 700);
        }
        canvas.setColor(0xff000000);
        canvas.text(visage::String("abc"), font, visage::Font::Justification::kCenter, 50, 0, 350,
                    700);
        canvas.rectangleBorder(50, 250, 800, 200, 2.0f);
        canvas.rectangle(0, 349, 900, 3);
    };
    app.show(900, 700);
    app.runEventLoop();
    return 0;
}
