/*
  ==============================================================================

    OscComponent.h
    Created: 10 Jul 2024 6:57:13pm
    Author:  Joe Paller

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synth1Component.h"

//==============================================================================
/*
*/
class OscComponent  : public Synth1Component
{
public:
    OscComponent(juce::String name, juce::AudioProcessorValueTreeState& valueTree, juce::String waveSelectorId, juce::String coarseTuneId, juce::String fineTuneId, juce::String pulseWidthId, juce::String gainId);
    ~OscComponent() override;

    void resized() override;

private:
    juce::ComboBox oscWaveSelector { "Waveform" };
    juce::Slider coarseTuneSlider;
    juce::Slider fineTuneSlider;
    juce::Slider pulseWidthSlider;
    juce::Slider gainSlider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> coarseTuneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fineTuneAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> pulseWidthAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;


    juce::Label waveformLabel{"Waveform","Waveform"};
    juce::Label coarseTuneLabel{"Coarse Tune","Coarse"};
    juce::Label fineTuneLabel{"Fine Tune","Fine"};
    juce::Label pulseWidthLabel{"Pulse Width","Pulse Width"};
    juce::Label gainLabel{"Gain","Gain"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
