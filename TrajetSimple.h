/*************************************************************************
                           TrajetSimple.h  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include <cstddef>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
//un trajet simple est défini par une ville de départ, une ville d'arrivée et un moyen de transport 
//
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
  //----------------------------------------------------- Méthodes publiques
  void Afficher()const;
  // Mode d'emploi :affiche le trajetSimple sous la forme: "de Dep à Dest en MT"
  //
  // Contrat :
  //

  const char* GetMoyenTransport()const;
  // Mode d'emploi :renvoie le moyen de transport
  //
  // Contrat :
  //
  int nbreEtapes()const;

//------------------------------------------------- Surcharge d'opérateurs
  TrajetSimple & operator = ( const TrajetSimple & unTrajetSimple );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
  TrajetSimple ( const TrajetSimple & unTrajetSimple );
  // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

  TrajetSimple (const char* villeD, const char* villeA,const char* trans, const char* name=NULL );
    // Mode d'emploi :
    //
    // Contrat :
    //

  virtual ~TrajetSimple ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
 
//----------------------------------------------------- Attributs protégés
  char* moyenTransport;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // XXX_H

