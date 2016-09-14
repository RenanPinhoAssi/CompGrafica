#ifndef LISTENC_H
#define LISTENC_H
#include "Elemento.h"
#include <exception>

template<typename T>
class ListaEnc {

private:
    Elemento<T>* head;
    int size;

public:

    ListaEnc(){
        size = 0;
    }
    ~ListaEnc(){}

    Elemento<T>* getHead(){
        return head;
    }

    void checkAll(){
        Elemento<T>* actualElement = head;
        for(int i = 0; i < size; i++){
               actualElement->tellName();
               actualElement = actualElement->getProximo();
            }
    }

    void eliminaDoInicio(){
        Elemento<T>* formerHead = head;
        try{
            head = formerHead->getProximo();
        }catch (...){
            head = NULL;
        }
        formerHead->~Elemento();
        size--;
    }

    void eliminaNaPosicao(int pos){
        Elemento<T>* actualElement = head;
        Elemento<T>* last = head;
        if(pos <= (size-1) && pos > 0 && size > 1){
            for(int i = 0; i < pos; i++){
               last = actualElement;
               actualElement = actualElement->getProximo();
            }
            last->setProximo(NULL);

            if(pos < (size-1)){
                last->setProximo(actualElement->getProximo());
            }
            actualElement->~Elemento();
            size--;
        }
    }

    void eliminaNoFim(){
        eliminaNaPosicao((size-1));
    }
    // Adiiciona

    void adicionaNoInicio(Elemento<T>& dado){
        try{
            dado.setProximo(head);
        }catch (...){}
        head = &dado;
        size++;
    }

    void adicionaNaPosicao(Elemento<T>& dado, int pos){
        Elemento<T>* last = head;
        if(pos <= size && pos > 0 && size > 0){

            for(int i = 0; i < pos - 1; i++){
               last = last->getProximo();
            }
            dado.setProximo(NULL);
            if(pos < size){
                dado.setProximo(last->getProximo());
            }
            last->setProximo(&dado);
            size++;
        }
    }

     void adicionaNoFim(Elemento<T>& dado){
        adicionaNaPosicao(dado, size);
    }

    int myLength(){
        return size;
    }

    Elemento<T>* retiraByName(char* argName){
        Elemento<T>* actualElement = head;
        Elemento<T>* last = head;
        for(int i = 0; i < size; i++){
            if(actualElement->getInfo().objName != argName){
                last = actualElement;
                try{actualElement = actualElement->getProximo();}catch(...){}
            }else{
                return actualElement;
            }
       }
       return NULL;
    }

    void retiraTest(char* argName){
        Elemento<T>* actualElement = head;
        Elemento<T>* last = head;
        for(int i = 0; i < size; i++){
            if(actualElement->getInfo().objName != argName){
                last = actualElement;
                actualElement = actualElement->getProximo();
                cout << "Not This";
            }else{
                cout << "Found!";
                break;
            }
       }
       cout << "End!";
    }

    int posicao(const Elemento<T>& dado) const;
    T* posicaoMem(const Elemento<T>& dado) const;
    bool contem(const Elemento<T>& dado);
    T retiraDaPosicao(int pos){ }
    Elemento<T>* retiraDoInicio(){ }
    T retira(const Elemento<T>& dado){  }
    T retiraNoFim();
    T retiraEspecifico(const Elemento<T>& dado);
    void adicionaEmOrdem(const Elemento<T>& data);
    bool listaVazia() const;
    bool igual(Elemento<T> dado1, Elemento<T> dado2);
    bool maior(Elemento<T> dado1, Elemento<T> dado2);
    bool menor(Elemento<T> dado1, Elemento<T> dado2);
    void destroiLista();
};

#endif // OBJECTOS2D_H
