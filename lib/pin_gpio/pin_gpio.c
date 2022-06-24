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