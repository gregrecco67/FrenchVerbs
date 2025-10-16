#pragma once

#include <visage/app.h>
#include "embedded/example_fonts.h"
#include "Label.h"
#include <visage_widgets/text_editor.h>
#include <visage_utils/dimension.h>

class Conjugation : public visage::Frame {
public:
    std::string name_{""};
    std::array<std::string, 6> forms;
    visage::Font font{20, resources::fonts::Lato_Regular_ttf};
    Conjugation();
    void draw(visage::Canvas &canvas);
    Label pn1, pn2, pn3, pn4, pn5, pn6;
    visage::TextEditor e1, e2, e3, e4, e5, e6;
    visage::Frame singPns, plPns, singForms, plForms;
    visage::Frame header, body;
};