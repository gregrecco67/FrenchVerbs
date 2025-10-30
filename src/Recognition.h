#pragma once

#include <visage/app.h>
#include "embedded/example_fonts.h"
#include "Label.h"
#include <visage_widgets/text_editor.h>
#include <visage_utils/dimension.h>
#include <visage_graphics/theme.h>

namespace gwr::frvb
{

class Recognition : public visage::Frame
{
  public:
    std::string name_{""};
    visage::Font font{20, resources::fonts::Lato_Regular_ttf};
    Recognition();
    void draw(visage::Canvas &canvas);
    void clearAll();
    std::string userForm, dbForm; // forms (db) and answers (db)
    bool isCorrect{true};
    Label form;                     // pronouns
    visage::TextEditor head, parse; // editors
};

} // namespace gwr::frvb