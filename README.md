# TeensyAudioWaveshaper
Waveshaper effect for Teensy Audio. Almost complete.

![Waveshaper input vs output](https://github.com/dxinteractive/TeensyAudioWaveshaper/blob/master/docs/example2.gif)

Maps audio input to an output using a linearly interpolated lookup table. Useful for overdrive, distortion, fuzzes, clipping, expo converters, phase inversion, waveform modification and adjustments etc.

### `waveshaper.shape(int16_t* waveshape, int length);`
- **`waveshape`** is an array containing the values to map to. An input value of -32768 will map to the value of the first element of the array, and an input value of 32767 will map to the value of the last element. All input values between these will be interpolated evenly across the values in the waveshape array.

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
  AudioMemory(40);
  audioAdaptor.enable();
  waveform.begin(1.0, 200.0, WAVEFORM_SINE);
  waveshaper.shape(WAVESHAPE_EXAMPLE, 17);
}

void loop() {
}
```
