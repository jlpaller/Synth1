/*
  ==============================================================================

    AdsrComponent.h
    Created: 6 Jul 2024 5:06:04pm
    Author:  Joe Paller

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synth1Component.h"


//==============================================================================
/*
*/
class AdsrComponent  : public Synth1Component
{
public:
    AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& valueTree, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider releaseSlider;
    juce::Slider sustainSlider;
    
    //create attachments to the controls which connect to value tree state
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    
    juce::Label attackLabel{"Envelope Attack", "Attack"};
    juce::Label decayLabel{"Envelope Decay", "Decay"};
    juce::Label sustainLabel{"Envelope Sustain", "Sustain"};
    juce::Label releaseLabel{"Envelope Release", "Release"};
    
    juce::String moduleName {""};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
