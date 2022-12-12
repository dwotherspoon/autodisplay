# AutoDisplay

AutoDisplay is a work-in-progress project, this repository contains only the firmware. AutoDisplay aims to provide a solution for customisable digital displays for cars (particularly classic cars). It targets the Teensy 4.1 microcrontroller but may support others in the future.

## Wishlist/Planned Features
- Fully configurable gauges at run-time.
- Fully configurable displays at compile-time.
- Ability to connect to Speeduino or other ECU to obtain input data.
- Ability to sample speed sensor (by interrupt).
- Support for various sensors e.g. GPS (U-blox Neo), BME280 (Temperature, Humidity, Pressure) and analogue (e.g. resistive fuel and coolant sensors) etc. 
- Mobile app (Android) to configure displays by Bluetooth.
- Various PCB designs to fit within classic gauges (e.g. Smiths 4"/100mm and 5"/125mm gauges)
- Datalogging to SD functionality (from Speeduino).
- Support for writing mileage and trip distances to NVRAM (likely I2C FRAM).