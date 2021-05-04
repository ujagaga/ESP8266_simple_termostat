# ESP8266_simple_termostat
This is my solution for not too minimal, but still simple enough WiFi thermostat. I use it to maintain temperature of a miniature oven for drying silica gel. Since it only has one purpose, the temeparture is fixed, but it would not be much effort to make it adjustable. I added the Over The Air update to easilly update the firmware via WiFi. Just go to "/start_ota_update/" page to trigger the OTA server.

## Dependencies 
Arduino linraries: "OneWire", "DallasTemperature", "ArduinoOTA", "ESP8266WebServer"

## Hardware
ESP8266-01 or any ESP8266 general module, voltage stabilizer 3V3, Relay or Thyristor to activate a heater. Most triacs require over 20mA to trigger, but ESP8266 can only supply up to 12mA, so I am using TIC206 because of extremelly low gate trigger current.

NOTE: I had the code working and temperature was properly displayed, but the moment I connected the triac, the ESP module would not boot. 
It took adding R3 to 3V3 to get it to work. I could not find the reason for this, so if you do, please let me know.

## Oven construction
Just FYI in case you need it for the same thing, here is the oven description. 
The internal oven size is about 15x15x6cm. I used a tin box of chocolates for the internal box. For temperature isolation I use 6mm of cardboard and fibreboard. It can take up to 200 degrees celsius before it burns. 
The external box is made od plastic panels. 
I used brass wire for the grid to hold silica gel bags in the center of the oven. 
The heater is a 40W halogen light bulb, but a 20W bulb would suffice.

## Contact
ujagaga@gmail.com
