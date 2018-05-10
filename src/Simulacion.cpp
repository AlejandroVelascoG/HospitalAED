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

using namespace std;
//Constantes
const int DOCTORES= 10;
const int CAMILLAS = 30;
const int ENFERMERAS=20;
const int ESPECIALISTAS= 5;
const int MAX_CAP_SALA = 100;

//Tiempos

int Tespera;
const int TRECUPERACION = 30;



int main(){

	// numero aleatorio de pacientes que ingresan en la sala

	int cantPacientes = rand()% (100 - 50);

	// vector que representa la sala
	vector<Paciente> sala;

for(int i = 0; i<15; i++){
	Paciente nuevo;
	sala.push_back(nuevo);
	}

for(int i = 0; i<sala.size(); i++){
	cout << sala[i].getDocumento() << endl;
	}

}


