#ifndef BIESTADO_H
#define BIESTADO_H

typedef struct Biestado Biestado; //defino objeto "Biestado"
typedef struct Biestado_VT; //virtualtable- tabla de punteros
{
    void (* const si)(Biestado *self);
        //^puntero^ a funcion
    void (* const no)(Biestado *self);

}Biestado_VT;

struct Biestado{
    const Biestado_VT * vptr; //virtualpointer

};

inline static void Biestado_si (Biestado *self)
//^introduce su contenido si se llama luego esta funcion
{
    *self -> vptr -> si(self);
};
inline static void Biestado_no (Biestado *self)
{
    *self -> vptr -> no(self);
};

#endif