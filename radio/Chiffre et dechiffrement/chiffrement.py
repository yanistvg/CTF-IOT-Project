def chiffrement_cesar(message, cle):
    resultat = ""

    for i in range(len(message)):
        char = message[i]

        if char.isalpha():
            # Calculer le décalage en fonction de la clé
            decalage = ord(cle[i % len(cle)]) - ord('a') if cle[i % len(cle)].islower() else ord(cle[i % len(cle)]) - ord('A')

            # Appliquer le décalage au caractère
            if char.islower():
                resultat += chr((ord(char) + decalage - ord('a')) % 26 + ord('a'))
            else:
                resultat += chr((ord(char) + decalage - ord('A')) % 26 + ord('A'))
        else:
            resultat += char

    return resultat

# Exemple d'utilisation
message_a_chiffrer = "IOT-2SU{GEKCIMCECAGFBIAISGBIAENM}"
cle = "ABFEDJNMIOINMGDSMSANSIFL"

message_chiffre = chiffrement_cesar(message_a_chiffrer, cle)
print("Message chiffré:", message_chiffre)
