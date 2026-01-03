/*************************************************************************
                           Trajet  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( TRAJET_H )
#define TRAJET_H

//--------------------------------------------------- Interfaces utilisées
#include<cstddef>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
//défini par une ville de départ et une ville d'arrivée
//techniquement classe qui n'a pas de sens(quasi abstraite mais sans l'être)
//
//------------------------------------------------------------------------

class Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
  virtual void Afficher ()const;
  // Mode d'emploi :afficher un trajet
  //la version standard consistera simplement à afficheer : de villeDep à villeDest
  //
  // Contrat :ne fait pas de retour à la ligne
  //
  //virtual bool EstEquivalent( const Trajet & unTrajet)const;
  // Mode d'emploi :regarde si le trajet en paramètre est équivalent à l'objet appelé
  //un trajet est équivalent à un autre si les deux passent par les mêmes ville 
  //
  // Contrat : pas de surcharge pas de fonction 
  //
  const char* GetVilleDepart ()const;
  // Mode d'emploi :renvoie le nom de la ville de départ
  //
  // Contrat :
  //

  const char* GetVilleArrive()const; 
  // Mode d'emploi :renvoie le nom de la ville d'arrivée
  //
  // Contrat :
  //
  virtual Trajet* GetEtape(int i) const;
  virtual int CompternombreEtapes()const; 
  virtual int nbreEtapes()const;
//------------------------------------------------- Surcharge d'opérateurs
  Trajet & operator = ( const Trajet & unTrajet);
    // Mode d'emploi : copie le membre de droit dans le membre de gauche 
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
  Trajet ( const Trajet & Trajet );
  // Mode d'emploi (constructeur de copie): crée une copie de l'objet en paramètre
  //
  // Contrat :
  //
  
  Trajet (const char* uneVilleDepart, const char* uneVilleArrive, const char* unNom=NULL);
  // Mode d'emploi :
  //
  // Contrat :
  //
  
  virtual ~Trajet ( );
  // Mode d'emploi :
  //
  // Contrat :
  //
  
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
  //const char* moyenTransport;
  char* nom;
  char* villeDep;
  char* villeDest;

};

//-------------------------------- Autres définitions dépendantes de <Trajet>

#endif // TRAJET_H

