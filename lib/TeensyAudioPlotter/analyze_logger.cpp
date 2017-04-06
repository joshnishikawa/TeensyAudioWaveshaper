#include "analyze_logger.h"

void AudioAnalyzeLogger::update(void)
{
	audio_block_t *block;
	block = receiveReadOnly();
  if (!block) return;

  for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
    lastBlock[i] = block->data[i];
  }

  transmit(block);
  release(block);
}
