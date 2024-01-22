#include <KeyboardController.h>
#include "keymap.h"

USBHost usb;
KeyboardController keyboard(usb);

bool Maj = false;

void keyPressed() {
  struct send_char_t key = { 0, 0 };

  key.mod = keyboard.getModifiers();
  key.ch  = keyboard.getOemKey();

  Serial1.write((char*)&key, sizeof(struct send_char_t));
}

void keyReleased() {
}

void setup() {
  delay(200);
  Serial1.begin(115200);
  Serial1.setTimeout(50);
}

void loop() {
  usb.Task();
}