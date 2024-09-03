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
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto startY = 55;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    const auto knobDiameter = bounds.getWidth() / 3 - padding;
    
    oscWaveSelector.setBounds(padding, startY + 5, knobDiameter, knobDiameter/3);
    waveformLabel.setBounds(oscWaveSelector.getX(), startY - labelYOffset , oscWaveSelector.getWidth(), labelHeight);
    
    coarseTuneSlider.setBounds(oscWaveSelector.getRight() + padding*2, startY, knobDiameter, knobDiameter);
    coarseTuneLabel.setBounds(coarseTuneSlider.getX(), coarseTuneSlider.getY() - labelYOffset, coarseTuneSlider.getWidth(), labelHeight);
    
    fineTuneSlider.setBounds(coarseTuneSlider.getRight() + padding, startY, knobDiameter, knobDiameter);
    fineTuneLabel.setBounds(fineTuneSlider.getX(), fineTuneSlider.getY() - labelYOffset, fineTuneSlider.getWidth(), labelHeight);
    
    pulseWidthSlider.setBounds(oscWaveSelector.getX(), coarseTuneSlider.getY() + padding + knobDiameter, knobDiameter, knobDiameter);
    pulseWidthLabel.setBounds(pulseWidthSlider.getX(), pulseWidthSlider.getY() - labelYOffset, pulseWidthSlider.getWidth(), labelHeight);
    
    gainSlider.setBounds((coarseTuneSlider.getX() + fineTuneSlider.getX())/2, coarseTuneSlider.getY() + padding + knobDiameter, knobDiameter, knobDiameter);
    gainLabel.setBounds(gainSlider.getX(), gainSlider.getY() - labelYOffset, gainSlider.getWidth(), labelHeight);

}
