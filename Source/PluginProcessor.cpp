/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ArdynsBitcrusherAudioProcessor::ArdynsBitcrusherAudioProcessor()
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
    state = new AudioProcessorValueTreeState(*this, nullptr);

    state->createAndAddParameter("bitDepth", "BitDepth", "BitDepth", NormalisableRange<float>(8, 128, 1), 8, nullptr, nullptr);
    state->createAndAddParameter("blend", "Blend", "Blend", NormalisableRange<float>(0.f, 1.f, 0.001), 1.f, nullptr, nullptr);

    state->state = ValueTree("bitDepth");
    state->state = ValueTree("blend");
}

ArdynsBitcrusherAudioProcessor::~ArdynsBitcrusherAudioProcessor()
{
}

//==============================================================================
const String ArdynsBitcrusherAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ArdynsBitcrusherAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ArdynsBitcrusherAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ArdynsBitcrusherAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ArdynsBitcrusherAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ArdynsBitcrusherAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ArdynsBitcrusherAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ArdynsBitcrusherAudioProcessor::setCurrentProgram (int index)
{
}

const String ArdynsBitcrusherAudioProcessor::getProgramName (int index)
{
    return {};
}

void ArdynsBitcrusherAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ArdynsBitcrusherAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ArdynsBitcrusherAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ArdynsBitcrusherAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ArdynsBitcrusherAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; i++)
        buffer.clear(i, 0, buffer.getNumSamples());

    int bitDepth = *state->getRawParameterValue("bitDepth");
    float blend = *state->getRawParameterValue("blend");

    for(int channel = 0; channel < buffer.getNumChannels(); channel++)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for(int sample = 0; sample < buffer.getNumSamples(); sample++)
        {
            float modSig = *channelData;
            modSig *= bitDepth;
            modSig = roundFloatToInt(modSig);
            modSig /= bitDepth;
            *channelData = (blend * modSig) + ((1 - blend) * (*channelData));

            channelData++;
        }
    }
}

//==============================================================================
bool ArdynsBitcrusherAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ArdynsBitcrusherAudioProcessor::createEditor()
{
    return new ArdynsBitcrusherAudioProcessorEditor (*this);
}

//==============================================================================
void ArdynsBitcrusherAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    MemoryOutputStream stream(destData, false);
    state->state.writeToStream(stream);
}

void ArdynsBitcrusherAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    ValueTree tree = ValueTree::readFromData(data, sizeInBytes);
    if (tree.isValid()) {
        state->state = tree;
    }
}

AudioProcessorValueTreeState& ArdynsBitcrusherAudioProcessor::getState() {
    return *state;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ArdynsBitcrusherAudioProcessor();
}
