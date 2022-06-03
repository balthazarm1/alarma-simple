#include <unity.h>
#include <timer_systick.h>
#include <pin_gpio.h>
//^^^^ incluyo header creado
#include <stm32f1xx.h>
//creo puerto falso.. necesito libreria de stm32 
static GPIO_TypeDef miPuerto;


//otra equivalencia es #define MI_PIN 13 pero esto lo haria el procesador
enum {MI_PIN = 13}; //defino constante llamada MI_PIN con valor 13 | esto lo hace el compiler


void setUp(void) //lo que hara al iniciar una prueba
{
    miPuerto = (GPIO_TypeDef){.CRH=0x44444444, . CRL=0x44444444};   //miPuerto es una estructura. lo que se hace aqui es copiar la estructura de la igualdad de la derecha hacia la izquierda | aqui ya se creo el puerto falso

}
void tearDown(void){}



int main(void)
{
    TimerSysTick_init();
    TimerSysTick_esperaMilisegundos(500); //delay necesario
    UNITY_BEGIN();

    UNITY_END();   
}