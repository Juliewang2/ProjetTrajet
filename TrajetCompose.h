/*************************************************************************
                           TrajetCompose  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#if ! defined ( TRAJETCOMPOSE_H )
#define TRAJETCOMPOSE_H

//--------------------------------------------------- Interfaces utilisées
#include"Trajet.h"
#include"TrajetSimple.h"
#include<cstddef>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
//
//
//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
  void Afficher (  )const;
  // Mode d'emploi :
  //
  // Contrat :
  //
  bool EstEquivalent(const Trajet& unTrajet)const;
  // Mode d'emploi : dit si le trajet est équivalent ou non
  //un trajet est équivalent s'il à les même ville de départ ét d'arrivé et qu'il passe par les mêmes étapes
  //
  // Contrat : pour l'instant la méthode renvoit toujours false car elle a besoin de la surchargee poour être efficaces
  //
  
  //bool EstEquivalent(const TrajetCompose& unTrajetCompo)const;
  // Mode d'emploi :
  //
  // Contrat :
  //


//------------------------------------------------- Surcharge d'opérateurs
  TrajetCompose & operator = ( const TrajetCompose & unTrajetCompose);
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
  TrajetCompose ( const TrajetCompose & unTrajetCompose);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

  TrajetCompose(const TrajetSimple* tabTrajet,int tailleTraj,const char* unNom=NULL);
    // Mode d'emploi :on construit le trajet composé à partir d'un tableau de TrajetSimple
    //
    // Contrat :le tableau ne doit pas être vide (et taille doit être >1)
    //

  TrajetCompose(const TrajetSimple* const* tabTrajet,int tailleTraj,const char* unNom=NULL);
    // Mode d'emploi :on construit le trajet composé à partir d'un tableau de pointeur de TrajetSimple
    //
    // Contrat :le tableau ne doit pas être vide (et taille doit être >1)
    //
  Trajet* GetEtape(int i) const;
  int CompternombreEtapes()const; 
  virtual ~TrajetCompose ();
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
  TrajetSimple** compoTrajet;
  int tailleTrajet;
};

//-------------------------------- Autres définitions dépendantes de <TrajetCompose>
bool TrajetValide(const TrajetSimple*const* tabTrajet,int taille);


#endif // TRAJETCOMPOSE_H

