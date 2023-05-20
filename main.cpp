#include "pile.h"
#include "arbre.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    // Pile pile;
    // pile.empiler("Hello");
    // pile.empiler("World");
    // pile.empiler("!");
    // pile.print_pile();
    // cout << "Size of pile: " << pile.sizeofpile() << endl;
    // cout << "Depiler: " << pile.depiler() << endl;
    // pile.print_pile();
    // Pile pile2;
    // string a="( 12 + 3 ) * 4 - 2";
    // //pile2.evaluer("12 3 4 + 2 * -");
    // pile2.infixetosuffixe(a);
    // cout << a << endl;
    // pile2.evaluer(a);

    // string expression = "( 12 * 3 ) - ( 4 * 2 )";
    // arbre Arbre(expression);
    // Arbre.afficher(); // Affiche l'arbre binaire représentant l'expression
    // cout << "=" << Arbre.evaluerarbre() << endl; // Affiche le résultat de l'expression
    //arbre Arbre(" ( X + 2 ) * ( X + 1 ) ");
    arbre Arbre("(X * X + 2 * X + 1 + ( X ^ 3 ) + X )/ 2"); //  /!\ TESTER LA DERIVE DE TOUT CA /!\

    // Affichage de l'arbre initial
    cout << "Arbre initial : ";
    Arbre.afficher();
    cout << endl;

    // Dérivation de l'expression par rapport à X
    noeud* derived = Arbre.derivate(Arbre.racine, 'X');

    // Affichage de l'expression dérivée
    cout << "Expression derivee : ";
    Arbre.afficher(derived);
    cout << endl;
    return 0;
}



