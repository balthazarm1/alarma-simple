#include <pin_gpio.h>
void Pin_init(Pin *self, GPIO_TypeDef *puerto, int numeroDePin)
{
    self -> puerto = puerto;        // equivalencia : (*self).puerto=puerto
    self -> pin = numeroDePin;
}
bool Pin_lee(Pin *self)
{
    return (bool)(self -> puerto -> IDR & (1 << ( self -> pin ))); //comparacion que devolvera un True o False
}
void Pin_escribe (Pin *self, bool valor)
{
    if(!valor) //si valor es nulo
        self -> puerto -> BRR = (1 << self -> numeroDePin); // equivale a self -> puerto -> BRR =0x00002000
    else //si valor es uno
        self -> puerto -> BSRR = (1 << self -> numeroDePin);
}