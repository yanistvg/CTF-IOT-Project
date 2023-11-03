#include <Keyboard.h>

void setup() {
  Serial1.begin(9600);
  Keyboard.begin(KeyboardLayout_fr_FR);
}

void loop() {
  char c = 0x00;

  if (Serial1.available() > 0) {
    c = Serial1.read();
    if (c != 0x0A && c != 0x0D && c != 0x00) {
      Keyboard.write(c);
    }
  }
}
