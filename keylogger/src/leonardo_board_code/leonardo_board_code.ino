#include <Keyboard.h>
#include "keymap.h"

bool intercept = false;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial1.setTimeout(50);
  Keyboard.begin(KeyboardLayout_en_US);
}

void loop() {
  struct send_char_t key;

  if (Serial1.available()) {
    Serial1.readBytes((char*)&key, sizeof(struct send_char_t));

    if (!intercept) {
      processKey(&key);
      Serial.println((int)key.ch);
      Serial.println((int)key.mod);
      Serial.println((int)key.buf);
  
      intercept = true;
    } else {
      intercept = false;
    }
  }
}

void processKey(struct send_char_t *key) {

  if( (key->mod & LEFT_CTRL ) == LEFT_CTRL  || (key->mod & RIGHT_CTRL ) == RIGHT_CTRL ) Keyboard.press(KEY_LEFT_CTRL);
  if( (key->mod & LEFT_SHIFT) == LEFT_SHIFT || (key->mod & RIGHT_SHIFT) == RIGHT_SHIFT) Keyboard.press(KEY_LEFT_SHIFT);
  if( (key->mod & LEFT_CMD  ) == LEFT_CMD   || (key->mod & RIGHT_CMD  ) == RIGHT_CMD  ) Keyboard.press(KEY_HOME);
  if( (key->mod & ALT       ) == ALT                                                  ) Keyboard.press(KEY_LEFT_ALT);
  if( (key->mod & ALT_GR    ) == ALT_GR                                               ) Keyboard.press(KEY_RIGHT_ALT);

  Keyboard.press(keymaps[key->ch]);
  delay(50);
  Keyboard.release(keymaps[key->ch]);

  if( (key->mod & LEFT_CTRL ) == LEFT_CTRL  || (key->mod & RIGHT_CTRL ) == RIGHT_CTRL ) Keyboard.release(KEY_LEFT_CTRL);
  if( (key->mod & LEFT_SHIFT) == LEFT_SHIFT || (key->mod & RIGHT_SHIFT) == RIGHT_SHIFT) Keyboard.release(KEY_LEFT_SHIFT);
  if( (key->mod & LEFT_CMD  ) == LEFT_CMD   || (key->mod & RIGHT_CMD  ) == RIGHT_CMD  ) Keyboard.release(KEY_HOME);
  if( (key->mod & ALT       ) == ALT                                                  ) Keyboard.release(KEY_LEFT_ALT);
  if( (key->mod & ALT_GR    ) == ALT_GR                                               ) Keyboard.release(KEY_RIGHT_ALT);

}
