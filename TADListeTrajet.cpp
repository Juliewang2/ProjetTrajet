/*************************************************************************
                           TADListeTrajet  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <TADListeTrajet> (fichier TADListeTrajet.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
//------------------------------------------------------ Include personnel
#include "TADListeTrajet.h"
#include "Trajet.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void TADListeTrajet::Afficher ()const
// Algorithme :parcours la chaine en commençant par la tête et continuant en passant par le pointeur suivant
//la fonction dit également si la chaine est vide(peut se court-circuiter si la vérification est faite en amont
//cette fonction est nécessaire pour afficher les élément de la liste qui sont encapsulé
{
  const ChaineTrajet* temp;//enlever le const pour le test
  if(tete==nullptr){//si chaine vide
    cout<<"la chaine est vide"<<endl;
  }
  else{
    temp=tete;
    while(temp!=nullptr){
      (temp->traj)->Afficher();
      cout<<endl;
      temp=temp->suivant;
    }    
  }
} //----- Fin de Afficher

TADListeTrajet TADListeTrajet::TrajetMatchingSimple(const char* villeDepart,const char* villeArrive)const
// Algorithme :parcours les chaines en commençant par la tête à la recherche de trajet commençant à ville départ et se terminant à villeArrive
// la liste renvoyé commencera par le premier élément trouvé (ajout en queue à chaque match)
{
  TADListeTrajet res;
  ChaineTrajet* cellI=tete;
  while (cellI!=nullptr){
    if (strcmp((cellI->traj)->GetVilleDepart(),villeDepart)==0)
      if(strcmp((cellI->traj)->GetVilleArrive(),villeArrive)==0)
	res.AjouterEnQueue(cellI->traj);
    cellI=cellI->suivant;
  }
  return res;
  
}
void TADListeTrajet::AjouterEnTete(Trajet* unTrajet)
// Algorithme :utilise le pointeur de tete pour ajouter un trajet via une nouvelle chaine
// on considère l'ancienne tete comme le suivant de la nouvelle tete
//si l'élément ajouté est le seul de la liste, on précise que la queue pointe également sur ce seul élément
{
  ChaineTrajet* nouvelleCell=new ChaineTrajet();
  nouvelleCell->traj=unTrajet;
  nouvelleCell->suivant=tete;
  tete=nouvelleCell;
  if(queue==nullptr){//si la chaine était vide
    queue=tete;
  }
  taille++;
} //----- Fin de AjouterEnTete

void TADListeTrajet::AjouterEnQueue(Trajet* unTrajet )
// Algorithme : utitlise le pointeur de queue pour ajouter un élément
//on considère la nouvelle queue comme le suivant de l'ancienne queue
//si l'élément ajouté est le seul de la liste, la tete et la queue pointe directement sur cette nouvelle cellule
  
{
  ChaineTrajet* nouvelleCell=new ChaineTrajet();
  nouvelleCell->traj=unTrajet;
  nouvelleCell->suivant=nullptr;
  if(tete==nullptr){//si la chaine était vide
    queue=nouvelleCell;
    tete=nouvelleCell;
  }
  else{
    queue->suivant=nouvelleCell;
    queue=nouvelleCell;
  }
  taille++;
  
  
} //----- Fin de AjouterEnQueue
const Trajet&TADListeTrajet::TrajetEnTete()const
// Algorithme : renvoie le trajet de l'élément en tete en tant que référence constante
// si la liste est vide, on provoque une erreur (l'utilisateur doit être responsable aussi)

{
  return *(tete->traj);
}

const Trajet&TADListeTrajet::TrajetEnQueue()const
// Algorithme : renvoie le trajet de l'élément en queue en tant que référence constante
// si la liste est vide, on provoque une erreur (l'utilisateur doit être responsable aussi)

{
  return *(queue->traj);
}

bool TADListeTrajet::ChaineEstVide()const
// Algorithme : on vérifie si la tête vaut null
//
{
  if(tete==nullptr)
    return true;
  return false;
  
} //----- Fin de ChaineEstVide
int TADListeTrajet::Taille()const
// Algorithme : on renvoie la taille
{
  return taille;
}

Trajet* TADListeTrajet::Pop(){
  //Algorithme :on renvoie l'élément en tête que l'on retire de la liste
  ChaineTrajet* temp;
  Trajet* trajetTete=nullptr;
  
  if(tete!=nullptr){
    trajetTete=tete->traj;
    temp=tete;
    tete=tete->suivant;
    delete temp;
    taille--;
    if(tete==nullptr){
      queue=tete;
    } 
  }
  return trajetTete;
}
Trajet* TADListeTrajet::getTrajet(int i)
{    int count=0;
     ChaineTrajet* p = tete;
     while (p!=nullptr&& count<i ){
      p=p->suivant;
        count++;
     }
     if (p!=nullptr && count==i){
       return p->traj;
     }
     return nullptr;
}
ChaineTrajet* TADListeTrajet::getTete()const
{
  return tete;
}  

//------------------------------------------------- Surcharge d'opérateurs
TADListeTrajet & TADListeTrajet::operator = ( const TADListeTrajet & unTADListeTrajet )
// Algorithme : on fait la m^me chose que dans le constructeur de copie 
//
{
  ChaineTrajet* temp;
  if(this!=&unTADListeTrajet){
    temp=tete;
    while(temp!=nullptr){
      temp=tete->suivant;
      delete tete;
      tete=temp;
    }
    queue=nullptr;
    if(unTADListeTrajet.tete!=nullptr){
      tete=new ChaineTrajet();
      tete->traj=(unTADListeTrajet.tete)->traj;
      tete->suivant=nullptr;
      queue=tete;
      temp=unTADListeTrajet.tete;
      while(temp->suivant!=nullptr){
	
        temp=temp->suivant;
        queue->suivant=new ChaineTrajet();
        queue=queue->suivant;
        queue->traj=temp->traj;
        queue->suivant=nullptr;
      }
    }
    taille=unTADListeTrajet.taille;
  }
  return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
TADListeTrajet::TADListeTrajet (const TADListeTrajet & unTADListeTrajet ):taille(unTADListeTrajet.taille)
// Algorithme : si la liste n'est pas vide, on initialise la tete et la queue avec le premier élément
//puis on parcours la liste de la tete a la queue en ajoutant en queue dans le this l'élément actuel
{
  
#ifdef MAP
  cout << "Appel au constructeur de copie de <TADListeTrajet>" << endl;
#endif
  ChaineTrajet* temp=unTADListeTrajet.tete;
  tete=nullptr;
  queue=nullptr;
  if(unTADListeTrajet.tete!=nullptr){
    tete=new ChaineTrajet();
    tete->traj=(unTADListeTrajet.tete)->traj;
    tete->suivant=nullptr;
    queue=tete;
    while(temp->suivant!=nullptr){
      temp=temp->suivant;
      temp->traj->Afficher();
      queue->suivant=new ChaineTrajet();
      queue=queue->suivant;
      queue->traj=temp->traj;
      queue->suivant=nullptr;
    }
  }
} //----- Fin de TADListeTrajet (constructeur de copie)


TADListeTrajet::TADListeTrajet ( ):tete(nullptr),queue(nullptr),taille(0)
// Algorithme :
//
{
#ifdef MAP
  cout << "Appel au constructeur de <TADListeTrajet>" << endl;
#endif
} //----- Fin de TADListeTrajet


TADListeTrajet::~TADListeTrajet ( )
// Algorithme :on se positionne en tete, on garde un pointeur sur le suivant et on supprime la tete actuelle et on recommence
//
{
#ifdef MAP
  cout << "Appel au destructeur de <TADListeTrajet>" << endl;
#endif
  ChaineTrajet* temp;
  temp=tete;
  while(temp!=nullptr){
    temp=tete->suivant;
    delete tete;
    tete=temp;
  }   
} //----- Fin de ~TADListeTrajet


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

