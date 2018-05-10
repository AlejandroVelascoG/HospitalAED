/*
 * Paciente.cpp
 *
 *  Created on: 8/05/2018
 *      Author: vonnewmann
 */

#include "Paciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

Paciente::Paciente() {

	Documento = rand() %(1000000000 - 0);
	Edad = rand()% (91 - 0);
	Triage = rand()% (5 - 1);
	TiempoDeVida = rand()% (481 - 60);// de 1 a 8 horas

}

/*

Paciente::~Paciente(){

}
*/

int Paciente::getDocumento(){
	return Documento;
}

int Paciente::getEdad(){
	return Edad;
}


int Paciente::getTriage(){
	return Triage;
}


void Paciente::setTriage(int tr){
	Triage = tr;
}



int Paciente::getTiempoDeVida(){
	return TiempoDeVida;
}



void Paciente::setTiempoDeVida(int tv){
	TiempoDeVida = tv;
}
