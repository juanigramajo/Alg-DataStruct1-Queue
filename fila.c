#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int item;
const int indefinido=-9999;

struct nodo {
    item dato;
    struct nodo *siguiente;
};
typedef struct nodo *Nodo;

struct fila { 
    Nodo frente;
	Nodo final;
};
typedef struct fila Fila;



Fila filaVacia();
int esFilaVacia(Fila F);
Fila enfila(Fila F, item X);
Fila enfilaFrente(Fila F, item X);
item frente(Fila F);
Fila defila(Fila F);
void mostrar(Fila F);
Fila concatenar(Fila F, Fila F2);
Fila mezclar(Fila F, Fila F2, Fila FM);



int main(){

    Fila F, F2, FMezclada;
    item primerElemento;

    F = filaVacia();
    F2 = filaVacia();
    FMezclada = filaVacia();
    
    F = enfila(F, 1);
    F = enfila(F, 3);
    F = enfila(F, 5);
    F = enfila(F, 7);
    F = enfila(F, 9);

    F2 = enfila(F2, 2);
    F2 = enfila(F2, 4);
    F2 = enfila(F2, 6);
    F2 = enfila(F2, 8);
    F2 = enfila(F2, 10);


    printf("\n\n------Comienza el programa------\n");

    mostrar(F);
    mostrar(F2);

    primerElemento = frente(F);
    printf("\nEl primer elemento de la fila 1 es: [%d]\n", primerElemento);


    printf("\nAgrego un elemento...");
    F = enfila(F, 11);
    mostrar(F);
    
    
    printf("\nBorrando el primer elemento...");
    F = defila(F);
    mostrar(F);


    printf("\nAgrego un elemento al frente...");
    F = enfilaFrente(F, 77);
    mostrar(F);


    FMezclada = mezclar(F, F2, FMezclada);
    printf("\nMezclando ambas filas...");
    mostrar(FMezclada);
    
    return 0;
}


Fila filaVacia()
{
    Fila F;

    F.frente = NULL;
    F.final = NULL;

    return F;
}

int esFilaVacia(Fila F)
{
    if ((F.final == NULL) && (F.frente == NULL))
    {
        return(true);
    } else
    {
        return(false);
    }
}

Fila enfila(Fila F, item X)
{

    Nodo nuevo;

    nuevo = (Nodo)malloc(sizeof(struct nodo));

    nuevo->dato = X;
    nuevo->siguiente = NULL;

    if (esFilaVacia(F))
    {
        F.final = nuevo;
        F.frente = nuevo;
    } else
    {
        F.final->siguiente = nuevo;
        F.final = nuevo;
    }
    

    return F;
}

Fila enfilaFrente(Fila F, item X)
{

    Nodo nuevo;

    nuevo = (Nodo)malloc(sizeof(struct nodo));

    nuevo->dato = X;
    nuevo->siguiente = NULL;

    if (esFilaVacia(F))
    {
        F.final = nuevo;
        F.frente = nuevo;
    } else
    {
        nuevo->siguiente = F.frente;
        F.frente = nuevo;
    }
    

    return F;
}

item frente(Fila F)
{
    
    if (esFilaVacia(F))
    {
		return indefinido;
	} else
    {
		return F.frente->dato;
    }
}

Fila defila(Fila F)
{

    Nodo aux;
    aux = F.frente;

    if (!esFilaVacia(F))
    {

        if (F.frente == F.final)
        {

            F.final = NULL;
            F.frente = NULL;

        } else
        {

            F.frente = F.frente->siguiente;            
        }

    }
    
    free(aux);

    return F;
}

void mostrar(Fila F)
{
    printf("\nNodos en la fila: |--");

    while (F.frente != NULL)
    {
        printf("%d--", F.frente->dato);
        F.frente = F.frente->siguiente;
    }

    printf("|\n\n");
}

Fila concatenar(Fila FConcatenada, Fila F1)
{

    if (esFilaVacia(F1))
    {
        return FConcatenada;

    } else
    {
        return concatenar(enfila(FConcatenada, frente(F1)), defila(F1));
    }

}

Fila mezclar(Fila F1, Fila F2, Fila FMezclada)
{

    if (esFilaVacia(F1) && esFilaVacia(F2))
    {
        return F1;
    } else if (!esFilaVacia(F1) && esFilaVacia(F2))
    {
        FMezclada = concatenar(FMezclada, F1);
        return FMezclada;
    } else if (esFilaVacia(F1) && !esFilaVacia(F2))
    {
        FMezclada = concatenar(FMezclada, F2);
        return FMezclada;
    } else if (frente(F1) > frente(F2))
    {
        FMezclada = enfila(FMezclada, frente(F2));
        return mezclar(F1, defila(F2), FMezclada);
    } else
    {
        return mezclar(defila(F1), F2, FMezclada);
    }
}