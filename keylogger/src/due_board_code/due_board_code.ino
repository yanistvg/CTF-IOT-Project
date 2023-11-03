#include <KeyboardController.h>

USBHost usb;
KeyboardController keyboard(usb);

void keyPressed() {
  int mod = keyboard.getModifiers();
  short ch = keyboard.getOemKey();
  Serial1.write(ch);
  Serial.print(ch);
  Serial.print(" : mod=");
  Serial.println(mod);
}

void keyReleased() {
}

void setup() {
  delay(200);
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  usb.Task();
}