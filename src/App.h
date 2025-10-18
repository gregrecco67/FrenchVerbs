#pragma once

#include <visage_app/application_window.h>
#include <visage_file_embed/embedded_file.h>
#include "embedded/example_fonts.h"
#include "DbManager.h"
#include <visage_widgets/button.h>
#include <visage_widgets/text_editor.h>
#include <visage_utils/dimension.h>
#include "Label.h"
#include "Conj.h"
#include <iostream>

namespace gwr::frvb
{

class App : public visage::ApplicationWindow
{
  public:
    App();
    void newQuiz();
    void markQuiz();
    void compare();
    void readContents();
    void color();
    void clearColors();
    void red(Label *l);
    void grn(Label *l);
    void blk(Label *l);
    bool userInputIsShown{true}; // true when fields show USER input, false when they show DB answers
    bool quizIsMarked{false};
    bool matches(std::string &userAnswer, std::string &dbAnswer);
    DbManager dbm;
    visage::Font font{80, resources::fonts::Lato_Regular_ttf};
    void draw(visage::Canvas &canvas) override;
    std::vector<std::string> splitForms(std::string entry);
    visage::UiButton newBtn{"New"}, markBtn{"Mark"}, cmpBtn{"Compare"};
    Label header, body, headword;
    Conjugation conjPres, conjImpf, conjPc, conjFut, conjCond, conjPs, conjSubjPr, conjSubjImpf;
    visage::Frame left, right;
};

} // namespace gwr::frvb