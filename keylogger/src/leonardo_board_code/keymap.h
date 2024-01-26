#ifndef _KEYMAP_H_
#define _KEYMAP_H_

#define LEFT_CTRL   0x01
#define LEFT_SHIFT  0x02
#define ALT         0X04
#define LEFT_CMD    0x08
#define RIGHT_CTRL  0x10
#define RIGHT_SHIFT 0x20
#define ALT_GR      0x40
#define RIGHT_CMD   0x80

struct send_char_t {
  short mod;
  short buf;
  char ch;
};

struct frame_t {
  byte frame[50];
};

char keymaps[105] = {
  (char)0x00,             /* 0   */ (char)0x00,             /* 1   */ (char)0x00,             /* 2   */ (char)0x00,             /* 3   */ 'a',                    /* 4   */
  'b',                    /* 5   */ 'c',                    /* 6   */ 'd',                    /* 7   */ 'e',                    /* 8   */ 'f',                    /* 9   */
  'g',                    /* 10  */ 'h',                    /* 11  */ 'i',                    /* 12  */ 'j',                    /* 13  */ 'k',                    /* 14  */
  'l',                    /* 15  */ 'm',                    /* 16  */ 'n',                    /* 17  */ 'o',                    /* 18  */ 'p',                    /* 19  */
  'q',                    /* 20  */ 'r',                    /* 21  */ 's',                    /* 22  */ 't',                    /* 23  */ 'u',                    /* 24  */
  'v',                    /* 25  */ 'w',                    /* 26  */ 'x',                    /* 27  */ 'y',                    /* 28  */ 'z',                    /* 29  */
  '1',                    /* 30  */ '2',                    /* 31  */ '3',                    /* 32  */ '4',                    /* 33  */ '5',                    /* 34  */
  '6',                    /* 35  */ '7',                    /* 36  */ '8',                    /* 37  */ '9',                    /* 38  */ '0',                    /* 39  */
  (char)KEY_RETURN,       /* 40  */ (char)KEY_ESC,          /* 41  */ (char)KEY_BACKSPACE,    /* 42  */ (char)KEY_TAB,          /* 43  */ ' ',                    /* 44  */
  '-',                    /* 45  */ '=',                    /* 46  */ '{',                    /* 47  */ '}',                    /* 48  */ (char)0x00,             /* 49  */
  '|',                    /* 50  */ ';',                    /* 51  */ '\'',                   /* 52  */ '~',                    /* 53  */ ',',                    /* 54  */
  '>',                    /* 55  */ '/',                    /* 56  */ (char)KEY_CAPS_LOCK,    /* 57  */ (char)KEY_F1,           /* 58  */ (char)KEY_F2,           /* 59  */
  (char)KEY_F3,           /* 60  */ (char)KEY_F4,           /* 61  */ (char)KEY_F5,           /* 62  */ (char)KEY_F6,           /* 63  */ (char)KEY_F7,           /* 64  */
  (char)KEY_F8,           /* 65  */ (char)KEY_F9,           /* 66  */ (char)KEY_F10,          /* 67  */ (char)KEY_F11,          /* 68  */ (char)KEY_F12,          /* 69  */
  (char)0x00,             /* 70  */ (char)0x00,             /* 71  */ (char)0x00,             /* 72  */ (char)KEY_INSERT,       /* 73  */ (char)0x00,             /* 74  */
  (char)KEY_PAGE_UP,      /* 75  */ (char)KEY_DELETE,       /* 76  */ (char)KEY_END,          /* 77  */ (char)KEY_PAGE_DOWN,    /* 78  */ (char)KEY_RIGHT_ARROW,  /* 79  */
  (char)KEY_LEFT_ARROW,   /* 80  */ (char)KEY_DOWN_ARROW,   /* 81  */ (char)KEY_UP_ARROW,     /* 82  */ (char)0x00,             /* 83  */ '/',                    /* 84  */
  '*',                    /* 85  */ '-',                    /* 86  */ '+',                    /* 87  */ (char)KEY_RETURN,       /* 88  */ '1',                    /* 89  */
  '2',                    /* 90  */ '3',                    /* 91  */ '4',                    /* 92  */ '5',                    /* 93  */ '6',                    /* 94  */
  '7',                    /* 95  */ '8',                    /* 96  */ '9',                    /* 97  */ '0',                    /* 98  */ '.',                    /* 99  */
  '<',                    /* 100 */ (char)KEY_LEFT_GUI,     /* 101 */ (char)0x00,             /* 102 */ (char)0x00,             /* 103 */ (char)0x00              /* 104 */
 };

 /* Keymap for fr keyboard */
