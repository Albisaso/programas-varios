 /*
 * Pre:  La terna de parámetos «dia», «mes» y «agno» definen una fecha
 *       válida del calendario gregoriano, la fecha «dia/mes/agno».
 * Post: El valor del parámetro «f», al ser escrito en base 10, tiene un
 *       formato de ocho dígitos «aaaammdd» que representa
 *       la fecha «dia/mes/agno» donde los dígitos «aaaa» representan el
 *       año de la fecha, los dígitos «mm», el mes y los dígitos «dd», el
 *       día.
 */
void componer(int dia, int mes, int agno, int& f) {
	f = agno * 10000 + mes * 100 + dia;
}


/*
 * Pre:  El valor de «f» escrito en base 10 tiene la forma «aaaammdd»
 *       donde los dígitos «aaaa» representan el año de una fecha válida
 *       del calendario gregoriano, los dígitos «mm», el mes y los dígitos
 *       «dd», el día.
 * Post: Los valores de los parámetros «dia», «mes» y «agno» son iguales,
 *       respectivamente, al día, al mes y al año de la fecha «f».
 */
void descomponer(int f, int& dia, int& mes, int& agno) {
	dia = f % 100;
	mes = (f / 100) % 100;
	agno = f / 10000;
}


/*
 * Pre:  Los valores de los parámetros «f1» y «f2» escritos en base 10
 *       tienen la forma «aaaammdd», donde los dígitos «aaaa» representan
 *       el año, los dígitos «mm», el mes y los dígitos «dd» el día de
 *       sendas fechas del calendario gregoriano.
 * Post: Ha devuelto true si y solo si la fecha representada por el valor
 *       del parámetro «f1» es anterior a la representada por «f2».
 */
bool esAnterior(int f1, int f2) {
	return f1 < f2;
}


/*
 * Pre:  agno > 1582.
 * Post: Ha devuelto true si y solo si el año «agno» es bisiesto de
 *       acuerdo con las reglas del el calendario gregoriano.
 */
bool esBisiesto(int agno) {
	bool multiplo4 = (agno % 4 == 0);
	bool multiplo100 = (agno % 100 == 0);
	bool multiplo400 = (agno % 400 == 0);
	return multiplo400 || (multiplo4 && !multiplo100);
}


/*
 * Pre:  1 ≤ mes ≤ 12 y agno > 1582.
 * Post: Ha devuelto el número de días del mes correspondiente al
 *       parámetro «mes» del año correspondiente al parámetro «agno».
 *       Por ejemplo: diasDelMes(10, 2018) devuelve 31,
 *                    diasDelMes(2, 2018) devuelve 28 y
 *                    diasDelMes(2, 2020) devuelve 29.
 */
int diasDelMes(int mes, int agno) {
	if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 ||
		mes == 10 || mes == 12) {
		return 31;
	}
	else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
		return 30;
	}
	else if (mes == 2 && esBisiesto(agno)) {
		return 29;
	}
	else {
		return 28;
	}
}


/*
 * Pre:  agno > 1582.
 * Post: Ha devuelto el número de días que tiene el año «agno».
 *       Por ejemplo: diasDelAgno(2018) devuelve 365 y
 *                    diasDelAgno(2020) devuelve 366.
 */
int diasDelAgno(int agno) {
	if (esBisiesto(agno)) {
		return 366;
	}
	else {
		return 365;
	}
}


/*
 * Pre:  1 ≤ dia ≤ 31, 1 ≤ mes ≤ 12 y agno > 1582 y la fecha formada por
 *       «dia/mes/agno» es una fecha válida del calendario gregoriano.
 * Post: Ha devuelto el número de día del año de la fecha formada por
 *       «dia/mes/agno».
 *       Por ejemplo: diaEnElAgno(1, 1, 2019) devuelve 1;
 *                    diaEnElAgno(31, 12, 2018) devuelve 365;
 *                    diaEnElAgno(1, 2, 2019) devuelve 32 y
 *                    diaEnElAgno(31, 12, 2020) devuelve 366.
 */
int diaEnElAgno(int dia, int mes, int agno) {
	int total = dia;
	for (int i = 1; i < mes; i++) {
		total += diasDelMes(i, agno);
	}
	return total;
}


/*
 * Pre:  El valor de «fecha» escrito en base 10 tiene la forma «aaaammdd»,
 *       donde los dígitos «aaaa» representan el año, los dígitos «mm», el
 *       mes y los dígitos «dd» el día de una fecha válida del calendario
 *       gregoriano.
 * Post: Ha devuelto la fecha correspondiente al día posterior a la fecha
 *       representada por el valor del parámetro «fecha», representada con
 *       el mismo formato «aaaammdd» que «fecha».
 */
int diaSiguiente(int fecha) {
	int dia, mes, agno;
	if (fecha % 100 == diasDelMes((fecha / 100) % 100, fecha / 10000) &&
		(fecha / 100) % 100 == 12) {
		//La fecha indicada es el ultimo día de un agno
		return ((fecha / 10000) + 1) * 10000 + 101;
		//Al sumar 101 a una fecha compuesta donde sus ultimas cuatro cifras
		//son ceros hacemos que el mes y el día valgan 1
	}
	else if (fecha % 100 == diasDelMes((fecha / 100) % 100, fecha / 10000)) {
		//La fecha indicada es el último día de un mes, descontando
		//el mes 12 que se ejecutaría en el if
		descomponer(fecha, dia, mes, agno);
		mes++;
		dia = 1;
		componer(dia, mes, agno, fecha);
		return fecha;
	}
	else {
		return fecha + 1;
	}
}
