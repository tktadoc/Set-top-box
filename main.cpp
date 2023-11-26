//
// main.cpp
// Created on 21/10/2018
//

#include <iostream>
#include "Multimedia.h"
#include "Video.h"
#include "Photo.h"
#include "Film.h"
#include "Groupe.h"
#include "Collection.h"
#include <vector>
#include "sstream"
using namespace std;


int main(int argc, const char* argv[])
{
    std::cout << "Hello brave new world" << std::endl;
    Collection NotreCollection;
    double t[5] = {12,13,15.4, 16, 17};
    Groupe_ptr g1 = NotreCollection.groupe("groupe 1");
    Media_ptr f1 = NotreCollection.film("film1", "/home/netgeek/Images/v2",73.4,t);
    //f1->set_chapitre(t,5);
 g1->afficher(std::cout);

    stringstream sortie;
    NotreCollection.search_G("groupe 1", sortie);
    cout<<sortie.str();
    
     return 0;
}