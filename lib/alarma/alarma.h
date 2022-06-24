#ifndef ALARMA_H
#define ALARMA_H
#include <stdbool.h>
#include "biestado.h"

typedef struct Alarma Alarma;

typedef enum{
    DETECCION_Z1,FIN_TEMP,ARMAR,DESARMAR
} EventosAlarma;


typedef void (*EstadoAlarma)(Alarma *self, EventosAlarma evento);

void Alarma_estadoDesarmada(Alarma *self, EventosAlarma evento);
void Alarma_estadoTempArmado(Alarma *self, EventosAlarma evento);
void Alarma_estadoArmada(Alarma *self, EventosAlarma evento);
void Alarma_estadoTempDisparo(Alarma *self, EventosAlarma evento);
void Alarma_estadoDisparada(Alarma *self, EventosAlarma evento);

//typedef void (*Biestado)(bool indicacion); //indicar es un puntero que toma un valor bool (argumento true or false)

struct Alarma   //estados de la MEF guardados en memoria
{
    EstadoAlarma estado;
    //se encargar de hacer los printf 
    Biestado indicarActividadZ1;
    Biestado indicarArmado;
    Biestado indicarAlerta; //si es true suena la alarma
    Biestado indicarTemporizacion;
};

void Alarma_init(Alarma *self,  //defino constructor | inicilizador
                 EstadoAlarma estadoInicial,
                 Biestado indicarActividadZ1,
                 Biestado indicarArmado,
                 Biestado indicarAlerta,
                 Biestado indicarTemporizacion)
{
    printf("Inicializando...\n");
    self->estado = estadoInicial;
    self->indicarActividadZ1 = indicarActividadZ1;
    self->indicarArmado = indicarArmado;
    self->indicarAlerta = indicarAlerta;
    self->indicarTemporizacion = indicarTemporizacion;
}

void Alarma_transicionEstado(Alarma *self,EstadoAlarma nuevoEstado) //recibe estado
{
    self->estado = nuevoEstado;
}

void Alarma_procesaEvento(Alarma *self, EventosAlarma evento) //recibe evento
{
    self->estado(self,evento);
}

//metodos por estados

void Alarma_estadoDesarmada(Alarma *self, EventosAlarma evento)
{
    switch (evento)
    {
    case DETECCION_Z1:
        self->indicarActividadZ1(true);
        break;
    case ARMAR:
        self->indicarTemporizacion(true);
        Alarma_transicionEstado(self,Alarma_estadoTempArmado);
        break;
    default:
        printf("...ignorado...\n");
        break;
    }
}
void Alarma_estadoTempArmado(Alarma *self, EventosAlarma evento)
{
    switch (evento)
    {
    case DETECCION_Z1:
        self->indicarActividadZ1(true);
        break;
    case DESARMAR:
        self->indicarArmado(false);
        Alarma_transicionEstado(self,Alarma_estadoDesarmada);
        break;
    case FIN_TEMP:
        self->indicarArmado(true);
        Alarma_transicionEstado(self,Alarma_estadoArmada);
        break;
    default:
        printf("...ignorado...\n");
        break;
    }

}
void Alarma_estadoArmada(Alarma *self, EventosAlarma evento)
{
    switch (evento)
    {
    case DETECCION_Z1:
        self->indicarTemporizacion(true);
        Alarma_transicionEstado(self,Alarma_estadoTempDisparo);
        break;
    case DESARMAR:
        self->indicarArmado(false);
        Alarma_transicionEstado(self,Alarma_estadoDesarmada);
        break;
    case FIN_TEMP:
        self->indicarAlerta(true);
        Alarma_transicionEstado(self,Alarma_estadoDisparada);
        break;
    default:
        printf("...ignorado...\n");
        break;
    }

}
void Alarma_estadoTempDisparo(Alarma *self, EventosAlarma evento)
{
    switch (evento)
    {
    case DETECCION_Z1:
        self->indicarActividadZ1(true);
        break;
    case DESARMAR:
        self->indicarArmado(false);
        Alarma_transicionEstado(self,Alarma_estadoDesarmada);
        break;
    case FIN_TEMP:
        self->indicarAlerta(true);
        Alarma_transicionEstado(self,Alarma_estadoDisparada);
        break;
    default:
        printf("...ignorado...\n");
        break;
    }

}
void Alarma_estadoDisparada(Alarma *self, EventosAlarma evento)
{
    switch (evento)
    {
    case DETECCION_Z1:
        self->indicarAlerta(true);
        break;
    case DESARMAR:
        self->indicarArmado(false);
        Alarma_transicionEstado(self,Alarma_estadoDesarmada);
        break;
    case FIN_TEMP:
        self->indicarAlerta(false);
        Alarma_transicionEstado(self,Alarma_estadoArmada);
        break;
    default:
        printf("...ignorado...\n");
        break;
    }
}

// fin clase Alarma

#endif