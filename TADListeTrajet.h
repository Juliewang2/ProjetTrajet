/*************************************************************************
                           TADListeTrajet  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TADListeTrajet> (fichier TADListeTrajet.h) ----------------
#if ! defined ( TADLISTETRAJET_H )
#define TADLISTETRAJET_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef struct ChaineTrajet{//utilisation d'une classe contre productif dans ce cas spécifique (casse le const)
  Trajet* traj;
  struct ChaineTrajet* suivant;
}ChaineTrajet;
  
//------------------------------------------------------------------------
// Rôle de la classe <TADListeTrajet>
//classe permettant de gérer des ChaineTrajet et de les ordonner (on peut
//la voir comme l'interface des Chaine)
//le concept de queue prend son sens avec la méthode afficher (la tete est
//le premier élément affiché et la queue est le dernier)
//
//a la base, les trajet de la liste sont censé être intouchable par cette dernière
//cela dit, il faut aussi gérer le cas où les utilisateur du TADListe sont les propriétaire du trajet et que la liste est leur seule référence
//pour s'assurer que tout le monde soit détruit la propriété traj du maillon n'est plus const(impliquant que tout les ajout ne seront plus const)
//comme la liste n'est toujours pas propriétaire, une méthode pop permettra au proprio de récupérer son trajet
//ça crée d'autre problème mais pour l'instant la solution est difficile àimaginer (en fait non mais on n'est pas parti sur ça)
//

//------------------------------------------------------------------------

class TADListeTrajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

  //bool DejaPresent(const Trajet* unTrajet);
  // Mode d'emploi :dit si un trajet équivalent se trouve dans la liste
  //
  // Contrat : pour l'instant la fonction marche bizarement car la surcharge est interdite :(
  //si le trajet est composé,quoi qu'il se passe il renverra faux
  //a l'inverse, si c'est un trajet simple qui appelle, le résultat portera juste sur si les ville de départ et d'arrive sont égales
  
  TADListeTrajet TrajetMatchingSimple(const char* villeDepart,const char* villeArrive)const;
  // Mode d'emploi :recherche dans la liste les trajet commençant par villeDepart et finissant par villeArrive
  //renvoie un TADListe contenant tout les trajet correspondant
  // Contrat : les chaine doivent être écrite en format c/c++
  //
  
  const Trajet& TrajetEnTete()const;
  // Mode d'emploi : renvoie une référence constante sur le Trajet en tete de Liste
  //
  // Contrat : la liste ne doit pas être vide
  //
  const Trajet& TrajetEnQueue()const;
  // Mode d'emploi : renvoie une référence constante sur le Trajet en queue de Liste
  //
  // Contrat : la liste ne doit pas être vide
  //
  void AjouterEnQueue (Trajet* unTrajet);
  // Mode d'emploi : ajoute le trajet en queue de liste
  //
  // Contrat :
  //
  void AjouterEnTete(Trajet* unTrajet);
  // Mode d'emploi : ajoute le trajet en tete de liste
  //
  // Contrat :
  //
  Trajet* Pop();
  //mode d'emploie: supprime l'élément en tête qu'il renvoie
  
  void Afficher()const;
  //Mode d'Emploie : affiche les élément de la chaine en commençant par la tete


  int Taille()const;
  // //Mode d'Emploie : renvoie la taille de la chaine

  bool ChaineEstVide()const;
  //Mode d'emploie : dit si oui ou non la chaine est vide
  Trajet* getTrajet(int i);
  ChaineTrajet* getTete()const;
//------------------------------------------------- Surcharge d'opérateurs
  TADListeTrajet & operator = ( const TADListeTrajet & unTADListeTrajet );
  // Mode d'emploi :
  //
  // Contrat :
  //


//-------------------------------------------- Constructeurs - destructeur
    TADListeTrajet ( const TADListeTrajet & unTADListeTrajet );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    TADListeTrajet ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~TADListeTrajet ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
  ChaineTrajet* tete;
  ChaineTrajet* queue;
  int taille;
};

//-------------------------------- Autres définitions dépendantes de <TADListeTrajet>

#endif // TADLISTETRAJET_H

