#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <DNSServer.h>
#include <ArduinoOTA.h>

#define ONE_WIRE_BUS  2
#define HEATER_PIN    3   // UART RX
#define target        120
#define DNS_PORT      53

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
// arrays to hold device address
DeviceAddress insideThermometer;
static DNSServer dnsServer;
static ESP8266WebServer server(80);
static IPAddress apIP(192, 168, 4, 1);
float tempC = 0;
static bool updateStartedFlag = false;

static String html1 = "<!DOCTYPE HTML><html><head><title>Thermostat</title></head><body style=\"background-color:black;\"><center><p style=\"font-size:25vw;color:#FFC300;margin:0;\">";
static String html2 = "<span>&#8451;</span></p></center><script>setInterval(function(){location.reload();},3000);</script></body></html>";


void OTA_init() {

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);
  ArduinoOTA.setHostname("PLA_thermostat");  
   
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";
  });
  ArduinoOTA.onEnd([]() {
    updateStartedFlag = false;
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {

  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.print("Error: ");
    Serial.println(error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

  updateStartedFlag = true;
}

void handleRoot() {
  server.send(200, "text/html", html1 + String(tempC, 1) + html2);  
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found");
}

static void startOtaUpdate(void){
  OTA_init();    
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void setup(void)
{
  delay(100);   
//  Serial.begin(115200);
  sensor.begin();

  // Prepare the sensor
  Serial.print("Found ");
  Serial.print(sensor.getDeviceCount(), DEC);
  Serial.println(" devices.");
  Serial.print("Parasite power is: "); 
  if (sensor.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  if (!sensor.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();
  sensor.setResolution(insideThermometer, 9); 
  Serial.print("Device 0 Resolution: ");
  Serial.print(sensor.getResolution(insideThermometer), DEC); 
  Serial.println();
  

  Serial.print("Setting soft-AP ... ");
  boolean result = WiFi.softAP("PLA_thermostat", "");
  if(result == true)
  {
    Serial.println("Ready");
    /* if DNSServer is started with "*" for domain name, it will reply with provided IP to all DNS request */
    dnsServer.start(DNS_PORT, "*", apIP);
  }
  else
  {
    Serial.println("Failed!");
  }

  pinMode(HEATER_PIN, OUTPUT);

  server.on("/", handleRoot);              
  server.on("/start_ota_update", startOtaUpdate);
  server.onNotFound(handleNotFound);
  server.begin(); 
}


void loop(void)
{  
  if(updateStartedFlag){
    digitalWrite(HEATER_PIN, LOW);
    ArduinoOTA.handle();
  }else{
    sensor.requestTemperatures();
    tempC = sensor.getTempC(insideThermometer);
  
    if((tempC > (target + 1)) || (tempC < -30)){
       digitalWrite(HEATER_PIN, LOW);
    }if(tempC < (target - 1)){
       digitalWrite(HEATER_PIN, HIGH);
    }

    server.handleClient(); 

    dnsServer.processNextRequest();
  }   
}
