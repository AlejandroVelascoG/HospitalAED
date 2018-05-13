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

	Documento = 1112000000+rand() %(1112999999 - 0);
	Edad = rand()% (91 - 0);
	Triage =1+ rand()% (5 - 1);
	TiempoDeVida = 60+ rand()% (481);// de 1 a 8 horas
	Rango = this->setRango();

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

int Paciente::getRango(){
	return Rango;
}

int Paciente::setRango(){
if (Edad <18) Rango = 1;
if (Edad <35 && Edad >= 18) Rango = 4;
if (Edad <60 && Edad >= 35) Rango = 3;
if (Edad <=90 && Edad >=60) Rango = 2;

return Rango;
}

bool Paciente::operator<(Paciente &paciente){
	if(this->getTriage() * 10 + this->getRango() <  paciente.getTriage() * 10 + paciente.getRango()){
		return true;
	}else {
		return false;
	}
}

bool Paciente::operator >(Paciente &paciente){
	if(this->getTriage() * 10 + this->getRango() >  paciente.getTriage() * 10 + paciente.getRango()){
			return true;
		}else {
			return false;
		}
}
