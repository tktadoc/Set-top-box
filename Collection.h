#ifndef Graph_Collection
#define Graph_Collection
#include <iostream>
#include <string>
#include "sstream"
#include "list"
#include <memory>
#include "Multimedia.h"
#include "Video.h"
#include "Photo.h"
#include "Film.h"
#include "Groupe.h"
#include <map>

typedef std::shared_ptr<Multimedia> Media_ptr;// smart pointeurs non intrusifs de multimédia
typedef std::shared_ptr<Groupe> Groupe_ptr;// smart pointerus non intrusifs de groupe


class Collection {

private : 
          std::map <std::string, Media_ptr> CollectionMedias{};
          std::map <std::string, Groupe_ptr> CollectionGroupes{};

public  :

                                                // les accesseurs pour la collection

         std::map <std::string, Media_ptr> getMedias() const {return CollectionMedias;}
         std::map <std::string, Groupe_ptr> getGroupes() const {return CollectionGroupes;}


                                    // les fonctions respectives pour créer un groupe , un film , une video , une photo et les ajouter dans le table adéquate

         Groupe_ptr groupe(std::string name = ""){

         Groupe_ptr groupe(new Groupe(name));
         CollectionGroupes.insert(std::pair<std::string, Groupe_ptr>(name,groupe));
         return groupe;
           }


         Media_ptr film(std::string name ="" , std::string pathname="", unsigned int time = 0, double t[] = {}, unsigned int n = 0){
         Film* f = new Film(name, pathname, time, t);
        f->set_chapitre(t,n);
         Media_ptr film(f);

         CollectionMedias.insert(std::pair<std::string, Media_ptr>(name,film));
         return film;

           }

        Media_ptr video(std::string name ="", std::string pathname ="", unsigned int time = 0){

        Media_ptr video(new Video(name, pathname, time)); 
        CollectionMedias.insert(std::pair<std::string, Media_ptr>(name,video));
        return video;

           }

         Media_ptr photo(std::string name = "", std::string pathname = "", double latitude = 0.0, double longitude = 0.0){

         Media_ptr photo(new Photo(name, pathname, latitude, longitude)); 
         CollectionMedias.insert(std::pair<std::string, Media_ptr>(name,photo));
         return photo;

           }

                                            // pour rechercher et afficher un groupe ou un multimédia à partie de son nom

        void search_G(std::string name, std::ostream & sortie) const{

              if(CollectionGroupes.find(name)!= CollectionGroupes.end()){ sortie <<"le Groupe existe et voici ses caractéristiques ";
                           if(CollectionGroupes.find(name)->second->front() != NULL) {CollectionGroupes.find(name)->second->afficher(sortie);}
    
                    }
             else { sortie <<"le Groupe n'existe pas ou a été supprimé"<<std::endl;}
                           
                         
    
           }

        void search_M(std::string name, std::ostream & sortie) const{

    

             if(CollectionMedias.find(name)!= CollectionMedias.end()){ sortie <<"le multimédia existe et voici ses caractéristiques ";
                            CollectionMedias.find(name)->second->afficher(sortie);
    
                     }
             else { sortie <<"le multimédia n'existe pas ou a été supprimé ";}

            }

                                            // pour rechercher un multimédia et le jouer

      void play(std::string name, std::ostream & sortie) const{

    

            if(CollectionMedias.find(name)!= CollectionMedias.end()){ sortie<<"playing ";
                            CollectionMedias.find(name)->second->play();
    
                    }
            else { sortie<<"le multimédia n'existe pas ou a été supprimé";}
            }

            //pour supprimer un groupe
    
    void deleteGroupe(std::string name){
            
            CollectionGroupes.erase(name);

            }
            //pour supprimer un multimédia
    
    void deleteMedia(std::string name){
            
           
            for(auto pair : CollectionGroupes){
              
               for(std::list<Media_ptr>::iterator it =(pair.second)->begin(); it != (pair.second)->end(); it++){ if((*it)->getName() == name) {  (*it).reset(); }}

            }
             CollectionMedias.erase(name);

            }
};


#endif