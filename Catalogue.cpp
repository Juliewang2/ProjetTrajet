/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

//---------------------------------------------------------------- INCLUDE

  //-------------------------------------------------------- Include système
    using namespace std;
    #include <iostream>
    #include <fstream>

  //------------------------------------------------------ Include personnel
    #include "Catalogue.h"
    #include "TADListeTrajet.h"
    #include "Trajet.h"
    #include "TrajetSimple.h"
    #include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Catalogue::Affichage()const
  // Algorithme : appelle la méthode Affichage de la listeTrajet
  //(comme on a ajouter les élément par la queue, l'affichage est ordonné (parce qu'il commence par la tête)
  //court circuitage du cas ou la liste est vide
{
  if(listeTrajet.ChaineEstVide()){
    cout<<"Le catalogue est vide"<<endl;
  }
  else{
    cout<<"nombre de trajet dans le catalogue:\t"<<listeTrajet.Taille()<<endl;
    cout<<"contenue:"<<endl<<"{"<<endl;
    listeTrajet.Afficher();
    cout<<"}"<<endl;
  }
}
void Catalogue::Sauvgarder()
{    ofstream outputFile;
     int j=0;
     outputFile.open("Sauvgarder.txt");
     if (outputFile.is_open()){
        while (j<listeTrajet.Taille()){
              Trajet* currentTrajet=listeTrajet.getTrajet(j);
              if (currentTrajet==nullptr){
                j++;
                continue;
              }
              if (typeid(*currentTrajet)==typeid(TrajetSimple)){
                 TrajetSimple* ts = dynamic_cast<TrajetSimple*>(currentTrajet);
                 outputFile<<ts->nbreEtapes()<<"@"<<currentTrajet->GetVilleDepart()<<"@"<<currentTrajet->GetVilleArrive()<<"@"<<ts->GetMoyenTransport()<<endl;
                 j++;
                }
              else if (typeid(*currentTrajet)==typeid(TrajetCompose)){
                 int i;
                 TrajetCompose* tc=dynamic_cast<TrajetCompose*>(currentTrajet);
                 outputFile<<tc->CompternombreEtapes()<<"@";
                 for (i=0;i<tc->CompternombreEtapes();i++){
                      TrajetSimple* ts=dynamic_cast<TrajetSimple*>(tc->GetEtape(i));
                      outputFile<<tc->GetEtape(i)->GetVilleDepart()<<"@"<<tc->GetEtape(i)->GetVilleArrive()<<"@"<<ts->GetMoyenTransport();
                      if (i==tc->CompternombreEtapes()-1){
                        outputFile<<endl;
                      }
                      else{
                        outputFile<<"@";
                      }
                 }
                 j++;
              }    
        }       
    outputFile.close();
    cout<<"catalogue est sauvgardé"<<endl;   
     }
}
void Catalogue::Charger()
{   ifstream inputFile;
    inputFile.open("sauvgarder.txt");
    char ligne[300];
    char* villeDep;
    char* villeArr;
    char* moyenTransport;
    char* nombreEtapes;
    if (inputFile.is_open()){
        while (inputFile.getline(ligne,300)){
            nombreEtapes=strtok(ligne,"@");
            if (nombreEtapes==nullptr){
              continue;
            }
            if (strcmp(nombreEtapes,"1")==0){
               villeDep=strtok(NULL,"@");
               villeArr=strtok(NULL,"@");
               moyenTransport=strtok(NULL,"@");
               if (villeDep==nullptr||villeArr==nullptr||moyenTransport==nullptr){
                  continue;
               }
               TrajetSimple* trajet=new TrajetSimple(villeDep,villeArr,moyenTransport);
               listeTrajet.AjouterEnQueue(trajet);
            }
            else if (strcmp(nombreEtapes,"1")!=0){
                int j;
                int nombreEtapesInt=atoi(nombreEtapes);
                TrajetSimple** trajetTab=new TrajetSimple*[nombreEtapesInt];
                for (j=0;j<nombreEtapesInt;j++){
                     villeDep=strtok(NULL,"@");
                     villeArr=strtok(NULL,"@");
                     moyenTransport=strtok(NULL,"@");
                     if (villeDep==nullptr||villeArr==nullptr||moyenTransport==nullptr){
                         for (int k=0;k<j;k++){
                            delete trajetTab[k];
                         }
                         delete [] trajetTab;
                         break;
                      }
                     trajetTab[j]=new TrajetSimple(villeDep,villeArr,moyenTransport);
                }
                TrajetCompose* trajetCompo=new TrajetCompose(trajetTab,nombreEtapesInt);
                listeTrajet.AjouterEnQueue(trajetCompo);
            }
        }
        inputFile.close();
        cout<<"catalogue chargé"<<endl;
    }
}

