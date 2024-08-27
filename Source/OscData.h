/*
  ==============================================================================

    OscData.h
    Created: 10 Jul 2024 5:57:06pm
    Author:  Joe Paller

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class OscData : public juce::dsp::Oscillator<float>
{
public:
    void setWaveType(const int waveType, const float pulseWidth);
    void setNote(const int midiNoteNumber);
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void getNextAudioBlock (juce::dsp::AudioBlock<float>& block);
    void setTuning(const float tuneSliderValue, const float fineTuneSliderValue);

private:
    float tuneValue;
    float fineTuneValue;
    
};
