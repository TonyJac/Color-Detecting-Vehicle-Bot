#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "D-Link";
const char* password = "password";
int redPin = 13;
int greenPin = 2;
ESP8266WebServer server(80);

String webPage = "";

void setup(void) {

  webPage += "<h1>Traffic Light</h1><p>Red Light <a href=\"socket1On\"><button>ON</button></a>&nbsp";
  webPage += "<p>Green Light <a href=\"socket2On\"><button>ON</button></a>&nbsp";
  webPage += "<p>Switch Off <a href=\"socket3On\"><button>ON</button></a>&nbsp";
  // preparing GPIOs
  pinMode(redPin, OUTPUT);
  digitalWrite(redPin, LOW);
  pinMode(greenPin, OUTPUT);
  digitalWrite(greenPin, LOW);


  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", []() {
    server.send(200, "text/html", webPage);
  });
  server.on("/socket1On", []() {
    server.send(200, "text/html", webPage);
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin,LOW);
    delay(500);
  });
  server.on("/socket2On", []() {
    server.send(200, "text/html", webPage);
    digitalWrite(greenPin, HIGH);
    digitalWrite(redPin,LOW);
    delay(500);
  });
  server.on("/socket3On", []() {
    server.send(200, "text/html", webPage);
    digitalWrite(greenPin, LOW);
    digitalWrite(redPin,LOW);
    delay(500);
  });
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
