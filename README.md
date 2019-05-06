# Robot 2A Martine - A New Hope

## Contexte et objectifs:
La carte de la base roulante et celle de l'ascenseur initialement prévues ne pourront pas etre prêtes dans les temps. Après discusion avec l'équipe du robot 1A, il n'y a que peu de choses sur lesquelles preter main forte. Il serait donc possible de continuer à travailler sur le robot 2A pour pouvoir présenter une version minimale de celui-ci à la coupe.

L'objectif serait de passer l'homologation et de pouvoir pousser quelques palets au cours de la coupe. Pour espérer être dans les temps, il est vital de faire au plus simple afin de disposer d'une base méca/elec prete, avec le code haut niveau à faire sur la route.

La version B du robot abandonne l'ascenseur pour ne garder qu'un étage base roulante + un étage contrôle. D'un point de vue mécanique: la base roulante est quasiment prête et l'étage de controle peut être assemblé rapidement.

Volontaires:
* Victor (Mécanique, Elec)
* Félix (Elec)
* Raphael (Elec: Carte alimentation & Code)
* Arnaud (Elec: carte ultrason)

Conseil:
* Iris (Mécanique)

A confirmer:
* Vincent (Elec et prog?)

## Nouvelle structure:
Après discution avec Felix, Iris et Luc: idéalement, il aurait fallu récupérer la carte de la base roulante de l'année dernière, mais le STM32 dessus étant mort, et des levels shifters devant etre implémentés, faire rapidement une nouvelle carte est plus simple. La nouvelle structure serait donc la suivante (en gras: les cartes électroniques):

* Etage de contrôle:
  * **Carte de controle (CC)**:
    * [STM32 Nucleo-64 F401RE](https://www.st.com/en/evaluation-tools/nucleo-f401re.html)
  * **Carte d'alimentation**
  * Batterie
* Etage base roulante (Méca finie)
  * Moteurs (En place)
  * [Ecodeurs UsDigital S4T](https://www.usdigital.com/products/encoders/incremental/rotary/shaft/S4T?specification=mechanical#description) (En place)
  * Capteurs ultrasons (ref à définir)
  * **Carte adaptateur nappe moteur-pin** (car réutilisable facilement si à part)
  * **Carte de controle base roulante (CBR)**:
    * [Nucleo-32 F303K8](https://www.st.com/en/evaluation-tools/nucleo-f303k8.html) de format Arduino Nano, programmable avec l'IDE Arduino
    * Level shifters pour communiquer avec les encodeurs ([par exemple ceux-ci](https://www.sparkfun.com/products/12009))
    * Driver moteurs: à commander et si possible à integrer directement sur la carte
  * **Carte capteur ultrasons (CU)**

## Avancement:

Tâches de la partie méca (Victor):
* Impression des dernieres équerres
* Assemblage de l'étage de controle
* Découpe au fablab des parois/bases plexiglass
* Design et impression (ou adaptation) de supports pour les cartes électroniques

Tâches de la partie électronique:
* Carte alimentation à finir (Raph')
* Carte base roulante à faire (Victor & Félix)
* Carte nappe moteur-pin à vérifier et imprimer
* Carte ultrason à faire (Arnaud)

Tâches de de partie Code:
* Finir l'asservissement PID (nécessite la base roulante prete) (Raph')
