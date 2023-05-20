#ifndef PILE_H
#define PILE_H

#include "arbre.h"
#include <iostream>
#include <string>

using namespace std;

struct item {
    int value;
    noeud *noeud;
    item *next;
};

class Pile {
    public:
        Pile();
        ~Pile();
        Pile(const Pile &other);
        void empiler(int value);
        int depiler();
        void print_pile();
        bool is_empty();
        int sizeofpile();
        void evaluer(string a);
        void infixetosuffixe(string &a);
        void empiler(noeud *n);
        noeud *depiler_noeud();

    private:
        item *head;
};

#endif
