/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ArdynsBitcrusherAudioProcessorEditor::ArdynsBitcrusherAudioProcessorEditor (ArdynsBitcrusherAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    addAndMakeVisible(bitDepthKnob = new Slider("bitDepthKnob"));
    bitDepthKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    bitDepthKnob->setSliderStyle(Slider::Rotary);
    bitDepthAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "bitDepth", *bitDepthKnob);

    addAndMakeVisible(blendKnob = new Slider("blendKnob"));
    blendKnob->setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    blendKnob->setSliderStyle(Slider::Rotary);
    blendAttachment = new AudioProcessorValueTreeState::SliderAttachment(p.getState(), "blend", *blendKnob);


    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

ArdynsBitcrusherAudioProcessorEditor::~ArdynsBitcrusherAudioProcessorEditor()
{
}

//==============================================================================
void ArdynsBitcrusherAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::ghostwhite);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    
    Rectangle<int> area = getLocalBounds();
    area = area.removeFromBottom(50);
    Rectangle<int> bitDepthTextArea = area.removeFromLeft(area.getWidth() / 2);
    Rectangle<int> blendTextArea = area;

    g.drawText("Bit Depth", bitDepthTextArea, Justification::centred);
    g.drawText("Dry/Wet", blendTextArea, Justification::centred);
}

void ArdynsBitcrusherAudioProcessorEditor::resized()
{
    Rectangle<int> area = getLocalBounds();
    int border = 50;

    area.reduced(border);
    bitDepthKnob->setBounds(area.removeFromLeft(area.getWidth() / 2));
    blendKnob->setBounds(area);
}
