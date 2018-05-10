/*
 * COLAp.h
 *
 *  Created on: 5/05/2018
 *      Author: vonnewmann
 */

#ifndef SRC_COLAP_H_
#define SRC_COLAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>


template <typename TipoDato>
class COLAp {

public:

	COLAp(int n);

	// 	~COLAp();

	bool isEmpty();

	TipoDato & encontrarMax();

	int size();

	void insertar(TipoDato & dato);

	void eliminarMax();

	void imprimir();

private:

	int heapsize;
	int arreglo [];

};



#endif /* SRC_COLAP_H_ */
