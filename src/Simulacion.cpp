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

// CONSTANTE TIEMPO

const int TIEMPO = 120;



//CONSTANTE QUE CONTROLARÁ LA CANTIDAD DE PACIETES QUE CLASIFICARA EN CIERTO TIEMPO

const int PARTICION = 4;

// ASIGNACION DE ESPACIO DENTRO DEL ARRGLO TIEMPO DE LA CLASE PACIENTE

const int ESPACIO_OBSER = 0;
const int ESPACIO_EMER = 1;
const int ESPACIO_QUIRO = 2;
const int ESPACIO_HOSP = 3;
const int ESPACIO_CONSUL = 4;


// SALA CONSTANTES

const int MAX_CAP_SALA = 100;// ESTA no se va utilizar de momento
const int PACIENTES_INI = 50;

// EMERGENCIAS CAPACIDAD:
const int CAP_MAX_EMER = 20;

// OBSERVACIÓN CAPACIDAD:
const int CAP_MAX_OBSER = 10;

// QUIRÓFANO CAPACIDAD:
const int CAP_MAX_QUIR = 5;

// CONSULTORIOS:
const int CAP_MAX_CONS = 15;

// HOSPITALIZACIÓN:
const int CAP_MAX_HOSP = 30;



// FUNCIONES
void clasificar (Paciente &p1, vector<Paciente> &EMERGENCIAS, Heap <Paciente> &COLA_EMER, vector<Paciente> &OBSERVACION, queue<Paciente> &COLA_OBSER,
		vector<Paciente> &CONSULTORIOS, queue<Paciente> &COLA_CONS);

void imprimir(Heap<Paciente> heap);

void imprimir(vector<Paciente> heap);

void crearPacientes(Heap<Paciente> &SALA);

void nuevoPaciente(Heap<Paciente> &SALA);

// FUNCIONES POR SALA

void f_observacion(vector<Paciente> &OBSERVACION,vector<Paciente> &HOSPITALIZACION,queue <Paciente> &COLA_HOSP,
		vector<Paciente> &DE_ALTA);

void f_emergencias(vector<Paciente> &EMERGENCIAS,vector<Paciente> &QUIROFANOS,Heap <Paciente> &COLA_QUIR,vector<Paciente> &OBSERVACION,
queue<Paciente> &COLA_OBSER);
void f_quirofano(vector<Paciente> &QUIROFANOS, vector<Paciente> &HOSPITALIZACION,queue<Paciente> &COLA_HOSP,
		vector<Paciente> &DECESOS) ;

void f_hozpitalizacion(vector<Paciente> &HOSPITALIZACION,Heap<Paciente> &COLA_QUIR, vector<Paciente> &QUIROFANOS,
		vector<Paciente> &DE_ALTA);

void f_consultorio(vector<Paciente> &CONSULTORIOS, vector<Paciente> &DE_ALTA);

// metodos para las colas adicionales y Heaps

void pop_Paciente_Cola_Obser(queue <Paciente> &COLA_OBSER, vector<Paciente> &OBSERVACION);

void pop_Paciente_Cola_Consul(queue<Paciente> &COLA_CONS, vector<Paciente> &CONSULTORIOS);

void pop_Paciente_Heap_Emer(Heap<Paciente> &COLA_EMER, vector<Paciente> &EMERGENCIAS);

void pop_Paciente_Heap_Quir(Heap<Paciente> &COLA_QUIR, vector<Paciente> &QUIROFANOS);



// ********MAIN*********************************************************************************************************


