/*
  ==============================================================================

    XyPad.cpp
    Created: 25 Jun 2023 9:50:19pm
    Author:  Keith Hetrick

  ==============================================================================
*/

#include "XyPad.h"

namespace Gui
{
    /*
     * XY Pad Thumb section
     */
    XyPad::Thumb::Thumb()
    {
    }

    void XyPad::Thumb::paint(Graphics &g)
    {
        g.setColour(Colours::white);
        g.fillEllipse(getLocalBounds().toFloat());
    }

    /*
     * XY Pad section
     */
    XyPad::XyPad()
    {
        addAndMakeVisible(thumb);
    }

    void XyPad::resized()
    {
        thumb.setBounds(getLocalBounds().withSizeKeepingCentre(thumbSize, thumbSize));
    }

    void XyPad::paint(Graphics &g)
    {
        g.setColour(Colours::black);
        g.fillRoundedRectangle(getLocalBounds().toFloat(), 10.f);
    }

    void XyPad::registerSlider(Slider *slider, Axis axis)
    {
    }

    void XyPad::deregisterSlider(Slider *slider)
    {
    }

}
