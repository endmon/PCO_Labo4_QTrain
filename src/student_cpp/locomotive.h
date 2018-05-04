/** locomotive.h
* Authors : Miguel Gouveia - Remy Nasserzare
*
* Date : 03-05-2018
*
* Ce fichier est le header de la classe Locomotive,
* implemente les prototypes de fonctions et les attributs.
*
* La classe Locomotive permet de construire un objet Locomotive et de fixer
* les parametres necessaires pour son fonctionnement. Implemente aussi une
* classe run() qui fait toute la gestion des deplacements de la locomotive.
*/

#ifndef LOCOMOTIVE_H
#define LOCOMOTIVE_H

#include <QString>
#include <QThread>
#include <QSemaphore>

class Locomotive : public QThread
{

public:

    /** Constructeur.
     * Initialise la locomotive avec un numero invalide et une vitesse nulle.
     */
    Locomotive();

    /** Constructeur.
     * Initialise la locomotive en precisant son numero et sa vitesse initiale.
     * @param numero Numero de la locomotive.
     * @param vitesse Vitesse initiale de la locomotive.
     */
    Locomotive(int numero, int vitesse);

    /** Retourne le numero de la locomotive.
     * @return Numero de la locomotive.
     */
    int numero() const;

    /** Fixe le numero de la locomotive.
     * @param numero Numero de la locomotive.
     */
    void fixerNumero(int numero);

    /** Retourne la vitesse actuelle de la locomotive.
     * @return Vitesse actuelle de la locomotive.
     */
    int vitesse() const;

    /** Fixe la vitesse de la locomotive.
     * Si la locomotive est en fonction, alors sa vitesse est modifiee en
     * consequence.
     * @param vitesse Vitesse de la locomotive.
     */
    void fixerVitesse(int vitesse);

    /** Determine la position initiale de la locomotive.
     * @param contactAvant Contact vers lequel la locomotive va se diriger.
     * @param contactArrier Contact a l'arriere de la locomotive.
     */
    void fixerPosition(int contactAvant, int contactArriere);

    /** Affiche un message.
     * @param message Message a afficher.
     */
    void afficherMessage(const QString &message);

    //! Allume les phares de la locomotive.
    void allumerPhares();

    //! Eteint les phares de la locomotive.
    void eteindrePhares();

    //! Demarre la locomotive.
    void demarrer();

    //! Arrete la locomotive.
    void arreter();

    //! Change le sens de marche de la locomotive.
    void inverserSens();

    /** Fixe la fin du tour.
    * @param entier représentant la fin du tour.
    */
    void fixerFinTour(int finTour);

    /** Fixe les contacts critiques.
    * @param tableau d'entiers contenant les débuts de contacts critiques.
    */
    void fixerContactCritique(int contactCritique[]);

    /** Fixe les fins de contacts critiques.
    * @param tableau d'entiers contenant les fins de contacts critiques.
    */
    void fixerFinContactCritique(int finContactCritique[]);

    /** Fixe la direction de l'aiguillage critique.
    * @param la direction de l'aiguillage critique (entier).
    */
    void fixerDirectionAiguillageCritique(int directionAiguillageCritique);

    /** Fixe une deviation (s'il y en a une).
    * @param booleen determinant la presence de deviation.
    */
    void fixerDeviation(bool deviation);

    /** Fixe tous les aiguillages critiques.
    * @param tableau d'entiers regroupant tous les aiguillages critiques.
    */
    void fixerAiguillageCritique(int aiguillageCritique[]);

    /** Fixe les aiguillages de deviation.
    * @param tableau d'entiers contenant tous les aiguillages de deviation.
    */
    void fixerAiguillageDeviation(int aiguillageDeviation[]);

    /** Fixe le nombre de tours dans le sens inverse.
    * @param entier representant le nombre de tours a effectuer en sens inverse.
    */
    void fixerNbTourInverse(int nbTourInverse);

    /** Fixe le numero de priorite.
    * Si la priorite vaut 0, il n'y a pas de priorite.
    * Si la priorite vaut 1, donne la priorité à la locomotive n’exploitant pas
    *   la voie d’évitement. L’autre locomotive doit toujours passer par
    *   voie d’évitement.
    * Si la priorite vaut 2, donne la priorité à la locomotive exploitant
    *   la voie d’évitement. L’autre locomotive ne doit plus pouvoir accéder
    *   au tronçon commun. Arrive au troncon commun, elle reste arrete
    *   jusqu'a un changement de priorite.
    * @param numero de la priorite.
    */
    static void fixerPriorite(int priorite);

    //! Code de fonctionnement de la locomotive.
    void run() override;

private:
    int _numero;
    int _vitesse;
    int _nbTourInverse;
    int _finTour;
    bool _enFonction;
    int* _contactCritique;
    int* _finContactCritique;
    int* _aiguillageCritique;
    int* _aiguillageDeviation;
    int _directionAiguillageCritique;
    int _deviation = false;
    static int _priorite;

    static QSemaphore _mutex;
    static QSemaphore _segmentCritique;
    static int _utilise;
};

#endif // LOCOMOTIVE_H
