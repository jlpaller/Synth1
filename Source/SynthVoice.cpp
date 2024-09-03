/*
  ==============================================================================

    SynthVoice.cpp
    Created: 3 Jul 2024 3:08:22pm
    Author:  Joe Paller

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    //returns true if our synth sound is correctly casting as juce::SynthesizerSound (which SynthSound should be extending from)
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc1.setNote(midiNoteNumber);
    osc2.setNote(midiNoteNumber);

    osc1AmpEnv.noteOn();
    osc2AmpEnv.noteOn();
    filterAdsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    osc1AmpEnv.noteOff();
    osc2AmpEnv.noteOff();
    filterAdsr.noteOff();
    
    if (! allowTailOff || ( ! osc1AmpEnv.isActive() && ! osc2AmpEnv.isActive() ) || ! filterAdsr.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void SynthVoice::prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels)
{

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc1.prepareToPlay(spec);
    osc2.prepareToPlay(spec);
    osc1AmpEnv.setSampleRate(sampleRate);
    osc2AmpEnv.setSampleRate(sampleRate);
    LPF.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    HPF.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    filterAdsr.setSampleRate(sampleRate);
    gain1.prepare(spec);
    gain2.prepare(spec);
    outputGain.prepare(spec);
    isPrepared = true;
    
}

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    //double check that all settings are set before trying to do anything with data
    jassert(isPrepared);
    
    if (! isVoiceActive())
        return;
        
    osc1buffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    osc2buffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

    //this next line just activates the filter adsr. doesn't actually do anything to the buffer
    filterAdsr.applyEnvelopeToBuffer(osc1buffer, 0, osc1buffer.getNumSamples());
    
    osc1buffer.clear();
    osc2buffer.clear();
    
    //creat buffers for each oscillator, then combine into one audio buffer
    juce::dsp::AudioBlock<float> audioBlock1 {osc1buffer};
    juce::dsp::AudioBlock<float> audioBlock2 {osc2buffer};
    osc1.getNextAudioBlock(audioBlock1);
    osc2.getNextAudioBlock(audioBlock2);

    gain1.process(juce::dsp::ProcessContextReplacing<float> (audioBlock1));
    gain2.process(juce::dsp::ProcessContextReplacing<float> (audioBlock2));

    osc1AmpEnv.applyEnvelopeToBuffer(osc1buffer, 0, osc1buffer.getNumSamples());
    osc2AmpEnv.applyEnvelopeToBuffer(osc2buffer, 0, osc2buffer.getNumSamples());
    
    outputGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock1));
    outputGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock2));
        
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, osc1buffer, channel, 0, numSamples);
        outputBuffer.addFrom(channel, startSample, osc2buffer, channel, 0, numSamples);
        
        if (! osc1AmpEnv.isActive() && ! osc2AmpEnv.isActive())
            clearCurrentNote();
    }
    
    LPF.process(outputBuffer);
    HPF.process(outputBuffer);
    
}

void SynthVoice::updateFilter(FilterData& filter, const float cutoff, const float resonance)
{
    float modulator = filterAdsr.getNextSample();
    filter.setTone(cutoff, resonance, modulator);
}

void SynthVoice::updateFilterADSR(const float attack, const float decay, const float sustain, const float release)
{
    filterAdsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateGains(const float gain1Val, const float gain2Val, const float outputGainVal)
{
    gain1.setGainLinear(gain1Val);
    gain2.setGainLinear(gain2Val);
    outputGain.setGainLinear(outputGainVal);
}

