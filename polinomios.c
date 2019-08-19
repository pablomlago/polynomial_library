#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polinomios.h"

//Función auxiliar para axustar os grados dos polinomios
//No caso de que o coeficiente principal sexa nulo
int axustarGrado(Pol* polUsuario);

int axustarGrado(Pol* polUsuario)
{
    float *datosAxustados = NULL;
    int gradoAxustado = 0; //Grado real do polinomio
    int i = 0;
    int erro = 0; //Mantense se a corrección non foi necesaria ou se realizou con éxito
    
    //Non chegamos a 0 pois consideramos polinomios os constantes 0
    i = polUsuario->gradoPol;
    while((i>0) && (*(polUsuario->coeficientes + i) == 0.0)) //Saímos cando algún dos coeficientes non é nulo
    {
        i--; //Reducimos tantos grados como coeficientes principales nulos atopemos
    }
    gradoAxustado = i; 
    
    //Se o polinomio orixinal ten un grado que non se corresponde cos seus coeficientes
    //Axustamos o grado e desfacémonos dos datos redundantes
    if(gradoAxustado < polUsuario->gradoPol) 
    {
        //Gardaremos neste vector os datos do polinomo
        datosAxustados = (float*)malloc((gradoAxustado+1)*sizeof(float));
    
        if(datosAxustados != NULL)
        {
            for(i = 0; i <= gradoAxustado; i++)
            {
                *(datosAxustados + i) = *(polUsuario->coeficientes + i);
            }
            //Borramos os coeficientes do polinomio anteriores
            free(polUsuario->coeficientes);
            //Asignámoslle o seu grado real
            polUsuario->gradoPol = gradoAxustado;
            //E os coeficientes non redundantes
            polUsuario->coeficientes = datosAxustados;
        }
        else
        {
            //Non se puido facer a reserva de memoria
            //Devolvemos erro para que outras funcións podan manexar esta situación
            erro = 1;
        }
    }
    
    return erro;
}

Pol* lerPolinomio() //Precondición: {TRUE}
{
    Pol* polinomio = NULL;
    int grado = 0;
    int i = 0;
    float temp = 0.0;
    
    printf("Introduce o grado do polinomio: ");
    scanf("%d", &grado);
    
    if(grado >= 0) //O grado introducido é válido
    {
        polinomio = (Pol*)malloc(sizeof(Pol));
        
        if(polinomio != NULL)
        {
            polinomio->gradoPol = grado;
            polinomio->coeficientes = (float*)malloc((grado+1)*sizeof(float));
            
            if(polinomio->coeficientes != NULL)
            {
                //Completamos o vector de coeficientes do polinomio
                //Pedindo o usuario que os introduza
                for(i = grado; i >= 0; i--)
                {
                    printf("Introduce o coeficiente do termo de grado %d: ", i);
                    scanf("%f", &temp);
                    *(polinomio->coeficientes + i) = temp;
                }
                if(axustarGrado(polinomio)) //Erro ao tentar axustar o polinomio ao seu verdadeiro grado
                {
                    //Abortamos a creación do polinomio
                    printf("Os coeficientes introducidos non se axustan o grado do polinomio!\n");
                    printf("A correción automática fallou!\n");
                    
                    free(polinomio->coeficientes);
                    polinomio->coeficientes = NULL;
                    
                    free(polinomio);
                    polinomio = NULL;
                }
            }
            else
            {
                printf("Non se puido facer a reserva de memoria para os coeficientes!\n");
                
                free(polinomio);
                polinomio = NULL;
            }
        }
        else
        {
            printf("Non se puido facer a reserva de memoria para o polinomio!\n");
        }
    }
    else
    {
        printf("Non se introduciu un grado válido!\n");
    }
    
    return polinomio;
}

void escribirPolinomio(const Pol *polUsuario) //{polUsuario != NULL}
{
    int i = 0;
    
    printf("Polinomio de grado %d\n", polUsuario->gradoPol);
    
    if(polUsuario->gradoPol > 0)
    {
        for(i = (polUsuario->gradoPol); i >= 0; i--)
        {
            if((*(polUsuario->coeficientes + i) != 0.0)) //Non mostramos os termos nulos
            {
                printf("%.03fx^%d ", *(polUsuario->coeficientes + i), i);
            }
        }
    }
    else
    {
        printf("%.03fx^0 ", *(polUsuario->coeficientes));
    }
    
    printf("\n");
}

float avaliarPolinomio(const Pol *polUsuario, float punto) //{PolUsuario != NULL}
{
    float sumaAcumulada = 0.0;
    float produtoAcumulado = 1.0; //Evitamos usar a función pow e empregar outra librería externa
    int i = 0; 
    
    for(i = 0; i <= (polUsuario->gradoPol); i++)
    {
        if(i > 0)
        {
            produtoAcumulado *= punto;
        }
        sumaAcumulada += *(polUsuario->coeficientes + i) * produtoAcumulado;
    }
    
    return sumaAcumulada;
}

