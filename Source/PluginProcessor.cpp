/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthSound.h"
#include "SynthVoice.h"
#include "FilterData.h"

//==============================================================================
Synth1AudioProcessor::Synth1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), valueTree(*this, nullptr, "Parameters", createParams())
#endif
{
    synth.addSound (new SynthSound());
    synth.addVoice (new SynthVoice());
}

Synth1AudioProcessor::~Synth1AudioProcessor()
{
}

//==============================================================================
const juce::String Synth1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Synth1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Synth1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Synth1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Synth1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Synth1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Synth1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Synth1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Synth1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Synth1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Synth1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    
    
}

void Synth1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Synth1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Synth1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //process the block for each voice
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        //check if each synth voice is actually pointing to a SynthVoice object
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {

            auto& osc1Wave = *valueTree.getRawParameterValue(juce::StringRef("OSC1_WAVE"));
            auto& osc1PW = *valueTree.getRawParameterValue(juce::StringRef("OSC1_PW"));
            auto& osc1Tune = *valueTree.getRawParameterValue(juce::StringRef("OSC1_TUNE"));
            auto& osc1Fine = *valueTree.getRawParameterValue(juce::StringRef("OSC1_FINE"));
            auto& osc1A = *valueTree.getRawParameterValue(juce::StringRef("OSC1_ATTACK"));
            auto& osc1R = *valueTree.getRawParameterValue(juce::StringRef("OSC1_RELEASE"));
            auto& osc1Gain = *valueTree.getRawParameterValue(juce::StringRef("OSC1_GAIN"));

            auto& osc2Wave = *valueTree.getRawParameterValue(juce::StringRef("OSC2_WAVE"));
            auto& osc2PW = *valueTree.getRawParameterValue(juce::StringRef("OSC2_PW"));
            auto& osc2Tune = *valueTree.getRawParameterValue(juce::StringRef("OSC2_TUNE"));
            auto& osc2Fine = *valueTree.getRawParameterValue(juce::StringRef("OSC2_FINE"));
            auto& osc2A = *valueTree.getRawParameterValue(juce::StringRef("OSC2_ATTACK"));
            auto& osc2R = *valueTree.getRawParameterValue(juce::StringRef("OSC2_RELEASE"));
            auto& osc2Gain = *valueTree.getRawParameterValue(juce::StringRef("OSC2_GAIN"));

//            auto& ampAttack = *valueTree.getRawParameterValue(juce::StringRef("AMP_ATTACK"));
//            auto& ampDecay = *valueTree.getRawParameterValue(juce::StringRef("AMP_DECAY"));
//            auto& ampSustain = *valueTree.getRawParameterValue(juce::StringRef("AMP_SUSTAIN"));
//            auto& ampRelease = *valueTree.getRawParameterValue(juce::StringRef("AMP_RELEASE"));
            
            auto& filterType = *valueTree.getRawParameterValue(juce::StringRef("FILTER_TYPE"));
            auto& filterCutoff = *valueTree.getRawParameterValue(juce::StringRef("FILTER_CUTOFF"));
            auto& filterResonance = *valueTree.getRawParameterValue(juce::StringRef("FILTER_RESONANCE"));
            
            auto& filterAttack = *valueTree.getRawParameterValue(juce::StringRef("FILTER_ATTACK"));
            auto& filterDecay = *valueTree.getRawParameterValue(juce::StringRef("FILTER_DECAY"));
            auto& filterSustain = *valueTree.getRawParameterValue(juce::StringRef("FILTER_SUSTAIN"));
            auto& filterRelease = *valueTree.getRawParameterValue(juce::StringRef("FILTER_RELEASE"));
            auto& outputVolume = *valueTree.getRawParameterValue(juce::StringRef("VOLUME"));
 
            voice->getOscillator1().setWaveType(osc1Wave.load(), osc1PW.load());
            voice->getOscillator1().setTuning(osc1Tune.load(), osc1Fine.load());
            voice->getOscillator2().setWaveType(osc2Wave.load(), osc2PW.load());
            voice->getOscillator2().setTuning(osc2Tune.load(), osc2Fine.load());
            voice->updateAmpEnv(osc1A.load(), osc1R.load(), osc2A.load(), osc2R.load());
            //voice->updateADSR(ampAttack.load(), ampDecay.load(), ampSustain.load(), ampRelease.load());
            voice->updateFilter(filterType.load(), filterCutoff.load(), filterResonance.load());
            voice->updateFilterADSR(filterAttack.load(), filterDecay.load(), filterSustain.load(), filterRelease.load());
            voice->updateGains(osc1Gain.load(), osc2Gain.load(), outputVolume.load());

        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
}

