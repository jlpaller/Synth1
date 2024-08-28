/*
  ==============================================================================

    This file contains the layout of subcomponents in the plugin UI.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Synth1AudioProcessorEditor::Synth1AudioProcessorEditor (Synth1AudioProcessor& p)
: AudioProcessorEditor (&p)
, audioProcessor (p)
, osc1("Oscillator 1",audioProcessor.valueTree, "OSC1_WAVE", "OSC1_TUNE", "OSC1_FINE", "OSC1_PW", "OSC1_GAIN")
, osc2("Oscillator 2", audioProcessor.valueTree, "OSC2_WAVE", "OSC2_TUNE", "OSC2_FINE", "OSC2_PW", "OSC2_GAIN")
//, adsr("Amp Envelope", audioProcessor.valueTree, "AMP_ATTACK", "AMP_DECAY", "AMP_SUSTAIN", "AMP_RELEASE")
, osc1Env("Osc 1 Gain Env", audioProcessor.valueTree, "OSC1_ATTACK", "OSC1_RELEASE")
, osc2Env("Osc 2 Gain Env", audioProcessor.valueTree, "OSC2_ATTACK", "OSC2_RELEASE")
, filter(audioProcessor.valueTree, "FILTER_TYPE", "FILTER_CUTOFF", "FILTER_RESONANCE")
, filterAdsr("Filter Envelope", audioProcessor.valueTree, "FILTER_ATTACK", "FILTER_DECAY", "FILTER_SUSTAIN", "FILTER_RELEASE")
, volume("Volume", audioProcessor.valueTree, "VOLUME")
{

    setSize (920, 620);
    
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(osc1Env);
    addAndMakeVisible(osc2Env);
    //addAndMakeVisible(adsr);
    addAndMakeVisible(filter);
    addAndMakeVisible(filterAdsr);
    addAndMakeVisible(volume);
    
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
    const auto paddingY = 10; // pad from the top
    const auto paddingY2 = 300; // pad from the top for second level
    const auto moduleWidth = 300;
    const auto moduleHeight = 280;
    
    //row 1
    osc1.setBounds(paddingX, paddingY, moduleWidth, moduleHeight);
    osc1Env.setBounds(osc1.getRight(), paddingY, moduleWidth/2, moduleHeight);
    osc2.setBounds(osc1Env.getRight(), paddingY, moduleWidth, moduleHeight);
    osc2Env.setBounds(osc2.getRight(), paddingY, moduleWidth/2, moduleHeight);

    //row 2
    filter.setBounds(paddingX, paddingY2, moduleWidth, moduleHeight);
    filterAdsr.setBounds(filter.getRight(), paddingY2, moduleWidth, moduleHeight);
    volume.setBounds(filterAdsr.getRight(), paddingY2, moduleWidth/3, moduleHeight);

}



