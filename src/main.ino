#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <TeensyAudioPlotter.h>
#include "effect_waveshaper.h"

AudioSynthWaveform waveform;
AudioAnalyzeLogger dryLogger;
AudioEffectWaveshaper waveshaper;
AudioAnalyzeLogger wetLogger;
AudioOutputStepper stepper;

AudioConnection patchCord1(waveform, 0, dryLogger, 0);
AudioConnection patchCord2(dryLogger, 0, waveshaper, 0);
AudioConnection patchCord3(waveshaper, 0, wetLogger, 0);
AudioConnection patchCord4(wetLogger, 0, stepper, 0);

TeensyAudioPlotter plotter;

int16_t WAVESHAPE_INVERT[2] = {
  32767,
  -32768
};

int16_t WAVESHAPE_UNIPOLAR[2] = {
  32767,
  0
};

int16_t WAVESHAPE_EXAMPLE[17] = {
  -19300,
  -19000,
  -18000,
  -16000,
  -13000,
  -10500,
  -7500,
  -4000,
  0,
  4000,
  7500,
  10500,
  13000,
  16000,
  18000,
  19000,
  19300
};

void setup() {
  Serial.begin(9600);
  AudioMemory(40);

  plotter.setStepper(stepper);
  plotter.addLogger(dryLogger);
  plotter.addLogger(wetLogger);
  //plotter.continuous(false);

  waveform.begin(1.0, 200.0, WAVEFORM_SINE);
  waveshaper.shape(WAVESHAPE_EXAMPLE, 17);
}

void loop() {
  plotter.step();
  if(plotter.newBlock()) {
    Serial.print("(processorUsage)");
    Serial.println(waveshaper.processorUsage());
  }
  plotter.done();
}
