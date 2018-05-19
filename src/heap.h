/*
 * heap.h
 *
 *  Created on: 13/05/2018
 *      Author: alejandrovg
 */

#ifndef SRC_HEAP_H_
#define SRC_HEAP_H_

template <typename DataType>
class Heap{

public:

	Heap();

	Heap(int n);

	DataType encontrarMin();

	void insertar(DataType dato);

	int getCuenta();

	DataType eliminarMin();

	void percolate_up(int pos);

	void percolate_down(int pos);

	DataType operator[](int i);

private:

	int cuenta;

	int size;

	DataType *arreglo;

	void resize();

};

#endif /* SRC_HEAP_H_ */

#include "heap.cpp"
