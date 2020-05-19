/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "FilmStripSlider.h"

//==============================================================================
/**
*/
class ShaqLimitAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ShaqLimitAudioProcessorEditor (ShaqLimitAudioProcessor&);
    ~ShaqLimitAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ShaqLimitAudioProcessor& processor;
    Slider thresh, at, rt, outGain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShaqLimitAudioProcessorEditor)
};
