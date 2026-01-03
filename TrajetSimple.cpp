/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
#include <cstring>
#include "TrajetSimple.h"
//------------------------------------------------------ Include personnel
using namespace std;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void TrajetSimple::Afficher()const
  // Algorithme : on appelle déjà le afficher de Trajet et on ajoute " en MT" 
//
{ cout<<this->nbreEtapes()<<":";
  Trajet::Afficher();//affiche "de villeDep à villeDest"
  cout<<" en "<<moyenTransport;
} //----- Fin de Méthode



const char * TrajetSimple::GetMoyenTransport()const
// Algorithme :
//
{
  return moyenTransport;

} //----- Fin de Méthode
int TrajetSimple::nbreEtapes()const
{
    return 1;
}

//------------------------------------------------- Surcharge d'opérateurs
TrajetSimple & TrajetSimple::operator = ( const TrajetSimple & unTrajetSimple )
// Algorithme :
//
{
  if (this!=&unTrajetSimple){
    Trajet::operator= (unTrajetSimple);
    if(moyenTransport)
      delete [] moyenTransport;
    moyenTransport=new char[strlen(unTrajetSimple.moyenTransport)+1];
    strcpy(moyenTransport,unTrajetSimple.moyenTransport);
  }
  return *this;
  
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
TrajetSimple::TrajetSimple ( const TrajetSimple & unTrajetSimple ):Trajet(unTrajetSimple.villeDep,unTrajetSimple.villeDest,unTrajetSimple.nom)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <TrajetSimple>" << endl;
#endif
    moyenTransport=new char[strlen(unTrajetSimple.moyenTransport)+1];
    strcpy(moyenTransport,unTrajetSimple.moyenTransport);
    
} //----- Fin de TrajetSimple (constructeur de copie)


TrajetSimple::TrajetSimple ( const char* villeD, const char* villeA,const char* trans, const char* nom):Trajet(villeD,villeA,nom)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
    moyenTransport=new char[strlen(trans)+1];
    strcpy(moyenTransport,trans);
    
      
} //----- Fin de TrajetSimple


TrajetSimple::~TrajetSimple ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
    delete [] moyenTransport;
} //----- Fin de ~TrajetSimple


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

