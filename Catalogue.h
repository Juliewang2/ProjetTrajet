/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H
#include<iostream>
#include<cstring>
#include<fstream>
//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "TADListeTrajet.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
//
//
//------------------------------------------------------------------------

class Catalogue 
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
  bool AjoutTrajet (Trajet& unTrajet);
  // Mode d'emploi : prend en paramètre un trajet et l'intègre dans le catalogue
  //
  // Contrat :
  //

  void Affichage ()const;
  // Mode d'emploi : affiche le trajet
  //
  // Contrat :
  //
  void Sauvgarder ();
  void Charger();
  void RechercheParcours (const char * villeDepart, const char* villeArrivee)const;
  // Mode d'emploi : affiche les trajet qui parte de villeDepart et qui arrivent à villeArrivee
  //renvoie le nombre de trajet trouvé
  // Contrat :si il n'y a aucun trajet correspondant, la fonction affichera "aucun trajet correspondant trouvé dans le catalogue
  //
  bool VerifieRecherche(const char* villeDepart,const char* villeArrivee)const;


//------------------------------------------------- Surcharge d'opérateurs
  Catalogue & operator = (  Catalogue & unCatalogue );
  // Mode d'emploi :
  //
  // Contrat :
  //


//-------------------------------------------- Constructeurs - destructeur
  

  Catalogue (Catalogue & unCatalogue );
  // Mode d'emploi (constructeur de copie) :
  //
  // Contrat :
  //
  
  Catalogue ( );
  // Mode d'emploi : crée un catalogue vide, on utilisera les méthode pour 
  //
  // Contrat :
  //
  
  virtual ~Catalogue ( );
  // Mode d'emploi :
  //
  // Contrat :
  //
  friend std::ostream & operator << (std::ostream & flux,const Catalogue & unCtalogue);
  friend std::istream & operator>>(std::istream & in,Catalogue & unCatalogue);
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
  TADListeTrajet listeTrajet;
  
};

//-------------------------------- Autres définitions dépendantes de <Catalogue>
#endif // CATALOGUE_H

