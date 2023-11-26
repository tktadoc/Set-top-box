#ifndef Graph_Video
#define Graph_Video
#include <iostream>
#include <string>
#include "Multimedia.h"



class Video : public Multimedia {
       protected :
          unsigned int time{};
          
       protected :

       friend class Collection;

         //les construvteurs

          Video()
          {}
          Video(unsigned int time)
          : time(time)
          {}
          Video(std::string name , std::string pathname)
          :Multimedia(name, pathname)
          {}
          Video(std::string name, std::string pathname, unsigned int time)
          : Multimedia(name, pathname), time(time)
          {}

          // Constructeur de copie

          Video(Video const &v)
          :Multimedia(v.name, v.pathname), time(v.time)
          {}
      
      public : 

         //les modifieurs

         void setTime(unsigned int time){this->time = time;}

         //les accesseurs

         unsigned int getTime()const{ return time;}
         void afficher(std::ostream &s)const override{
         s<<"le nom de la vidéo est "<<getName()<<",  son chemin d'accès est "<<getPathname()<<", et sa durée est de "<<getTime()<<" secondes.";
         } 
 

         //pour lire la video

         void play()const override {

             system(("mpv "+pathname+"&").data());
             

              }


         //les destructeurs

         ~Video(){}
         


};





#endif