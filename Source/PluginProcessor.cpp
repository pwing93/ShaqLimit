/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ShaqLimitAudioProcessor::ShaqLimitAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

ShaqLimitAudioProcessor::~ShaqLimitAudioProcessor()
{
}

//==============================================================================
const String ShaqLimitAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ShaqLimitAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ShaqLimitAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ShaqLimitAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ShaqLimitAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ShaqLimitAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ShaqLimitAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ShaqLimitAudioProcessor::setCurrentProgram (int index)
{
}

const String ShaqLimitAudioProcessor::getProgramName (int index)
{
    return {};
}

void ShaqLimitAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ShaqLimitAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    delayBuffer = CircularBuffer(10, 1);
    allBuffers = Array<CircularBuffer>();
    
    for (int channel = 0; channel < getTotalNumOutputChannels(); channel++)
    {
        allBuffers.add(CircularBuffer(10,1));
    }

    gain = 1.0f;
    xPeak = 0.0f;
}

void ShaqLimitAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ShaqLimitAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void ShaqLimitAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    //auto* data = buffer.getWritePointer(0);

    //declaration and initialization of parameter variables
    float coeff;
    
    
    for (int i = 0; i < buffer.getNumSamples(); i++)
    {
        for (int channel = 0; channel < getTotalNumOutputChannels(); channel++)
        {
            auto* data = buffer.getWritePointer(channel);
            CircularBuffer* delayBuffer = &allBuffers.getReference(channel);
            
            //get current sample and find its absolute value to find amplitude
            float sample = data[i];
            float amplitude = abs(sample);
            
            if (amplitude < xPeak) coeff = attackTime;
            else coeff = releaseTime;
            
            xPeak = (1 - coeff) * xPeak + coeff * amplitude;
            
            float filter = fmin(1.0f, limiterThresh / xPeak);
            
            if (gain > filter) coeff = attackTime;
            else coeff = releaseTime;
            
            gain = (1 - coeff) * gain + coeff * filter;
            
            float limitedSample = gain * delayBuffer->getData();
            delayBuffer->setData(sample);
            delayBuffer->nextSample();
            
            data[i] = limitedSample;
            
            data[i] = data[i] * oGain;
        }
    }
}

//==============================================================================
bool ShaqLimitAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* ShaqLimitAudioProcessor::createEditor()
{
    return new ShaqLimitAudioProcessorEditor (*this);
}

//==============================================================================
void ShaqLimitAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ShaqLimitAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ShaqLimitAudioProcessor();
}
