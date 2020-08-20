#include <stdio.h>
#include <stdlib.h>

#define N 5

typedef void (*menu_t)();

typedef struct{
    char *  nombre;
    char * apellidos;
    int edad;
    char * telefono;
} paciente;

typedef struct{
    int num;
    paciente * ocupada_por;
} cama;


void incorporarPaciente();
void getCama();
void altaPaciente();
void listPacientes();
void camasDisponibles();

cama * camas_hospital; 
cama * final;
int cantidad = 0;
int cantidad_ocupadas = 0;

int main(int argc, const char *argv[]){

    cama * aux;
 

    printf("Camas iniciales : ");
    scanf("%d", &cantidad);
    camas_hospital = (cama *) malloc(sizeof(cama) * cantidad);
    
    final = camas_hospital + cantidad;

    int index_last = 0;
    
    for (aux = camas_hospital; aux < final; ++aux) 
    {
        index_last++;
        aux->num = index_last;
        aux->ocupada_por = NULL;
        
    }

    int opcion = -1;

    menu_t * opciones = (menu_t *) malloc(N*sizeof(menu_t));

    *opciones = incorporarPaciente;
    *(opciones+1) = getCama;
    *(opciones+2) = altaPaciente;
    *(opciones+3) = listPacientes;
    *(opciones+4) = camasDisponibles;

    while (opcion != 0) 
    {
        printf("1-Incorporar Paciente\n2-Obtener cama dado un paciente 2\n 3-Dar de alta a paciente \n4-Listar a los pacientes\n5- Camas Disponibles \n 0-Salir\n");
        
        printf("Selecciona tu opción: ");
        scanf("%d", &opcion);
        
        if (opcion > 0 && opcion <= N) 
        {
            (*(opciones[opcion-1]))();
        }
    }
    
    free(opciones);
    
    for (aux = camas_hospital; aux < final; ++aux) 
    {
        free(aux->ocupada_por->nombre); 
        free(aux->ocupada_por->apellidos);
        free(aux->ocupada_por->telefono); 
        free(aux->ocupada_por);
    }

    free(camas_hospital);
    return 0;
}

void incorporarPaciente()
{
    if(cantidad_ocupadas == cantidad)
    {
            camas_hospital = (cama *) realloc(camas_hospital, sizeof(cama) * (cantidad + 5));
            
            final = camas_hospital + cantidad + 5;
    }
    
    for (cama * aux = camas_hospital; aux < final; ++aux) 
    {
        if(aux->ocupada_por == NULL)
            {
                aux->ocupada_por = (paciente * ) malloc(sizeof(paciente));

                aux->ocupada_por->nombre = (char * ) malloc(sizeof(char)*25);
                printf("Nombre del paciente: ");
                scanf("%s", aux->ocupada_por->nombre);
                
                aux->ocupada_por->apellidos = (char * ) malloc(sizeof(char)*25);
                printf("Apellido del paciente: ");
                scanf("%s", aux->ocupada_por->apellidos);

                printf("Edad: ");
                scanf("%d", &aux->ocupada_por->edad);

                aux->ocupada_por->telefono = (char * ) malloc(sizeof(char)*25);
                printf("Telefono: ");
                scanf("%s", aux->ocupada_por->telefono);

                cantidad_ocupadas++;
                return;
            }
        else{
            printf("Cama ocupada: %d ", aux->num);
        }
         
    }
}

void getCama()
{
    int num_cam;
    printf("Ingresar el número de cama: ");
    scanf("%d", &num_cam);
    
    cama * buscado = camas_hospital + num_cam;
    printf("Número de cama: %d \n", buscado->num);
    printf("Nombre del paciente: %s \n", buscado->ocupada_por->nombre);
    printf("Apellido del paciente: %s \n", buscado->ocupada_por->apellidos);
    printf("Edad: %d \n", buscado->ocupada_por->edad);
    printf("Telefono: %s \n", buscado->ocupada_por->telefono);
    
}

void altaPaciente()
{
    int num_cam;
    printf("Ingresar el número de cama: ");
    scanf("%d", &num_cam);
    
    cama * buscado= camas_hospital + num_cam - 1;
    printf("Nombre del paciente: %d \n", buscado->num);
    printf("Nombre del paciente: %s \n", buscado->ocupada_por->nombre);
    printf("Apellido del paciente: %s \n", buscado->ocupada_por->apellidos);
    printf("Edad: %d \n", buscado->ocupada_por->edad);
    printf("Telefono: %s \n", buscado->ocupada_por->telefono);
    cantidad_ocupadas--;

    free(buscado->ocupada_por->nombre);
    free(buscado->ocupada_por->apellidos);
    free(buscado->ocupada_por->telefono);
    free(buscado->ocupada_por);
    buscado->ocupada_por = NULL;
       
}

void listPacientes()
{
    printf("\n\n--- Listado de pacientes ---\n\n");
    for (cama * aux = camas_hospital; aux < final; ++aux) 
    {
        if(aux->ocupada_por != NULL){
            printf("cama -- %4d \t %25s \t %25s \t %25s \t %4d \n",
               aux->num,
               aux->ocupada_por->nombre, 
               aux->ocupada_por->apellidos,
               aux->ocupada_por->telefono, 
               aux->ocupada_por->edad);
        }
        
    }
}

void camasDisponibles()
{
    printf("\n\nCantidad de camas disponibles %4d \n\n", cantidad-cantidad_ocupadas);
    printf("\n\nCantidad de camas ocupadas %4d \n\n", cantidad_ocupadas);
}

