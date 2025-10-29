#pragma once

#include <visage_app/application_window.h>
#include <visage_file_embed/embedded_file.h>
#include "embedded/example_fonts.h"
#include "DbManager.h"
#include <visage_widgets/button.h>
#include <visage_widgets/text_editor.h>
#include <visage_utils/dimension.h>
#include "Label.h"
#include "Recognition.h"
#include <iostream>
#include <string>

namespace gwr::frvb
{

class App2 : public visage::ApplicationWindow
{
  public:
    App2();
    void newQuiz();
    void markQuiz();
    void compare(); // swap btwn user input and db
    void readContents();
    void color();
    void clearColors();
    void red(Label *l);
    void red(visage::TextEditor *e);
    void grn(Label *l);
    void grn(visage::TextEditor *e);
    void blk(Label *l);
    void blk(visage::TextEditor *e);
    bool userInputIsShown{true}; // true when fields show USER input, false when they show DB answers
    bool quizIsMarked{false};
    bool matches(std::string &userAnswer, std::string &dbAnswer);
    SQLite::Statement getRightStatment(std::string &inverb);
    std::string replaceAccentedCharacters(std::string &input);
    std::string replaceUnaccentedCharacters(std::string &input);
    DbManager dbm;
    visage::Font font{20, resources::fonts::Lato_Regular_ttf};
    void draw(visage::Canvas &canvas) override;
    std::vector<std::string> splitForms(std::string entry);
    visage::UiButton newBtn{"New"}, markBtn{"Mark"}, cmpBtn{"Compare"};
    Label header, body;
    Recognition r1, r2, r3, r4, r5, r6, r7, r8;
    std::array<Recognition *, 8> recogs;
};

} // namespace gwr::frvb