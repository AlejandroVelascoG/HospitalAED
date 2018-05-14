/*
 * Simulacion.cpp
 *
 *  Created on: 5/05/2018
 *      Author: vonnewmann
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Paciente.h"
#include "heap.h"
using namespace std;
//Constantes
const int DOCTORES= 10;
const int CAMILLAS = 30;
const int ENFERMERAS=20;
const int ESPECIALISTAS= 5;
const int MAX_CAP_SALA = 100;

//Tiempos
const int TIEMPOTEMPORAL = 0;
int Tespera;
const int TRECUPERACION = 30;

// vector que representa la sala
	vector<Paciente> sala;

// función de imprimir el árbol

void imprimir(Heap<Paciente> heap);

//nueva funcion para crear pacientes

void crearPacientes(vector<Paciente> &sala, int n);

// cantidad de pacientes
int cantPacientes();
//ya funciona del todo el aleatorio
int main(){

	// INICIO DE LA SIMULACION
	//while(TIEMPOTEMPORAL < 100){
	srand(time(NULL));
//cada vez que TIEMPOTEMPORAL sea un multiplo de 3 se crearan pacientes de 1 a 10 pacientes arbitrarios
	/* if (TIEMPOTEMPORAL% 3==0) {
		int n = cantPacientes;
		crearPacientes(sala, n);
	}
	if(sala.empty()!= false){
	}

	}*/

	vector<Paciente> s1;

	crearPacientes(s1, 4);

	/* for(int i = 0; i<s1.size(); i++){
		cout << s1[i].getEdad() << "\t" << s1[i].getRango()<< "\t" <<  s1[i].getTriage() << endl;
	}
	*/
	Heap<Paciente> arbol;
	for(int i = 0; i<s1.size(); i++){
		arbol.insertar(s1[i]);
	}
	imprimir(arbol);
	cout << "---" << endl;
	cout << arbol[1].getTriage() << arbol[1].getRango() << endl;
	cout << "---" << endl;
	arbol.eliminarMin();
	imprimir(arbol);

}

// numero aleatorio de pacientes que ingresan en la sala
int cantPacientes(){
	int cantPaciente = rand()%(10-0);
	return cantPaciente;
}
void crearPacientes(vector<Paciente> &sala, int n){
	for (int i = 0; i< n; i++){
		Paciente nuevo;
		sala.push_back(nuevo);
	}
}

void imprimir(Heap<Paciente> heap){
	for(int i = 1; i<heap.getCuenta()+1; i++){
		cout << heap[i].getTriage() << heap[i].getRango() << endl;
	}
}
