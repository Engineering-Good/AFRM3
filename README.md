# Automated Flag Raising Machine 3 (AFRM3)

## Introduction

The aim of the Automated Flag Raising Machine (AFRM) is to allow students with
disabilities to participate in flag raising ceremonies. The AFRM3 is the third
iteration of a motorised machine to pull a flag rope at the push of a button.

It features a motor driven pulley to pull the flag rope. The pulley rotation is
monitored for speed control and to detect when the rope is stuck. The device is
controlled by an Arduino.

## Documentation

The full documentation is avaible [here as PDF](/Documentation/build/AFRM3.pdf).
It covers the User Guide, as well as how to build the hardware and modify the
software.

## Contributing

The main source code file is [/Code/AFRM3/AFRM3.ino](/Code/AFRM3/AFRM3.ino). The
other Arduino file, [/Code/Testmodes/Testmodes.ino](/Code/Testmodes/Testmodes.ino)
can be used to test and debug the button functionality, as well as determine
default speed settings.

Please keep the documentation up to date when modifying hardware or software.
This project is using [Sphinx](https://www.sphinx-doc.org) to generate HTML and
PDF versions of the documentation. In short, edit the reStructured Text (.rst)
in [/Documentation/source/](/Documentation/source/), and then run the included
Makefile to generate the documentation.

The schematics can be opened and edited using [KiCad](https://www.kicad.org/).