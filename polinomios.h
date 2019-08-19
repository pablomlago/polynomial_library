#pragma once

struct {
    int gradoPol;
    float *coeficientes;
} typedef Pol;

//Precondición : {TRUE}
Pol* lerPolinomio();

//Precondición: {polUsuario != NULL}
void escribirPolinomio(const Pol *polUsuario);

//Precondición: {polUsuario != NULL}
float avaliarPolinomio(const Pol *polUsuario, float punto);

//Precondición: {polUsuario != NULL}
Pol* derivarPolinomio(const Pol *polUsuario);

//Precondición: {pol1 != NULL && pol2 != NULL}
Pol* sumarPolinomios(Pol* pol1, Pol* pol2);

//Precondición: {pol1 != NULL && pol2 != NULL} 
Pol* multiplicarPolinomios(const Pol* pol1,const Pol* pol2);

//Precondición: {dividendo != NULL && divisor != NULL && 
    //&& dividendo->gradoPol >= divisor->gradoPol && 
    //&& ((divisor->gradoPol != 0) || (divisor->coeficientes) != 0.0))
Pol* dividirPolinomios(Pol** cociente, const Pol* dividendo, const Pol* divisor); //Devolvemos o resto

