#include "arbre.h"
#include "pile.h"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

noeud::noeud(const char t, char o, float v, noeud *FilsG, noeud *filsD) {
    type = t;
    if (t == 'o')
    {
        ope=o;
    }else if(t == 'v'){
        ope=o;
    }
    val=v;
    filsG = FilsG;
    filsD = filsD;
}

arbre::arbre() {
    racine = nullptr;
}

arbre::~arbre() {
    noeud *current = racine;
    while (current != nullptr) {
        noeud *next = current->filsD;
        delete current;
        current = next;
    }
}

arbre::arbre(string a){
    Pile pile1;
    Pile pile2;
    pile1.infixetosuffixe(a);
    cout << a << endl;
    noeud *current = racine;

    for(int i=0;i<a.size();i++){
        if(a[i]==' '){
            continue;
        }
        if(a[i]>='0' && a[i]<='9'){
            int valeur = 0;
            while(a[i]>='0' && a[i]<='9'){
                valeur = valeur*10 + (a[i]-'0');
                i++;
            }
            noeud *n = new noeud;
            n->type = 'f';
            n->val = valeur;
            pile2.empiler(n);
        }
        else if(a[i]=='+' || a[i]=='-' || a[i]=='*' || a[i]=='/' || a[i]=='^'){
            noeud *n = new noeud;
            n->type = 'o';
            n->ope = a[i];
            n->filsD = pile2.depiler_noeud();
            n->filsG = pile2.depiler_noeud();
            pile2.empiler(n);
        }else if(a[i]=='X' || a[i]=='Y' || a[i]=='Z'){
            noeud *n = new noeud;
            n->type = 'v';
            n->ope = a[i];
            pile2.empiler(n);
        }
    }
    (*this).racine = pile2.depiler_noeud();
}



void arbre::afficher(noeud *n) { // /!\ NE PAS OUBLIER DE METTRE DES ESPACES ENTRE CHAQUES VALEURS ET OPERATEURS !!!
    if (n == nullptr) {
        return;
    }

    if (n->type == 'o') {
        cout << "( ";
        afficher(n->filsG);
        cout << n->ope << " ";
        afficher(n->filsD);
        cout << ") ";
    } else if(n->type == 'f'){
        cout << n->val << " ";
    }else if(n->type == 'v'){
        cout << n->ope << " ";
    }
}

void arbre::afficher() {
    afficher((*this).racine);
}

float arbre::evaluerarbre(noeud *n) {
    if (n->type == 'f') {
        return n->val;
    }else if(n->type == 'v'){
        return n->ope;
    }

    int gauche = evaluerarbre(n->filsG);
    int droite = evaluerarbre(n->filsD);

    switch (n->ope) {
        case '+':
            return gauche + droite;
        case '-':
            return gauche - droite;
        case '*':
            return gauche * droite;
        case '/':
            return gauche / droite;
        case '^':
            return pow(gauche, droite);
        default:
            return 0;
    }
}

float arbre::evaluerarbre() {
    return evaluerarbre((*this).racine);
}

arbre::arbre(noeud *racine) {
    (*this).racine = racine;
}

noeud* arbre::derivate(noeud* n, char v) {
    noeud* current = n;
    cout << "on derive: ";
    (*this).afficher(current);
    cout << endl;

    if (current->type == 'f') {
        cout << "valeur: " << current->val << endl;
        noeud* deriv = new noeud('f');
        deriv->val = 0;
        (*this).afficher(deriv); cout << endl;
        return deriv;
    }
    else if (current->type == 'v') {
        if (current->ope == v) {
            noeud* deriv = new noeud('f');
            deriv->val = 1;
            (*this).afficher(deriv); cout << endl;
            return deriv;
        }
        else {
            noeud* deriv = new noeud('f');
            deriv->val = 0;
            (*this).afficher(deriv); cout << endl;
            return deriv;
        }
    }
    else {
        if (current->ope == '+' || current->ope == '-') {
            noeud* deriv = new noeud(current->type, current->ope);
            deriv->filsG = derivate(current->filsG, v);
            deriv->filsD = derivate(current->filsD, v);
            (*this).afficher(deriv); cout << endl;
            return deriv;
        }else if (current->ope == '*') {
            noeud* deriv = new noeud('o', '+');
            deriv->filsG = new noeud('o', '*');
            deriv->filsG->filsG = derivate(current->filsG, v);
            deriv->filsG->filsD = current->filsD;

            deriv->filsD = new noeud('o', '*');
            deriv->filsD->filsG = current->filsG;
            deriv->filsD->filsD = derivate(current->filsD, v);

            (*this).afficher(deriv); cout << endl;
            return deriv;
        }else if (current->ope == '/') {
            noeud* deriv = new noeud('o', '/');
            deriv->filsG = new noeud('o', '-');
            deriv->filsG->filsG = new noeud('o', '*');
            deriv->filsG->filsG->filsG = derivate(current->filsG, v);
            deriv->filsG->filsG->filsD = current->filsD;

            deriv->filsG->filsD = new noeud('o', '*');
            deriv->filsG->filsD->filsG = current->filsG;
            deriv->filsG->filsD->filsD = derivate(current->filsD, v);

            deriv->filsD = new noeud('o', '*');
            deriv->filsD->filsG = current->filsD;
            deriv->filsD->filsD = current->filsD;

            (*this).afficher(deriv); cout << endl;
            return deriv;
        }
        else if (current->ope == '^') {
            int exponent = current->filsD->val;
            noeud* derivateBase = derivate(current->filsG, v);
            noeud* derivateFilsG = derivate(current->filsG, v);

            if (exponent == 0) {
                noeud* deriv = new noeud('f');
                deriv->val = 0;
                return deriv;
            }
            else {
                noeud* deriv = new noeud('o', '*');
                deriv->filsG = new noeud('o', '*');
                deriv->filsG->filsG = new noeud('f');
                deriv->filsG->filsG->val = exponent;
                deriv->filsG->filsD = new noeud('o', '^');
                deriv->filsG->filsD->filsG = current->filsG;
                deriv->filsG->filsD->filsD = new noeud('f');
                deriv->filsG->filsD->filsD->val = exponent - 1;
                deriv->filsD = new noeud('o', '*');
                deriv->filsD->filsG = derivateBase;
                deriv->filsD->filsD = derivateFilsG;
                (*this).afficher(deriv); cout << endl;
                return deriv;
            }
        }
    }

    return nullptr; // Retourne nullptr si aucun cas ne correspond (retour par défaut)
}

