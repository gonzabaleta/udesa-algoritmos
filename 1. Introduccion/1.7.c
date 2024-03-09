#include <stdio.h>
#include <stdlib.h>

typedef struct Persona
{
    int edad;
    char *nombre;
} Persona;

Persona *inicializarPersonas(int n)
{
    Persona *personas = (Persona *)calloc(n, sizeof(Persona));

    for (int i = 0; i < n; i++)
    {
        struct Persona persona;
        persona.edad = 10;
        persona.nombre = "Martin";
        personas[i] = persona;
    }

    return personas;
}

int main()
{
    Persona *personas = inicializarPersonas(10);

    for (int i = 0; i < 10; i++)
    {
        printf("%s: %d años\n", personas[i].nombre, personas[i].edad);
    }
}