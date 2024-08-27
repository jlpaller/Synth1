/*
  ==============================================================================

    Synth1Component.h
    Created: 26 Aug 2024 6:56:53pm
    Author:  Joe Paller

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Synth1Component  : public juce::Component
{
public:
    Synth1Component();
    ~Synth1Component() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& valueTree, juce::String paramId, std::unique_ptr<SliderAttachment>& attachment);

    using ComboAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    void setComboBoxWithLabel(juce::ComboBox& combo, juce::Label& label, juce::AudioProcessorValueTreeState& valueTree, juce::String paramId, std::unique_ptr<ComboAttachment>& attachment, juce::StringArray choices);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Synth1Component)
};
