#include "pile.h"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;


Pile::Pile() {
    head = nullptr;
}

Pile::~Pile() {
    item *current = head;
    while (current != nullptr) {
        item *next = current->next;
        delete current;
        current = next;
    }
}

Pile::Pile(const Pile &other) {
    head = nullptr;
    item *current = other.head;
    while (current != nullptr) {
        empiler(current->value);
        current = current->next;
    }
}

void Pile::empiler(int value) {
    item *new_item = new item;
    new_item->value = value;
    new_item->next = head;
    head = new_item;
}

int Pile::depiler() {
    if (head == nullptr) {
        return 0;
    }
    item *top = head;
    head = head->next;
    int value = top->value;
    delete top;
    return value;
}

bool Pile::is_empty() {
    return head == nullptr;
}

int Pile::sizeofpile() {
    int size = 0;
    item *current = head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size;
}

void Pile::print_pile() {
    item *current = (*this).head;
    while (current != nullptr) {
        if (current->value!=0){
            cout << current->value << endl;
        }else if (current->noeud!=nullptr){
            cout << current->noeud->val << endl;
        }

        current = current->next;
    }
}





void Pile::evaluer(string a) {
    int s = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if(a[i] >= '0' && a[i] <= '9'){
            s = s * 10 + (a[i] - '0');
        } else if (a[i] == ' ' && a[i-1] != ' ' && a[i-1] != '+' && a[i-1] != '-' && a[i-1] != '*' && a[i-1] != '/') {
            empiler(s);
            s = 0;
        } else if (a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/' || a[i] == '^') {
            int c = depiler();
            int b = depiler();
            int expression;
            if (a[i] == '+') {
                expression = b + c;
            } else if (a[i] == '-') {
                expression = b - c;
            } else if (a[i] == '*') {
                expression = b * c;
            } else if (a[i] == '/') {
                expression = b / c;
            }else if(a[i] == '^'){
                expression = pow(b,c);
            }
            empiler(expression);
        }
        std::cout << "i: " << i << " a[i]: " << a[i] << " s: " << s << std::endl;
        print_pile();
    }
    if (a.back() != ' ') {
        empiler(s);
    }
}

void Pile::infixetosuffixe(string &a){
    //Pile (*this);
    string resultat;
    //we add a space, if there is not, at the end of the string to be sure that the last number is added to the result
    if(a.back() != ' '){
        a += ' ';
    }
    for(int i=0; i<a.size(); i++){
        if(a[i] >= '0' && a[i] <= '9'){
            resultat += a[i];
        }
        else if(a[i] == '+' || a[i] == '-' || a[i] == '*' || a[i] == '/' || a[i] == '^'){
            if((*this).is_empty()){
                (*this).empiler(a[i]);
            }
            else{
                if(a[i] == '+' || a[i] == '-'){
                    if((*this).head->value == '*' || (*this).head->value == '/'){
                        resultat += (*this).depiler();
                        (*this).empiler(a[i]);
                    }
                    else{
                        (*this).empiler(a[i]);
                    }
                }
                else if(a[i] == '*' || a[i] == '/'|| a[i] == '^'){
                    (*this).empiler(a[i]);
                }
            }
        }
        else if(a[i] == '('){
            (*this).empiler(a[i]);
        }
        else if(a[i] == ')'){
            while((*this).head->value != '('){
                resultat += (*this).depiler();
            }
        }else if(a[i] == ' ' && a[i-1] != ' '){
            resultat += ' ';
        }else{
            resultat+=a[i];
        }
    }
    while(!(*this).is_empty()){
        if((*this).head->value != '('){
            resultat += (*this).depiler();
        }else{
            (*this).depiler();
        }
    }
    a=resultat;
}

void Pile::empiler(noeud *noeud) {
    item *new_item = new item;
    new_item->noeud = noeud;
    new_item->next = head;
    head = new_item;
}

noeud *Pile::depiler_noeud() {
    if (head == nullptr) {
        return nullptr;
    }
    item *top = head;
    head = head->next;
    noeud *noeud = top->noeud;
    delete top;
    return noeud;
}
