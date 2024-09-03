/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 6 Jul 2024 5:06:04pm
    Author:  Joe Paller

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::String name, juce::AudioProcessorValueTreeState& valueTree, juce::String attackId, juce::String decayId, juce::String sustainId, juce::String releaseId)
{
    moduleName = name;
    
    setSliderWithLabel(attackSlider, attackLabel, valueTree, attackId, attackAttachment, juce::Slider::SliderStyle::LinearVertical);
    setSliderWithLabel(decaySlider, decayLabel, valueTree, decayId, decayAttachment, juce::Slider::SliderStyle::LinearVertical);
    setSliderWithLabel(sustainSlider, sustainLabel, valueTree, sustainId, sustainAttachment, juce::Slider::SliderStyle::LinearVertical);
    setSliderWithLabel(releaseSlider, releaseLabel, valueTree, releaseId, releaseAttachment, juce::Slider::SliderStyle::LinearVertical);

}

AdsrComponent::~AdsrComponent()
{
}


void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight() - 45;
    const auto sliderStartX = padding + 5;
    const auto sliderStartY = 55;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto labelStart = sliderStartY - labelYOffset;
    
    attackSlider.setBounds (sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attackLabel.setBounds (attackSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    decaySlider.setBounds (attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    decayLabel.setBounds (decaySlider.getX(), labelStart, sliderWidth, labelHeight);
    
    sustainSlider.setBounds (decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainLabel.setBounds (sustainSlider.getX(), labelStart, sliderWidth, labelHeight);
    
    releaseSlider.setBounds (sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseLabel.setBounds (releaseSlider.getX(), labelStart, sliderWidth, labelHeight);
}
