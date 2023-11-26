#include "Multimedia.h"

        
         //les constructeurs

           Multimedia::Multimedia() {}
           Multimedia::Multimedia(std::string name, std::string pathname )
           : name(name), pathname(pathname)
           {}


        //les modifieurs
            void Multimedia::setName(std::string name){ this->name = name; }
            void Multimedia::setPathname(std::string pathname){ this->pathname = pathname; }

          

        //les accesseurs
            std::string Multimedia::getName()const{ return name; } 
            std::string Multimedia::getPathname()const{ return pathname; }

            void Multimedia::afficher(std::ostream &s)const{ s<<"le nom du fichier est "<<getName()<<" et son chemin d'accès est "<<getPathname()<<std::endl; }
            

        //le destructeur
            Multimedia::~Multimedia(){}