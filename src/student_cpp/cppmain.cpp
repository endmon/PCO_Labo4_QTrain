/** cppmain.cpp
* Authors : Miguel Gouveia - Remy Nasserzare
*
* Date : 03-05-2018
*
* Fonction principale du programme, la fonction main lance l'application,
* initialise les locomotives et recupere les commandes passees par le champ
* texte du programme pour modifier les priorites.
*/

#include "ctrain_handler.h"
#include "locomotive.h"

#include <QList>

//Creation des locomotives
static Locomotive locomotive1;
static Locomotive locomotive2;

//Arret d'urgence
void emergency_stop()
{
    locomotive1.arreter();
    locomotive2.arreter();
    afficher_message("\nSTOP!");
    mettre_maquette_hors_service();
}


//Fonction principale
int cmain()
{
    afficher_message("Hit play to start the simulation...");

    //Choix de la maquette
    selection_maquette(MAQUETTE_A);

    //Initialisation des parcours
    QList<int> parcours1, parcours2;
    parcours1 << 23 << 16 << 15 << 14 << 7 << 6 << 5 << 34 << 33 << 32 << 25
              << 24;
    parcours2 << 22 << 21 << 20 << 19 << 13 << 12 << 11 << 10 << 4 << 3 << 2
              << 1 << 31 << 30 << 29 << 28 ;

    //Initialisation des aiguillages de la locomotive1
    diriger_aiguillage(9,  DEVIE,       0);
    diriger_aiguillage(8,  DEVIE,       0);
    diriger_aiguillage(11, TOUT_DROIT,  0);
    diriger_aiguillage(5,  TOUT_DROIT,  0);
    diriger_aiguillage(3,  DEVIE,       0);
    diriger_aiguillage(2,  TOUT_DROIT,  0);
    diriger_aiguillage(21, TOUT_DROIT,  0);
    diriger_aiguillage(20, DEVIE,       0);
    diriger_aiguillage(23, TOUT_DROIT,  0);
    diriger_aiguillage(17, TOUT_DROIT,  0);
    diriger_aiguillage(15, DEVIE,       0);
    diriger_aiguillage(14, DEVIE,       0);

    //Initialisation des aiguillages de la locomotive2
    diriger_aiguillage(22, TOUT_DROIT,       0);
    diriger_aiguillage(19, TOUT_DROIT,       0);
    diriger_aiguillage(16, TOUT_DROIT,       0);
    diriger_aiguillage(13, TOUT_DROIT,       0);
    diriger_aiguillage(10, TOUT_DROIT,      0);
    diriger_aiguillage(7,  TOUT_DROIT,      0);
    diriger_aiguillage(4,  TOUT_DROIT,      0);
    diriger_aiguillage(1,  TOUT_DROIT,      0);



    //Initialisation de la locomotive1
    int tabContactCritique1[2] = {14, 32};
    int tabFinContactCritique1[2] = {33, 6};
    int tabAiguillageCritique[2] = {22, 1};
    int tabAiguillageDeviation[2] = {2, 21};

    locomotive1.fixerNumero(1);
    locomotive1.fixerVitesse(13);
    locomotive1.fixerPosition(16, 23);
    locomotive1.fixerFinTour(23);
    locomotive1.fixerNbTourInverse(2);
    locomotive1.fixerContactCritique(tabContactCritique1);
    locomotive1.fixerFinContactCritique(tabFinContactCritique1);
    locomotive1.fixerDirectionAiguillageCritique(DEVIE);
    locomotive1.fixerAiguillageCritique(tabAiguillageCritique);
    locomotive1.fixerAiguillageDeviation(tabAiguillageDeviation);
    locomotive1.fixerDeviation(true);
    locomotive1.afficherMessage("Locomotive 1, Prete!");
    locomotive1.start();

    //Initialisation de la locomotive2
    int tabContactCritique2[2] = {4,28};
    int tabFinContactCritique2[2] = {30,2};

    locomotive2.fixerNumero(2);
    locomotive2.fixerVitesse(13);
    locomotive2.fixerPosition(21, 22);
    locomotive2.fixerFinTour(22);
    locomotive2.fixerNbTourInverse(2);
    locomotive2.fixerContactCritique(tabContactCritique2);
    locomotive2.fixerFinContactCritique(tabFinContactCritique2);
    locomotive2.fixerDirectionAiguillageCritique(TOUT_DROIT);
    locomotive2.fixerAiguillageCritique(tabAiguillageCritique);
    locomotive2.afficherMessage("Locomotive 2, Prete!");
    locomotive2.start();

    //Recupere les commandes du champ de texte et modifie
    //les priorites en fonction
    while(true)
    {
        QString commande = getCommand();

        if(commande == "Priorite_0")
        {
            afficher_message("Pas de priorite");
            Locomotive::fixerPriorite(0);
        }
        else if (commande == "Priorite_1")
        {
            afficher_message("Priorite pour la locomotive 2");
            Locomotive::fixerPriorite(1);
        }
        else if (commande == "Priorite_2")
        {
            afficher_message("Priorite pour la locomotive 1");
            Locomotive::fixerPriorite(2);
        }
        else
        {
            afficher_message("Commande non reconnu");
        }
    }

    return EXIT_SUCCESS;
}
