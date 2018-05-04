
# Labo 4 : Train

Auteurs: Miguel Lopes Gouveia, Remy Nasserzare

## Description des fonctionnalités du logiciel

Implémenter un programme concurrent qui permet de faire circuler 2 trains sur des circuits prédéfinis, pendant une durée indeterminée.
Une partie des circuits est commune, et les trains doivent alors se la partager, c'est ce qu'on appelle une "zone critique". On veut ajouter la gestion de priorité au système en place,
ce qui nous permettra de déterminer si un train est plus prioritaire que l'autre ou pas. Les prioritées doivent pouvoir être changées par l'utilisateur en rentrant des commandes dans le champ texte du programme.
Tout les 2 tours, les locomotives doivent partir en sens inverse.


## Choix de l'implémentation

Nous avons la choisi la maquette A pour cette implémentation.

Nous avons définis les 3 priorités comme ci-dessous:

- La priorité 0. Il n'y a pas de priorité. Il faut écrire "Priorite_0" pour la sélectionner dans le programme.
- La priorité 1. Donne la priorité à la locomotive n’exploitant pas la voie d’évitement. L’autre locomotive doit donc toujours utiliser la voie d’évitement. Il faut écrire "Priorite_1" pour la sélectionner dans le programme.
- La priorité 2. Donne la priorité à la locomotive exploitant la voie d’évitement. L’autre locomotive ne doit plus du tout pouvoir accéder au tronçon commun. Il faut écrire "Priorite_2" pour la sélectionner dans le programme.

### cppmain

Classe principale du programme.
Initialise les locomotives et les lances en faisant appel à la méthode start().
Fixe les aiguillages, seules les aiguillages liés à la section critiques vont bouger après coup.
Ecoute le champ texte en attente d'une commande venant modifier les prioritées et modifie les prioritées en conscéquence.

### locomotive

Classe qu'on utilise pour définir les locomotives et gérer leur fonctionnement lors de l'éxécution du programme.
Cette classe fait toute la partie gestion du parcours des locomotives (zone critique, invertion et priorité).

## Tests Simulation :

Les tests suivant sont ceux qu'on a effectué au fur à mesure de notre développement.

* Test avec une seule locomotive. Permet de comprendre le fonctionnement des capteurs, aiguillages, ainsi que faire fonctionner l'inversion de la locomotive après 2 tours.
* Test avec deux locomotives fonctionant sur des tronçons différents. Cela a permis de tester le bon fonctionnement de thread tournant en parallèle et si l'invertion des locomotives étaient bien indépendant.
* Test de deux locomotives se partageants un tronçon en commun. Pour ce teste nous avons désactivé l'invertion pour se concentrer sur la gestion de la zone critique. Ce test nous a permis de parametrer les aiguillages et les capteurs pour eviter toutes collisions.
* Test précédent mais en réactivant l'invertion. Cela permet de vérifier si la zone critique est bien gérer même en sens inverse.
* Test des différents paramètres. Nous avons testé le circuit en le lançant avec différents paramètre de vitesse et du nombre de tour nécessaire pour une inversion.
* Test des différentes prioritées. Nous avons testé le bon fonctionnement du circuit avec les 3 priorités. Cela à permis de voir si une de ces priorités étaient mal gérées. Jusqu'a maintenant le programmme fonctionnait sans priorité, c'est à dire la priorité 0;
* Test des différentes prioritées pendant le fonctionnement de la simulation, en envoyant les commandes au travers du champ de texte du programme. Cela permet de vérifier le bon changement des prioritées. Par exemple, que la locomotive arreté redémarre bien une fois qu'on est plus en priorité 2;
* Test de la simulation pendant plusieurs minutes, pour vérifier le bon fonctionnement sur la durée.


## Tests maquette :
Malheureusement, nous n'avons pas testé notre sur la maquette et donc nous ne somme pas sur de son bon fonctionnement sur celle-ci.