#include<iostream>
#include<cstring>
#include<fstream>
#include <limits>
#include"Catalogue.h"
#include"TrajetSimple.h"
#include"TrajetCompose.h"
using namespace std;
#define TAILLE_MAX_CHAINE 100

enum Operation{AJOUT_TRAJ_S=1,AJOUT_TRAJ_COMPO=2,AFFICHAGE=3,RECHERCHE=4,QUITTER=5,SAUVGARDER=6,CHARGER=7};
void clearInput(){
  //vide le buffer d'entrée
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(),'\n');//ignorer les caracteres inutiles jusqu'a la fin de la ligne
}
TrajetSimple* CreateTrajetSimple(){
  //Demaande à l'utilisateur le Trajet Simple à Ajouter
  TrajetSimple* trajet(nullptr);
  char villeDepart[TAILLE_MAX_CHAINE];
  char villeArrive[TAILLE_MAX_CHAINE];
  char moyenTransport[TAILLE_MAX_CHAINE];
  cout<<"veuillez entrer une ville de départ:\t";
  cin>>villeDepart;
  cout<<"veuillez entrer une ville d'arrivée:\t";
  cin>>villeArrive;
  cout<<"veuillez donner un moyen de transport:\t";
  cin>>moyenTransport;
  trajet=new TrajetSimple(villeDepart,villeArrive,moyenTransport);
  return trajet;
}


TrajetCompose* CreateTrajetCompose(){
  //crée un trajet composé basé sur les information donné par l'utilisateur
  //renvoie nullptr au moindre problème, incluant un trajet invalide
  //
  //comme on utilise un tableau dynamique de pointeur, impliquant une initialisation dynamique des trajet simple
  //et que le constructeur des trajets composé fait une copie profonde du tableau servant à l'initialisation (donc pas de transfert de propriété)
  //on doit faire non seulement un delete pour le tableau mais aussi pour les élément à l'intérieur (qui ne servent que de patron pour le trajet composé)
  
  TrajetCompose* trajet=nullptr;
  TrajetSimple** tabTrajet;
  int t;
  int taille=0;
  cout<<"veuillez entrer un nombre d'étape:\t";
  if (!(cin>>taille)||taille<1){
    cerr<<"entree invalide"<<endl;
    clearInput();
    return nullptr;
  }
  tabTrajet=new TrajetSimple*[taille];
  for(t=0;t<taille;t++){
    cout<<"trajet n°"<<t+1<<": "<<endl;
    tabTrajet[t]=CreateTrajetSimple();
  }
  if(TrajetValide(tabTrajet,taille)){
    trajet=new TrajetCompose(tabTrajet,taille);
  }
  else if (TrajetValide(tabTrajet,taille)==false){
    cout<<"liaison invalide"<<endl;
  }
  
  for(t=0;t<taille;t++){
    delete tabTrajet[t];
  }
  delete [] tabTrajet; 
  return trajet;
  
}

