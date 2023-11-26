#ifndef Graph_Film
#define Graph_Film
#include <iostream>
#include <string>
#include <stdlib.h>
#include "Video.h"

class Film : public Video{

private : 

double* durees {};
unsigned int nb_chapitres{};


protected :

friend class Collection;
friend class TCPServer;

//les constructeurs
Film()
{}
Film(double t[])
:durees(t)
{}
Film(unsigned int time)
:Video(time)
{}
Film(unsigned int time, double t[])
:Video(time),durees(t)
{}
Film(std::string name , std::string pathname)
:Video(name,pathname)
{}
Film(std::string name , std::string pathname, unsigned int time)
:Video(name,pathname,time)
{}
Film(std::string name , std::string pathname, unsigned int time, double t[])
:Video(name,pathname,time), durees(t)
{}

// Constructeur de copie

Film(Film const &f)
:Video(f.name, f.pathname, f.time), nb_chapitres(f.nb_chapitres)
{ 
     durees = new double[nb_chapitres];
         if(durees != NULL){
            for (unsigned int i=0; i<nb_chapitres; i++){
            (durees[i]) = *new double(f.durees[i]);
}
}

}

public : 

// les accesseurs
unsigned int  getNbChapitres() const { return nb_chapitres;}

 void afficher_getChapitres(std::ostream &s) const { for(unsigned int i =0; i<getNbChapitres(); i++){ s<<durees[i]<<" secondes\t";}}

 double* get_tab_chapitres() const {

  double * tab = new double[nb_chapitres];
  if(tab != NULL){

    for(unsigned int i = 0; i<nb_chapitres; i++ ){ tab[i]= * new double(durees[i]);}
  }

    return tab;
 }

// le modifieur pour remplir le tableau de chapitres
void set_chapitre(double tab[], unsigned int n){
    nb_chapitres = n;
        // durees = (double *)calloc(n,sizeof(double));
         durees = new double[n];
         if(durees != NULL){
            for (unsigned int i=0; i<n; i++){
            (durees[i]) = *new double(tab[i]);
}
         }

    
}

// pour afficher les caractéristiques du film
void afficher(std::ostream &s)const override{
         s<<"le nom du film est "<<getName()<<",  son chemin d'accès est "<<getPathname()<<", sa durée est de "<<getTime()<<" secondes."<<" Il contient "<<getNbChapitres()<<" chapitres de durées respeectives ";
         afficher_getChapitres(s);
         } 

// le destructeur

~Film(){ 
  delete(durees);
  std::cout<<"film "<<getName()<<" détruit"<<std::endl;
  }
};

#endif