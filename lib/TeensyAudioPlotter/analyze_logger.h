#ifndef analyze_logger_h_
#define analyze_logger_h_

#include "Arduino.h"
#include "AudioStream.h"

class AudioAnalyzeLogger : public AudioStream
{
  public:
    AudioAnalyzeLogger(void): AudioStream(1, inputQueueArray) {}
    virtual void update(void);
    int16_t lastBlock[AUDIO_BLOCK_SAMPLES];
  private:
    audio_block_t *inputQueueArray[1];
};

#endif