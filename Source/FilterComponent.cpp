/*
  ==============================================================================

    FilterComponent.cpp
    Created: 12 Aug 2024 1:49:51pm
    Author:  Joe Paller

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& valueTree, juce::String filterTypeId, juce::String filterCutoffId, juce::String filterResonanceId)
{
    setSliderWithLabel(filterCutoffSlider, filterCutoffLabel, valueTree, filterCutoffId, filterCutoffAttachment);
    setSliderWithLabel(filterResonanceSlider, filterResonanceLabel, valueTree, filterResonanceId, filterResonanceAttachment);
    setComboBoxWithLabel(filterTypeComboBox, filterTypeLabel, valueTree, filterTypeId, filterTypeAttachment, {"Low-Pass", "Band-Pass", "High-Pass"});
    
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5, 5);
    auto labelSpace = bounds.removeFromTop(25.0f);
    
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Filter", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void FilterComponent::resized()
{
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    
    filterTypeComboBox.setBounds(10, startY + 5, 90, 30);
    filterTypeLabel.setBounds(10, startY - labelYOffset , 90, labelHeight);
    
    filterCutoffSlider.setBounds(filterTypeComboBox.getRight(), startY, sliderWidth, sliderHeight);
    filterCutoffLabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - labelYOffset, filterCutoffSlider.getWidth(), labelHeight);
    
    filterResonanceSlider.setBounds(filterCutoffSlider.getRight(), startY, sliderWidth, sliderHeight);
    filterResonanceLabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - labelYOffset, filterResonanceSlider.getWidth(), labelHeight);
}
