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


//  ATENCION  ATENCION   ATENCION   ATENCION

/* Quizas no sea necesario el metodo alaeatorio, podes cambiar los intevalos de los  metodos f_emergencias.....
 * y bajar la probabilidad de los numeros para controlarlos. Ej: si el numero generado en quirofano es 0<=2 mate el paciente
 */


// CONSTANTE TIEMPO

const int TIEMPO = 720;

//CONTADOR CON EL QUE LA SIMULACION VA A CORRER

const int CONTADOR = 0;

// SALA

Heap<Paciente> SALA;
const int MAX_CAP_SALA = 100;// ESTA no se va utilizar de momento
const int PACIENTES_INI = 50;

// EMERGENCIAS:

vector <Paciente>EMERGENCIAS;
Heap<Paciente> COLA_EMER;
const int CAP_MAX_EMER = 10;

// OBSERVACIÓN:

vector<Paciente> OBSERVACION;
queue<Paciente> COLA_OBSER;
const int CAP_MAX_OBSER = 10;

// QUIRÓFANO:

vector <Paciente>QUIROFANOS;
Heap<Paciente> COLA_QUIR;
const int CAP_MAX_QUIR = 5;

// CONSULTORIOS:

vector<Paciente> CONSULTORIOS;
queue<Paciente> COLA_CONS;
const int CAP_MAX_CONS = 15;

// HOSPITALIZACIÓN

vector<Paciente> HOSPITALIZACION;
queue<Paciente> COLA_HOSP;
const int CAP_MAX_HOSP = 30;

// PACIENTES DE ALTA

vector<Paciente> DE_ALTA;

// VECTOR DECESOS

vector<Paciente> DECESOS;

// FUNCIONES

void clasificar(Paciente p1);

void imprimir(Heap<Paciente> heap);

void crearPacientes(Heap<Paciente> &SALA);

void nuevoPaciente();

// FUNCIONES POR SALA

void f_observacion();

void f_emergencias();

void f_quirofano();

// metodos para las colas adicionales y Heaps

void pop_Paciente_Cola_Obser();

void pop_Paciente_Cola_Consul();

void pop_Paciente_Heap_Emer();

void pop_Paciente_Heap_Quir();

// int numeroAleatorio(Paciente paciente);

// void f_quir(vector<Paciente> &qui);


// ********MAIN****************


int main(){
	srand(time(NULL));
	crearPacientes(SALA);

	// CLASIFICA PRIMEROS 25 PACIENTES Y DEJA LA SALA CON 25 ESPERANDO

	for(int i = 0; i<PACIENTES_INI/2; i++){
		Paciente pac = SALA.eliminarMin();
		clasificar(pac);
	}

	Paciente nuevo = EMERGENCIAS.front();
	//nuevo.getTiempo(0)++;
	cout << "deberia imprimir esto" << nuevo.getTiempo(0);


}


