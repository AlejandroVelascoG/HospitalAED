/*
 * Paciente.h
 *
 *  Created on: 8/05/2018
 *      Author: vonnewmann
 */

#ifndef SRC_PACIENTE_H_
#define SRC_PACIENTE_H_


class Paciente {
private:


	int Documento;
	int Edad;
	int Triage;
	int Rango;
	int setRango();
	int Tiempo[5];

public:

	Paciente();

	// ~Paciente();

	int getDocumento();

	int getEdad();

	int getTriage();

	void setTriage(int tr);

	int getTiempo(int i);

	int getRango();

	bool operator<(Paciente &paciente);

	bool operator>(Paciente &paciente);


};

#endif /* SRC_PACIENTE_H_ */

