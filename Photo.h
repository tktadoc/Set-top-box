#ifndef Photo_H_INCLUDED
#define Photo_H_INCLUDED
#include <iostream>
#include <string>
#include "Multimedia.h"

class Photo : public Multimedia{
   
   private : 
     double latitude{};
     double longitude{};

   protected : 

   friend class Collection;

    //les constructeurs
     Photo()
     {}
     Photo(std::string name, std::string pathname)
     :Multimedia::Multimedia(name,pathname)
     {}
     Photo(double latitude, double longitude)
     :latitude(latitude), longitude(longitude)
     {}
     Photo(std::string name, std::string pathname, double latitude, double longitude)
     :Multimedia::Multimedia(name, pathname), latitude(latitude), longitude(longitude)
     {}

  public : 

    // les modifieurs
     void setLatitude(double latitude){this->latitude = latitude;}
     void setLongitude(double longitude){this->longitude = longitude;}

    //les accesseurs
     double getLatitude()const{return latitude;}
     double getLongitude()const{return longitude;}
     void  afficher(std::ostream &s )const override {
         s<<"le nom de la photo est "<<getName()<<",  son chemin d'accès est "<<getPathname()<<", sa latitude est "<<getLatitude()<<" et sa longitude est "<<getLongitude();
         } 
   
    //le destructeur

    ~Photo(){}

    //pour ouvrir la photo
    void play()const override{

      system(("imagej "+pathname+"&").data());
    
    }



};

#endif