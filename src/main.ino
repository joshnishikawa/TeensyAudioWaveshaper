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

float WAVESHAPE_INVERT[2] = {
  1.0,
  -1.0
};

float WAVESHAPE_UNIPOLAR[2] = {
  0.0,
  1.0
};

float WAVESHAPE_EXAMPLE[17] = {
  -0.588,
  -0.579,
  -0.549,
  -0.488,
  -0.396,
  -0.320,
  -0.228,
  -0.122,
  0.0,
  0.122,
  0.228,
  0.320,
  0.396,
  0.488,
  0.549,
  0.579,
  0.588
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
  plotter.done();
}
