#ifndef Graph_Groupe
#define Graph_Groupe
#include <iostream>
#include <string>
#include "list"
#include <memory>
#include "Multimedia.h"
typedef std::shared_ptr<Multimedia> Media_ptr;// smart pointeurs non intrusifs de multimédia


class Groupe : public std::list<Media_ptr>{

private : 

std::string name{};

public : 


// le constructeur
Groupe(std::string name)
: std::list<Media_ptr>(), name(name)
{}

// l'accesseur

std::string get_name() const { return name;}


// afficher tous les elements de la liste

void afficher(std::ostream& sortie) const {

    sortie<<"Nom du Groupe : "<<name<<" ";
    sortie<<"Il contient les éléments multimédias suivants : ";
    for (Media_ptr i : *(this)){
        i->afficher(sortie);
       
    }
    
    }

~Groupe(){ 

   /*for (std::shared_ptr<Multimedia> &i : *(this)){
        i.reset();
       
    }*/ 
    std::cout<<"groupe détruit"<<std::endl;}
};




#endif