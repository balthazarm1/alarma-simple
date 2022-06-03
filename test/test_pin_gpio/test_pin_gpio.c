#include <unity.h>
#include <timer_systick.h>
#include <stdbool.h>
#include <pin_gpio.h>
//^^^^ incluyo header creado
#include <stm32f1xx.h>
//creo puerto falso.. necesito libreria de stm32 
static GPIO_TypeDef miPuerto;

#define MI_PIN 13 // esto lo haria el procesador
// enum {MI_PIN = 13}; //defino constante llamada MI_PIN con valor 13 | esto lo hace el compiler

static  Pin miPin; //utilizo de la libreria pin_gpio.h para definir pines. debo definir el identificador Pin


void setUp(void) //lo que hara al iniciar una prueba
{
    miPuerto = (GPIO_TypeDef){.CRH=0x44444444, . CRL=0x44444444};   //miPuerto es una estructura. lo que se hace aqui es copiar la estructura de la igualdad de la derecha hacia la izquierda | aqui ya se creo el puerto falso

}
void tearDown(void){}

//creo prueba
void pin_debePermitirLeerEstado(void) // es imporante tomar en cuenta que sea static o global. que sea static me hara tomar en cuenta si la utilizo o no (por que es local). no me avisara si llegase a ser global
{
    Pin miPin;
    Pin_init(&miPin, &miPuerto, MI_PIN); //se necesitara de esta funcion en el header que crearemos para tomar en cuenta esos argumentos que necesitamos
            //^ toma direcciones
    const bool estado= Pin_lee(&miPin); //para definir bool (logica de bool) necesito la libreria stdbool | ademas se usara de una funcion Pin_lee
}

int main(void)
{
    TimerSysTick_init();
    TimerSysTick_esperaMilisegundos(500); //delay necesario
    UNITY_BEGIN();
    RUN_TEST(pin_debePermitirLeerEstado);
    UNITY_END();   
}