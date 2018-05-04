/** locomotive.cpp
* Authors : Miguel Gouveia - Remy Nasserzare
*
* Date : 03-05-2018
*
* Implementation de la classe Locomotive, toute la logique des deplacements
* est geree dans la methode run().
*
*/

#include "locomotive.h"
#include "ctrain_handler.h"
#include <iostream>

//Variables globales

//Utilise en lecture/ecriture par les locomotives pour savoir si le troncon est
// occupe. Pour pouvoir lire ou ecrire _utilise il faut acquerir _mutex.
int Locomotive::_utilise = -1;
//Utilise en ecriture par le main et en lecture par les locomotives, pour
// pouvoir lire _priorite, il faut acquerir _mutex.
int Locomotive::_priorite = 0;

QSemaphore Locomotive::_mutex(1);
QSemaphore Locomotive::_segmentCritique(1);

Locomotive::Locomotive() :
    _numero(-1),
    _vitesse(0),
    _enFonction(false)
{

}

Locomotive::Locomotive(int numero, int vitesse) :
    _numero(numero),
    _vitesse(vitesse),
    _enFonction(false)
{

}

int Locomotive::numero() const
{
    return _numero;
}

void Locomotive::fixerNumero(int numero)
{
    _numero = numero;
}

int Locomotive::vitesse() const
{
    return _vitesse;
}

void Locomotive::fixerVitesse(int vitesse)
{
    _vitesse = vitesse;

    if (_enFonction)
        mettre_vitesse_progressive(_numero, vitesse);
}

void Locomotive::fixerPosition(int contactAvant, int contactArriere)
{
    assigner_loco(contactAvant, contactArriere, _numero, _vitesse);
}

void Locomotive::afficherMessage(const QString &message)
{
    afficher_message_loco(_numero, qPrintable(message));
}

void Locomotive::allumerPhares()
{
    mettre_fonction_loco(_numero, ALLUME);
}

void Locomotive::eteindrePhares()
{
    mettre_fonction_loco(_numero, ETEINT);
}

void Locomotive::demarrer()
{
    mettre_vitesse_progressive(_numero, _vitesse);
    _enFonction = true;
}

void Locomotive::arreter()
{
    arreter_loco(_numero);
    _enFonction = false;
}

void Locomotive::inverserSens()
{
    inverser_sens_loco(_numero);
}

void Locomotive::fixerFinTour(int finTour)
{
    _finTour = finTour;
}

void Locomotive::fixerContactCritique(int contactCritique[])
{
    _contactCritique = contactCritique;
}

void Locomotive::fixerFinContactCritique(int finContactCritique[])
{
    _finContactCritique = finContactCritique;
}

void Locomotive::fixerDirectionAiguillageCritique(int
                                                  directionAiguillageCritique)
{
    _directionAiguillageCritique = directionAiguillageCritique;
}

void Locomotive::fixerDeviation(bool deviation)
{
    _deviation = deviation;
}

void Locomotive::fixerAiguillageCritique(int aiguillageCritique[])
{
    _aiguillageCritique = aiguillageCritique;
}

void Locomotive::fixerAiguillageDeviation(int aiguillageDeviation[])
{
    _aiguillageDeviation = aiguillageDeviation;
}

void Locomotive::fixerPriorite(int priorite)
{
    _priorite = priorite;
}

void Locomotive::fixerNbTourInverse(int nbTourInverse)
{
    _nbTourInverse = nbTourInverse;
}

void Locomotive::run()
{
    allumerPhares();
    demarrer();

    //variables locale utilise dans la boucle
    int tour = 0;
    int reverse = 0;
    while(true)
    {
        //gere l'invertion de locomotive au bout de X tour.
        if(tour % _nbTourInverse == 0 && tour > 0)
        {
           reverse++;
           reverse %= _nbTourInverse;
           inverserSens();
           afficherMessage("Et on repart en arriere.");

        }

        attendre_contact(_contactCritique[reverse]);
        _mutex.acquire();
        /*verifie que la section critique est vide et s'assure que la
        locomotive exploitant la deviation ne rentre pas lors de la priorite 1
        et que l'autre locomotive ne rentre pas lors de la priorite 2*/
        if(_utilise < 0 && (_priorite != 1 || !_deviation) &&
           ( _priorite != 2 || _deviation))
        {
            _utilise = numero();

            //Pour s'assurer que l'aiguillage est bien positionne
            if(_deviation) diriger_aiguillage(_aiguillageDeviation[reverse],
                                              TOUT_DROIT, 0);

            _segmentCritique.acquire();
            afficherMessage("On prend le troncon commun.");
            _mutex.release();
        }
        else if (_deviation)
        {
            //Pour que la locomotive prenne la deviation
            diriger_aiguillage(_aiguillageDeviation[reverse], DEVIE, 0);
            afficherMessage("On prend la deviation.");
            _mutex.release();
            attendre_contact(_finTour);
            tour++;
            continue;
        }
        else
        {
            _mutex.release();
            afficherMessage("On s'arrete devant le troncon commun.");
            arreter();
            if(_priorite == 2)
            {
                while(true)
                {
                    if(_priorite != 2) break;
                }
            }
            _segmentCritique.acquire();
            _mutex.acquire();
            afficherMessage("On prend le troncon commun.");
            _utilise = numero();
            _mutex.release();

            demarrer();
        }
        //Pour que les locomotives reste sur leur troncons
        diriger_aiguillage(_aiguillageCritique[reverse],
                           _directionAiguillageCritique, 0);

        // attendre le contact de sortie de section critique
        attendre_contact(_finContactCritique[reverse]);

        // libère l'utilisation de la section critique
        _mutex.acquire();
        afficherMessage("On quitte le troncon commun");
        _utilise = -1;
        _mutex.release();

        // libere la section critique
        _segmentCritique.release();
        attendre_contact(_finTour);
        tour++;
    }
}
