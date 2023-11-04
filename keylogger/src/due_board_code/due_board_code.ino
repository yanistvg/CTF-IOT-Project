#include <KeyboardController.h>
#include "keymap.h"

USBHost usb;
KeyboardController keyboard(usb);

bool Maj = false;

void keyPressed() {
  int mod = keyboard.getModifiers();
  char ch = keyboard.getOemKey();

  String to_send = "";
  if (ch == 57) {
    Maj = !Maj;
  } else {
    if (Maj || mod == 2)
      to_send = keymap_Maj[int(ch)];
    else
      to_send = keymaps[int(ch)];
  }

  Serial1.write(to_send[0]);
  Serial.write(to_send[0]);
}

void keyReleased() {
}

void setup() {
  delay(200);
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  usb.Task();
}