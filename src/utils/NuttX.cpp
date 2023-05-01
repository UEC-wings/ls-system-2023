#include "NuttX.h"

void NuttX::init(Stream &stream)
{
  _serial = &stream;
  do {
    _serial->println("");
    str = _serial->readStringUntil('>');
  } while ((str.lastIndexOf("nsh") == -1) && (str.lastIndexOf("nxplayer") == -1));
  do {
    _serial->println("nxplayer");
    str = _serial->readStringUntil('>');
  } while (str.lastIndexOf("nxplayer") == -1);
}

NutStatus NuttX::play(String filename)
{
  while (interval_play > millis() - lasttime_play);
  String temp = "play ";
  temp.concat(filename);
  do {
    _serial->println(temp);
    str = _serial->readStringUntil('>');
  } while (str.lastIndexOf("nxplayer") == -1);

  lasttime_play = millis();
  if (str.lastIndexOf("busy") != -1)//Audio device busy
  {
    return NUTTX_BUSY;
  }
  else if (str.lastIndexOf("not found") != -1)
  {
    return NUTTX_NOT_FOUND;
  }
  return NUTTX_PLAY;
}

void NuttX::stop()
{
  do {
    _serial->println("stop");
    str = _serial->readStringUntil('>');
  } while (str.lastIndexOf("nxplayer") == -1);
}

void NuttX::pause()
{
  do {
    _serial->println("pause");
    str = _serial->readStringUntil('>');
  } while (str.lastIndexOf("nxplayer") == -1);
}

void NuttX::resume()
{
  do {
    _serial->println("resume");
    str = _serial->readStringUntil('>');
  } while (str.lastIndexOf("nxplayer") == -1);
}

bool NuttX::isplaying()
{
  while (interval_play > millis() - lasttime_play);
  do {
    _serial->println("play");
    str = _serial->readStringUntil('>');
  } while (str.lastIndexOf("nxplayer") == -1);

  lasttime_play = millis();
  if (str.lastIndexOf("busy") != -1)//Audio device busy
  {
    return 1;
  }
  return 0;
}