int main(){
	//CONTADOR CON EL QUE LA SIMULACION VA A CORRER
	int CONTADOR = 0;

	//SALA:
	Heap<Paciente> SALA;

	//EMERGENCIAS:
	vector <Paciente>EMERGENCIAS;
	Heap<Paciente> COLA_EMER;

	// OBSERVACIÓN:
	vector<Paciente> OBSERVACION;
	queue<Paciente> COLA_OBSER;

	//QUIROFANO:
	vector <Paciente>QUIROFANOS;
	Heap<Paciente> COLA_QUIR;

	//CONSULTORIOS:
	vector<Paciente> CONSULTORIOS;
	queue<Paciente> COLA_CONS;

	//HOSPITALIZACION:
	vector<Paciente> HOSPITALIZACION;
	queue<Paciente> COLA_HOSP;

	// PACIENTES DE ALTA
	vector<Paciente> DE_ALTA;

	// VECTOR DECESOS
	vector<Paciente> DECESOS;


	srand(time(NULL));
	crearPacientes(SALA);

	// CLASIFICA PRIMEROS 25 PACIENTES Y DEJA LA SALA CON 25 ESPERANDO

	for(int i = 0; i<PACIENTES_INI/2; i++){
		Paciente pac = SALA.eliminarMin();
		clasificar(pac,EMERGENCIAS,COLA_EMER,OBSERVACION,COLA_OBSER,CONSULTORIOS,COLA_CONS);
	}



		while(CONTADOR <= TIEMPO){
			if (CONTADOR %5 ==0){
				int interv = 1+rand()% (10);
				for (int i =0; i< PACIENTES_INI/interv; i++){
					nuevoPaciente(SALA);
				}//cierra el if de CONTADOR %5
			}
			if (CONTADOR %12 ==0){
				for(int i = 0 ; i<PACIENTES_INI/PARTICION; i++ ){
					Paciente pac = SALA.eliminarMin();
					clasificar(pac,EMERGENCIAS,COLA_EMER,OBSERVACION,COLA_OBSER,CONSULTORIOS,COLA_CONS);
				}

			}//cierra el if de CONTADOR %12

			f_observacion(OBSERVACION,HOSPITALIZACION,COLA_HOSP,DE_ALTA);

			f_emergencias(EMERGENCIAS,QUIROFANOS,COLA_QUIR,OBSERVACION,COLA_OBSER);

			f_quirofano(QUIROFANOS, HOSPITALIZACION,COLA_HOSP,DECESOS);

			f_hozpitalizacion(HOSPITALIZACION,COLA_QUIR, QUIROFANOS,DE_ALTA);

			f_consultorio(CONSULTORIOS, DE_ALTA);

			pop_Paciente_Cola_Obser(COLA_OBSER, OBSERVACION);

			pop_Paciente_Cola_Consul(COLA_CONS, CONSULTORIOS);

			pop_Paciente_Heap_Quir(COLA_QUIR, QUIROFANOS);

			CONTADOR ++;
		}

		cerr <<"Estos pacientes se les dio DE ALTA:"<<endl;
		imprimir(DE_ALTA);

	cerr <<"Estos pacientes murieron: "<<endl;
	imprimir(DECESOS);

}


// ********END MAIN***********



// PACIENTES INICIALES

void crearPacientes(Heap<Paciente> &SALA){

	for (int i = 0; i< PACIENTES_INI; i++){
		Paciente nuevo;
		SALA.insertar(nuevo);
	}
}

;
void nuevoPaciente(Heap<Paciente> &SALA){
	Paciente px;
	SALA.insertar(px);
}


void clasificar (Paciente &p1, vector<Paciente> &EMERGENCIAS, Heap <Paciente> &COLA_EMER, vector<Paciente> &OBSERVACION, queue<Paciente> &COLA_OBSER,
		vector<Paciente> &CONSULTORIOS, queue<Paciente> &COLA_CONS){

	if(p1.getRango() <= 14){

		if(EMERGENCIAS.size() >= CAP_MAX_EMER){

			COLA_EMER.insertar(p1);
		}else {
			EMERGENCIAS.push_back(p1);
		}
	}else if(p1.getRango() >= 21 && p1.getRango() < 31){
		if(EMERGENCIAS.size() >= CAP_MAX_EMER){
			COLA_EMER.insertar(p1);
		}else {
			EMERGENCIAS.push_back(p1);
		}
	}else if(p1.getRango()>= 31 && p1.getRango()< 41){
		if(OBSERVACION.size() >= CAP_MAX_OBSER){
			COLA_OBSER.push(p1);
		}else {
			OBSERVACION.push_back(p1);
		}
	}else if(p1.getRango() >=  41){
		if(CONSULTORIOS.size()>=CAP_MAX_CONS){
			COLA_CONS.push(p1);
		}else {
			CONSULTORIOS.push_back(p1);
		}
	}
}

// Este metodo decide a traves de una probabilidad si envia al paciente a hospitalizacion(o su cola) o le dan de alta


