/*
  ==============================================================================

    OscData.cpp
    Created: 10 Jul 2024 5:57:06pm
    Author:  Joe Paller

  ==============================================================================
*/

#include "OscData.h"

void OscData::setWaveType(const int waveType, const float pulseWidth)
{
    // AudioParameterChoice for oscillator wave returns its raw value as an int in PluginProcesor.cpp
    // Sine = 0
    // Saw = 1
    // Square = 2
    
    switch (waveType)
    {
        case 0: //sine
            initialise([](float x) { return std::sin (x); });
            break;
            
        case 1: //saw
            initialise([](float x) { return x / juce::MathConstants<float>::pi; });
            break;
            
        case 2: //square
            initialise([pulseWidth](float x) { return x < pulseWidth ? -1.0f : 1.0f; });
            break;
            
        default:
            jassertfalse;
            break;
    }
}

void OscData::setTuning(const float tuneSliderValue, const float fineTuneSliderValue)
{
    tuneValue = tuneSliderValue;
    //-half step = 0.94387
    //+half step = 1.05946
    fineTuneValue = fineTuneSliderValue;
    //-octave = 0.5
    //+octave = 2.0
}


void OscData::setNote(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) * tuneValue * fineTuneValue);
}

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    prepare(spec);
}
    
void OscData::getNextAudioBlock (juce::dsp::AudioBlock<float>& block)
{
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

    

