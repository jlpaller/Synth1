/*
  ==============================================================================

    VolumeComponent.cpp
    Created: 28 Aug 2024 5:28:54pm
    Author:  Joe Paller

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VolumeComponent.h"

//==============================================================================
VolumeComponent::VolumeComponent(juce::String name, juce::AudioProcessorValueTreeState& valueTree, juce::String volumeId)
{
    moduleName = name;
    
    setSliderWithLabel(volumeSlider, volumeLabel, valueTree, volumeId, volumeAttachment, juce::Slider::SliderStyle::LinearVertical);

}

VolumeComponent::~VolumeComponent()
{
}

void VolumeComponent::resized()
{
    const auto bounds = getLocalBounds().reduced (10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth();
    const auto sliderHeight = bounds.getHeight() - 45;
    const auto sliderStartX = padding;
    const auto sliderStartY = 55;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;
    
    volumeSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    volumeLabel.setBounds (volumeSlider.getX(), labelStart, sliderWidth, labelHeight);
}
