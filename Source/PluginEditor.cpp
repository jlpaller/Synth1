/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth1AudioProcessorEditor::Synth1AudioProcessorEditor (Synth1AudioProcessor& p)
: AudioProcessorEditor (&p)
, audioProcessor (p)
, osc1("Oscillator 1",audioProcessor.valueTree, "OSC1_WAVE", "OSC1_TUNE", "OSC1_FINE", "OSC1_PW")
, osc2("Oscillator 2", audioProcessor.valueTree, "OSC2_WAVE", "OSC2_TUNE", "OSC2_FINE", "OSC2_PW")
, adsr("Amp Envelope", audioProcessor.valueTree, "AMP_ATTACK", "AMP_DECAY", "AMP_SUSTAIN", "AMP_RELEASE")
, filter(audioProcessor.valueTree, "FILTER_TYPE", "FILTER_CUTOFF", "FILTER_RESONANCE")
, filterAdsr("Filter Envelope", audioProcessor.valueTree, "FILTER_ATTACK", "FILTER_DECAY", "FILTER_SUSTAIN", "FILTER_RELEASE")
{

    setSize (920, 500);
    
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(filterAdsr);
    
}

Synth1AudioProcessorEditor::~Synth1AudioProcessorEditor()
{
}

//==============================================================================
void Synth1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

}

void Synth1AudioProcessorEditor::resized()
{
    const auto paddingX = 5; // pad from the left
    const auto paddingY = 35; // pad from the top
    const auto paddingY2 = 235; // pad from the top for second level
    const auto moduleWidth = 300;
    const auto moduleHeight = 200;
    
    osc1.setBounds(paddingX, paddingY, moduleWidth, moduleHeight);
    osc2.setBounds(osc1.getRight(), paddingY, moduleWidth, moduleHeight);
    adsr.setBounds(osc2.getRight(), paddingY, moduleWidth, moduleHeight);
    filter.setBounds(paddingX, paddingY2, moduleWidth, moduleHeight);
    filterAdsr.setBounds(filter.getRight(), paddingY2, moduleWidth, moduleHeight);

}



