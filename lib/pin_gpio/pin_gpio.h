//creo encabezado
#ifndef PIN_GPIO_H
#define PIN_GPIO_H
#include <stm32f1xx.h> //para identificar GPIO_TypeDef
#include <stdbool.h>

typedef struct Pin { //creo la etiqueta Pin que devuelve el identificador(type def) Pin | se llama estructura anonima si nose pone nombre a la estructura
    int foo; //como la estructura no puede ser vacia se acreca un entero que no tiene funcion
} Pin;      //es importante poner el typedef, sino seria solo un struct.
/*equivalencia
    struct Pin {
        int foo;
    };
    typedef struct Pin Pin
*/

void Pin_init(Pin *self, GPIO_TypeDef *puerto, int pin); //sin haber echo nada en test_gpio.c el compilador dira que no existe la funcion, eso es por que falta crearlo en pin_gpio.c
            //    ^     toma puntero del pin
                            //^ toma puntero del puerto
                                                //^ numero de puerto

bool Pin_lee(Pin *self);
#endif