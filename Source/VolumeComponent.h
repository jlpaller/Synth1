/*
  ==============================================================================

    VolumeComponent.h
    Created: 28 Aug 2024 5:28:54pm
    Author:  Joe Paller

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synth1Component.h"

//==============================================================================
/*
*/
class VolumeComponent  : public Synth1Component
{
public:
    VolumeComponent(juce::String name, juce::AudioProcessorValueTreeState& valueTree, juce::String volumeId);
    ~VolumeComponent() override;

    void resized() override;

private:
    
    juce::Slider volumeSlider;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> volumeAttachment;
    
    juce::Label volumeLabel{"Volume", "Volume"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeComponent)
};
