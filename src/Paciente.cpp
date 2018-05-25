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

	Documento = 1112000000+rand() %(1112999999);
	Edad = rand()% (91 - 0);
	Triage =1+ rand()% (5 - 1);
	Rango = setRango();
	Tiempo =new int [5];
	for(int i = 0; i < 5; i++ ){
		Tiempo[i] =0;
	}

}

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

int Paciente::addTiempo(int i){
	Tiempo[i]++;;
	return Tiempo[i];
}

int Paciente::getTiempo(int i ){
	return Tiempo[i];
}

int Paciente::getRango(){
	return Rango;
}


int Paciente::setRango(){
if (Edad <18) Rango = 1 + Triage *10;
if (Edad <35 && Edad >= 18) Rango = 4 + Triage *10;
if (Edad <60 && Edad >= 35) Rango = 3 + Triage *10;
if (Edad <=90 && Edad >=60) Rango = 2 + Triage *10;

return Rango;
}

bool Paciente::operator<(Paciente &paciente){
	if(getTriage() * 10 + getRango() <  paciente.getTriage() * 10 + paciente.getRango()){
		return true;
	}else {
		return false;
	}
}

bool Paciente::operator >(Paciente &paciente){
	if(getTriage() * 10 + getRango() >  paciente.getTriage() * 10 + paciente.getRango()){
			return true;
		}else {
			return false;
		}
}
