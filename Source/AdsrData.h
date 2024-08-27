/*
  ==============================================================================

    AdsrData.h
    Created: 6 Jul 2024 5:07:33pm
    Author:  Joe Paller

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR(float attack, float decay, float sustain, float release);

private:
    juce::ADSR::Parameters AdsrParams;
};
