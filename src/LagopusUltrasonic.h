#include "utils/RS485.h"
#include "LsPinAssign.h"

RS485 Sensor;

class LagopusUltrasonic
{
private:
  RS485 ultrasonic;
public:
  LagopusUltrasonic(/* args */);
  ~LagopusUltrasonic();
  bool initUltrasonic();

};



