#include "H_DISTORTION/PluginProcessor.h"
#include "H_DISTORTION/PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
    : AudioProcessorEditor(&p), processorRef(p)
{
    juce::ignoreUnused(processorRef);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(500, 500);

    // these define the parameters of our slider object
    juce::String options[3] = {"Hard Clip", "Soft Clip", "Half-Wave Rect"};

    addAndMakeVisible(&disChoice); // 1
    disChoice.addItem(options[0], 1);
    disChoice.addItem(options[1], 2);
    disChoice.addItem(options[2], 3);
    disChoice.addListener(this);
    disChoice.setSelectedId(1);

    // this function adds the choice to the editor

    addAndMakeVisible(&Threshold);
    Threshold.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    Threshold.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, Threshold.getTextBoxHeight());
    Threshold.setRange(0.0f, 1.0f, 0.001);
    Threshold.addListener(this);

    addAndMakeVisible(&ThreshLabel);
    ThreshLabel.setText("Threshold", juce::NotificationType::dontSendNotification);
    ThreshLabel.setJustificationType(juce::Justification::centredBottom);
    ThreshLabel.attachToComponent(&Threshold, false);

    addAndMakeVisible(&Mix);
    Mix.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    Mix.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, Mix.getTextBoxHeight());
    Mix.setRange(0.0f, 1.0f, 0.001);
    Mix.addListener(this);

    addAndMakeVisible(&MixLabel);
    MixLabel.setText("Mix", juce::NotificationType::dontSendNotification);
    MixLabel.setJustificationType(juce::Justification::centredBottom);
    MixLabel.attachToComponent(&Mix, false);

    addAndMakeVisible(&PostGain);
    PostGain.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    PostGain.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, Mix.getTextBoxHeight());
    PostGain.setRange(-60.0f, 24.0f, 0.01);
    PostGain.setTextValueSuffix(" dB");
    PostGain.addListener(this);

    addAndMakeVisible(&PostGainLabel);
    PostGainLabel.setText("Post Gain", juce::NotificationType::dontSendNotification);
    PostGainLabel.setJustificationType(juce::Justification::centredBottom);
    PostGainLabel.attachToComponent(&PostGain, false);
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
    disChoice.setBounds(100, 50, 300, 100); // 2
    Mix.setBounds(30, 320, 130, 120);
    Threshold.setBounds(190, 220, 130, 120);
    PostGain.setBounds(350, 320, 130, 120);
}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g)
{
    // fill the whole window white
    g.fillAll(juce::Colours::darkgrey);

    // set the current drawing colour to black
    g.setColour(juce::Colours::white);

    // set the font size and draw text to the screen
    g.setFont(20.0f);
}

void AudioPluginAudioProcessorEditor::comboBoxChanged(juce::ComboBox *comboBox)
{
    processorRef.menuChoice = comboBox->getSelectedId();
}

void AudioPluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if (&Mix == slider)
    {
        processorRef.mix = Mix.getValue();
    }
    if (&Threshold == slider)
    {
        processorRef.thresh = Threshold.getValue();
    }
    if (&PostGain == slider)
    {
        processorRef.post_gain = juce::Decibels::decibelsToGain((float)PostGain.getValue());
    }
}
