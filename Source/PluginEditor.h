/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "XyPad.h"
#include "Panel1.h"
#include "Panel2.h"

//==============================================================================
/**
*/
class XyPadAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    XyPadAudioProcessorEditor (XYPadAudioProcessor&);

    void paint (Graphics&) override;
    void resized() override;
private:
    XYPadAudioProcessor& audioProcessor;
    AudioProcessorValueTreeState& parameters;

    Gui::Panel1 panel1;
    Gui::Panel2 panel2;
    TabbedComponent tabbedComponent{ TabbedButtonBar::TabsAtTop };
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XyPadAudioProcessorEditor)
};
