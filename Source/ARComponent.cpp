/*
  ==============================================================================

    ARComponent.cpp
    Created: 28 Aug 2024 5:00:42pm
    Author:  Joe Paller

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ARComponent.h"

//==============================================================================
ARComponent::ARComponent(juce::String name, juce::AudioProcessorValueTreeState& valueTree, juce::String attackId, juce::String releaseId)
{
    moduleName = name;
    
    setSliderWithLabel(attackSlider, attackLabel, valueTree, attackId, attackAttachment, juce::Slider::SliderStyle::LinearVertical);
    setSliderWithLabel(releaseSlider, releaseLabel, valueTree, releaseId, releaseAttachment, juce::Slider::SliderStyle::LinearVertical);

}

ARComponent::~ARComponent()
{
}

void ARComponent::resized()
{
    const auto bounds = getLocalBounds().reduced (10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 2 - padding;
    const auto sliderHeight = bounds.getHeight() - 45;
    const auto sliderStartX = padding + 5;
    const auto sliderStartY = 55;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;
    
    attackSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attackLabel.setBounds (attackSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    releaseSlider.setBounds (attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseLabel.setBounds (releaseSlider.getX(), labelStart, sliderWidth, labelHeight);

}
