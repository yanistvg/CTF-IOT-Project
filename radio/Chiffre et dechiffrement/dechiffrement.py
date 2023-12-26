def dechiffrement_cesar(message_chiffre, cle):
    resultat = ""

    for i in range(len(message_chiffre)):
        char = message_chiffre[i]

        if char.isalpha():
            # Calculer le décalage en fonction de la clé
            decalage = ord(cle[i % len(cle)]) - ord('a') if cle[i % len(cle)].islower() else ord(cle[i % len(cle)]) - ord('A')

            # Appliquer le décalage inverse au caractère
            if char.islower():
                resultat += chr((ord(char) - decalage - ord('a')) % 26 + ord('a'))
            else:
                resultat += chr((ord(char) - decalage - ord('A')) % 26 + ord('A'))
        else:
            resultat += char

    return resultat

# Exemple d'utilisation
message_chiffre =  "IPY-2BH{OSSPUSFWOSGSTQFTSHGMDNAY}"
cle = "ABFEDJNMIOINMGDSMSANSIFL"

message_dechiffre = dechiffrement_cesar(message_chiffre, cle)
print("Message déchiffré:", message_dechiffre)
