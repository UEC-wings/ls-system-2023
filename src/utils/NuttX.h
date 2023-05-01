#ifndef NuttX_h
#define NuttX_h
#include "Arduino.h"

enum NutStatus
{
  NUTTX_NOT_FOUND = -1,
  NUTTX_PLAY = 0,
  NUTTX_BUSY = 1
};

class NuttX
{
  public:
    void init(Stream &stream);
    NutStatus play(String filename);
    void stop();
    void pause();
    void resume();
    bool isplaying();
  private:
    Stream* _serial;
    String str;
    unsigned long lasttime_play = 0;
    unsigned long interval_play = 100;
};

#endif
