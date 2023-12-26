# Spectrology
Convertisseur d'images en fichiers audio avec des spectrogrammes correspondants.

## Utilisation

```
usage: spectrology.py [-h] [-r] [-o OUTPUT] [-b BOTTOM] [-t TOP] [-p PIXELS]
                      [-s SAMPLING]
                      INPUT

arguments positionnels :
  INPUT                 Nom de l'image à convertir.

options :
  -h, --help            Afficher ce message d'aide et quitter.
  -r, --rotate          Faire pivoter l'image de 90 degrés.
  -o OUTPUT, --output OUTPUT
                        Nom du fichier audio de sortie (valeur par défaut : out.wav).
  -b BOTTOM, --bottom BOTTOM
                        Plage de fréquences inférieure (valeur par défaut : 200).
  -t TOP, --top TOP     Plage de fréquences supérieure (valeur par défaut : 20000).
  -p PIXELS, --pixels PIXELS
                        Pixels par seconde (valeur par défaut : 30).
  -s SAMPLING, --sampling SAMPLING
                        Taux d'échantillonnage (valeur par défaut : 44100).
```

```
python spectrology.py test.bmp -b 13000 -t 19000
```
![spectrogram](https://solusipse.net/blog/img/posts/audio-samples/7.png)

Pour plus d'informations sur cette technique, consultez cet article : https://solusipse.net/blog/post/basic-methods-of-audio-steganography-spectrograms/.

## License
See `LICENSE`.
