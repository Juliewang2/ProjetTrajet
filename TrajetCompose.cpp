/*************************************************************************
                           TrajetCompose  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
//------------------------------------------------------ Include personnel
#include "TrajetCompose.h"
#include "TrajetSimple.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void TrajetCompose::Afficher()const
// Algorithme :
//
{
  int i;
  cout<<CompternombreEtapes()<<":";
  for(i=0;i<tailleTrajet;i++){
    compoTrajet[i]->Afficher();
    if(i!=(tailleTrajet-1))
      cout<<" - ";
  }
} //----- Fin de Afficher
bool TrajetCompose::EstEquivalent(const Trajet& unTrajet)const{
// Algorithme :normallement je devrais avoir plusieurs comportement en fonction de si le paramètre est composé ou non
// dans la mesure ou la surcharge et le transtypage sont interdits, le cas le plus adapté serait de renvoyer constamment faux
  //puisque qu'il est peu probable que deux trajet composé soit équivalent (et un trajet simple ne sera quasiment jamais
  //équivalent à un trajet composé)
  return false;
}
  

//------------------------------------------------- Surcharge d'opérateurs
TrajetCompose & TrajetCompose::operator = ( const TrajetCompose & unTrajetCompose )
// Algorithme :
//
{
  int i;
  if(this!=&unTrajetCompose){
    tailleTrajet=unTrajetCompose.tailleTrajet;
    
    for(i=0;i<tailleTrajet;i++)
      delete compoTrajet[i];
    delete [] compoTrajet;
    
    compoTrajet=new TrajetSimple*[tailleTrajet];
    for(i=0;i<tailleTrajet;i++)
      compoTrajet[i]=new TrajetSimple(*(unTrajetCompose.compoTrajet[i]));
  }
  return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
TrajetCompose::TrajetCompose ( const TrajetCompose & unTrajetCompose ):Trajet(unTrajetCompose.villeDep,unTrajetCompose.villeDest,unTrajetCompose.nom),tailleTrajet(unTrajetCompose.tailleTrajet)
  // Algorithme :
  //
{
#ifdef MAP
  cout << "Appel au constructeur de copie de <TrajetCompose>" << endl;
#endif
  int i;
  compoTrajet=new TrajetSimple*[unTrajetCompose.tailleTrajet];
  for(i=0;i<tailleTrajet;i++){
    compoTrajet[i]=new TrajetSimple(*(unTrajetCompose.compoTrajet[i]));
    }
} //----- Fin de TrajetCompose (constructeur de copie)


TrajetCompose::TrajetCompose(const TrajetSimple* tabTrajet,int uneTailleTraj,const char* unNom):Trajet(tabTrajet[0].GetVilleDepart(),tabTrajet[uneTailleTraj-1].GetVilleArrive(),unNom),tailleTrajet(uneTailleTraj)
// Algorithme :on fait une allocation dynamique du tableau, puis pour chaque case on alloue dynamiquement une case de type TrajetSimple
//faire de trajetCompo un tableau de pointeur permet de "delayer" l'appel du constructeur qui sinon se ferait à l'initialisation du tableau
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
    int i;
    compoTrajet=new TrajetSimple*[uneTailleTraj];
    for(i=0;i<uneTailleTraj;i++){
      compoTrajet[i]=new TrajetSimple(tabTrajet[i]);
    }
} //----- Fin de TrajetCompose
int TrajetCompose::CompternombreEtapes()const{
    return tailleTrajet;
}
Trajet* TrajetCompose::GetEtape(int i) const
{ return compoTrajet[i]; }
TrajetCompose::TrajetCompose(const TrajetSimple* const* tabTrajet,int uneTailleTraj,const char* unNom):Trajet(tabTrajet[0]->GetVilleDepart(),tabTrajet[uneTailleTraj-1]->GetVilleArrive(),unNom),tailleTrajet(uneTailleTraj)
// Algorithme :on fait une allocation dynamique du tableau, puis on alloue une nouvelle case
//
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetCompose>" << endl;
#endif
    int i;
    compoTrajet=new TrajetSimple*[uneTailleTraj];
    for(i=0;i<uneTailleTraj;i++){
      compoTrajet[i]=new TrajetSimple(*(tabTrajet[i]));
    }
} //----- Fin de TrajetCompose

TrajetCompose::~TrajetCompose ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetCompose>" << endl;
#endif
    int i;
    for(i=0;i<tailleTrajet;i++)
      delete compoTrajet[i];
    delete [] compoTrajet;
} //----- Fin de ~TrajetCompose


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- fonction ordinaire
bool TrajetValide( const TrajetSimple* const* tabTrajets,int taille){
  //parcours le tableau de trajet et vérifie si les trajet sont lié
  //deux trajet t1 et t2 sont lié si t1.villeArrive==t2.villeDepart
  //un trajet composé qui n'est pas constitué exclusivement de trajet lié n'est pas valide
  int t;
  if(taille==0)
    return false;//un trajet composé vide n'est pas valide
  else if(taille==1)
    return true;//un trajet composé ne contenant qu'un seul élément est forcémment valide
  else{
    for(t=1;t<taille;t++){
      if(strcmp(tabTrajets[t-1]->GetVilleArrive(),tabTrajets[t]->GetVilleDepart())!=0){
	return false;//on a trouvé deux trajet non lié: on arrête la fonction et on renvoie false
      }
    }
    return true;//la recherche n'a pas trouvé de problème: on renvoie true
  }
}