bool Catalogue::AjoutTrajet (Trajet & unTrajet)
// Algorithme : ajoute un trajet dans la liste
//ajout en queue pour avoir un affichage ordonné
//a rajouter quand on aura accès aux surcharge :( : élimination des redondance en utilisant la méthode EstEquivalent des Trajets
//renvoie de false si échec (impossible sans EstEquivalent)  
{
  //if(listeTrajet.ExisteDeja(unTrajet))
  //return false
  //else{
  listeTrajet.AjouterEnQueue(&unTrajet);
  //}
  return true;
} //----- Fin de Méthode

void Catalogue::RechercheParcours(const char* villeDepart,const char* villeArrive)const{
  //Algorithme : appelle la méthode TrajetMatching de listeTrajet
  //pour récupérer une liste de trajet commençant par villeDepart et finissant par villeArrive
  
  TADListeTrajet listeRecherche(listeTrajet.TrajetMatchingSimple(villeDepart,villeArrive));
  if (listeRecherche.ChaineEstVide()){
    cout<<"pas de trajet correspondant :("<<endl;
  }
  else{
    cout<<"nombre de trajet correspondant:\t"<<listeRecherche.Taille()<<endl;
    cout<<"contenue de la recherche:"<<endl<<"{"<<endl;
    listeRecherche.Afficher();
    cout<<"}"<<endl;
  }
} //----- Fin de Rechercher
bool Catalogue::VerifieRecherche(const char* villeDepart,const char* villeArrive)const{
  TADListeTrajet listeRecherche(listeTrajet.TrajetMatchingSimple(villeDepart,villeArrive));
  if (listeRecherche.ChaineEstVide()){
      return false;
  }
  else{
      return true;
  }
}
  


//------------------------------------------------- Surcharge d'opérateurs
Catalogue & Catalogue::operator = ( Catalogue & unCatalogue )
// Algorithme :
//
{
  listeTrajet=unCatalogue.listeTrajet;
  return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue (Catalogue & unCatalogue )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Catalogue>" << endl;
#endif
    listeTrajet=unCatalogue.listeTrajet;
} //----- Fin de Catalogue (constructeur de copie)


Catalogue::Catalogue ( )
// Algorithme :initialisation automatique de listeTrajet
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Catalogue>" << endl;
#endif
} //----- Fin de Catalogue


Catalogue::~Catalogue ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Catalogue>" << endl;
#endif
    Trajet* trajADetruire;
    while(!listeTrajet.ChaineEstVide()){
      trajADetruire=listeTrajet.Pop();
      delete trajADetruire;
    }
} //----- Fin de ~Catalogue
ostream & operator << (ostream & flux,const Catalogue & unCatalogue){
  if(unCatalogue.listeTrajet.ChaineEstVide()){
    flux<<"Le catalogue est vide"<<endl;
  }
  else{
    flux<<"nombre de trajet dans le catalogue:\t"<<unCatalogue.listeTrajet.Taille()<<endl;
    flux<<"contenue:"<<endl<<"{"<<endl;
    int j;
    ChaineTrajet* p=unCatalogue.listeTrajet.getTete();
    for (j=0;j<unCatalogue.listeTrajet.Taille();j++){
      flux<<p->traj;
      p=p->suivant;
    }
    flux<<"}"<<endl;
  }
  return flux;
}
istream & operator>>(istream & in,Catalogue & unCatalogue){
     char villeDep[100];
     char villeArr[100];
     char moyenTransport[100];
     char nombreEtapes[10];
     in>>nombreEtapes;
     if (strcmp(nombreEtapes,"1")==0){
      in>>villeDep;
      in>>villeArr;
      in>>moyenTransport;
      unCatalogue.listeTrajet.AjouterEnQueue(new TrajetSimple(villeDep,villeArr,moyenTransport));
     }
     else {
        int nombreEtapesInt=atoi(nombreEtapes);
        TrajetSimple** trajetTab = new TrajetSimple*[nombreEtapesInt];
        int j;
        for (j=0;j<nombreEtapesInt;j++){
              in>>villeDep;
              in>>villeArr;
              in>>moyenTransport;
              trajetTab[j]=new TrajetSimple(villeDep,villeArr,moyenTransport);
        }
        unCatalogue.listeTrajet.AjouterEnQueue(new TrajetCompose(trajetTab,nombreEtapesInt)); 
     }
      return in;
  }    

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

