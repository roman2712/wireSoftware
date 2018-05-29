#include "wireSoftware.h"

wireSoftware::wireSoftware(int _SDA_pin, int _SCL_pin)
{
  SDA_pin = _SDA_pin;
  SCL_pin = _SCL_pin;

  pin_one(SDA_pin);
  pin_one(SCL_pin);

  stop();
}

void wireSoftware::pin_null(byte pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void wireSoftware::pin_one(byte pin)
{
  pinMode(pin, INPUT);
}

byte wireSoftware::pin_read(byte pin)
{
  return digitalRead(pin);
}

void wireSoftware::start()
{
  pin_one(SCL_pin);
  pin_one(SDA_pin);
  pin_null(SDA_pin);
  pin_null(SCL_pin);
}

void wireSoftware::restart()
{
  pin_one(SDA_pin);
  pin_one(SCL_pin);
  pin_null(SDA_pin);
  pin_null(SCL_pin);
}

void wireSoftware::stop()
{
  pin_null(SDA_pin);
  pin_null(SCL_pin);
  pin_one(SCL_pin);
  pin_one(SDA_pin);
}

void wireSoftware::send_bit(byte b)
{
  if (b) pin_one(SDA_pin);
  else pin_null(SDA_pin);
  pin_one(SCL_pin);
  pin_null(SCL_pin);
}

byte wireSoftware::read_bit()
{
  pin_one(SDA_pin);
  pin_one(SCL_pin);
  while (!pin_read(SCL_pin));
  byte SDA = pin_read(SDA_pin);
  pin_null(SCL_pin);
  return SDA;
}

byte wireSoftware::send(byte data)
{
  for (byte i = 0; i < 8; ++i)
  {
    send_bit(data & 0x80);
    data = data << 1;
  }
  return read_bit();
}

byte wireSoftware::read(byte a)
{
  byte data = 0;
  for (byte i = 0; i < 8; ++i)
  {
    data = data << 1;
    data |= read_bit();
  }
  send_bit(a);
  return data;
}