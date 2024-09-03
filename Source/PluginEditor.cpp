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
, osc1Env("Osc 1 Amp Env", audioProcessor.valueTree, "OSC1_ATTACK", "OSC1_DECAY", "OSC1_SUSTAIN", "OSC1_RELEASE")
, osc2Env("Osc 2 Amp Env", audioProcessor.valueTree, "OSC2_ATTACK", "OSC2_DECAY", "OSC2_SUSTAIN", "OSC2_RELEASE")
, LPF(audioProcessor.valueTree, "Low Pass", "LPF_CUTOFF", "LPF_RESONANCE")
, HPF(audioProcessor.valueTree, "High Pass", "HPF_CUTOFF", "HPF_RESONANCE")
, filterAdsr("Filter Envelope", audioProcessor.valueTree, "FILTER_ATTACK", "FILTER_DECAY", "FILTER_SUSTAIN", "FILTER_RELEASE")
, volume("Volume", audioProcessor.valueTree, "VOLUME")
{

    setSize (1220, 620);
    
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
    addAndMakeVisible(osc1Env);
    addAndMakeVisible(osc2Env);
    addAndMakeVisible(LPF);
    addAndMakeVisible(HPF);
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
    const auto moduleWidth = 280;
    const auto moduleHeight = 250;
    const auto paddingY2 = moduleHeight + paddingY*2; // pad from the top for second level

    
    //row 1
    osc1.setBounds(paddingX, paddingY, moduleWidth, moduleHeight);
    osc1Env.setBounds(osc1.getRight(), paddingY, moduleWidth, moduleHeight);
    osc2.setBounds(osc1Env.getRight(), paddingY, moduleWidth, moduleHeight);
    osc2Env.setBounds(osc2.getRight(), paddingY, moduleWidth, moduleHeight);

    //row 2
    LPF.setBounds(paddingX, paddingY2, moduleWidth/2, moduleHeight);
    HPF.setBounds(LPF.getRight(), paddingY2, moduleWidth/2, moduleHeight);
    filterAdsr.setBounds(HPF.getRight(), paddingY2, moduleWidth, moduleHeight);
    volume.setBounds(filterAdsr.getRight(), paddingY2, moduleWidth/3, moduleHeight);

}



