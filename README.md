# Arduino-RFID-Wiegand-
This sketch works with a wiegand RFID reader to control door access.

The external file RFIDkeys.h just contains an array of the keys used for the system. Add new keys to this file once you find out the key by scanning a RFID card.

It requires this library: https://github.com/paulo-raca/YetAnotherArduinoWiegandLibrary

### To-DO:
Add MySensor functions (https://www.mysensors.org/) to interface via radio link to a home automation server.
