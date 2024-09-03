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
    
    void updateFilter(FilterData& filter, const float cutoff, const float resonance);
    void updateFilterADSR(float attack, float decay, float sustain, float release);
    void updateGains(const float gain1, const float gain2, const float outputGain);
    
    FilterData& getHPF() { return HPF; }
    FilterData& getLPF() { return LPF; }
    
    OscData& getOscillator1() { return osc1; }
    OscData& getOscillator2() { return osc2; }
    
    AdsrData& getOsc1ADSR() { return osc1AmpEnv; }
    AdsrData& getOsc2ADSR() { return osc2AmpEnv; }
    
private:
    juce::AudioBuffer<float> osc1buffer;
    juce::AudioBuffer<float> osc2buffer;
    
    OscData osc1;
    OscData osc2;
    AdsrData osc1AmpEnv;
    AdsrData osc2AmpEnv;

    juce::dsp::Gain<float> gain1;
    juce::dsp::Gain<float> gain2;
    
    FilterData LPF = FilterData(0);
    FilterData HPF = FilterData(2);
    AdsrData filterAdsr;

    juce::dsp::Gain<float> outputGain;
    
    bool isPrepared {false};
};
