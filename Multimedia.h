#ifndef Graph_Multimedia
#define Graph_Multimedia
#include <iostream>
#include <string>
class Collection;

class Multimedia {
        
        protected :
            std::string name{} ;
            std::string pathname{};

        protected :

        friend class Collection;

            //les constructeurs
            Multimedia();
            Multimedia(std::string name , std::string pathname);

        public :


           //les modifieurs
            void setName(std::string);
            void setPathname(std::string);
            
           //pour jouer un fichier Multimedia

          virtual void play() const =0;

           //les accesseurs
            std::string getName()const;
            std::string getPathname()const;

          //pour afficher les caractéristiques d'une fichier multimédia
            virtual void afficher(std::ostream &)const; 
            

           //le destructeur
            ~Multimedia();

};
#endif