#include "H_DISTORTION/PluginProcessor.h"
#include "H_DISTORTION/PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    juce::ignoreUnused(processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(200, 200);

    // add the listener to the slider
    distortionGain.addListener(this);

    // these define the parameters of our slider object
    distortionGain.setSliderStyle(juce::Slider::LinearBarVertical);
    distortionGain.setRange(0.0, 127.0, 1.0);
    distortionGain.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    distortionGain.setPopupDisplayEnabled(true, false, this);
    distortionGain.setTextValueSuffix(" Volume");
    distortionGain.setValue(1.0);

    // this function adds the slider to the editor
    addAndMakeVisible(&distortionGain);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // sets the position and size of the slider with arguments (x, y, width, height)
    distortionGain.setBounds(40, 30, 20, getHeight() - 60);
}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g)
{
    // fill the whole window white
    g.fillAll(juce::Colours::white);

    // set the current drawing colour to black
    g.setColour(juce::Colours::black);

    // set the font size and draw text to the screen
    g.setFont(15.0f);

    g.drawFittedText("Distortion Gain", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    processorRef.noteOnVelocity = distortionGain.getValue();
}
