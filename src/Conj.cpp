#include "Conj.h"

using namespace visage::dimension;

Conjugation::Conjugation()
{
    setFlexLayout(true);
    layout().setFlexRows(true);
    addChild(header, true);
    addChild(body, true);
    header.setFlexLayout(true);
    header.layout().setDimensions(100_vw, 18_vh);
    body.setFlexLayout(true);
    body.layout().setFlexRows(false);
    body.layout().setDimensions(100_vw, 75_vh);
    body.addChild(singPns, true);
    body.addChild(singForms, true);
    body.addChild(plPns, true);
    body.addChild(plForms, true);
    singPns.setFlexLayout(true);
    singPns.layout().setFlexGap(5.f);
    singPns.layout().setFlexRows(true);
    singPns.layout().setDimensions(10_vw, 100_vh);
    plPns.setFlexLayout(true);
    plPns.layout().setFlexRows(true);
    plPns.layout().setFlexGap(5.f);
    plPns.layout().setDimensions(10_vw, 100_vh);
    pn1.setText("je/j'");
    pn2.setText("tu");
    pn3.setText("elle");
    for (auto &pn : {&pn1, &pn2, &pn3})
    {
        singPns.addChild(pn, true);
        pn->layout().setDimensions(100_vw, 28_vh);
        pn->outline = false;
    }
    pn4.setText("nous");
    pn5.setText("vous");
    pn6.setText("ils");
    for (auto &pn : {&pn4, &pn5, &pn6})
    {
        plPns.addChild(pn, true);
        pn->layout().setDimensions(100_vw, 28_vh);
        pn->outline = false;
    }
    singForms.setFlexLayout(true);
    singForms.layout().setDimensions(40_vw, 100_vh);
    singForms.layout().setFlexRows(true);
    singForms.layout().setFlexGap(5.f);
    singForms.layout().setFlexItemAlignment(visage::Layout::ItemAlignment::Center);
    plForms.setFlexLayout(true);
    plForms.layout().setDimensions(40_vw, 100_vh);
    plForms.layout().setFlexRows(true);
    plForms.layout().setFlexGap(5.f);
    plForms.layout().setFlexItemAlignment(visage::Layout::ItemAlignment::Center);
    singForms.addChild(e1, true);
    singForms.addChild(e2, true);
    singForms.addChild(e3, true);
    plForms.addChild(e4, true);
    plForms.addChild(e5, true);
    plForms.addChild(e6, true);

    for (auto &fr : {&pn1, &pn2, &pn3, &pn4, &pn5, &pn6})
    {
        fr->setFont(font.withSize(20.f));
    }
    
    for (auto &fr : {&e1, &e2, &e3, &e4, &e5, &e6})
    {
        fr->setFlexLayout(true);
        fr->setFont(font.withSize(20.f));
        fr->setDefaultText("...");
        fr->setJustification(visage::Font::Justification::kCenter);
        fr->layout().setDimensions(95_vw, 28_vh);
        fr->setTextFieldEntry();
    }

    es[0] = &e1;
    es[1] = &e2;
    es[2] = &e3;
    es[3] = &e4;
    es[4] = &e5;
    es[5] = &e6;
    pronouns[0] = &pn1;
    pronouns[1] = &pn2;
    pronouns[2] = &pn3;
    pronouns[3] = &pn4;
    pronouns[4] = &pn5;
    pronouns[5] = &pn6;
}

void Conjugation::draw(visage::Canvas &canvas)
{
    canvas.setColor(0xff000000);
    if (name_.empty())
    {
        return;
    }
    canvas.text(name_, font, visage::Font::Justification::kCenter, 0, 0, 100_vw, 15_vh);
}

void Conjugation::clearAll()
{
    for (size_t i = 0; i < 6; ++i)
    {
        es[i]->clear();
        dbForms[i].clear();
    }
}