void f_observacion(vector<Paciente> &OBSERVACION,vector<Paciente> &HOSPITALIZACION,queue <Paciente> &COLA_HOSP,
		vector<Paciente> &DE_ALTA){
	for(int i = 0; i<OBSERVACION.size(); i++){
			OBSERVACION[i].addTiempo(ESPACIO_OBSER);
		int temp= OBSERVACION[i].getTiempo(ESPACIO_OBSER);
		if( temp> 10){

			int interv = 1+rand()% (10);

			if(interv <= 3){
				HOSPITALIZACION.size()<CAP_MAX_HOSP ?
						HOSPITALIZACION.push_back(OBSERVACION[i]) : COLA_HOSP.push(OBSERVACION[i]);
				OBSERVACION.erase(OBSERVACION.begin()+i);
			}else if(3<interv && interv <=6){
				DE_ALTA.push_back(OBSERVACION[i]);
				OBSERVACION.erase(OBSERVACION.begin()+i);
			}
		}
	}
}

// Este metodo decide a traves de una probabilidad si envia al paciente a observacion(o su cola) o a el quirofano
//(o su cola)

void f_emergencias(vector<Paciente> &EMERGENCIAS,vector<Paciente> &QUIROFANOS,Heap <Paciente> &COLA_QUIR,vector<Paciente> &OBSERVACION,
queue<Paciente> &COLA_OBSER){
	//FALTA SUMAR TIEMPO
	for(int i = 0; i<EMERGENCIAS.size(); i++){
		EMERGENCIAS[i].addTiempo(ESPACIO_EMER);
		int temp = EMERGENCIAS[i].getTiempo(ESPACIO_EMER);
		if(temp< 20){
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
				}else if(OBSERVACION.size()<CAP_MAX_OBSER){
					OBSERVACION.push_back(EMERGENCIAS[i]);
				}
				EMERGENCIAS.erase(EMERGENCIAS.begin()+i);
			}
		}
	}
}

// Este metodo decide a traves de una probabilidad si envia al paciente a HOSPITALIZACION(o su cola) o se muere

void f_quirofano(vector<Paciente> &QUIROFANOS, vector<Paciente> &HOSPITALIZACION,queue<Paciente> &COLA_HOSP,
		vector<Paciente> &DECESOS) {

	for(int i = 0; i<QUIROFANOS.size(); i++){
		QUIROFANOS[i].addTiempo(ESPACIO_QUIRO);
		int temp = QUIROFANOS[i].getTiempo(ESPACIO_QUIRO);
		int interv = 1+rand()% (10);
		if(interv <= 3){
			if(HOSPITALIZACION.size() >= CAP_MAX_QUIR )
				COLA_HOSP.push(QUIROFANOS[i]);
			else if(HOSPITALIZACION.size()< CAP_MAX_QUIR )
				HOSPITALIZACION.push_back(QUIROFANOS[i]);

		QUIROFANOS.erase(QUIROFANOS.begin()+ i);
		}else if(3<interv && interv<=6){
			int prob_quirofano = 1+rand()% (20 - 0);
			if(prob_quirofano < 19){
				HOSPITALIZACION.push_back(QUIROFANOS[i]);
				QUIROFANOS.erase(QUIROFANOS.begin()+ i);
			}
			if(prob_quirofano == 20){
				DECESOS.push_back(QUIROFANOS[i]);
				QUIROFANOS.erase(QUIROFANOS.begin()+ i);
			}
		}
	}
}

void f_hozpitalizacion(vector<Paciente> &HOSPITALIZACION,Heap<Paciente> &COLA_QUIR, vector<Paciente> &QUIROFANOS,
		vector<Paciente> &DE_ALTA){

	for(int i = 0; i<HOSPITALIZACION.size(); i++){
		HOSPITALIZACION[i].addTiempo(ESPACIO_HOSP);
		int temp = HOSPITALIZACION[i].getTiempo(ESPACIO_HOSP);
		if ( temp< 20){
			int interv = 1+rand()% (10);
			if(interv <= 3){
				if(QUIROFANOS.size() == CAP_MAX_QUIR )
					COLA_QUIR.insertar(HOSPITALIZACION[i]);
				else if(QUIROFANOS.size() < CAP_MAX_QUIR )
					QUIROFANOS.push_back(HOSPITALIZACION[i]);
					HOSPITALIZACION.erase(HOSPITALIZACION.begin() +i);
			}else if (interv > 3 && interv <= 8){
				DE_ALTA.push_back(HOSPITALIZACION[i]);
				HOSPITALIZACION.erase(HOSPITALIZACION.begin() +i);
			}
		}
	}
}


