DA8568C
=======

DA8568C Arduino Library

This Library is based on the code from crx091081gb:
http://registeringdomainnamesismorefunthandoingrealwork.com/blogs/?p=51
thanks a lot!

It is written for TI DA8568C and probably also usable with the AD5668 16 Bit DAC.

I've tested the code on the Arduino Duemilanove Platform using just the Chip,
connected as written in the comments of the header file and validating it with
and DVM.

You will find a very basic and simple example in the examples folder. This sketch simply outputs an increasing integer to all DAC outputs (as well as to the serial line)- you can measure them using an DVM or similar.

