# Chiffrement de César en Python

Ce script Python implémente le chiffrement de César, un chiffrement par substitution simple, avec une clé sous forme de chaîne de caractères.

## Utilisation

###   1. Chiffrer un message :

Modifiez le script pour spécifier le message à chiffrer et la clé, puis exécutez-le.

    # Exemple d'utilisation
    message_a_chiffrer = "Bonjour"
    cle = "CleSecrete"
    
    message_chiffre = chiffrement_cesar(message_a_chiffrer, cle)
    print("Message chiffré:", message_chiffre)

### 2. Déchiffrer un message :

Modifiez le script pour spécifier le message chiffré et la même clé utilisée pour le chiffrement, puis exécutez-le.

    # Exemple d'utilisation
    message_dechiffre = dechiffrement_cesar(message_chiffre, cle)
    print("Message déchiffré:", message_dechiffre)

## Avertissement

Le chiffrement de César est un algorithme de chiffrement très simple et ne doit pas être utilisé dans des situations nécessitant une sécurité robuste.
