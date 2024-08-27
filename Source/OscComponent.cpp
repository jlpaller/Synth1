/*
  ==============================================================================

    OscComponent.cpp
    Created: 10 Jul 2024 6:57:13pm
    Author:  Joe Paller

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::String name, juce::AudioProcessorValueTreeState& valueTree, juce::String waveSelectorId, juce::String coarseTuneId, juce::String fineTuneId, juce::String pulseWidthId)
{
    moduleName = name;
        
    coarseTuneSlider.setSkewFactorFromMidPoint(1.0f);
    
    setComboBoxWithLabel(oscWaveSelector, waveformLabel, valueTree, waveSelectorId, oscWaveSelectorAttachment, {"Sine","Saw","Square"});
    setSliderWithLabel(coarseTuneSlider, coarseTuneLabel, valueTree, coarseTuneId, coarseTuneAttachment);
    setSliderWithLabel(fineTuneSlider, fineTuneLabel, valueTree, fineTuneId, fineTuneAttachment);
    setSliderWithLabel(pulseWidthSlider, pulseWidthLabel, valueTree, pulseWidthId, pulseWidthAttachment);
    
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5, 5);
    auto labelSpace = bounds.removeFromTop(25.0f);
    
    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText(moduleName, labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void OscComponent::resized()
{
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    
    oscWaveSelector.setBounds(10, startY + 5, 90, 30);
    waveformLabel.setBounds(10, startY - labelYOffset , 90, labelHeight);
    
    coarseTuneSlider.setBounds(oscWaveSelector.getRight(), startY, sliderWidth, sliderHeight);
    coarseTuneLabel.setBounds(coarseTuneSlider.getX(), coarseTuneSlider.getY() - labelYOffset, coarseTuneSlider.getWidth(), labelHeight);
    
    fineTuneSlider.setBounds(coarseTuneSlider.getRight(), startY, sliderWidth, sliderHeight);
    fineTuneLabel.setBounds(fineTuneSlider.getX(), fineTuneSlider.getY() - labelYOffset, fineTuneSlider.getWidth(), labelHeight);
    
    pulseWidthSlider.setBounds(oscWaveSelector.getX(), startY + 65, sliderWidth-30, sliderHeight-30);
    pulseWidthLabel.setBounds(pulseWidthSlider.getX(), pulseWidthSlider.getY() - labelYOffset, pulseWidthSlider.getWidth(), labelHeight);

}
