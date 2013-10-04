/*
 * Library for using the TI DA8568C and (yet untested) the AD5668
 * Created by Stephan Bergemann, October 4, 2013
 * based on the code by crx091081gb:
 * http://registeringdomainnamesismorefunthandoingrealwork.com/blogs/?p=51
 */

#ifndef _DA8568C_H_
#define _DA8568C_H_

#include "Arduino.h"

//AD5668 Command definitions
#define WRITE 0
#define UPDATE 1
#define WRITE_UPDATE_ALL 2
#define WRITE_UPDATE_N 3
#define POWER 4
#define LOAD_CC_REG 5
#define LOAD_LDAC_REG 6
#define RESET 7
#define SETUP_INTERNAL_REGISTER 8

/*
 * DA8568C Class to communicate with the TI DA8568C and probably also the AD5668
 */
class DA8568C {
  public:
    
    // Default Pins:
    //    DATAOUT     PIN 3  -- (MOSI)              --> DIN  Pin 15 on DA8568C
    //    SPICLK      PIN 4  -- (SCLK)              --> SCLK Pin 16 on DA8568C
    //    SLAVESELECT PIN 5  -- (SS)                --> SYNC Pin  2 on DA8568C
    //    LDAC        PIN 6  -- (Load DACs)         --> LDAC Pin  1 on DA8568C
    //    CLR         PIN 7  -- (Async Clear Input) --> CLR  Pin  9 on DA8568C
    DA8568C(int dataoutpin=3, int spiclkpin=4, int slaveselectpin=5, int ldacpin=6, int clrpin=7);
    
    // Initialization of the DA8568C (takes some time)
    void init();
    
    // interfacing method
    void write(byte command, byte address, unsigned int data);
    
    // The DA8568 as well as the AD5668 provide internal reference currents, that
    // can be enabled to produce exact voltages per integer.
    // This on-board reference is off by default to allow the usage of an external
    // reference (connected to the VREF PIN (8).
    // If you don't provide that external reference it is highly recommended
    // to turn this internal reference on and leave Pin 8 diconnected.
    void enable_internal_ref();
    
    // Disable the mentioned internal reference (this method is more for completeness
    // than for actual being used :D ... as the internal reference is turned off by
    // default already)
    void disable_internal_ref();

  private:
    void output_bytes(byte b1, byte b2, byte b3, byte b4, boolean ldacswitch=false);
    int _dataoutpin;
    int _spiclkpin;
    int _slaveselectpin;
    int _ldacpin;
    int _clrpin;
};

#endif
