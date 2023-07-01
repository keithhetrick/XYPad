/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
XYPadAudioProcessor::XYPadAudioProcessor()
: AudioProcessor (BusesProperties()
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
parameters(*this, nullptr, "xypad", {
    std::make_unique<AudioParameterFloat>(ParameterID {"pan", 1},
                                          "Pan",
                                          NormalisableRange<float>{-1.f, 1.f, 0.01f},
                                          0.f),
    std::make_unique<AudioParameterFloat>(ParameterID {"gain", 1},
                                          "Gain",
                                          NormalisableRange<float>{-60.f, 0.f, 0.01f},
                                          0.f)
})

{
    parameters.addParameterListener("gain", this);
    parameters.addParameterListener("pan",  this);
}

XYPadAudioProcessor::~XYPadAudioProcessor()
{
    parameters.removeParameterListener("gain", this);
    parameters.removeParameterListener("pan",  this);
}

//==============================================================================
const juce::String XYPadAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool XYPadAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool XYPadAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool XYPadAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double XYPadAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int XYPadAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int XYPadAudioProcessor::getCurrentProgram()
{
    return 0;
}

void XYPadAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String XYPadAudioProcessor::getProgramName (int index)
{
    return {};
}

void XYPadAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void XYPadAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const dsp::ProcessSpec spec{ sampleRate, static_cast<uint32>(samplesPerBlock), static_cast<uint32>(getTotalNumInputChannels()) };
    gainProcessor.prepare(spec);
    panProcessor.prepare(spec);
    
    gainProcessor.setGainDecibels(parameters.getRawParameterValue("gain")->load());
    panProcessor. setPan(parameters.getRawParameterValue("pan")->load());
}

void XYPadAudioProcessor::releaseResources()
{
    gainProcessor.reset();
    panProcessor. reset();
}

bool XYPadAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;

}


void XYPadAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    dsp::AudioBlock<float> audioBlock{ buffer };
    
    dsp::ProcessContextReplacing<float> context { audioBlock };
    gainProcessor.process(context);
    panProcessor.process(context);
}

//==============================================================================
bool XYPadAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* XYPadAudioProcessor::createEditor()
{
    return new XyPadAudioProcessorEditor (*this);
}

//==============================================================================
void XYPadAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void XYPadAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

AudioProcessorValueTreeState& XYPadAudioProcessor::getApvts()
{
    return parameters;
}

void XYPadAudioProcessor::parameterChanged(const String& parameterID, float newValue)
{
    if (parameterID.equalsIgnoreCase("gain"))
        gainProcessor.setGainDecibels(newValue);
    if (parameterID.equalsIgnoreCase("pan"))
        panProcessor.setPan(newValue);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new XYPadAudioProcessor();
}
