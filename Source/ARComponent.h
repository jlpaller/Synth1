/*
  ==============================================================================

    ARComponent.h
    Created: 28 Aug 2024 5:00:42pm
    Author:  Joe Paller

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synth1Component.h"


//==============================================================================
/*
*/
class ARComponent  : public Synth1Component
{
public:
    ARComponent(juce::String name, juce::AudioProcessorValueTreeState& valueTree, juce::String attackId, juce::String releaseId);
    ~ARComponent() override;

    void resized() override;

private:
    juce::Slider attackSlider;
    juce::Slider releaseSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    
    juce::Label attackLabel{"Envelope Attack", "Attack"};
    juce::Label releaseLabel{"Envelope Release", "Release"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARComponent)
};
