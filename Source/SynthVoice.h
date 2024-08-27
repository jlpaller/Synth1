/*
  ==============================================================================

    SynthVoice.h
    Created: 3 Jul 2024 3:08:22pm
    Author:  Joe Paller

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "AdsrData.h"
#include "OscData.h"
#include "FilterData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    
    void updateADSR(float attack, float decay, float sustain, float release);
    void updateFilter(const int filterType, const float cutoff, const float resonance);
    void updateFilterADSR(float attack, float decay, float sustain, float release);
    
    OscData& getOscillator1() { return osc1; }
    OscData& getOscillator2() { return osc2; }

    
private:
    juce::AudioBuffer<float> synthBuffer;
    
    OscData osc1;
    OscData osc2;
    AdsrData ampAdsr;
    FilterData filter;
    AdsrData filterAdsr;
    
    juce::dsp::Gain<float> gain;
    
    bool isPrepared {false};


   
    
};
