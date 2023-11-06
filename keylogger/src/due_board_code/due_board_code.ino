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

  for(int i=0; i<to_send.length(); i++)
    Serial1.write(to_send[i]);
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