Pol* derivarPolinomio(const Pol *polUsuario) 
{
    Pol* polinomioDerivado = NULL;
    int gradoDerivado = 0;
    int i = 0;
    
    //O polinomio derivado sempre será un grado inferior
    //Salvo no caso de que o polinomio orixinal sexa constante
    gradoDerivado = polUsuario->gradoPol - 1;
    
    
    polinomioDerivado = (Pol*)malloc(sizeof(Pol));
        
    if(polinomioDerivado != NULL)
    {
        if(gradoDerivado >= 0) //Podería ser que fóra -1 (o polinomio orixinal era constante)
        {
            polinomioDerivado->coeficientes = (float*)malloc((gradoDerivado + 1)*sizeof(float));
        } 
        else
        {
            //Mantense o grado no caso de que o polinomio orixinal fose constante
            polinomioDerivado->coeficientes = (float*)malloc(sizeof(float));
        }
        
        if(polinomioDerivado->coeficientes != NULL)
        {
            if(gradoDerivado >= 0)
            {
                polinomioDerivado->gradoPol = gradoDerivado;
                //Calculamos os coeficientes do polinomio derivado
                for(i = 0; i <= gradoDerivado; i++)
                {
                    //O polinomio inicial sempre terá un termo máis que o derivado
                    *(polinomioDerivado->coeficientes + i) = *(polUsuario->coeficientes + (i+1))*(i+1);
                }
            }
            else
            {
                //Polinomio nulo se o polinomio orixinal era constante
                polinomioDerivado->gradoPol = 0;
                *(polinomioDerivado->coeficientes) = 0.0;
            }
        }
        else
        {
            printf("Non se puido facer a reserva de memoria para os coeficientes!\n");
            
            free(polinomioDerivado);
            polinomioDerivado = NULL;
        }
        
    }
    else
    {
        printf("Non se puido facer a reserva de memoria para o polinomio!\n");
    }
    
    return polinomioDerivado;
}


Pol* sumarPolinomios(Pol* pol1, Pol* pol2) //{pol1, pol2 != NULL}
{
    Pol* temp = NULL;
    Pol* polSuma = NULL;
    int i = 0;
    
    if(pol1->gradoPol > pol2->gradoPol) //pol2 sempre é o polinomio de maior grado
    {
        temp = pol1;
        pol1 = pol2;
        pol2 = temp;
        temp = NULL;
    }
    
    polSuma = (Pol*)malloc(sizeof(Pol));
    
    if(polSuma != NULL)
    {
        polSuma->gradoPol = pol2->gradoPol; //A priori, supoñemos que o grado da suma será o do polinomio de maior grado
        polSuma->coeficientes = (float*)malloc((polSuma->gradoPol+1)*sizeof(float));
                
        if(polSuma->coeficientes != NULL)
        {
            for(i = 0; i <= pol1->gradoPol; i++) //Sumamos os coeficientes ata onde alcanzan os do polinomio de grado menor 
            {
                *(polSuma->coeficientes + i) = *(pol1->coeficientes + i) + *(pol2->coeficientes + i);
            }
            //E completamos cos restantes
            for(; i <= pol2->gradoPol; i++) //Omitimos o primeiro termo xa que non interesa cambiar o valor actual de i
            {
                *(polSuma->coeficientes + i) = *(pol2->coeficientes + i);
            }
            //O polinomio suma pode ter un grado inferior ao esperado
            //É necesario realizar unha correción se esto se produce
            if(axustarGrado(polSuma)) 
            {
                //A función axustar grado devolveu erro
                printf("A correción automática do grado do polinomio suma fallou!\n");
                
                free(polSuma->coeficientes);
                polSuma->coeficientes = NULL;
                
                free(polSuma);
                polSuma = NULL;
            }
        }
        else
        {
            printf("Non se puido facer a reserva de memoria para os coeficientes!\n");
            
            free(polSuma);
            polSuma = NULL;
        }
    }
    else
    {
        printf("Non se puido facer a reserva de memoria para o polinomio!\n");
    }
    return polSuma;
}

Pol* multiplicarPolinomios(const Pol* pol1,const Pol* pol2)
{
    Pol* polMultiplicacion = NULL;
    int gradoMul = pol1->gradoPol + pol2->gradoPol; //Sabemos cal vai ser o grado do polinomio resultado
    int i = 0, j = 0; //Variables contador
    
    polMultiplicacion = (Pol*)malloc(sizeof(Pol));
    
    if(polMultiplicacion != NULL)
    {
        polMultiplicacion->gradoPol = gradoMul;
        polMultiplicacion->coeficientes = (float*)malloc((gradoMul+1)*sizeof(float));
        
        if(polMultiplicacion->coeficientes != NULL)
        {
            //Inicializamos a 0 todos os coeficientes do polinomio multiplicación
            for(i = 0; i <= polMultiplicacion->gradoPol; i++) 
            {    
                *(polMultiplicacion->coeficientes + i) = 0.0;
            }
            for(i = 0; i <= pol1->gradoPol; i++)
            {
                for(j = 0; j <= pol2->gradoPol; j++)
                {
                    //i + j dá o grado do coeficiente que se obtén
                    *(polMultiplicacion->coeficientes + i + j) += *(pol1->coeficientes + i) * (*(pol2->coeficientes + j));
                }
            }
        }
        else
        {
            printf("Non se puido facer a reserva de memoria para os coeficientes!\n");
            
            free(polMultiplicacion);
            polMultiplicacion = NULL;
        }
    }
    else
    {
        printf("Non se puido facer a reserva de memoria para o polinomio!\n");
    }
    
    return polMultiplicacion;
}

