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

namespace gwr::frvb 
{

class App : public visage::ApplicationWindow {
public:
    App();
    void newQuiz();
    DbManager dbm;
    visage::Font font{80, resources::fonts::Lato_Regular_ttf};
    void draw(visage::Canvas &canvas) override;
    std::vector<std::string> splitForms(std::string entry);
    visage::UiButton newBtn{"New"}, markBtn{"Mark"};
    // visage::TextEditor pres1s, pres2s, pres3s, pres1p, pres2p, pres3p;
    Label header, body, headword;
    // Label headword, present, presSing, presPl, pronPresSing, pronPresPl;
    Conjugation conjPres;
    

};

} // namespace gwr::frvb