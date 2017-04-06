/*
 * Waveshaper for Teensy 3.X audio
 *
 * Copyright (c) 2017 Damien Clarke, http://damienclarke.me
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef effect_waveshaper_h_
#define effect_waveshaper_h_

#include "Arduino.h"
#include "AudioStream.h"

class AudioEffectWaveshaper : public AudioStream
{
  public:
    AudioEffectWaveshaper(void): AudioStream(1, inputQueueArray) {}
    virtual void update(void);
    void shape(int16_t* waveshape, int length);
  private:
    audio_block_t *inputQueueArray[1];
    int16_t* waveshape;
    int16_t lerpshift;
};

#endif