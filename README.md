# Arduino Unified Sensor Firmware
## Overview

This firmware for Arduino uses [unified sensor library](https://github.com/adafruit/Adafruit_Sensor) to gather data from sensors connected to Arduino and send them to PC via serial port. See [Arduino Sensor Monitor](https://github.com/vitaliy1919/Arduino-Sensors-Monitor-PC) to be able to get the data from sensors on PC.

## Usage
### Prerequisites
- Visual Studio Code with PlatformIO IDE extension (tested on v 1.8.3) installed

At first, the sensors need to be connected to Arduino either by IIC or directly to input ports.

Then you have to write/find a driver compatible with unified sensor library by Adafruit. The list of available drivers and information about library is available at the official Github [repository](https://github.com/adafruit/Adafruit_Sensor). 

For this project the drivers for Sparkfun ADXL335 accelerometer and Ivensense ITG3200 Gyroscope were written and can be used as an example.

### Sending data from sensors
At first the sensors need to be created.
``` c
IvensenseITG3200_Unified itg3200(1, 0x69);
Adafruit_Sensor *sensor[] = {
  new Spartkfun_ADXL345_Unified(0, A0, A1, A2),
  new IvensenseITG3200_Unified::Temperature(&itg3200),
  new IvensenseITG3200_Unified::Gyro(&itg3200)

};
```

Then, in `setup()` function, they need to be initialized:

``` c
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    sensor[i]->begin();
  }
}
```

Note, that `begin()` function is not standart for unified sensors, the library was slightly modified.

Finally, in the `loop()` function we need to send information to the serial port:
``` c
void loop() {
  sensors_event_t event;
  for (int i = 0; i < 3; i++) 
  {
    sensor[i]->getEvent(&event);
    writeEvent(&event);
    Serial.println();
  }
}
```

And that is all, now upload the firmware to Arduino and you are ready to receive the data on your PC.

## Important note
This project uses customized unified library, so you need to use it for your project, otherwise it will not work. However, in terms of writing drivers the differences are miniscule - you just need to provide additional `begin()` function that initialize a sensor.