Pol* dividirPolinomios(Pol** cociente, const Pol* dividendo, const Pol* divisor)
{
    //A función devolverá o resto e gardará o cociente en resultado
    Pol* resto = NULL;
    int i = 0;
    int gradoCoef = 0;
    float temp = 0.0;
   
    if((*cociente) != NULL)
    {
        //Borramos o polinomio que se atopara almacenado no cociente
        free((*cociente)->coeficientes);
        (*cociente)->coeficientes = NULL;

        free((*cociente));
        (*cociente) = NULL;
    }

    (*cociente) = (Pol*)malloc(sizeof(Pol));

    if((*cociente) != NULL)
    {
        //O grado do cociente é a diferenza entre os grados do dividendo e o divisor
        gradoCoef = dividendo->gradoPol - divisor->gradoPol;
        (*cociente)->coeficientes = (float*)malloc((gradoCoef+1)*sizeof(float));

        if((*cociente)->coeficientes != NULL)
        {
            //Asignámoslle o grado correspondente ao polinomio cociente
            (*cociente)->gradoPol = gradoCoef;

            //Inicializamos todos os coeficientes do cociente a 0
            for(i = 0; i <= (*cociente)->gradoPol; i++)
            {
                *((*cociente)->coeficientes + i) = 0.0;
            }

            //Creamos o polinomio resto
            resto = (Pol*)malloc(sizeof(Pol));

            if(resto != NULL)
            {
                //Que terá, nun principio, o mesmo grado que o dividendo
                //E irá albergando os restos parciais
                resto->coeficientes = (float*)malloc((dividendo->gradoPol + 1)*sizeof(float));

                if(resto->coeficientes != NULL)
                {
                    resto->gradoPol = dividendo->gradoPol;

                    //Inicializamos os coeficientes do resto cos do dividendo
                    for(i = 0; i <= resto->gradoPol; i++)
                    {
                        *(resto->coeficientes + i) = *(dividendo->coeficientes + i);
                    }

                    //Mentras se pode dividir
                    while(resto->gradoPol >= divisor->gradoPol)
                    {
                        //Obtemos o grado de cada un dos coeficientes do resto
                        gradoCoef = resto->gradoPol - divisor->gradoPol;

                        temp = *(resto->coeficientes + resto->gradoPol) /
                                *(divisor->coeficientes + divisor->gradoPol);

                        *((*cociente)->coeficientes + gradoCoef) = temp;

                        //O coeficiente de maior grado do resto será necesariamente 0
                        //Realizando esta asignación evitamos erros 
                        //Debido a limitada capacidade de representación dun float
                        *(resto->coeficientes + resto->gradoPol) = 0.0;

                        //Non precisamos chegar a i = divisor->gradoPol
                        //Xa que ese coeficiente do resto será nulo
                        for(i = 0; i < divisor->gradoPol; i++)
                        {
                            *(resto->coeficientes + i + gradoCoef) -= *(divisor->coeficientes + i)*temp;
                        }

                        i = resto->gradoPol - 1; //Restamos 1 porque sabemos a priori que o coeficiente de maior grado é nulo

                        //Comprobamos se o grado do resto diminuíu en máis de unha unidade
                        //Xa que se puideron anular outros termos
                        while((i>0) && (*(resto->coeficientes + i) == 0.0))
                        {
                            i--;
                        }

                        resto->gradoPol = i; //E axustamos segundo esta correción
                    }
                    //Asignamos ao resto o seu grado orixinal (o do dividendo)
                    //Para realizar a correción do grado
                    //De forma que se eliminen os coeficientes redundantes
                    //Axustándose así ao seu grado real
                    resto->gradoPol = dividendo->gradoPol;

                    if(axustarGrado(resto))
                    {
                        printf("A correción automática do grado do resto fallou!\n");
                        printf("Non obstante, o cociente proporcionado é correcto!\n");
                        free(resto->coeficientes);
                        resto->coeficientes = NULL;

                        free(resto);
                        resto = NULL;
                    }
                }
                else
                {
                    printf("Non se puido facer a reserva de memoria para os coeficientes!\n");

                    free(resto);
                    resto = NULL;
                }
            }
            else
            {
                printf("Non se puido facer a reserva de memoria para o polinomio!\n");
            }
        }

        else
        {
            printf("Non se puido facer a reserva de memoria para os coeficientes!\n");

            free((*cociente));
            (*cociente) = NULL;
        }
    }
    else
    {
        printf("Non se puido facer a reserva de memoria para o polinomio!\n");
    }
    
    return resto;
}