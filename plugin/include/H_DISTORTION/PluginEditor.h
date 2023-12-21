#pragma once

#include "PluginProcessor.h"

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor, private juce::Slider::Listener, private juce::Slider::RotaryParameters, private juce::ComboBox::Listener
{
public:
    explicit AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    juce::ComboBox disChoice;
    void comboBoxChanged(juce::ComboBox *comboBox) override;
    void sliderValueChanged(juce::Slider *slider) override;
    AudioPluginAudioProcessor &processorRef;
    juce::Slider Threshold;
    juce::Label ThreshLabel;
    juce::Slider Mix;
    juce::Label MixLabel;
    juce::Slider PostGain;
    juce::Label PostGainLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
