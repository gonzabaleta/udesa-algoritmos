#include <stdio.h>

typedef struct Persona
{
    char *nombre;
    char *apellido;
    char *domicilio;
    int edad;
} Persona;

char *masGrande(Persona **personas, int len)
{
    Persona *max = personas[0];
    for (int i = 0; i < len; i++)
    {
        if (personas[i]->edad > max->edad)
        {
            max = personas[i];
        }
    }

    return max->nombre;
}

int main()
{
    Persona javier;
    javier.nombre = "Javier";
    javier.edad = 21;

    Persona gustavo;
    gustavo.nombre = "Gustavo";
    gustavo.edad = 35;

    Persona susana;
    susana.nombre = "Susana";
    susana.edad = 60;

    Persona alex;
    alex.nombre = "Alex";
    alex.edad = 161;

    Persona *personas[4] = {&javier, &gustavo, &susana, &alex};

    printf("%s\n", masGrande(personas, 4));
}