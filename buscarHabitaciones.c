#include "headers.h"

int obtenerNumHab(){
    int numHab, hit=0;
    do{
        puts("Ingrese numero de habitacion:");
        fflush(stdin);
        scanf("%i", &numHab);
        if ((numHab%100)>habXPiso){
            puts("\nEl numero de habitacion ingresado excede la cantidad de habitaciones del piso");
            printf("Intente un valor entre 1 y %i\n", habXPiso);
        } else{
            if(numHab>((pisosHab*100)+pisosHab)){
                puts("\nEl numero de habitacion ingresado excede el numero de pisos en la clinica");
                printf("Intente un valor entre 1 y %i\n", ((pisosHab*100)+pisosHab));
            }else{
                hit=1;
            }
        }
    } while(hit==0);
    return numHab;
}

HABITACION obtenerHab(){
    int numHab, op, hit=0;
    HABITACION hab;
    PACIENTE pac;
    numHab=obtenerNumHab();
    while (hit==0){
        puts("Ingrese una opcion:");
        puts("\t1.-Internar paciente conocido.");
        puts("\t2.-Internar un paciente nuevo.");
        fflush(stdin);
        scanf("%i", &op);
        switch (op){
            case 1:
                puts("Ingrese nombre o documento del paciente a internar:");
                pac=buscarPaciente();
                if (pac.eliminado==1)
                    puts("Ha intentado internar un usuario que no se encuentra en la base de datos.");
                else
                    hit=1;
            break;
            case 2:
                pac=guardarPaciente();
                hit=1;
            break;
            default:
                puts ("Ha ingresado una opcion incorrecta.");
            break;
        }
    }
    if(pac.eliminado==0){
        hab.nroHabitacion=numHab;
        hab.dniPac=pac.dni;
        hab.ocupado=1;
    }else{
        puts("El paciente que intenta internar se encuentra eliminado de la base de datos.");
    }
    return hab;
}

