#include <Keyboard.h>

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.setTimeout(50);
  Keyboard.begin(KeyboardLayout_fr_FR);
}

void loop() {
  String c = "";

  if (Serial1.available() > 0) {
    c = Serial1.readString();
    for(int i=0; i<c.length(); i++) {
      Serial.write(c[i]);
      Keyboard.write(c[i]);
    }
  }
}
