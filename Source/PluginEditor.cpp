/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
XYPadAudioProcessorEditor::XYPadAudioProcessorEditor (XYPadAudioProcessor& p) :
    AudioProcessorEditor (&p),
    audioProcessor (p),
    gainAttachment(p.getApvts(), "gain", gainSlider),
    panAttachment (p.getApvts(), "pan", panSlider)
{
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(panSlider);
    addAndMakeVisible(gainLabel);
    addAndMakeVisible(panLabel);
    addAndMakeVisible(xyPad);
    
    gainLabel.setJustificationType(Justification::centred);
    panLabel. setJustificationType(Justification::centred);
    gainLabel.attachToComponent(&gainSlider, false);
    panLabel. attachToComponent(&panSlider, false);
    
    xyPad.registerSlider(&gainSlider, Gui::XyPad::Axis::Y);
    xyPad.registerSlider(&panSlider,  Gui::XyPad::Axis::X);
    
    setSize (500, 300);
    setResizable(true, true);
}

XYPadAudioProcessorEditor::~XYPadAudioProcessorEditor()
{
    xyPad.deregisterSlider(&gainSlider);
    xyPad.deregisterSlider(&panSlider);
}

//==============================================================================
void XYPadAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void XYPadAudioProcessorEditor::resized()
{
    const auto container = getLocalBounds().reduced(20);
    auto bounds = container;
    gainSlider.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.25f)));
    xyPad.setBounds(bounds.removeFromLeft(container.proportionOfWidth(0.5f)).reduced(20));
    panSlider.setBounds(bounds);
}
