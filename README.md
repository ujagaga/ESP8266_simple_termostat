# ESP8266_simple_termostat
This is my solution for not too minimal, but still simple enough WiFi thermostat. I use it to maintain temperature of a miniature oven for drying silica gel. Since it only has one purpose, the temeparture is fixed, but it would not be much effort to make it adjustable. I added the Over The Air update to easilly update the firmware via WiFi. This means that you have to upload the code once and then for all adjustments, in your web browser go to "/start_ota_update/" page to trigger the OTA server. The ESP will create its own wifi AP, so you will need to connect to it first.

## Dependencies 
Arduino linraries: "OneWire", "DallasTemperature", "ArduinoOTA", "ESP8266WebServer"

## Hardware
ESP8266-01 or any ESP8266 general module, voltage stabilizer 3V3, Relay or Thyristor to activate a heater. Most triacs require over 20mA to trigger, but ESP8266 can only supply up to 12mA, so I am using TIC206 because of extremelly low gate trigger current.

NOTE: Without the capacitor on the triac gate, the wifi connection is dropped when the triac is turned off. I am using ESP-01. Other modules may not experience this same bahaviour.

## Oven construction
Just FYI in case you need it for the same thing, here is the oven description. 
The internal oven size is about 15x15x6cm. I used a tin box of chocolates for the internal box. For temperature isolation I use 6mm of cardboard and fibreboard. It can take up to 200 degrees celsius before it burns. 
The external box is made od plastic panels. 
I used brass wire for the grid to hold silica gel bags in the center of the oven. 
The heater is a 40W halogen light bulb, but a 20W bulb would suffice.

## PLA drybox
I also use this same construction for a PLA drybox keeping the temperature at 60 degrees Celsius. It consists of a plastic box containing a single PLA spool, a 30mm 5V fan to keep air flowing over a 40W halogen light bulb to keep the air warm. 

## Contact
ujagaga@gmail.com
