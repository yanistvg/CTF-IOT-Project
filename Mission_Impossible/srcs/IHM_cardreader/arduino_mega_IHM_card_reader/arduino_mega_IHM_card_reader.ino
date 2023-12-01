#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd = LiquidCrystal(42, 44, 46, 48, 50, 52);

char code[5] = {0, 0, 0, 0, '\n'};
int index_code = 0;


const byte Ligne = 4; //quatre ligne sur le digicode
const byte Colonne = 4; //quatre colonne sur le digicode
//On définit maintenant les symboles correspondant à chaque bouton
char hexaBouton[Ligne][Colonne] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte Ligne_Pins[Ligne] = {37, 35, 33, 31}; // On connecte la ligne du digicode 
byte Colonne_Pins[Colonne] = {29, 27, 25, 23}; // On connecte la colonne du digicode
Keypad mon_keypad = Keypad( makeKeymap(hexaBouton), Ligne_Pins, Colonne_Pins, Ligne, Colonne); 

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);
  lcd.begin(16, 2);

  pinMode(13, OUTPUT);
  digitalWrite(13, 1);
}

void loop() {
  if (Serial.available()) {
    String serialMsg = Serial.readString();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(serialMsg);
    delay(2000);
    lcd.clear();
  }

  char keypad_matrix = mon_keypad.getKey();
  
  if (keypad_matrix){
    if (keypad_matrix == 'D') {
      if (index_code > 0) {
        code[index_code-1] = 0;
        index_code--;
      } else {
        code[index_code] = 0;
      }
    }

    if (keypad_matrix >= '0' && keypad_matrix <= '9' && index_code < 4) {
      code[index_code] = keypad_matrix;
      index_code++;
    }

    if (keypad_matrix == 'A' && index_code >= 4) {
      // Serial.print(code);
      for (int y=0; y<5; y++) {
        Serial.write(code[y]);
        code[y] = 0;
      }
      Serial.write('\n');
      index_code = 0;
    }
  }

  lcdPrintPinCodeWithStart();
  delay(100);
}

void lcdPrintPinCodeWithStart() {
  short i=0;

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("PIN > ");

  while(code[i] != 0 && i < 4) {
    lcd.print("*");
    i++;
  }
  code[4] = '\n';
}