/*
  ==============================================================================

    AdsrData.cpp
    Created: 6 Jul 2024 5:07:33pm
    Author:  Joe Paller

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateADSR (const float attack, const float decay, const float sustain, const float release)
{
    AdsrParams.attack = attack;
    AdsrParams.decay = decay;
    AdsrParams.sustain = sustain;
    AdsrParams.release = release;
    setParameters(AdsrParams);
}

void ARData::updateAR(const float attack, const float release)
{
    AdsrParams.attack = attack;
    AdsrParams.release = release;
    AdsrParams.decay = 0.1f;
    AdsrParams.sustain = 1.0f;
    setParameters(AdsrParams);
}
