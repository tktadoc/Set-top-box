//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "tcpserver.h"
#include "Collection.h"
#include <vector>
#include <map>



const int PORT = 3331;

 // la base de données

 Collection NotreCollection;
 double t[5] = {12,13,15.4, 16, 17};
 Groupe_ptr g1 = NotreCollection.groupe("groupe1");
 Media_ptr f1 = NotreCollection.film("film1", "~/Images/testcode/v2",73.4,t,5);

 // les différentes commandes de la set-top box ici on utilise des pointeurs de methodes qu'on mettra dans une map contenant ainsi toutes les commandes

 // pour rechercher un groupe 
 auto searchGroupe =  [](std::string word, std::stringstream & enter, std::stringstream & sortie)
    { word.clear();
      enter >> word;
     //std::cout  << word;
    NotreCollection.search_G(word, sortie);
     return sortie.str();};

  // pour rechercher un multimédia
 auto searchMedia =  [](std::string word, std::stringstream & enter, std::stringstream & sortie)
    { word.clear();
      enter >> word;
     //std::cout  << word;
    NotreCollection.search_M(word, sortie);
     return sortie.str();};

  // pour jouer un multimédia
   auto play =  [](std::string word, std::stringstream & enter, std::stringstream & sortie)
    { word.clear();
      enter >> word;
     //std::cout  << word;
    NotreCollection.play(word, sortie);
     return sortie.str();};

     //la map qui contient toutes les commandes
  std::map <std::string, std::function<std::string(std::string word, std::stringstream &enter, std::stringstream &sortie)>> Commandes;
  
 

int main(int argc, char* argv[])
{
  // on rajoute les commandes à la tables(map) des commandes
  Commandes.insert(std::pair<std::string, std::function<std::string(std::string word, std::stringstream &enter, std::stringstream &sortie)>>("searchGroupe",searchGroupe));
  Commandes.insert(std::pair<std::string, std::function<std::string(std::string word, std::stringstream &enter, std::stringstream &sortie)>>("searchMedia",searchMedia));
  Commandes.insert(std::pair<std::string, std::function<std::string(std::string word, std::stringstream &enter, std::stringstream &sortie)>>("play",play));
  g1->push_back(f1);
  
  // cree le TCPServer
  auto* server = new TCPServer([&](std::string const& request, std::string& response) {
    std::stringstream sortie;
    std::stringstream enter;
    std::string word;// pour decouper l'entrée en diffirents mots on utilise ce stringstream, il va récuperer l'intitulé de la commande
     enter  << request;
     enter >> word; 

     // the request sent by the client to the server
    std::cout << "request: " << request << std::endl;

    // pour rechercher la commande entrée par le client dans la liste des commandes
    if(Commandes.find(word)!= Commandes.end()){
      
     response = Commandes.find(word)->second(word, enter,sortie);// effectue le traitement adéquat et renvoie la réponse au serveur
    }
    // si la commande entrée par le client n'est pas dans la map des commandes prédéfinies
    else{ response = "Commande non définie.";}

    enter.clear();
    word.clear();
    sortie.clear();

    // return false would close the connecytion with the client
    return true;
  });


  // lance la boucle infinie du serveur
  std::cout << "Starting Server on port " << PORT << std::endl;

  int status = server->run(PORT);

  // en cas d'erreur
  if (status < 0) {
    std::cerr << "Could not start Server on port " << PORT << std::endl;
    return 1;
  }

  return 0;
}

