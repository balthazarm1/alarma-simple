//creo que esta bien esto | pero no se si deberia estar en la carpeta src
#include <main.h>
#include <stdbool.h>
#include "alarma.h"
#include "biestado.h"


//clase Indicador : Biestado
typedef struct Indicador Indicador
{
    Biestado super;
    const char *etiqueta;
    
}Indicador;

void Indicador_si (Indicador *self)
{
    printf ("Activar [%s]\n", self -> etiqueta);
}

void Indicador_no (Indicador *self)
{
    printf ("Desactivar [%s]\n", self -> etiqueta);
}

void Indicador_init (Indicador *self, const char *etiqueta)
{
    static const Biestado_VT vt ={
        .si = Indicador_si,
        .no = Indicador_no
    };
    ((biestado *) self)-> vptr = &vt;  //self es una direccion de memoria pero tratara como puntero a biestado
    self -> etiqueta = etiqueta;
}
//fin Indicador

static void ind_actividadZ1(bool indicacion)
{
    if(indicacion)
        printf("Z1!\n");
}
static void ind_armado(bool indicacion)
{
    if (indicacion)
        printf("Armada\n");
    else
        printf("Desarmando...\n");
}
static void ind_alerta(bool indicacion)
{
    if (indicacion)
        printf("Disparada!!\n");
    else
        printf("Deja de sonar...\n");
}
static void ind_temporizacion(bool indicacion)
{
    if(indicacion)
        printf("Temporizar\n");
}

static void inicializaAlarma (Alarma *alarma)
{
    static Indicador indicarActividadZ1;
    static Indicador indicarArmado;
    static Indicador indicarAlerta; //si es true suena la alarma
    static Indicador indicarTemporizacion;

    Indicador_init (&indicarActividadZ1, "Z1");
    Indicador_init (&indicarArmado, "Armado");
    Indicador_init (&indicarAlerta, "Alerta"); //si es true suena la alarma
    Indicador_init (&indicarTemporizacion, "Temporizacion");


    Alarma_init(&alarma,Alarma_estadoDesarmada,
                indicarActividadZ1,
                indicarArmado,
                indicarAlerta,
                indicarTemporizacion);
}

int main()
{
    Alarma alarma;
    
    
    
    Alarma_procesaEvento(&alarma,DETECCION_Z1);
    
    Alarma_procesaEvento(&alarma,ARMAR);
    
    Alarma_procesaEvento(&alarma,DETECCION_Z1);
    
    Alarma_procesaEvento(&alarma,FIN_TEMP);
    
    Alarma_procesaEvento(&alarma,DETECCION_Z1);
    
    Alarma_procesaEvento(&alarma,FIN_TEMP);
    
    Alarma_procesaEvento(&alarma,FIN_TEMP);
    
    Alarma_procesaEvento(&alarma,DETECCION_Z1);
    
    Alarma_procesaEvento(&alarma,DESARMAR);
    

    return 0;
}
