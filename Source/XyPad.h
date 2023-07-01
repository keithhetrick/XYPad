/*
  ==============================================================================

    XyPad.h
    Created: 25 Jun 2023 9:50:19pm
    Author:  Keith Hetrick

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace Gui
{
    class XyPad : public Component, Slider::Listener
    {
    public:
        enum Axis { X, Y };
        class Thumb : public Component
        {
        public:
            Thumb();
            void mouseDown(const MouseEvent& event) override;
            void mouseDrag(const MouseEvent& event) override;
            void paint(Graphics& g) override;
            std::function<void(Point<double>)> moveCallback;
        private:
            ComponentBoundsConstrainer constrainer;
            ComponentDragger dragger;
        };

        XyPad();

        void registerSlider(Slider* slider, Axis axis);
        void deregisterSlider(Slider* slider);
        
        void resized() override;
        void paint(Graphics& g) override;
    private:
        void sliderValueChanged(Slider* slider) override;

        Thumb thumb;
        std::vector<Slider*> xSliders, ySliders;
        static constexpr int thumbWidth = 40;

        std::mutex mutex;
    };
}
