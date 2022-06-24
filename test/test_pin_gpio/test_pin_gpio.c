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
void pin_debePermitirLeerEstado_0(void) // es imporante tomar en cuenta que sea static o global. que sea static me hara tomar en cuenta si la utilizo o no (por que es local). no me avisara si llegase a ser global
{
    Pin miPin;
    Pin_init(&miPin, &miPuerto, MI_PIN); //se necesitara de esta funcion en el header que crearemos para tomar en cuenta esos argumentos que necesitamos
            //^ toma direcciones
    const bool estado= Pin_lee(&miPin); //para definir bool (logica de bool) necesito la libreria stdbool | ademas se usara de una funcion Pin_lee que devolvera un booleano | const permite que sea de lectura nada mas
    TEST_ASSERT_FALSE(estado); //se agrega el FALSE para que espere una respuesta falsa
    
}
void pin_debePermitirLeerEstado_1(void)
{
    Pin miPin;
    Pin_init(&miPin, &miPuerto, MI_PIN);
    miPuerto.IDR = 1 << MI_PIN;
    const bool estado= Pin_lee(&miPin); 
    TEST_ASSERT_TRUE(estado);
}
void pin_debePermitirPonerSalidaEnCero(void) 
{
    Pin miPin; //dicha variable se la define varias veces => esta sera un posible refactory
    Pin_init(&miPin, &miPuerto, MI_PIN);
    Pin_escribe(&miPin, 0);
    const uint32_t reset = miPuerto.BRR | (miPuerto.BSRR >> 16); //creo resultado RESET
//  ^ constante                         ^ or  
    const uint32_t set = miPuerto.BSRR & ((1UL << 16)- 1UL)
    enum{ RESET_ESPERADO = (1UL << MI_PIN), SET_ESPERADO = 0 }; //creo resultado RESET_ESPERADO
//                           ^Unsigned Long
    TEST_ASSERT_EQUAL_HEX32(reset, RESET_ESPERADO);
    TEST_ASSERT_EQUAL_HEX32(set, SET_ESPERADO);
}
void pin_debePermitirPonerSalidaEnUno(void) 
{
    Pin miPin; 
    Pin_init(&miPin, &miPuerto, MI_PIN);
    Pin_escribe(&miPin, 1);
    const uint32_t reset = miPuerto.BRR | (miPuerto.BSRR >> 16); //creo resultado RESET
//  ^ constante                         ^ or  
    const uint32_t set = miPuerto.BSRR & ((1UL << 16)- 1UL) //para volver mas rigurosa la funcion
    enum{ RESET_ESPERADO = 0, SET_ESPERADO (1UL << MI_PIN)}; //creo resultado RESET_ESPERADO
//                           ^Unsigned Long
    TEST_ASSERT_EQUAL_HEX32(reset, RESET_ESPERADO);
    TEST_ASSERT_EQUAL_HEX32(set, SET_ESPERADO);
}

int main(void)
{
    TimerSysTick_init();
    TimerSysTick_esperaMilisegundos(500); //delay necesario
    UNITY_BEGIN();
    RUN_TEST(pin_debePermitirLeerEstado_0);
    RUN_TEST(pin_debePermitirLeerEstado_1);
    RUN_TEST(pin_debePermitirPonerSalidaEnCero);
    RUN_TEST(pin_debePermitirPonerSalidaEnUno);
    UNITY_END();   
}