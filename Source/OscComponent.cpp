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
OscComponent::OscComponent(juce::String name, juce::AudioProcessorValueTreeState& valueTree, juce::String waveSelectorId, juce::String coarseTuneId, juce::String fineTuneId, juce::String pulseWidthId, juce::String gainId)
{
    moduleName = name;
        
    coarseTuneSlider.setSkewFactorFromMidPoint(1.0f);
    
    setComboBoxWithLabel(oscWaveSelector, waveformLabel, valueTree, waveSelectorId, oscWaveSelectorAttachment, {"Sine","Saw","Square"});
    setSliderWithLabel(coarseTuneSlider, coarseTuneLabel, valueTree, coarseTuneId, coarseTuneAttachment);
    setSliderWithLabel(fineTuneSlider, fineTuneLabel, valueTree, fineTuneId, fineTuneAttachment);
    setSliderWithLabel(pulseWidthSlider, pulseWidthLabel, valueTree, pulseWidthId, pulseWidthAttachment);
    setSliderWithLabel(gainSlider, gainLabel, valueTree, gainId, gainAttachment);
    
}

OscComponent::~OscComponent()
{
}

void OscComponent::resized()
{
    const auto startY = 55;
    const auto startY2 = 170;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    
    oscWaveSelector.setBounds(10, startY + 5, 90, 30);
    waveformLabel.setBounds(oscWaveSelector.getX(), startY - labelYOffset , 90, labelHeight);
    
    coarseTuneSlider.setBounds(oscWaveSelector.getRight(), startY, sliderWidth, sliderHeight);
    coarseTuneLabel.setBounds(coarseTuneSlider.getX(), coarseTuneSlider.getY() - labelYOffset, coarseTuneSlider.getWidth(), labelHeight);
    
    fineTuneSlider.setBounds(coarseTuneSlider.getRight(), startY, sliderWidth, sliderHeight);
    fineTuneLabel.setBounds(fineTuneSlider.getX(), fineTuneSlider.getY() - labelYOffset, fineTuneSlider.getWidth(), labelHeight);
    
    pulseWidthSlider.setBounds(oscWaveSelector.getX(), startY2, sliderWidth, sliderHeight);
    pulseWidthLabel.setBounds(pulseWidthSlider.getX(), pulseWidthSlider.getY() - labelYOffset, pulseWidthSlider.getWidth(), labelHeight);
    
    gainSlider.setBounds((coarseTuneSlider.getX() + fineTuneSlider.getX())/2, startY2, sliderWidth, sliderHeight);
    gainLabel.setBounds(gainSlider.getX(), gainSlider.getY() - labelYOffset, gainSlider.getWidth(), labelHeight);

}
