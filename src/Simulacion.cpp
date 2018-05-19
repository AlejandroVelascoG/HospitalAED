/*
 * Simulacion.cpp
 *
 *  Created on: 5/05/2018
 *      Author: vonnewmann
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <time.h>
#include "Paciente.h"
#include "heap.h"

using namespace std;

//Constantes

const int PACIENTES_INI = 50;
vector<Paciente> EMERGENCIAS (15);
vector<Paciente> OBSERVACION (30);
vector<Paciente> QUIROFANOS (5);
vector<Paciente> CONSULTORIOS;
Heap<Paciente> sala;
queue<Paciente> COLA_CONS;
const int MAX_CAP_SALA = 100;

//Tiempos

const int TIEMPOTEMPORAL = 0;
int Tespera;
const int TRECUPERACION = 30;

void clasificar(Paciente p1);

// función de imprimir el árbol

void imprimir(Heap<Paciente> heap);

// funcion para crear pacientes

void crearPacientes(Heap<Paciente> &sala);

void nuevoPaciente();

int main(){
	srand(time(NULL));
	crearPacientes(sala);

	// CLASIFICA PRIMEROS 25 PACIENTES Y DEJA LA SALA CON 25 ESPERANDO

	for(int i = 0; PACIENTES_INI /2;i++){
		Paciente pac = sala.eliminarMin();
		clasificar(pac);
	}

}




// PACIENTES INICIALES

void crearPacientes(Heap<Paciente> &sala){
	for (int i = 0; i< PACIENTES_INI; i++){
		Paciente nuevo;
		sala.insertar(nuevo);
	}
}

void nuevoPaciente(){
	Paciente px;
	sala.insertar(px);
}

void clasificar(Paciente p1){
	if(p1.getRango() <= 14){
		EMERGENCIAS.push_back(p1);
	}else if(p1.getRango() >= 21 && p1.getRango() <= 24){
		EMERGENCIAS.push_back(p1);
	}else if(p1.getRango() >= 31 && p1.getRango() <= 34){
		OBSERVACION.push_back(p1);
	}else if(p1.getRango() >=  41){
		if(CONSULTORIOS.size==10){
			COLA_CONS.push(p1);
		}else if(CONSULTORIOS.size<10){
			CONSULTORIOS.push_back(p1);
		}
	}
}



void imprimir(Heap<Paciente> heap){
	for(int i = 1; i<heap.getCuenta()+1; i++){
		cout << heap[i].getTriage() << heap[i].getRango() << endl;
	}
}


