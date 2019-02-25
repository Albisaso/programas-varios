/*********************************************************************************
 * Curso de Programación 1. Tema 7 y prueba voluntaria de evaluación 1
 * Autores: Miguel Ángel Latre, Javier Martínez y
 *          Sergio Beltrán García con NIP: 757201
 * Última revisión: 3 de noviembre de 2018
 * Resumen: Programa que escribe en la pantalla el calendario de un determinado
 *          mes de un año, que se solicitan al usuario. El programa se asegura de
 *          que el mes introducido está comprendido entre 1 y 12 y de que el año
 *          es igual o posterior a 1900.
 *          Clase de problemas correspondiente al tema 7 (diseño modular y
 *          descendente) y 1ª prueba voluntaria de evaluación (curso 2018-19).
\********************************************************************************/

#include <iostream>
#include <iomanip>
#include "../../Biblioteca/fechas.h"
using namespace std;


/*
 * Pre:  ---
 * Post: Ha solicitado reiteradamente al usuario un mes de un año igual o
 *       posterior a 1900, leyéndolos en los parámetros «mes» y «agno», hasta que
 *       1 ≤ mes ≤ 12 y hasta que agno ≥ 1900.
 */
void pedirDatos(int& mes, int& agno) {
	cout << "Introduzca el mes [1-12]: ";
	cin >> mes;
	while (mes < 1 || mes > 12) {
		cout << "El mes debe estar comprendido entre 1 y 12: ";
		cin >> mes;
	}
	cout << "Introduzca un agno igual o posterior a 1900: ";
	cin >> agno;
	while (agno < 1900) {
		cout << "El agno debe ser igual o posterior a 1900: ";
		cin >> agno;
	}
}


/*
 * Pre:  Los valores de los parámetros «dia», «mes» y «agno» representan
 *       conjuntamente una fecha válida del calendario gregoriano igual o
 *       posterior al 1 de enero de 1900.
 * Post: Ha devuelto un entero que codifica el día de la semana de la fecha
 *       representada por los valores de los parámetros «dia», «mes» y «agno», de
 *       acuerdo con la siguiente codificación: el 0 codifica el lunes, el 1
 *       codifica martes y así sucesivamente hasta el 6, que codifica el domingo.
 */
int diaDeLaSemana(const int dia, const int mes, const int agno) {
	int contador = 0;
	for (int i = 1900; i < agno; i++) {
		contador += diasDelAgno(i);
	}
	const int DIAS_POR_SEMANA = 7;
	int diaSemana = (contador + diaEnElAgno(dia, mes, agno) - 1) % DIAS_POR_SEMANA;
	//El día 1 de enero de 1900 fue lunes, de ahí el restarle un uno al contador
	return diaSemana;
}

/*
 * Pre:  1 ≤ mes ≤ 12
 * Post: Ha escrito en la pantalla el nombre (en mayúsculas) del mes
 *       correspondiente al valor del parámetro «mes».
 * Nota: Este código se explicará adecuadamente en el tema 10 (cadenas de
 *       caracteres).
 */
void escribirNombreMes(const int mes) {
	const int NUM_MESES = 12;
	const int MAX_LONG_NOMBRE_MES = 10;
	const char NOMBRES_MES[NUM_MESES][MAX_LONG_NOMBRE_MES + 1] = { "ENERO",
			"FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO", "JULIO", "AGOSTO",
			"SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE" };
	cout << NOMBRES_MES[mes - 1];
}

/*
 * Pre:  1 ≤ mes ≤ 12
 * Post: Ha escrito en la pantalla la cabecera del calendario del mes «mes» del
 *       año «agno» con un el formato del siguiente ejemplo:
 *
 *                     NOVIEMBRE 2018
 *          L   M   X   J   V   S   D
 *       ----------------------------
 */
void escribirCabecera(const int mes, const int agno) {
	cout << setw(23);
	escribirNombreMes(mes);
	cout << " " << agno << endl;
	cout << "   L   M   X   J   V   S   D" << endl;
	cout << "----------------------------" << endl;;
}


/*
 * Pre:  1 ≤ mes ≤ 12 y agno ≥ 1900
 * Post: Ha escrito en la pantalla el calendario del mes «mes» del año «agno» con
 *       el formato del siguiente ejemplo:
 *
 *                     NOVIEMBRE 2018
 *          L   M   X   J   V   S   D
 *       ----------------------------
 *                      1   2   3   4
 *          5   6   7   8   9  10  11
 *         12  13  14  15  16  17  18
 *         19  20  21  22  23  24  25
 *         26  27  28  29  30
 */
void escribirCalendario(const int mes, const int agno) {
	escribirCabecera(mes, agno);
	int i = 0;
	while (diaDeLaSemana(1, mes, agno) != i) {
		cout << setw(4) << " ";
		i++;
	}
	cout << setw(4);
	//Se han creado los espaciados necesarios para que el primer día del mes
	//de un agno coincida con la columna de la cabecera de su respectivo día
	const int DOMINGO = 6;
	for (int dia = 1; dia <= diasDelMes(mes, agno); dia++) {
		cout << dia << setw(4);
		if (diaDeLaSemana(dia, mes, agno) == DOMINGO) {
			cout << endl;
			//Si es domingo hay que bajar de línea
		}
	}
	if (diaDeLaSemana(diasDelMes(mes, agno), mes, agno) != DOMINGO) {
		cout << endl;
	}
	/*
	 *Si un mes no finaliza en domingo la función termina con un salto de línea, en caso
	 *contrario ya se habría hecho un salto de línea gracias al if que hay dentro del for;
	 *esto hace que al finalizar esta función exista un único salto de linea
	 */
}

/*
 * Pre:  ---
 * Post: Ha solicitado al usuario un mes de un año igual o posterior a 1900, se
 *       ha asegurado de que el mes introducido está comprendido entre 1 y 12 y
 *       de que el año es igual o posterior a 1900 y ha terminado escribiendo el
 *       calendario del mes solicitado en la pantalla.
 */
int main() {
	int mes, agno;
	pedirDatos(mes, agno);
	escribirCalendario(mes, agno);
	return 0;
}
