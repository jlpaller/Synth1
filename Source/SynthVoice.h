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
    
    void updateAmpEnv(const float attack1, const float release1, const float attack2, const float release2);
    void updateFilter(const int filterType, const float cutoff, const float resonance);
    void updateFilterADSR(float attack, float decay, float sustain, float release);
    void updateGains(const float gain1, const float gain2, const float outputGain);
    
    OscData& getOscillator1() { return osc1; }
    OscData& getOscillator2() { return osc2; }

    
private:
    juce::AudioBuffer<float> osc1buffer;
    juce::AudioBuffer<float> osc2buffer;
    
    OscData osc1;
    OscData osc2;
    ARData osc1AmpEnv;
    ARData osc2AmpEnv;
    //AdsrData ampAdsr;

    juce::dsp::Gain<float> gain1;
    juce::dsp::Gain<float> gain2;
    
    FilterData filter;
    AdsrData filterAdsr;

    juce::dsp::Gain<float> outputGain;
    
    bool isPrepared {false};
};
