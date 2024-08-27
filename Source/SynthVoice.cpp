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

    ampAdsr.noteOn();
    filterAdsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff)
{
    ampAdsr.noteOff();
    filterAdsr.noteOff();
    
    if (! allowTailOff || ! ampAdsr.isActive() || ! filterAdsr.isActive())
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
    ampAdsr.setSampleRate(sampleRate);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    filterAdsr.setSampleRate(sampleRate);
    gain.prepare(spec);
    gain.setGainLinear(0.2f);
        
    isPrepared = true;
}

void SynthVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    //double check that all settings are set before trying to do anything with data
    jassert(isPrepared);
    
    if (! isVoiceActive())
        return;
        
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    //this next line just activates the filter adsr. doesn't actually do anything to the buffer
    filterAdsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock {synthBuffer};
    osc1.getNextAudioBlock(audioBlock);
    osc2.getNextAudioBlock(audioBlock);
    ampAdsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    filter.process(synthBuffer);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
        
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if (! ampAdsr.isActive())
            clearCurrentNote();
    }
    
}

void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    ampAdsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::updateFilter(const int filterType, const float cutoff, const float resonance)
{
    float modulator = filterAdsr.getNextSample();
    filter.updateParameters(filterType, cutoff, resonance, modulator);
}

void SynthVoice::updateFilterADSR(const float attack, const float decay, const float sustain, const float release)
{
    filterAdsr.updateADSR(attack, decay, sustain, release);
}