//==============================================================================
bool Synth1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Synth1AudioProcessor::createEditor()
{
    return new Synth1AudioProcessorEditor (*this);
}

//==============================================================================
void Synth1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Synth1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Synth1AudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout Synth1AudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    auto coarseRange = juce::NormalisableRange<float>{0.5f, 2.0f,};
    coarseRange.setSkewForCentre(1.0f);
    auto fineRange = juce::NormalisableRange<float>{0.94387f, 1.05946f,};
    fineRange.setSkewForCentre(1.0f);
    
    //oscillator 1
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"OSC1_WAVE",1}, "Osc1_Waveform", juce::StringArray{"Sine","Saw","Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC1_TUNE",1}, "Osc1_Tune", coarseRange, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC1_FINE",1}, "Osc1_FineTune", fineRange, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC1_PW",1}, "Osc1_PulseWidth", juce::NormalisableRange<float>{0.0f, 0.9f,}, 0.0f));
    // osc1 AR envelope
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC1_ATTACK",1}, "Osc1_Attack", juce::NormalisableRange<float>{0.01f, 4.0f,}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC1_RELEASE",1}, "Osc1_Release", juce::NormalisableRange<float>{0.01f, 2.0f,}, 0.5f));
    //gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC1_GAIN",1}, "Osc1_Gain", juce::NormalisableRange<float>{0.0f, 0.5f,}, 0.25f));
    
    
    //oscillator 2
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"OSC2_WAVE",1}, "Osc2_Waveform", juce::StringArray{"Sine","Saw","Square"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC2_TUNE",1}, "Osc2_Tune", coarseRange, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC2_FINE",1}, "Osc2_FineTune", fineRange, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC2_PW",1}, "Osc2_PulseWidth", juce::NormalisableRange<float>{0.0f, 0.9f,}, 0.0f));
    // osc2 AR envelope
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC2_ATTACK",1}, "Osc2_Attack", juce::NormalisableRange<float>{0.01f, 4.0f,}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC2_RELEASE",1}, "Osc2_Release", juce::NormalisableRange<float>{0.01f, 2.0f,}, 0.5f));
    //gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"OSC2_GAIN",1}, "Osc2_Gain", juce::NormalisableRange<float>{0.0f, 0.5f,}, 0.25f));
    
    // Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>(juce::ParameterID{"FILTER_TYPE",1}, "FilterType", juce::StringArray{"Low-Pass","Band-Pass","High-Pass"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FILTER_CUTOFF",1}, "FilterCutoff", juce::NormalisableRange<float>{20.0f, 20000.0f, 0.1f, 0.6f}, 20000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FILTER_RESONANCE",1}, "FilterResonance", juce::NormalisableRange<float>{1.0f, 15.0f,}, 1.0f));

    // filter ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FILTER_ATTACK",1}, "Filter Attack", juce::NormalisableRange<float>{0.01f, 2.0f,}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FILTER_DECAY",1}, "Filter Decay", juce::NormalisableRange<float>{0.01f, 1.0f,}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FILTER_SUSTAIN",1}, "Filter Sustain", juce::NormalisableRange<float>{0.01f, 1.0f,}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"FILTER_RELEASE",1}, "Filter Release", juce::NormalisableRange<float>{0.01f, 3.0f,}, 0.5f));
    
    //Volume
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID{"VOLUME",1}, "Output Volume", juce::NormalisableRange<float>{0.01f, 1.0f,}, 0.505f));
    
    return {params.begin(),params.end()};
    
}

