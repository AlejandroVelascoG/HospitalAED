/*
 * COLAp.cpp
 *
 *  Created on: 5/05/2018
 *      Author: vonnewmann
 */
#include <iostream>
#include "COLAp.h"
#include <vector>
using namespace std;

/*

template <typename TipoDato>
COLAp<TipoDato>::COLAp(int n){
	heapsize = 0;


}

template <typename TipoDato>
COLAp<TipoDato>::~COLAp() {
	Celda *temp;

	while(start!= NULL){
		temp = &start;
		delete start;
		start = temp;
	}
	}

template <typename TipoDato>
bool COLAp<TipoDato>::isEmpty(){
	if (cuenta==0)return true;
	else return false;
}


template <typename TipoDato>
int COLAp<TipoDato>::size(){
	return cuenta;
}

template <typename TipoDato>
void COLAp<TipoDato>::push(TipoDato cp){
	Celda * nuevaCelda= new Celda;
	nuevaCelda->dato= cp;
	nuevaCelda->siguiente=NULL;
	if (isEmpty==true){
		start->siguiente= nuevaCelda;
		end->siguiente = nuevaCelda;
		cuenta++;
	}else{
		end->siguiente=nuevaCelda;
		cuenta++;
	}
	end=nuevaCelda;

}


template <typename TipoDato>
void COLAp<TipoDato>::pop(){
	Celda*temp= new Celda;
	temp= &start;
	if(start== end){
		start=NULL;
		end = NULL;
	}else{
		start= start->siguiente;

}
	delete temp;
}

template <typename TipoDato>
void COLAp<TipoDato>::imprimir(){
	Celda*temp;
	temp= start;
	while( temp!= NULL){
		cout<< temp->dato<<endl;
		temp= temp->siguiente;

	}
}

*/
