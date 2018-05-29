#ifndef WIRESOFTWARE_H_
#define WIRESOFTWARE_H_

#define ASK   0
#define NOASK   1

#ifdef ARDUINO
#if ARDUINO < 100
#include "WProgram.h"
#else
#include "Arduino.h"
#endif
#else
#include "ArduinoWrapper.h"
#endif

class wireSoftware {
	
  public:
    wireSoftware(int _SDA_pin, int _SCL_pin);
    void start();
    void restart();
    void stop();
    byte read(byte a);
    byte send(byte a);

  private:
    byte SCL_pin;
    byte SDA_pin;
    void pin_null(byte pin);
    void pin_one(byte pin);
    byte pin_read(byte pin);
    void send_bit(byte b);
    byte read_bit();
};

#endif
