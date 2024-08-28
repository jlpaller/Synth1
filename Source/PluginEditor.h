/*
  ==============================================================================

    This file contains the plugin UI components.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "AdsrComponent.h"
#include "OscComponent.h"
#include "FilterComponent.h"
#include "ARComponent.h"
#include "VolumeComponent.h"

//==============================================================================
/**
*/
class Synth1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Synth1AudioProcessorEditor (Synth1AudioProcessor&);
    ~Synth1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    Synth1AudioProcessor& audioProcessor;
    OscComponent osc1;
    OscComponent osc2;
    //AdsrComponent adsr;
    ARComponent osc1Env;
    ARComponent osc2Env;
    FilterComponent filter;
    AdsrComponent filterAdsr;
    VolumeComponent volume;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth1AudioProcessorEditor)
};
