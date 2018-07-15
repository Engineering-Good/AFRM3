.. Copyright 2018 Heiko Rothkranz
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
   http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

Software modification instructions
##################################

Comments were added directly in the source code in the hope that it will be
mostly self-explanatory.

This chapter is intended to provide an overview and additional information on
the most likely tasks.

.. _section-software-environment:

Setting up the Arduino development environment
**********************************************

The easiest way to develop for Arduino is to use the official "Arduino IDE" by
following the instructions on their website
(https://www.arduino.cc/en/Guide/HomePage).

.. _section-software-overview:

Overview
********

The source code begins with global configuration variables, named in ALL_CAPS.
These are intended to be easy to tweak in order to adapt the code to different
hardware or different environmental conditions.

Next is a section of global runtime variables and their initialisation. These
are used by the software during operation and probably don't need to be changed.

The Arduino software calls the ``setup()`` function first when the controller is
powered up. We use it to set up our input/output pins and to read the
configuration values from EEPROM storage.

After the ``setup()`` function finished, the ``loop()`` function (located at the
bottom of the source code file) is called periodically. The main programme logic
is controlled from here, but for better readability, we moved most of it into
separate functions, which are called from this loop.

.. _section-software-configuration:

Configuring for different flag poles
************************************

Different flag poles with different load on the AFRM3 usually require
configuration of different minimum PWM values for start up of the motor and for
continuous operation. If these are set too low, the motor might stall. If they
are set too high, you are limiting the range in which the speed controller can
operate and thus the flag may reach the end of the pole too fast.

The minimum PWM values can be configured near the top of the source code, e.g.:

.. code-block:: c
   
   const unsigned int MIN_PWM_START_UP = 160;
   const unsigned int MIN_PWM_CONT_UP = 125;
   const unsigned int MIN_PWM_START_DOWN = 110;
   const unsigned int MIN_PWM_CONT_DOWN = 75;

A stripped down, simplified version of the AFRM3 version is provided with the
"Testmodes" code. Using the "Testmodes" software, the motor operation only
depends on the position of the direction switch and the value of TEST_PWM:

.. code-block:: c
   
   // test values
   const byte TEST_PWM = 80;

It can be used to make finding the minimum PWM values easier.

.. _section-software-motor-drivers:

Adapting to different motor drivers
***********************************

:ref:`Motor drivers <section-hardware-motor-driver>` with a different interface
may require changes to the software.

You may have to define different pins in the configuration section near the top
of the source code:

.. code-block:: c
   
   // Motor interface
   const int PIN_PWM_UP      = 9;
   const int PIN_PWM_DOWN    = 10;
   const int PIN_SLEEP       = 11; // not connected and without effect for DRV8835
   const int PIN_REFLECTANCE = 1; // use A1 for digital input; 1 for analog input.

And initialise them accordingly in the setup() function:

.. code-block:: c
   
   // setup digital pins; encoder pins are setup by the Encoder library
   pinMode(PIN_PWM_UP, OUTPUT);
   pinMode(PIN_PWM_DOWN, OUTPUT);
   pinMode(PIN_SLEEP, OUTPUT);
   
   // output safe states to start
   digitalWrite(PIN_PWM_UP, LOW);
   digitalWrite(PIN_PWM_DOWN, LOW);
   digitalWrite(PIN_SLEEP, LOW);

The code for interfacing the motor driver is then entirely contained within the
``stop_motor()`` and ``move_motor()`` functions, which may need to be adapted, too.

.. _section-software-position-sensors:

Adapting to different position sensors
**************************************

Adapting to a different reflectance sensor with analog output or just
calibrating it can be done by changing these calibration values:

.. code-block:: c
   
   // Encoder
   const int REFLECTANCE_THRESHOLD = 600; // ~2.9V
   const byte REFLECTANCE_HISTORY = 8; // use the last 8 reflectance values to determine reflectance; max. 8 if reflectance_bits is of type byte
   const byte REFLECTANCE_OUTLIERS = 2; // allow 2 bits in the reflectance history to be different

Changing to an entirely different encoder will probably require further changes.
Currently, the beginning of the ``loop()`` function contains the code to
evaulate the sensor signal and to determine the ``encoder_count`` value from it.

