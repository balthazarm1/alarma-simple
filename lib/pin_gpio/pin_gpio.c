#include <pin_gpio.h>
void Pin_init(Pin *self, GPIO_TypeDef *puerto, int pin)
{
    self -> puerto = puerto;        // equivalencia : (*self).puerto=puerto
    self -> pin = pin;
}
bool Pin_lee(Pin *self)
{
    return self -> puerto -> IDR & (1 << ( self -> pin )); //comparacion que devolvera un True o False
}