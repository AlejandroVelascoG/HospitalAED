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

// SALA

Heap<Paciente> SALA;
const int MAX_CAP_SALA = 100;
const int PACIENTES_INI = 50;

// EMERGENCIAS:

vector<Paciente> EMERGENCIAS;
queue<Paciente> COLA_EMER;
const int CAP_MAX_EMER = 10;

// OBSERVACIÓN:

vector<Paciente> OBSERVACION;
queue<Paciente> COLA_OBSER;
const int CAP_MAX_OBSER = 10;

// QUIRÓFANO:

vector<Paciente> QUIROFANOS;
queue<Paciente> COLA_QUIR;
const int CAP_MAX_QUIR = 5;

// CONSULTORIOS:

vector<Paciente> CONSULTORIOS;
queue<Paciente> COLA_CONS;
const int CAP_MAX_CONS = 15;

// HOSPITALIZACIÓN

vector<Paciente> HOSPITALIZACION;
queue<Paciente> COLA_HOSP;
const int CAP_MAX_HOSP = 30;


//Tiempos

const int TIEMPOTEMPORAL = 0;
int Tespera;
const int TRECUPERACION = 30;

void clasificar(Paciente p1);

// FUNCIONES

// función de imprimir el árbol

void imprimir(Heap<Paciente> heap);

// funcion para crear pacientes

void crearPacientes(Heap<Paciente> &SALA);

// funcion 1 nuevo paciente

void nuevoPaciente();

void f_observacion(vector<Paciente> obs);

int main(){
	srand(time(NULL));
	crearPacientes(SALA);

	// CLASIFICA PRIMEROS 25 PACIENTES Y DEJA LA SALA CON 25 ESPERANDO

	for(int i = 0; PACIENTES_INI /2;i++){
		Paciente pac = SALA.eliminarMin();
		clasificar(pac);
	}

}




// PACIENTES INICIALES

void crearPacientes(Heap<Paciente> &SALA){
	for (int i = 0; i< PACIENTES_INI; i++){
		Paciente nuevo;
		SALA.insertar(nuevo);
	}
}

void nuevoPaciente(){
	Paciente px;
	SALA.insertar(px);
}

void clasificar(Paciente p1){
	if(p1.getRango() <= 14){
		if(EMERGENCIAS.size() == CAP_MAX_EMER){
			COLA_EMER.push(p1);
		}else if(EMERGENCIAS.size()<CAP_MAX_EMER){
			EMERGENCIAS.push_back(p1);
		}
	}else if(p1.getRango() >= 21 && p1.getRango() <= 24){
		if(EMERGENCIAS.size()==CAP_MAX_EMER){
			COLA_EMER.push(p1);
		}else if(EMERGENCIAS.size()<CAP_MAX_EMER){
			EMERGENCIAS.push_back(p1);
		}
	}else if(p1.getRango() >= 31 && p1.getRango() <= 34){
		if(OBSERVACION.size()==CAP_MAX_OBSER){
			COLA_OBSER.push(p1);
		}else if(OBSERVACION.size()<CAP_MAX_OBSER){
			OBSERVACION.push_back(p1);
		}
	}else if(p1.getRango() >=  41){
		if(CONSULTORIOS.size()==CAP_MAX_CONS){
			COLA_CONS.push(p1);
		}else if(CONSULTORIOS.size()<CAP_MAX_CONS){
			CONSULTORIOS.push_back(p1);
		}
	}
}


void f_observacion(vector<Paciente> &obs){
	for(int i = 0; i<obs.size(); i++){
		int interv = 1+rand()% (10);
		if(interv < 3){
			HOSPITALIZACION.push_back(obs[i]);
			obs.erase(obs.begin()+i);
		}
	}
}









void imprimir(Heap<Paciente> heap){
	for(int i = 1; i<heap.getCuenta()+1; i++){
		cout << heap[i].getTriage() << heap[i].getRango() << endl;
	}
}



