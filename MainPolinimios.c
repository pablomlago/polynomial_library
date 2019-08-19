#include <stdio.h>
#include <stdlib.h>
#include "polinomios.h"

#define MAX_POLINOMIOS 5

int main() 
{
    
    //Vector estático de polinomios para facilitar o seu manexo
    Pol *vecPolinomios[MAX_POLINOMIOS];
    Pol* temp = NULL;
    //Vector para almacenar o cociente 
    Pol* cociente = NULL;
    
    //Variables contador
    int i = 0, j = 0;
    //Variables empregadas na avaliación do valor do polinomio nun punto
    float punto = 0.0, resultado = 0.0;
    //Variables para realizar a interacción co usuario
    int opcion = 0, confirmar = 0;
    
    //Mantemos en todo momento a conta dos polinomios gardados en memoria
    int polinomiosAlmacenados = 0;
    
    //Inicializamos os elementos do vector de polinomios a NULL
    for(i = 0; i < MAX_POLINOMIOS; i++)
    {
        vecPolinomios[i] = NULL;
    }
    
    do
    {
        printf("\nOpcións:\n"
                "(0)Introducir polinomio\n"
                "(1)Mostrar polinomio\n"
                "(2)Eliminar polinomio\n"
                "(3)Avaliar polinomio nun punto\n"
                "(4)Derivar polinomio\n"
                "(5)Sumar polinomios\n"
                "(6)Multiplicar polinomios\n"
                "(7)Dividir polinomios\n"
                "(8)Sair\n"
                "Que desexas facer? ");
        scanf("%d", &opcion);
        printf("\n");
        switch(opcion)
        {
            case 0:
                //Hai memoria dispoñible para gardar un novo polinomio en memoria
                if(polinomiosAlmacenados < MAX_POLINOMIOS)
                {
                    temp = lerPolinomio();
                    //Comprobamos que a lectura se realizou con éxito
                    if(temp != NULL)
                    {
                        vecPolinomios[polinomiosAlmacenados] = temp;
                        temp = NULL;
                    }
                    else
                    {
                        printf("A operación non se completou con éxito!\n");
                    }
                }
                else
                {
                    printf("Non hai espazo para almacenar máis polinomios!\n");
                }
                break;
            case 1: 
                //Comprobamos se hai algún polinomio gardado en memoria
                if(polinomiosAlmacenados > 0)
                {
                    //Permitimos ao usuario mostrar un polinomio concreto
                    printf("Que polinomio queres ver (0-%d)? (Noutro caso mostraránse todos): ", polinomiosAlmacenados-1);
                    scanf("%d", &opcion);
                    if((opcion >= 0) && (opcion < polinomiosAlmacenados))
                    {
                        escribirPolinomio(vecPolinomios[opcion]);
                    }
                    //Mostramos todos os polinomios gardados en memoria se o usuario non introduciu un válido
                    else
                    {
                        for(i = 0; i < polinomiosAlmacenados; i++)
                        {
                            escribirPolinomio(vecPolinomios[i]);
                        }
                    }
                    //Evitamos entrar noutras ramas do switch
                    //Xa que usamos opcion dentro desta rama para elixir un polinomio
                    opcion = 1; 
                }
                else
                {
                    printf("Non hai ningún polinomio gardado!\n");
                }
                break;
            case 2: 
                //Permitimos xestionar ao usuario os polinomios gardados en memoria
                if(polinomiosAlmacenados > 0)
                {
                    printf("Que polinomio queres eliminar(0-%d)? (Noutro caso borraranse todos): ", polinomiosAlmacenados - 1);
                    scanf("%d", &opcion);
                    //Pódese borrar un polinomio concreto
                    if((opcion >= 0) && (opcion < polinomiosAlmacenados))
                    {
                        printf("O polinomio a borrar é: ");
                        escribirPolinomio(vecPolinomios[opcion]);
                        //Pedimos confirmación antes de borrar un polinomio
                        printf("Estás seguro de querer eliminalo? (0: NON, 1: SI): ");
                        scanf("%d", &confirmar);
                        if(confirmar)
                        {
                            free(vecPolinomios[opcion]->coeficientes);
                            vecPolinomios[opcion]->coeficientes = NULL;
                            
                            free(vecPolinomios[opcion]);
                            vecPolinomios[opcion] = NULL;
                        }
                    }
                    //Ou borrar todos os polinomios gardados
                    else
                    {
                        for(i = 0; i < polinomiosAlmacenados; i++)
                        {
                            free(vecPolinomios[i]->coeficientes);
                            vecPolinomios[i]->coeficientes = NULL;
                            
                            free(vecPolinomios[i]);
                            vecPolinomios[i] = NULL;
                        }
                    }
                    //Evitamos entrar noutras ramas do switch
                    //Xa que usamos opcion dentro desta rama para elixir un polinomio
                    opcion = 2;
                }
                else
                {
                    printf("Non hai ningún polinomio gardado!\n");
                }
                break;
            case 3: 
                //Comprobamos que hai algún polinomio gardado
                if(polinomiosAlmacenados > 0)
                {
                    do 
                    {
                        confirmar = 0;
                        printf("Elixe o polinomio a avaliar nun punto (0-%d): ", polinomiosAlmacenados - 1);
                        scanf("%d", &opcion);
                        if((opcion >= 0) && (opcion < polinomiosAlmacenados))
                        {
                            printf("O polinomio elixido é o seguinte:\n");
                            escribirPolinomio(vecPolinomios[opcion]);
                            printf("É este o que queres avaliar? (0:NON, 1:SI): ");
                            scanf("%d", &confirmar);
                        }
                        else
                        {
                            printf("Elixe un polinomio válido!\n");
                        }
                    } while(!confirmar); //Forzamos ao usuario a introducir un polinomio válido
                    
                    //Pedimos ao usuario o punto no que avaliar o polinomio escollido
                    printf("En que punto o queres avaliar: ");
                    scanf("%f", &punto);
                    //Realizamos a avaliación e mostramos o resultado
                    resultado = avaliarPolinomio(vecPolinomios[opcion], punto);
                    printf("P(%.03f)= %.03f\n", punto, resultado);
                    
                    //Evitamos entrar noutras ramas do switch
                    //Xa que usamos opcion dentro desta rama para elixir un polinomio
                    opcion = 3;
                }
                else
                {
                    printf("Non hai ningún polinomio gardado!\n");
                }
                break;
            case 4: 
                //Comprobamos que hai polinomios gardados en memoria
                if(polinomiosAlmacenados > 0)
                {
                    do 
                    {
                        confirmar = 0;
                        printf("Elixe un polinomio que avaliar (0-%d): ", polinomiosAlmacenados - 1);
                        scanf("%d", &opcion);
                        if((opcion >= 0) && (opcion < polinomiosAlmacenados))
                        {
                            printf("O polinomio elixido é o seguinte: \n");
                            escribirPolinomio(vecPolinomios[opcion]);
                            printf("É este o que queres derivar? (0:NON, 1:SI): ");
                            scanf("%d", &confirmar);
                        }
                        else
                        {
                            printf("Elixe un polinomio válido!\n");
                        }
                    } while(!confirmar); //Forzamos ao usuario a escoller un polinomio válido
                    
                    
                    temp = derivarPolinomio(vecPolinomios[opcion]);
                    
                    if(temp != NULL)
                    {
                        printf("O polinomio derivado é:\n");
                        escribirPolinomio(temp);
                        if(polinomiosAlmacenados < MAX_POLINOMIOS)
                        {
                            confirmar = 0;
                            printf("Desexas gardar este polinomio en memoria? (0:NON, 1:SI): ");
                            scanf("%d", &confirmar);
                            if(confirmar)
                            {
                                vecPolinomios[polinomiosAlmacenados] = temp;
                                temp = NULL;
                            }
                        }
                        
                        //Podería ser nulo se se asignou o punteiro a un polinomio dos xa asignados en memoria
                        if(temp != NULL)
                        {
                            free(temp->coeficientes);
                            temp->coeficientes = NULL;
                            
                            free(temp);
                            temp = NULL;

                        }
                    }
                    else
                    {
                        printf("A operación non se completou con éxito!\n");
                    }
                    
                    //Evitamos entrar noutras ramas do switch
                    //Xa que usamos opcion dentro desta rama para elixir un polinomio
                    opcion = 4;
                }
                else
                {
                    printf("Non hai ningún polinomio gardado!\n");
                }
                break;
            case 5: 
                //Comprobamos que hai algún polinomio gardado
                if(polinomiosAlmacenados > 0)
                {
                    printf("Elixe os polinomios a sumar: \n");
                    for(i = 0; i < 2; i++)
                    {
                        do 
                        {
                            confirmar = 0;
                            printf("Elixe os sumandos (0-%d): ", polinomiosAlmacenados - 1);
                            scanf("%d", &opcion);
                            if((opcion >= 0) && (opcion < polinomiosAlmacenados))
                            {
                                printf("O polinomio elixido é o seguinte: \n");
                                escribirPolinomio(vecPolinomios[opcion]);
                                printf("É este o que queres sumar? (0:NON, 1:SI): ");
                                scanf("%d", &confirmar);
                            }
                            else
                            {
                                printf("Elixe un polinomio válido!\n");
                            }
                        } while(!confirmar); //Forzamos que o usuario introduza un polinomio válido
                        
                        if(i == 0)
                        {
                            temp = vecPolinomios[opcion];
                        }
                    }
                    
                    //Realizamos a suma de polinomios e gardamos o resultado nun punteiro temporal
                    temp = sumarPolinomios(temp, vecPolinomios[opcion]);
                    
                    if(temp != NULL)
                    {
                        printf("O polinomio suma é:\n");
                        escribirPolinomio(temp);
                        if(polinomiosAlmacenados < MAX_POLINOMIOS)
                        {
                            confirmar = 0;
                            printf("Desexas gardar este polinomio en memoria? (0:NON, 1:SI): ");
                            scanf("%d", &confirmar);
                            if(confirmar)
                            {
                                vecPolinomios[polinomiosAlmacenados] = temp;
                                temp = NULL;
                            }
                        }
                        //Liberamos memoria do polinomio temporal
                        if(temp != NULL)
                        {
                            free(temp->coeficientes);
                            temp->coeficientes = NULL;
                            
                            free(temp);
                            temp = NULL;
                        }
                    }
                    else
                    {
                        printf("A operación non se pudo completar con éxito!\n");
                    }
                    
                    //Evitamos entrar noutras ramas do switch
                    //Xa que usamos opcion dentro desta rama para elixir un polinomio
                    opcion = 5;
                }
                else
                {
                    printf("Non hai ningún polinomio gardado!\n");
                }
                break;
            case 6:
                if(polinomiosAlmacenados > 0)
                {
                    printf("Elixe os polinomios a multiplicar: \n");
                    for(i = 0; i < 2; i++)
                    {
                        do 
                        {
                            confirmar = 0;
                            printf("Elixe os factores (0-%d): ", polinomiosAlmacenados - 1);
                            scanf("%d", &opcion);
                            if((opcion >= 0) && (opcion < polinomiosAlmacenados))
                            {
                                printf("O polinomio elixido é o seguinte: \n");
                                escribirPolinomio(vecPolinomios[opcion]);
                                printf("É este o que queres multiplicar? (0:NON, 1:SI): ");
                                scanf("%d", &confirmar);
                            }
                            else
                            {
                                printf("Elixe un polinomio válido!\n");
                            }
                        } while(!confirmar); //Forzamos que o usuario introduza un polinomio válido
                        
                        if(i == 0)
                        {
                            temp = vecPolinomios[opcion];
                        }
                    }
                    
                    //Gardamos o resultado da multiplicación nun punteiro temporalmentr
                    temp = multiplicarPolinomios(temp, vecPolinomios[opcion]);
                    
                    if(temp != NULL)
                    {
                        printf("O polinomio multiplicación é:\n");
                        escribirPolinomio(temp);
                        if(polinomiosAlmacenados < MAX_POLINOMIOS)
                        {
                            confirmar = 0;
                            printf("Desexas gardar este polinomio en memoria? (0:NON, 1:SI): ");
                            scanf("%d", &confirmar);
                            if(confirmar)
                            {
                                vecPolinomios[polinomiosAlmacenados] = temp;
                                temp = NULL;
                            }
                        }
                        //Liberamos a memoria do punteiro temporal
                        if(temp != NULL)
                        {
                            free(temp->coeficientes);
                            temp->coeficientes = NULL;
                            
                            free(temp);
                            temp = NULL;
                        }
                    }
                    else
                    {
                        printf("A operación non se pudo completar con éxito!\n");
                    }
                    
                    //Evitamos entrar noutras ramas do switch
                    //Xa que usamos opcion dentro desta rama para elixir un polinomio
                    opcion = 6;
                }
                else
                {
                    printf("Non hai ningún polinomio gardado!\n");
                }
                break;
            case 7:
                //Precisamos ter polinomios almacenados en memoria para operar con eles
                if(polinomiosAlmacenados > 0)
                {
                    printf("Elixe os polinomios a dividir: \n");
                    for(i = 0; i < 2; i++)
                    {
                        do 
                        {
                            confirmar = 0;
                            if(i == 0)
                            {
                                printf("Elixe o dividendo (0-%d): ", polinomiosAlmacenados - 1);
                            }
                            else
                            {
                                printf("Elixe o divisor (0-%d): ", polinomiosAlmacenados - 1);   
                            }
                            scanf("%d", &opcion);
                            if((opcion >= 0) && (opcion < polinomiosAlmacenados))
                            {
                                printf("O polinomio elixido é o seguinte: \n");
                                escribirPolinomio(vecPolinomios[opcion]);
                                printf("É este o que queres empregar? (0:NON, 1:SI): ");
                                scanf("%d", &confirmar);
                            }
                            else
                            {
                                printf("Elixe un polinomio válido!\n");
                            }
                        } while(!confirmar);

                        if(i == 0)
                        {
                            temp = vecPolinomios[opcion];
                        }
                    }
                    //Comprobamos que non dividimos entre 0
                    if((vecPolinomios[opcion]->gradoPol == 0) && (*(vecPolinomios[opcion]->coeficientes) == 0.0))
                    {
                        printf("Non se pode dividir entre 0!\n");
                    }
                    else
                    {
                        //E comprobamos que o grado do dividendo(temp) non é menor que o do divisor(vecPolinomios[opcion])
                        if(temp->gradoPol < vecPolinomios[opcion]->gradoPol)
                        {
                            printf("O grado do dividendo é menor que o do divisor!\n");
                        }
                        else
                        {
                            temp = dividirPolinomios(&cociente,temp,vecPolinomios[opcion]);

                            if(cociente != NULL)
                            {
                                printf("O polinomio cociente é: \n");
                                escribirPolinomio(cociente);
                                if(polinomiosAlmacenados < MAX_POLINOMIOS)
                                {
                                    printf("Queres gardar este polinomio en memoria? (0:NON, 1: SI): ");
                                    scanf("%d", &confirmar);
                                    if(confirmar)
                                    {
                                        vecPolinomios[polinomiosAlmacenados] = cociente;
                                        //Sumamos un xa que tamén se nos da a opción de gardar o resto
                                        polinomiosAlmacenados++;
                                        cociente = NULL;
                                    }
                                }
                                //Liberamos a memoria do punteiro temporal para gardar o cociente
                                if(cociente != NULL)
                                {
                                    free(cociente->coeficientes);
                                    cociente->coeficientes = NULL;
                                    
                                    free(cociente);
                                    cociente = NULL;
                                }
                                
                                if(temp != NULL)
                                {
                                    printf("O polinomio resto é: \n");
                                    escribirPolinomio(temp);
                                    //Se hai espazo permitimos ao usuario gardar o polinomio en memoria
                                    if(polinomiosAlmacenados < MAX_POLINOMIOS)
                                    {
                                        printf("Queres gardar este polinomio en memoria? (0:NON, 1: SI): ");
                                        scanf("%d", &confirmar);
                                        if(confirmar)
                                        {
                                            vecPolinomios[polinomiosAlmacenados] = temp;
                                            temp = NULL;
                                        }
                                    }
                                    
                                    if(temp != NULL)
                                    {
                                        free(temp->coeficientes);
                                        temp->coeficientes = NULL;
                                        
                                        free(temp);
                                        temp = NULL;
                                    }
                                }
                                else
                                {
                                    printf("Non se puido calcular o resto!\n");
                                }   
                            }
                            else
                            {
                                printf("Non se puido completar a operación con éxito!\n");
                            }
                        }
                    }
                    //Evitamos entrar noutras ramas do switch
                    //Xa que usamos opcion dentro desta rama para elixir un polinomio
                    opcion = 7;
                }
                else
                {
                    printf("Non hai ningún polinomio gardado!\n");
                }
                break;
            default:
                opcion = 8;
                break;
        }
        
        //Ordenamos os polinomios gardados en memoria colocando consecutivamente os non nulos
        //E obtemos o número de polinomios gardados
        polinomiosAlmacenados = 0;
        for(i = 0; i < MAX_POLINOMIOS; i++)
        {
            if(vecPolinomios[i] == NULL)
            {
                j = i;
                while((j < MAX_POLINOMIOS) && (vecPolinomios[j] == NULL))
                {
                    j++;
                }
                if(j != MAX_POLINOMIOS)
                {
                    polinomiosAlmacenados++;
                    temp = vecPolinomios[i];
                    vecPolinomios[i] = vecPolinomios[j];
                    vecPolinomios[j] = temp;
                    temp = NULL;
                }
            }
            else
            {
                polinomiosAlmacenados++;
            }
        }
        printf("Polinomios almacenados: %d\n", polinomiosAlmacenados);
    } while(opcion != 8); 
    
    for(i = 0; i < polinomiosAlmacenados; i++)
    {
        free(vecPolinomios[i]->coeficientes);
        vecPolinomios[i]->coeficientes = NULL;

        free(vecPolinomios[i]);
        vecPolinomios[i] = NULL;
    }
    
    return (EXIT_SUCCESS);
}