// ********END MAIN***********



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
			COLA_EMER.insertar(p1);
		}else if(EMERGENCIAS.size()<CAP_MAX_EMER){
			EMERGENCIAS.push_back(p1);
		}
	}else if(p1.getRango() >= 21 && p1.getRango() < 31){
		if(EMERGENCIAS.size()==CAP_MAX_EMER){
			COLA_EMER.insertar(p1);
		}else if(EMERGENCIAS.size()<CAP_MAX_EMER){
			EMERGENCIAS.push_back(p1);
		}
	}else if(p1.getRango()>= 31 && p1.getRango()< 41){
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

// Este metodo decide a traves de una probabilidad si envia al paciente a hospitalizacion(o su cola) o le dan de alta

void f_observacion(){// HAY UN PROBLEMA, TENEMOS QUE PREGUNTAR PRIMERO SI ES POSIBLE ENVIARLO
	for(int i = 0; i<OBSERVACION.size(); i++){    // A OBSERVACIONES O A LA COLA DE OBSERVACIONES
		if( OBSERVACION[i].getTiempo(0)> 10){

			int interv = 1+rand()% (10);

			if(interv <= 3){
				HOSPITALIZACION.size()<CAP_MAX_HOSP ?
						HOSPITALIZACION.push_back(OBSERVACION[i]) : COLA_HOSP.push(OBSERVACION[i]);

				/*

				if(HOSPITALIZACION.size() == CAP_MAX_HOSP){
					COLA_HOSP.push(OBSERVACION[i]);
				}else if(HOSPITALIZACION.size()<CAP_MAX_HOSP){ //creo que con esto se soluciona
					HOSPITALIZACION.push_back(OBSERVACION[i]);
				}
				*/

				OBSERVACION.erase(OBSERVACION.begin()+i);
			}else if(3<interv && interv <=6){
				DE_ALTA.push_back(OBSERVACION[i]);
				OBSERVACION.erase(OBSERVACION.begin()+i);
			}
		}	//propongo agregar un atributo tiempo; para determinar cuanto tiempo se demoro un paciente es salir de la sala
	}
}

// Este metodo decide a traves de una probabilidad si envia al paciente a observacion(o su cola) o a el quirofano
//(o su cola)

void f_emergencias(){
	for(int i = 0; i<EMERGENCIAS.size(); i++){
		int interv = 1+rand()% (10);
		if(interv <= 3){
			if(QUIROFANOS.size() == CAP_MAX_QUIR )
				COLA_QUIR.insertar(EMERGENCIAS[i]);
			else if(QUIROFANOS.size()< CAP_MAX_QUIR )
				QUIROFANOS.push_back(EMERGENCIAS[i]);
		EMERGENCIAS.erase(EMERGENCIAS.begin()+i);
		}else if(3<interv && interv<=6){
			if(OBSERVACION.size() == CAP_MAX_OBSER){
				COLA_OBSER.push(EMERGENCIAS[i]);
			}else if(OBSERVACION.size()<CAP_MAX_OBSER){//creo que con esto se soluciona
				OBSERVACION.push_back(EMERGENCIAS[i]);
			}
			EMERGENCIAS.erase(EMERGENCIAS.begin()+i);
		}
	}
}

// Este metodo decide a traves de una probabilidad si envia al paciente a HOSPITALIZACION(o su cola) o se muere

void f_quirofano(){
	for(int i = 0; i<QUIROFANOS.size(); i++){
		int interv = 1+rand()% (10);
		if(interv <= 3){
			if(HOSPITALIZACION.size() == CAP_MAX_QUIR )
				COLA_HOSP.push(QUIROFANOS[i]);
			else if(HOSPITALIZACION.size()< CAP_MAX_QUIR )
				HOSPITALIZACION.push_back(QUIROFANOS[i]);

		QUIROFANOS.erase(QUIROFANOS.begin()+ i);
		}else if(3<interv && interv<=6){
			DECESOS.push_back(QUIROFANOS[i]);
			QUIROFANOS.erase(QUIROFANOS.begin()+ i);
		}
	}
}

//Función para pasar los pacientes de la cola de observaciones a el vector observacionres
void pop_Paciente_Cola_Obser(){
	while(COLA_OBSER.empty() == false){
		if (OBSERVACION.size() < CAP_MAX_OBSER){
			Paciente nuevo  = COLA_OBSER.front();
			COLA_OBSER.pop();
			OBSERVACION.push_back(nuevo);
		}else{
			break;
		}
	}
}

//Función para pasar los pacientes de la cola de consultorios a el vector consultorios
void pop_Paciente_Cola_Consul(){
	while(COLA_CONS.empty() == false){
		if (CONSULTORIOS.size() < CAP_MAX_CONS){
			Paciente nuevo  = COLA_CONS.front();
			COLA_CONS.pop();
			CONSULTORIOS.push_back(nuevo);
		}
	}
}

//Función para pasar los pacientes de Heap de emergencias a el vector emergencias
void pop_Paciente_Heap_Emer(){
	while(COLA_EMER.empty() == false ){
		if(EMERGENCIAS.size()< CAP_MAX_EMER){
			Paciente nuevo = COLA_EMER.eliminarMin();
			EMERGENCIAS.push_back(nuevo);
		}else
			break;
	}
}

//Función para pasar los pacientes de Heap de emergencias a el vector emergencias
void pop_Paciente_Heap_Quir(){
	while(COLA_QUIR.empty() == false ){
		if(QUIROFANOS.size()< CAP_MAX_QUIR){
			Paciente nuevo = COLA_QUIR.eliminarMin();
			QUIROFANOS.push_back(nuevo);
		}else
			break;
	}
}

/**int numeroAleatorio(Paciente P1){
	if(P1.getRango() <= 14){
}
*/

void imprimir(Heap<Paciente> heap){
	for(int i = 1; i<heap.getCuenta()+1; i++){
		cout << heap[i].getTriage() << heap[i].getRango() << endl;
	}
}
