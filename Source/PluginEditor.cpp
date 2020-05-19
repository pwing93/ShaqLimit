/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"
//==============================================================================
ShaqLimitAudioProcessorEditor::ShaqLimitAudioProcessorEditor (ShaqLimitAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 221);
    
    
    //>>>>>>>>>>>>>>>>>>>>>>
    //>>>>>>>>>>>>>>>>>>>>>>
    //>>>>>>>>>>>>>>>>>>>>>
    Image ballKnob = ImageCache::getFromMemory (BinaryData::ballOrange_png, BinaryData::ballBlack_pngSize);
    //>>>>>>>>>>>>>>>>>>>>>>
    //>>>>>>>>>>>>>>>>>>>>>
    //>>>>>>>>>>>>>>>>>>>>>
    
    addAndMakeVisible(&thresh);
    thresh.setSliderStyle(Slider::Rotary);
    thresh.setTextValueSuffix(" Threshold");
    thresh.setPopupDisplayEnabled(true, true, this);
    thresh.setTextBoxStyle(Slider::NoTextBox, false, 90, 20);
    thresh.setValue(0);
    thresh.setRange(-60.0f, 0.0f, 0.01);
    thresh.onValueChange = [this]
    {
        processor.limiterThresh = std::pow(10, (thresh.getValue() / 20));
    };
    
    addAndMakeVisible(&at);
    at.setSliderStyle(Slider::Rotary);
    at.setTextValueSuffix(" Attack");
    at.setPopupDisplayEnabled(true, true, this);
    at.setTextBoxStyle(Slider::NoTextBox, false, 90, 20);
    at.setRange(0.01f, 10.0f, 0.01);
    at.onValueChange = [this]
    {
        processor.attackTime = 1 - std::pow(MathConstants<float>::euler, ((1 / processor.getSampleRate()) * -2.2f) / at.getValue());
    };
    
    addAndMakeVisible(&rt);
    rt.setSliderStyle(Slider::Rotary);
    rt.setTextValueSuffix(" Release");
    rt.setPopupDisplayEnabled(true, true, this);
    rt.setTextBoxStyle(Slider::NoTextBox, false, 90, 20);
    rt.setRange(0.01f, 10.0f, 0.01);
    rt.onValueChange = [this]
    {
        processor.releaseTime = 1 - std::pow(MathConstants<float>::euler, ((1 / processor.getSampleRate()) * -2.2f) / rt.getValue());
    };
    
    addAndMakeVisible(&outGain);
    outGain.setSliderStyle(Slider::Rotary);
    outGain.setTextValueSuffix(" Gain");
    outGain.setPopupDisplayEnabled(true, true, this);
    outGain.setTextBoxStyle(Slider::NoTextBox, false, 90, 20);
    outGain.setRange(-10.0f, 20.0f, 0.01);
    outGain.onValueChange = [this]
    {
        processor.oGain = std::pow(10, (outGain.getValue() / 20));
    };
}

ShaqLimitAudioProcessorEditor::~ShaqLimitAudioProcessorEditor()
{
}

//==============================================================================
void ShaqLimitAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    Image bGround = ImageCache::getFromMemory (BinaryData::shaqFlex_png, BinaryData::shaqFlex_pngSize);
    g.drawImageAt (bGround, 0, 0);
    

    g.setColour (Colours::goldenrod);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void ShaqLimitAudioProcessorEditor::resized()
{
    thresh.setBounds(0, 0, 90, 90);
    at.setBounds(0, 110, 90, 90);
    rt.setBounds(283, 0, 90, 90);
    outGain.setBounds(283, 110, 90, 90);
    
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

    