void Rechercher(const Catalogue & cat){
  // demande à l'utilisateur quelles sont le départ ét l'arrivé
  char villeDepart[TAILLE_MAX_CHAINE];
  char villeArrive[TAILLE_MAX_CHAINE];
  cout<<"D'où voulez vous partir?\t";
  cin>>villeDepart;
  cout<<"quels sera votre ville de destination?\t";
  cin>>villeArrive;
  cat.RechercheParcours(villeDepart,villeArrive);
}
int main(){
  Catalogue cata;
  int numOp(0);
  Trajet* trajetAAjouter;
  cout<<"Bienvenue dans notre application de gestion de trajets"<<endl;
  while(numOp!=QUITTER){
    numOp=0;
    cout<<"Quelle opération souhaitez-vous effectuer?"<<endl;
    cout<<AJOUT_TRAJ_S<<":\t Ajout d'un Trajet Simple"<<endl;
    cout<<AJOUT_TRAJ_COMPO<<":\t Ajout d'un Trajet Composé"<<endl;
    cout<<AFFICHAGE<<":\t Affichage du Catalogue"<<endl;
    cout<<RECHERCHE<<":\t Recherche d'itinéraire possible pour un road trip"<<endl;
    cout<<QUITTER<<":\t Quitter l'application"<<endl;
    cout<<SAUVGARDER<<":\t Sauvegarder le catalogue dans un fichier"<<endl;
    cout<<CHARGER<<":\t Charger le catalogue depuis un fichier"<<endl;
    cout<<"CHOIX => :";
    if (!(cin>>numOp)){
      cerr<<"entrée invalide, veuillez réessayer"<<endl;
      clearInput();
      continue;
    }
    cout<<endl;
    
    switch(numOp){
    case AJOUT_TRAJ_S:
      trajetAAjouter=CreateTrajetSimple();
      if(trajetAAjouter==nullptr){
	       cout<<"echec de l'ajout"<<endl;
      }
      else{
         if (strcmp(trajetAAjouter->GetVilleDepart(),trajetAAjouter->GetVilleArrive())==0){
              cout<<"Le trajet ne peut pas commencer et se finir dans la meme ville."<<endl;
              delete trajetAAjouter;
              break;
         }
         else if (cata.VerifieRecherche(trajetAAjouter->GetVilleDepart(),trajetAAjouter->GetVilleArrive())==true){
              cout<<"Le trajet que vous essayez d'ajouter existe déjà dans le catalogue."<<endl;
              delete trajetAAjouter;
              break;
         }
	       cata.AjoutTrajet(*trajetAAjouter);//transfert de propriété de la case mémoire pointé par AjoutTrajet
	       cout<<"trajet bien ajouté"<<endl;
      }
      break;
      
    case AJOUT_TRAJ_COMPO:
    { bool invalide=false;
      trajetAAjouter=CreateTrajetCompose();
      if(trajetAAjouter==nullptr){
	       cout<<"echec de l'ajout"<<endl;
         break;
      }
      else{
         if (strcmp(trajetAAjouter->GetVilleDepart(),trajetAAjouter->GetVilleArrive())==0){
              cout<<"Le trajet ne peut pas commencer et se finir dans la meme ville."<<endl;
              delete trajetAAjouter;
              break;
         }
         else if (cata.VerifieRecherche(trajetAAjouter->GetVilleDepart(),trajetAAjouter->GetVilleArrive())==true){
              cout<<"Le trajet que vous essayez d'ajouter existe déjà dans le catalogue."<<endl;
              delete trajetAAjouter;
              break;
         }
         else if (trajetAAjouter->CompternombreEtapes()>1){
                for (int i=0;i<trajetAAjouter->CompternombreEtapes();i++){
                      if (strcmp((trajetAAjouter->GetEtape(i))->GetVilleDepart(),(trajetAAjouter->GetEtape(i))->GetVilleArrive())==0){
                          cout<<"Le trajet composé contient une étape invalide où la ville de départ et la ville d'arrivée sont les mêmes."<<endl;
                          invalide=true;
                          break;
                      }
                }
          }
          if (invalide){
            delete trajetAAjouter;
            break;
          }
	       cata.AjoutTrajet(*trajetAAjouter);//transfert de propriété de la case mémoire pointé par AjoutTrajet
	       cout<<"trajet bien ajouté"<<endl;
         break;
      }
    }  
      
    case AFFICHAGE:
      cata.Affichage();
      break;
      
    case RECHERCHE:
      Rechercher(cata);
      break;

    case QUITTER:
      cout<<"sOlONg"<<endl;
      break;
    case SAUVGARDER:
         cata.Sauvgarder();
         break;    
    case CHARGER:
        cata.Charger();
        break;
    default:
      cerr<<"opération non définie"<<endl;
      break;
    }
    
    cout<<endl;
  }
  
  return 0;
}
