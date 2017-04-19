# TeensyAudioWaveshaper
Waveshaper effect for Teensy Audio. Almost complete.

![Waveshaper input vs output](https://github.com/dxinteractive/TeensyAudioWaveshaper/blob/master/docs/example2.gif)

Maps audio input to an output using a linearly interpolated lookup table. Useful for overdrive, distortion, fuzzes, clipping, expo converters, phase inversion, waveform modification and control wave adjustments.

### `waveshaper.shape(float* waveshape, int length);`
- **`waveshape`** is an array containing the values to map to. These are floats in the range -1.0 to 1.0 inclusive. An input value of -1.0 will map to the value of the first element of the array, and an input value of 1.0 will map to the value of the last element. All input values between these will be interpolated evenly across the values in the waveshape array.

- **`length`** must be equal to the length of the `waveshape` array, which must be of length n^2 + 1 where 0 <= n < 16. Therefore the following array lengths are permitted: 2, 3, 5, 9, 17, 33, 65, 129, 257, 513, 1025, 2049, 4097, 8193, 16385.

### Example usage

```c++
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "effect_waveshaper.h"

AudioSynthWaveform waveform;
AudioEffectWaveshaper waveshaper;
AudioOutputI2S output;

AudioConnection patchCord1(waveform, 0, waveshaper, 0);
AudioConnection patchCord2(waveshaper, 0, output, 0);
AudioControlSGTL5000 audioAdaptor;

float WAVESHAPE_EXAMPLE[17] = {
  -0.588,
  -0.579,
  -0.549,
  -0.488,
  -0.396,
  -0.320,
  -0.228,
  -0.122,
  0,
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
  AudioMemory(40);
  audioAdaptor.enable();
  waveform.begin(1.0, 200.0, WAVEFORM_SINE);
  waveshaper.shape(WAVESHAPE_EXAMPLE, 17);
}

void loop() {
}
```
