/*
  ==============================================================================

    FilterComponent.h
    Created: 12 Aug 2024 1:49:51pm
    Author:  Joe Paller

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synth1Component.h"


//==============================================================================
/*
*/
class FilterComponent  : public Synth1Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& valueTree, juce::String filterTypeId, juce::String filterCutoffId, juce::String filterResonanceId);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider filterCutoffSlider;
    juce::Slider filterResonanceSlider;
    juce::ComboBox filterTypeComboBox { "Filter Type" };
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using ComboAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    std::unique_ptr<SliderAttachment> filterCutoffAttachment;
    std::unique_ptr<SliderAttachment> filterResonanceAttachment;
    std::unique_ptr<ComboAttachment> filterTypeAttachment;
    
    juce::Label filterCutoffLabel{"Filter Cutoff", "Cutoff"};
    juce::Label filterResonanceLabel{"Filter Resonance", "Resonance"};
    juce::Label filterTypeLabel{"Filter Type", "Filter Type"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)

};
