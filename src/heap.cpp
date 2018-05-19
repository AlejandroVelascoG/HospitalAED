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
		resize();
	}
	int posicion = cuenta +1;
	arreglo [posicion] = dato;
	while (dato < arreglo[posicion /2])
		if(posicion == 1 && dato < arreglo[posicion]){
			DataType temp = arreglo[posicion];
			arreglo[posicion] = dato;
			arreglo[posicion+1] = temp;
		}else{
			percolate_up (posicion);
			posicion = posicion/2;
		}
	cuenta++;
}

template <typename DataType>
DataType Heap<DataType>::eliminarMin(){
	DataType espacio = arreglo[1];
	if(cuenta == 1){
		--cuenta;
		return espacio;
	}else{
		DataType temp = arreglo[cuenta];
		int pos = 1;
		while(temp > arreglo [2* pos] && temp > arreglo [2 * pos +1]){
			if(pos==cuenta-1 || pos == cuenta){
				arreglo[pos] = temp;
				break;
			}else{
			percolate_down (pos);
			arreglo[2 * pos]< arreglo [2 * pos + 1] ?
					pos = 2 * pos : pos = 2 * pos +1;
			}
		}
		arreglo [pos] = temp;
		--cuenta;
		return espacio;
	}
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
void Heap<DataType>::percolate_up(int pos){
	DataType temp = arreglo[pos/2];
	if(arreglo[pos] < arreglo[pos/2]){
		arreglo[pos/2] = arreglo[pos];
		arreglo[pos] = temp;
	}
}

template <typename DataType>
void Heap<DataType>::percolate_down(int pos){
	arreglo[2*pos] < arreglo[2*pos+1] ?
			arreglo [pos] = arreglo[2*pos] : arreglo[pos] = arreglo [2 *pos +1];
}

template <typename DataType>
DataType Heap<DataType>::operator[](int i){
	return arreglo[i];
}



#endif
