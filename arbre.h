#ifndef ARBRE_H
#define ARBRE_H

#include <iostream>
#include <string>

using namespace std;

class noeud
{
    public :
        char type ; //‘o’ pour opérateur, ‘f’ pour valeur et 'v' pour variable
        char ope ;
        float val ;
        noeud * filsG, * filsD ;
        noeud(const char t='\0', char o='\0', float v=0, noeud *FilsG=nullptr, noeud *FilsD=nullptr) ;
} ;

class arbre
{
    public :
        noeud * racine ;
        arbre() ;
        ~arbre() ;
        arbre(string a) ;
        arbre(noeud * racine) ;
        noeud * derivate(noeud * n, char v) ; // dérivée par rapport à la variable v
        void afficher() ;
        void afficher(noeud * n) ;
        float evaluerarbre() ;
        float evaluerarbre(noeud * n) ;

};


#endif