void f_consultorio(vector<Paciente> &CONSULTORIOS, vector<Paciente> &DE_ALTA){

	for(int i = 0 ; i < CONSULTORIOS.size(); i++){
		CONSULTORIOS[i].addTiempo(ESPACIO_CONSUL);
		CONSULTORIOS[i].addTiempo(ESPACIO_CONSUL);
		int temp = CONSULTORIOS[i].getTiempo(ESPACIO_CONSUL);
		if (temp > 5){
			DE_ALTA.push_back(CONSULTORIOS[i]);
			CONSULTORIOS.erase(CONSULTORIOS.begin() +i);
		}
	}
}
//Función para pasar los pacientes de la cola de observaciones a el vector observacionres
void pop_Paciente_Cola_Obser(queue <Paciente> &COLA_OBSER, vector<Paciente> &OBSERVACION){
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
void pop_Paciente_Cola_Consul(queue<Paciente> &COLA_CONS, vector<Paciente> &CONSULTORIOS  ){
	while(COLA_CONS.empty() == false){
		if (CONSULTORIOS.size() < CAP_MAX_CONS){
			Paciente nuevo  = COLA_CONS.front();
			COLA_CONS.pop();
			CONSULTORIOS.push_back(nuevo);
		}
	}
}

//Función para pasar los pacientes de Heap de emergencias a el vector emergencias
void pop_Paciente_Heap_Emer(Heap<Paciente> &COLA_EMER, vector<Paciente> &EMERGENCIAS){
	while(COLA_EMER.empty() == false ){
		if(EMERGENCIAS.size()< CAP_MAX_EMER){
			Paciente nuevo = COLA_EMER.eliminarMin();
			EMERGENCIAS.push_back(nuevo);
		}else
			break;
	}
}

//Función para pasar los pacientes de Heap de emergencias a el vector emergencias
void pop_Paciente_Heap_Quir(Heap<Paciente> &COLA_QUIR, vector<Paciente> &QUIROFANOS){
	while(COLA_QUIR.empty() == false ){
		if(QUIROFANOS.size()< CAP_MAX_QUIR){
			Paciente nuevo = COLA_QUIR.eliminarMin();
			QUIROFANOS.push_back(nuevo);
		}else
			break;
	}
}

void imprimir(Heap<Paciente> heap){
	for(int i = 1; i<heap.getCuenta()+1; i++){
		cout <<"Documento :" <<heap[i].getDocumento()<< endl<< "EDAD  :"<<heap[i].getEdad()<< endl<<
		"Rango :"<< heap[i].getRango()<<endl<<"TRIAGE :"<<heap[i].getTriage()<<endl<<"TIEMPO QUE SE DEMORÓ EN EMEREGENCIAS  :" <<heap[i].getTiempo(ESPACIO_EMER)<<endl<<
		"TIEMPO QUE SE DEMORÓ EN OBSERVACION  :"<< heap[i].getTiempo(ESPACIO_OBSER)<<endl<<"TIEMPO QUE SE DEMORÓ EN QUIROFANO  :"<<heap[i].getTiempo(ESPACIO_QUIRO)<<endl
		<< "TIEMPO QUE SE DEMORÓ EN  HOSPITALIZACION :"<<heap[i].getTiempo(ESPACIO_HOSP)<<endl<<"TIEMPO QUE SE DEMORÓ EN CONSULTAS  :"<<heap[i].getTiempo(ESPACIO_CONSUL)<<endl
		<<endl<<endl<<endl;
	}
}

void imprimir(vector<Paciente> heap){
	for(int i = 0; i < heap.size(); i++){
		cout <<"Documento :" <<heap[i].getDocumento()<< endl<< "EDAD  :"<<heap[i].getEdad()<< endl<<
		"Rango :"<< heap[i].getRango()<<endl<<"TRIAGE :"<<heap[i].getTriage()<<endl<<"TIEMPO QUE SE DEMORÓ EN EMEREGENCIAS  :" <<heap[i].getTiempo(ESPACIO_EMER)<<endl<<
		"TIEMPO QUE SE DEMORÓ EN OBSERVACION  :"<< heap[i].getTiempo(ESPACIO_OBSER)<<endl<<"TIEMPO QUE SE DEMORÓ EN QUIROFANO  :"<<heap[i].getTiempo(ESPACIO_QUIRO)<<endl
		<< "TIEMPO QUE SE DEMORÓ EN  HOSPITALIZACION :"<<heap[i].getTiempo(ESPACIO_HOSP)<<endl<<"TIEMPO QUE SE DEMORÓ EN CONSULTAS  :"<<heap[i].getTiempo(ESPACIO_CONSUL)<<endl
		<<endl<<endl<<endl;
			}
	}

