/*************************************************************************
                           Trajet  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Trajet> (fichier Trajet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <cstddef>
//------------------------------------------------------ Include personnel
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Trajet::Afficher()const
// Algorithme :Affiche le trajet avec des cout en consultant villeDep et villeDest
//
{
  cout<<"de "<<villeDep<<" à "<<villeDest;
}//----- Fin de Afficher

//bool Trajet::EstEquivalent(const Trajet & unTrajet)const
// Algorithme :Affiche le trajet avec des cout en consultant villeDep et villeDest
//
//{
//  if (strcmp(villeDep,unTrajet.villeDep)==0&&strcmp(villeDest,unTrajet.villeDest)==0){
//    return true;
//  }
//  else{
//    return false;
//  }
//}//----- Fin de Afficher

const char* Trajet::GetVilleDepart ()const
// Algorithme :renvoie de l'attribut villeDep
//
{
  return  villeDep;
} //----- Fin de GetVilleDepart


const char* Trajet::GetVilleArrive ()const
// Algorithme :renvoie de l'attribut villeDep
//
{
  return villeDest;
} //----- Fin de GetVilleArrive
//------------------------------------------------- Surcharge d'opérateurs
Trajet & Trajet::operator = ( const Trajet & unTrajet )
// Algorithme : même algo que sur le constructeur de copie à quelque détails près(et cela vaut de manière assez générale pour le =) 
//    -on réaffecte des attribut déjà initialisé, donc si ce sont des pointeur, il faut les delete.
//    -comme on delete les attribut, il faut s'assurer avant tout que le paramètre, le membre de droite, ne soit pas le même que this, le membre de gauche
//            sinon on aura des erreurs bizarre parce qu'on veut affecter à une variable une valeur que l'on vient de delete
//    -enfin il faut renvoyer l'objet de gauche (donc this)
{
  if(this!=&unTrajet){
    if(villeDep)
      delete [] villeDep;
    villeDep=new char[strlen(unTrajet.villeDep)+1];
    strcpy(villeDep,unTrajet.villeDep);

    if(villeDest)
      delete [] villeDest;
    villeDest=new char[strlen(unTrajet.villeDest)+1];
    strcpy(villeDest,unTrajet.villeDest);
    
    if(unTrajet.nom){
      if(nom)
	delete [] nom;
      nom=new char[strlen(unTrajet.nom)+1];
      strcpy(nom,unTrajet.nom);
    }
    else
      nom=NULL;
  }
  return *this;
  
} //----- Fin de operator =
Trajet* Trajet::GetEtape(int i) const{
  return nullptr;
}
int Trajet::CompternombreEtapes()const{
  return 1;
}
int Trajet::nbreEtapes()const{
  return 1;
}

//-------------------------------------------- Constructeurs - destructeur
Trajet::Trajet (const char* uneVilleDepart, const char* uneVilleArrive, const char* unNom)
// Algorithme :appelle strlen puis strcpy sur tous les paramètre pour copier les chaine de caractère
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Trajet>" << endl;
#endif
    villeDep=new char[strlen(uneVilleDepart)+1];
    strcpy(villeDep,uneVilleDepart);

    villeDest=new char[strlen(uneVilleArrive)+1];
    strcpy(villeDest,uneVilleArrive);

    if(unNom){
      nom=new char[strlen(unNom)+1];
      strcpy(nom,unNom);
    }
    else
      nom=NULL;
    

} //----- Fin de Trajet



Trajet::Trajet ( const Trajet & unTrajet )
// Algorithme : déclaration avec strlen puis initialisation avec strcpy de tout les attribut en se servant de ceux du paramètre pour copier 
// typiquement on met chaque attribut du paramètre dans les appel de strlen et strcpy
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Trajet>" << endl;
#endif
    
    villeDep=new char[strlen(unTrajet.villeDep)+1];
    strcpy(villeDep,unTrajet.villeDep);

    villeDest=new char[strlen(unTrajet.villeDest)+1];
    strcpy(villeDest,unTrajet.villeDest);

    if(unTrajet.nom){
      nom=new char[strlen(unTrajet.nom)+1];
      strcpy(nom,unTrajet.nom);
    }
    else
      nom=NULL;
    
    
} //----- Fin de Trajet (constructeur de copie)



Trajet::~Trajet ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Trajet>" << endl;
#endif
    delete [] villeDep;
    delete [] villeDest;
    if(nom)
      delete[] nom;
} //----- Fin de ~Trajet


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

