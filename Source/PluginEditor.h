/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "XyPad.h"

//==============================================================================
/**
*/
class XYPadAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    XYPadAudioProcessorEditor (XYPadAudioProcessor&);
    ~XYPadAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment =  AudioProcessorValueTreeState::SliderAttachment;
    
    XYPadAudioProcessor& audioProcessor;
    
    Slider gainSlider{ Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow };
    Slider panSlider { Slider::SliderStyle::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow };
    SliderAttachment gainAttachment, panAttachment;
    Label gainLabel{ "gainLabel", "Gain" };
    Label panLabel { "panLabel", "Pan" };
    Gui::XyPad xyPad;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XYPadAudioProcessorEditor)
};