//char *keymaps[105] = {
//  (char)0x00,            /* 0   */ (char)0x00,            /* 1   */ (char)0x00,            /* 2   */ (char)0x00,            /* 3   */ "q",                    /* 4   */
//  "b",                    /* 5   */ "c",                    /* 6   */ "d",                    /* 7   */ "e",                    /* 8   */ "f",                    /* 9   */
//  "g",                    /* 10  */ "h",                    /* 11  */ "i",                    /* 12  */ "j",                    /* 13  */ "k",                    /* 14  */
//  "l",                    /* 15  */ ",",                    /* 16  */ "n",                    /* 17  */ "o",                    /* 18  */ "p",                    /* 19  */
//  "a",                    /* 20  */ "r",                    /* 21  */ "s",                    /* 22  */ "t",                    /* 23  */ "u",                    /* 24  */
//  "v",                    /* 25  */ "z",                    /* 26  */ "x",                    /* 27  */ "y",                    /* 28  */ "w",                    /* 29  */
//  "&",                    /* 30  */ "é",                    /* 31  */ "\"",                   /* 32  */ "'",                    /* 33  */ "(",                    /* 34  */
//  "-",                    /* 35  */ "è",                    /* 36  */ "_",                    /* 37  */ "ç",                    /* 38  */ "à",                    /* 39  */
//  (char)KEY_RETURN,      /* 40  */ (char)KEY_ESC,         /* 41  */ (char)KEY_BACKSPACE,   /* 42  */ (char)KEY_TAB,         /* 43  */ " ",                    /* 44  */
//  ")",                    /* 45  */ "=",                    /* 46  */ "^",                    /* 47  */ "$",                    /* 48  */ (char)0x00,            /* 49  */
//  "*",                    /* 50  */ "m",                    /* 51  */ "ù",                    /* 52  */ "œ",                    /* 53  */ ";",                    /* 54  */
//  ":",                    /* 55  */ "!",                    /* 56  */ (char)KEY_CAPS_LOCK,   /* 57  */ (char)KEY_F1,          /* 58  */ (char)KEY_F2,          /* 59  */
//  (char)KEY_F3,          /* 60  */ (char)KEY_F4,          /* 61  */ (char)KEY_F5,          /* 62  */ (char)KEY_F6,          /* 63  */ (char)KEY_F7,          /* 64  */
//  (char)KEY_F8,          /* 65  */ (char)KEY_F9,          /* 66  */ (char)KEY_F10,         /* 67  */ (char)KEY_F11,         /* 68  */ (char)KEY_F12,         /* 69  */
//  (char)0x00,            /* 70  */ (char)0x00,            /* 71  */ (char)0x00,            /* 72  */ (char)KEY_INSERT,      /* 73  */ (char)0x00,            /* 74  */
//  (char)KEY_PAGE_UP,     /* 75  */ (char)KEY_DELETE,      /* 76  */ (char)KEY_END,         /* 77  */ (char)KEY_PAGE_DOWN,   /* 78  */ (char)KEY_RIGHT_ARROW, /* 79  */
//  (char)KEY_LEFT_ARROW,  /* 80  */ (char)KEY_DOWN_ARROW,  /* 81  */ (char)KEY_UP_ARROW,    /* 82  */ (char)0x00,            /* 83  */ "/",                    /* 84  */
//  "*",                    /* 85  */ "-",                    /* 86  */ "+",                    /* 87  */ (char)KEY_RETURN,      /* 88  */ "1",                    /* 89  */
//  "2",                    /* 90  */ "3",                    /* 91  */ "4",                    /* 92  */ "5",                    /* 93  */ "6",                    /* 94  */
//  "7",                    /* 95  */ "8",                    /* 96  */ "9",                    /* 97  */ "0",                    /* 98  */ ".",                    /* 99  */
//  "<",                    /* 100 */ (char)KEY_LEFT_GUI,    /* 101 */ (char)0x00,            /* 102 */ (char)0x00,            /* 103 */ (char)0x00             /* 104 */
//};

#endif
