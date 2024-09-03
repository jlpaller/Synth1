/*
  ==============================================================================

    FilterData.cpp
    Created: 12 Aug 2024 1:01:50pm
    Author:  Joe Paller

  ==============================================================================
*/

#include "FilterData.h"

FilterData::FilterData(const int filterType)
{
    Type = filterType;
}

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
    filter.reset();
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = numChannels;
    
    filter.prepare(spec);
    isPrepared = true;
    
    setType(Type);
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    
    juce::dsp::AudioBlock<float> block { buffer };
    filter.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void FilterData::setType(const int filterType)
{
    if (filterType != Type)
    {
        switch (filterType)
        {
            case 0:
                filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
                break;
                
            case 1:
                filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
                break;
                
            case 2:
                filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
                break;
        }
        
        Type = filterType;
    }
    

        
}

void FilterData::setTone(const float frequency, const float resonance, const float modulator)
{
    //make sure cutoff is between 20 and 20kHz
    float modFreq = std::fmin(std::fmax(frequency * modulator, 20.0f), 20000.0f);
    
    filter.setCutoffFrequency(modFreq);
    filter.setResonance(resonance);
}

void FilterData::reset()
{
    filter.reset();
}
