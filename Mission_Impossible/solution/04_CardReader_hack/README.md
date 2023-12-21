# Attaque sur le lecteur de carte

## 1. Rappel du sujet

***La mission est d'entrer dans la salle des 4AS (option à l'INSA CVL en STI) affaint de pouvoir brancher un Keylogger sur la machine de l'enseignant et pouvoir récupérer sont mot de passe pour pouvoir changer ça note obtenue et avoir la moyenne. Comme vous ête dans l'option 2SU, vous avez une porte qui mène directement dans la salle des 4AS, mais cette enseignant, suite à des problème entre des éleves à mis en place un système de carte surveillé par une caméra pour que seulement les profésseur puissent passer par la porte.***

***Pour pouvoir ouvrir la porte, il faut utiliser une carte avec le lecteur de carte. L'ouverture de la porte se fait que lorsque la carte est reconnue, que personnes n'est devant la caméra, qu'il n'y a pas de coupure réseau.***

Maintenant que nous avons la possibilité de passer devant la caméra sans être détecté, nous devons maintenant trouver un moyen d'ouvrir la porte qui s'active à l'aide d'une carte à puce. Dans cette étapes, nous avons réussie à obtenir le code d'une carte utilisé par un anseignant. Cette dernière carte à étais désactivé ce qui rend le code inutile en l'état. Il faut donc trouver un moyen d'exploiter ce code pour pouvoir ouvrir la porte.

## 2. Attaque sur le lecteur de carte

### 2.1. Compréhension du code de la carte

Dans cette partie, nous allons vusialiser comment une carte à puce fait pour communiquer avec un lecteur de carte. Puis nous allons visualiser le code de la carte d'un anciant enseignant.

#### 2.1.1. Fonctionnement de la communication entre terminal et carte à puce


***`AFAIRE`***

#### 2.1.2. Identification du code de la carte

Nous pouvons visualiser dans le projet JavaCard le fichier `.jcproject`

```xml
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE properties SYSTEM "http://java.sun.com/dtd/properties.dtd">
<properties>
<comment>Java Card project properties</comment>
<entry key="door">0x01:0x02:0x03:0x04:0x05:0x06:0x07:0x08:0x09:0x00</entry>
<entry key="door.Door">0x01:0x02:0x03:0x04:0x05:0x06:0x07:0x08:0x09:0x00:0x01</entry>
</properties>
```

Ce fichier nous permet de savoir que l'applet à comme AID `0x01:0x02:0x03:0x04:0x05:0x06:0x07:0x08:0x09:0x00` et l'instance à pour AID `0x01:0x02:0x03:0x04:0x05:0x06:0x07:0x08:0x09:0x00:0x01`.

Nous pouvons maintenant visualiser le code pour identifier le fonctionnement. Pour commencer, nous avons les déclaration suivante :

```java
	private final static byte ID_CARD_CLA =(byte)0x80;
	
	private static final byte VALIDATE_PIN_INS = 0x22;
	private static final byte GET_ID_INS       = 0x23;
```

Cela nous permet de déterminer que le `CLA` de cette applet est `0x80` et que nous avons deux instructions. La première instruction qui permet de valider le code PIN à pour valeur `0x22` et la seconde instruction qui permet de récupérer un id avec l'instruction `0x23`.

Nous avons ensuite la méthode `process` qui permet de sélection la fonction adapté en fonction de l'instruction sélectionné.

```java
	public void validatePin(APDU apdu) {
		byte[] buffer = apdu.getBuffer();
		if(buffer[ISO7816.OFFSET_LC]==PIN_SIZE){
			apdu.setIncomingAndReceive();
			if(pin.check(buffer, ISO7816.OFFSET_CDATA,PIN_SIZE)==false)
				ISOException.throwIt(SW_VERIFICATION_FAILED);
		}else ISOException.throwIt(ISO7816.SW_WRONG_LENGTH);
	}
```

La méthode `validatePin` permet de vérifier le code PIN transmis. La carte va transmetre une erreur si le code ne correspond pas. En cas de validation du PIN, la carte transmet `0x9000`. Le code est transmis dans la trâme avec la valeur de `LC` et pas dans les paramètre `P1` et `P2`

```java
	public void getId(APDU apdu) {
		if(!pin.isValidated()) ISOException.throwIt(SW_PIN_VERIFICATION_REQUIRED);

		apdu.setOutgoing();
		apdu.setOutgoingLength((short) 1);
		apdu.sendBytesLong((byte[]) id, (short) 0, (short) 1);
	}
```

Pour finir, nous avons la méthode `getId` qui permet de transmettre l'id de la carte seulement lorsque le code PIN à étais vérifier au préalable.

Avec ces éléments, nous pouvons donc déterminé que les requêtes APDU transmis par le lecteur de carte doivent être les suivantes:

```text
Requête APDU pour valider le code PIN:

	0x80 0x22 0x00 0x00 0x04 0x00 0x00 0x00 0x00 0x7F
	CLA  INS  P1   P2   LC   --------CODE------- LE

Reqyête APDU pour récupérer l'ID de la carte:

	0x80 0x23 0x00 0x00 0x00 0x7F
	CLA  INS  P1   P2   LC   LE
```

Pour l'ordre des apples des requêtes APDU sont par déduction la validation du code PIN, puis si il n'y a pas d'erreur, la récupération de l'ID de la carte.

```java
	final static byte PIN_TRY_LIMIT = (byte) 0x03;
	private final static byte PIN_SIZE =(byte)0x04;

	private Door() {
		// initialisation du code pin de la carte
		pin = new OwnerPIN(PIN_TRY_LIMIT, MAX_PIN_SIZE);
		pin.update(new byte[]{0x01,0x05,0x08,0x03},(short) 0, PIN_SIZE);
		register();
	}
```

Il est aussi intéréssant à noter que dans la méthode `Door`, le système de code PIN est limité à trois tentative en cas d'erreur de code PIN et que le code est constitué de quatre nombre.

Avec ces informations, nous avons ce qu'il faut pour produire une carte qui permet d'ouvrir la porte. Mainteant il faut mettre en place l'environnement de développement sur sa machine.

### 2.2. Mis en place de l'envirronement de développement JavaCard

***`A FAIRE`***

### 2.3. Pret a ouvrir cette porte

***`A FAIRE`***
