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

    // these define the parameters of our slider object
    juce::String options[3] = {"Hard Clip", "Soft Clip", "Half-Wave Rect"};

    disChoice.addItem(options[0], 1);
    disChoice.addItem(options[1], 2);
    disChoice.addItem(options[2], 3);
    disChoice.addListener(this);
    disChoice.setSelectedId(1);

    // this function adds the choice to the editor
    addAndMakeVisible(&disChoice); // 1

    addAndMakeVisible(&Threshold);
    Threshold.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    // Threshold.setRotaryParameters(-1 * (4 * juce::MathConstants<float>::pi) / 3, (5 * juce::MathConstants<float>::pi) / 6, true);
    Threshold.setRange(0.0f, 1.0f, 0.001);
    Threshold.addListener(this);

    addAndMakeVisible(&Mix);
    Mix.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    Mix.setRange(0.0f, 1.0f, 0.001);
    Mix.addListener(this);
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
    disChoice.setBounds(50, 50, 200, 50); // 2
    Threshold.setBounds(50, 100, 200, 50);
    Mix.setBounds(50, 150, 200, 50);
}

void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g)
{
    // fill the whole window white
    g.fillAll(juce::Colours::white);

    // set the current drawing colour to black
    g.setColour(juce::Colours::black);

    // set the font size and draw text to the screen
    g.setFont(15.0f);
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
}
