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
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& valueTree, juce::String name, juce::String filterCutoffId, juce::String filterResonanceId)
{
    
    moduleName = name;

    
    setSliderWithLabel(filterCutoffSlider, filterCutoffLabel, valueTree, filterCutoffId, filterCutoffAttachment);
    setSliderWithLabel(filterResonanceSlider, filterResonanceLabel, valueTree, filterResonanceId, filterResonanceAttachment);
    //setComboBoxWithLabel(filterTypeComboBox, filterTypeLabel, valueTree, filterTypeId, filterTypeAttachment, {"Low-Pass", "Band-Pass", "High-Pass"});
    
}

FilterComponent::~FilterComponent()
{
}



void FilterComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto knobDiameter = std::min(bounds.getWidth()-padding, bounds.getHeight()/3);
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto startY = 55;
    
    
    filterCutoffSlider.setBounds(bounds.getWidth()/2 - knobDiameter/2, startY, knobDiameter, knobDiameter);
    filterCutoffLabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - labelYOffset, knobDiameter, labelHeight);
    
    filterResonanceSlider.setBounds(filterCutoffSlider.getX(), bounds.getHeight() - knobDiameter - padding + labelHeight, knobDiameter, knobDiameter);
    filterResonanceLabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - labelYOffset, knobDiameter, labelHeight);

}
