#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "analogWrite.h"

const char *ssid = "Principal";
const char *password = "12345678";

AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.printf("Connecting to %s.\n", ssid);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(300);
  }

  Serial.printf("\nServer running at %s\n", WiFi.localIP().toString().c_str());
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "/s = analogWrite, /t = digitalWrite, /o = pinMode; parametros: pin e value");
  });
  server.on("/s", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("pin") && request->hasParam("value"))
    {
      int pin = request->getParam("pin")->value().toInt();
      int value = request->getParam("value")->value().toInt();
      request->send(200, "text/plain", "OK; " + (String)pin + ": " + (String)value);
      analogWrite(pin, value);
    }
    else
    {
      request->send(200, "text/plain", "Missing params.");
    }
  });
  server.on("/t", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("pin") && request->hasParam("value"))
    {
      int pin = request->getParam("pin")->value().toInt();
      int value = request->getParam("value")->value().toInt();
      request->send(200, "text/plain", "OK; " + (String)pin + ": " + (String)value);
      digitalWrite(pin, value);
    }
    else
    {
      request->send(200, "text/plain", "Missing params.");
    }
  });
  server.on("/o", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("pin") && request->hasParam("value"))
    {
      int pin = request->getParam("pin")->value().toInt();
      int value = request->getParam("value")->value().toInt();
      request->send(200, "text/plain", "OK; " + (String)pin + ": " + (String)value);
      pinMode(pin, value);
    }
    else
    {
      request->send(200, "text/plain", "Missing params.");
    }
  });
  server.begin();
}

void loop() {}