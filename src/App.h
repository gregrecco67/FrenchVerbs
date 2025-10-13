#pragma once

#include <visage_app/application_window.h>
#include <visage_file_embed/embedded_file.h>
#include "embedded/example_fonts.h"
#include "DbManager.h"

namespace gwr::frvb 
{

class App : public visage::ApplicationWindow {
public:
    App();
    DbManager dbm;
    const visage::Font font{80, resources::fonts::Lato_Regular_ttf};
    void draw(visage::Canvas &canvas) override;
};

} // namespace gwr::frvb