/*
 * heap.cpp
 *
 *  Created on: 13/05/2018
 *      Author: alejandrovg
 */

#ifdef SRC_HEAP_H_

#include <iostream>

const int INI_CAP = 15;

template <typename DataType>
Heap<DataType>::Heap(){
	cuenta = 0;
	arreglo = new DataType[INI_CAP];
	size = INI_CAP;

}

template <typename DataType>
Heap<DataType>::Heap(int n){
	cuenta = 0;
	arreglo = new DataType[n];
	size = n;
}

template <typename DataType>
DataType Heap<DataType>::encontrarMin(){
	return arreglo[1];
}

template <typename DataType>
int Heap<DataType>::getCuenta(){
	return cuenta;
}


template <typename DataType>
void Heap<DataType>::insertar(DataType dato){
	if(cuenta+1 == size){
		this->resize();
	}
	if( cuenta == 0 ) arreglo[1] = dato;
	arreglo [cuenta + 1] = dato;
	int posicion= cuenta +1;
	while (dato < arreglo[posicion /2]){
		percolate_up ( dato, posicion);
		posicion = posicion/2;
	}
	cuenta++;


}

template <typename DataType>
DataType Heap<DataType>::eliminarMin(){
	DataType espacio = arreglo[1];
	DataType temp = arreglo[cuenta + 1];
	int pos = 1;
	while (temp > arreglo [2* pos]||temp> arreglo [2 * pos +1]){
		percolate_down (pos);
		arreglo[2 * pos]< arreglo [2 * pos + 1] ? pos = 2 * pos : pos = 2 * pos +1;
	}
	arreglo [pos] = temp;
	cuenta --;
	return espacio;
}

template <typename DataType>
void Heap<DataType>::resize(){
	DataType *temp = arreglo;
	size *= 2;
	arreglo = new DataType[size];
	for(int i = 0; i < cuenta; i++){
	arreglo[i] = temp[i];
	}
	delete[] temp;
}

template <typename DataType>
void Heap<DataType>::percolate_up(DataType dato, int pos){
	DataType temp = arreglo[pos/2];
	arreglo[pos/2] = dato;
	arreglo[pos]= temp;

}

template <typename DataType>
void Heap<DataType>::percolate_down(int pos){
	arreglo[2*pos] < arreglo[2*pos+1] ? arreglo [pos] : arreglo [2 *pos +1];
}

template <typename DataType>
DataType Heap<DataType>::operator[](int i){
	return arreglo[i];
}



#endif
