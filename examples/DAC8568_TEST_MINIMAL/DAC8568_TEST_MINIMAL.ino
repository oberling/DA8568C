#include <DA8568C.h>

DA8568C dac; // this implies using the PINs as defined in the Library
// otherwise use constructor arguments like
// DA8568C(int dataoutpin=3, int spiclkpin=4, int slaveselectpin=5, int ldacpin=6, int clrpin=7);

void setup() {
  dac.init();
  dac.enable_internal_ref();
  Serial.begin(9600);
}

unsigned int voltage=0;

void loop() {
  voltage+=1000;
  voltage %= 65535;
  for(int i=0; i<8; i++) {
    dac.write(WRITE_UPDATE_N, i, voltage);
  }
  Serial.println(voltage);
  delay(1000);
}
