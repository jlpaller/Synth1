/*
  ==============================================================================

    Synth1Component.cpp
    Created: 26 Aug 2024 6:56:53pm
    Author:  Joe Paller

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Synth1Component.h"

//==============================================================================
Synth1Component::Synth1Component()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Synth1Component::~Synth1Component()
{
}

void Synth1Component::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("Synth1Component", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void Synth1Component::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void Synth1Component::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& valueTree, juce::String paramId, std::unique_ptr<SliderAttachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 0, 0);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<SliderAttachment>(valueTree, paramId, slider);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    //label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

using ComboAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
void Synth1Component::setComboBoxWithLabel(juce::ComboBox& combo, juce::Label& label, juce::AudioProcessorValueTreeState& valueTree, juce::String paramId, std::unique_ptr<ComboAttachment>& attachment, juce::StringArray choices)
{
    combo.addItemList(choices, 1);
    addAndMakeVisible(combo);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(valueTree, paramId, combo);
    
    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    //label.setFont(15.0f);
    label.setJustificationType(juce::Justification::left);
    addAndMakeVisible(label);
}
