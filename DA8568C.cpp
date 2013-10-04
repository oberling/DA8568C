#include "DA8568C.h"

#define TOGGLE_LDAC true

DA8568C::DA8568C(int dataoutpin, int spiclkpin, int slaveselectpin, int ldacpin, int clrpin)
: _dataoutpin(dataoutpin), _spiclkpin(spiclkpin), _slaveselectpin(slaveselectpin),
_ldacpin(ldacpin), _clrpin(clrpin)
{
  pinMode(_dataoutpin, OUTPUT);
  pinMode(_spiclkpin, OUTPUT);
  pinMode(_slaveselectpin, OUTPUT);
  pinMode(_ldacpin, OUTPUT);
  pinMode(_clrpin, OUTPUT);
}

void DA8568C::init() {
  //disable DAC to start with
  digitalWrite(_dataoutpin,LOW);
  digitalWrite(_spiclkpin, LOW);
  digitalWrite(_slaveselectpin, LOW);
  digitalWrite(_ldacpin, HIGH);
  digitalWrite(_clrpin, LOW);
  // TODO: probably these delays can be shortened...
  delay(500);
  digitalWrite(_clrpin, HIGH);
  delay(500);
  delay(1000);
  write(SETUP_INTERNAL_REGISTER, 0, 1); //set up internal register on DAC
  delay(1000);
  write(POWER, 0, 0);
  delay(1000);
  write(RESET, 0, 0);
  delay(1000);
}

void DA8568C::output_bytes(byte b1, byte b2, byte b3, byte b4, boolean ldacswitch) {
  digitalWrite(_slaveselectpin, LOW);
  delayMicroseconds(1);
  shiftOut(_dataoutpin, _spiclkpin, MSBFIRST, b1);
  shiftOut(_dataoutpin, _spiclkpin, MSBFIRST, b2);
  shiftOut(_dataoutpin, _spiclkpin, MSBFIRST, b3);
  shiftOut(_dataoutpin, _spiclkpin, MSBFIRST, b4);
  delayMicroseconds(1);
  if(ldacswitch) {
    digitalWrite(_ldacpin, LOW);
    delayMicroseconds(1);
    digitalWrite(_ldacpin, HIGH);
    delayMicroseconds(1);
  }
  digitalWrite(_slaveselectpin, HIGH);
}

void DA8568C::write(byte command, byte address, unsigned int data) {
  switch (command) {
    case WRITE_UPDATE_N:
    {
      byte b1 = B00000000|command; //padding at beginning of byte 1
      byte b2 = address << 4 | data >> 12; //4 address bits and 4 MSBs of data
      byte b3 = (data << 4) >> 8; // middle 8 bits of data
      byte b4 = (data << 12) >> 8 | B00001111;
      output_bytes(b1, b2, b3, b4, TOGGLE_LDAC);
      break;
    }
    case SETUP_INTERNAL_REGISTER:
    {
      byte b1 = B00001000; //padding at beginning of byte
      byte b2 = B00000000;
      byte b3 = B00000000;
      byte b4 = B00000000|data;
      output_bytes(b1, b2, b3, b4);
      break;
    }
    case RESET:
    {
      byte b1 = B00000111; //padding at beginning of byte
      byte b2 = B00000000;
      byte b3 = B00000000;
      byte b4 = B00000000|data;
      output_bytes(b1, b2, b3, b4);
      break;
    }
    case POWER:
    {
      byte b1 = B00000100; //padding at beginning of byte
      byte b2 = B00000000;
      byte b3 = B00000000;
      byte b4 = B11111111;
      output_bytes(b1, b2, b3, b4);
      break;
    }
  }
}

void DA8568C::enable_internal_ref() {
  // 08 00 00 01:
  byte b1 = B00001000;
  byte b2 = B00000000;
  byte b3 = B00000000;
  byte b4 = B00000001;
  output_bytes(b1, b2, b3, b4);
}

void DA8568C::disable_internal_ref() {
  // 08 00 00 00:
  byte b1 = B00001000;
  byte b2 = B00000000;
  byte b3 = B00000000;
  byte b4 = B00000000;
  output_bytes(b1, b2, b3, b4);
}
