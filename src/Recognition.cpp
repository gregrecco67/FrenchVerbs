#include "Recognition.h"

using namespace visage::dimension;

namespace gwr::frvb
{

Recognition::Recognition()
{
    setFlexLayout(true);
    layout().setFlexRows(false);
    layout().setFlexGap(2_vw);
    layout().setPaddingLeft(1_vw);

    addChild(form, true);
    addChild(head, true);
    addChild(parse, true);

    form.layout().setDimensions(20_vw, 100_vh);

    head.setFont(font.withSize(20.f));
    head.setDefaultText("...");
    head.setJustification(visage::Font::Justification::kCenter);
    head.layout().setDimensions(20_vw, 100_vh);
    head.setTextFieldEntry();

    parse.setFont(font.withSize(20.f));
    parse.setDefaultText("...");
    parse.setJustification(visage::Font::Justification::kCenter);
    parse.layout().setDimensions(55_vw, 100_vh);
    parse.setTextFieldEntry();
}

void Recognition::draw(visage::Canvas &canvas)
{
    canvas.setColor(0xff000000);
    if (name_.empty())
    {
        return;
    }
    canvas.text(name_, font, visage::Font::Justification::kCenter, 0, 0, 100_vw, 15_vh);
}

void Recognition::clearAll()
{
    head.clear();
    parse.clear();
}

} // namespace gwr::frvb