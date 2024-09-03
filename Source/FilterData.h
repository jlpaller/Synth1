/*
  ==============================================================================

    FilterData.h
    Created: 12 Aug 2024 1:01:50pm
    Author:  Joe Paller

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterData
{
public:
    FilterData(const int filterType = 0);
    
    void prepareToPlay (double sampleRate, int samplesPerBlock, int numChannels);
    void process (juce::AudioBuffer<float>& buffer);
    void setType(const int filterType);
    void setTone(const float frequency, const float resonance, const float modulator = 1.0f);
    void reset();
    
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared = false;
    int Type = 0;
    
};
