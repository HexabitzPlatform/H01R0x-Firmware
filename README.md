## H01R00 Module ##

**H01R00 is a smart RGB LED module** based on Cree CLVBA-FKA-CC1F1L1BB7R3R3 RGB LED and STM32F0 MCU. It is part of the upcoming Hexabitz modular prototyping system.

- Use as a stand-alone smart RGB LED and easily control via a Command Line Interface (CLI).
- Firmware has embedded on / off / toggle, PWM, dimming and color sweep functionality.
- Program advanced C code with our easy-to-use APIs.
- Connect many H01R00 modules together and build interesting flat and curved boards with any configuration you imagine!
- Send commands to a single LED, a group of LEDs or broadcast to all of them at the same time.
- Connect to external hardware or combine with other Hexabitz modules!

===============================================

## About Hexabitz ##

Hexabitz is a new kind of electronic prototyping platforms with game-changing modularity and a hint of biomimicry. Hexabitz modules connect with each other using a novel edge-soldering system and allow you to build tidy, compact and completely re-configurable electronic boards. **Learn more about Hexabitz [here](https://www.hexabitz.com/)**.

===============================================

## Technical Specifications ##

- Six array ports and six power ports (+3.3V and GND). 

- Access to 6xUART, 2xI2C, SWD, BOOT0, RESET.

- Cree CLVBA-FKA-CC1F1L1BB7R3R3 RGB LED:

 * Dominant Wavelength: Red (619 - 624nm) Green (520 - 540nm) Blue (460 - 480nm).

 * Luminous Intensity (mcd) @IF=20mA: Red (224 - 560) Green (280 - 900) Blue (90 - 355).

- STM32F091CBU6 32-bit ARM Cortex-M0 MCU.

- 8MHz external oscillator.

## Physical Properties ##

- **Shape**: Hexagon

- **Size**: 3 cm short diagonal

- **Area**: 7.8 cm^2

- **Soldermask Color**: Dark green

- **Finish**: ENIG (gold) or HASL-LF (tin)

===============================================

## Documentation ##
We developed a new form of documentation we call it the Factsheet: it's a mix between a hardware datasheet listing electrical properties and a software cheat-sheet showing you quickly the most important software functions and commands. Factsheets are color-coded and designed to be printed double-sided. We think they will come in handy for your Hexabitz projects. Let us know if you like them! 

- [Module factsheet](https://d3s5r33r268y59.cloudfront.net/datasheets/11566/2018-03-01-06-19-35/H01R00%20Factsheet.pdf)

## Design Files ##
- Module schematics [[PDF](https://www.dropbox.com/s/ouq9ytm361xokm2/H01R00%20Schematics.pdf?dl=0)]

===============================================

## FAQ ##

### Q: Isn't a 32-bit MCU an overkill for a smart LED module? ###
A: Yes! But all Hexabitz modules -whether it's a complex Ethernet or IMU or a simple LED- share same backend hardware and software. This what gives the platform its unmatched modularity and scalability. Cortex-M0 MCUs are small, cheap, power-efficient, yet capable of really wonderful things. Having an embedded MCU provides a cheaper and more compact alternative to connecting an LED breakout with an external controller.

### Q: What level of soldering experience is required? ###
A: Hexabitz are designed for the absolute soldering beginners! The edge pads are large and easy to reach and anyone with basic knowledge of soldering can assemble a flat array. Curved and spherical arrays require more training but can be made easier with 3d-printed fixtures.

Check our [website](https://www.hexabitz.com/faq/) for more information or contact us about any questions or feedback!

===============================================

## See also these repositories ##

- [H05R00]() - Micro-SD Memory Card Module

- [H09R00]() - 600VAC / 1.2A Solid State Relay Module

===============================================



# README #

This README would normally document whatever steps are necessary to get your application up and running.

### What is this repository for? ###

* Quick summary
* Version
* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

### How do I get set up? ###

* Summary of set up
* Configuration
* Dependencies
* Database configuration
* How to run tests
* Deployment instructions

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Repo owner or admin
* Other community or team contact