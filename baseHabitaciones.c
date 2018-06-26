#include "headers.h"

void inicializadorHabitaciones(){
    FILE *db;
    int h=0, p;
    HABITACION hab;
    if (fopen(pathHab, "rb")!=NULL)
    {
        db=fopen(pathHab, "a+b");
        for (p=0;p<pisosHab;p++)
        {
            for (h=0;h<habXPiso;h++)
            {
                hab.nroHabitacion=(p*100)+h+1;
                hab.ocupado=0;
                fwrite(&hab, sizeof(HABITACION), 1, db);
            }
        }
    }
    fclose(db);
}

void guardarHabitacion(HABITACION guardar, FILE *db){
    int i, hit=0;
    fseek(db,0,SEEK_SET);
    HABITACION aux;
    while (i<(pisosHab*habXPiso)&&hit==0){
        fread(&aux, sizeof(HABITACION), 1, db);
        if (guardar.nroHabitacion==aux.nroHabitacion){
            hit=1;
        }
        i++;
    }
    fseek(db, -sizeof(HABITACION), SEEK_CUR);
    fwrite(&guardar, sizeof(HABITACION), 1, db);
}

void cargarHab(){
    int nroHabCargar;
    HABITACION aux;
    PACIENTE pac;
    FILE *db;
    db=fopen(pathHab, "r+b");
    if (db==NULL){
        perror("Fallo al cargar la base de datos de Habitaciones.");
    }else{
        nroHabCargar=obtenerNumHab();
        aux=buscarHabXNum(nroHabCargar, db);
        if (aux.ocupado==0){
            pac=obtenerInternado();
            if(pac.eliminado==0){
                aux.dniPac=pac.dni;
                aux.ocupado=1;
                fseek(db, -sizeof(HABITACION), SEEK_CUR);
                fwrite(&aux, sizeof(HABITACION), 1, db);
                puts("Se ha internado al paciente exitosamente.");
            }
        }else{
            puts("La habitacion seleccionada NO esta libre.");
        }
    }
    fclose(db);
}

void listarHabitaciones(int ocupado){
    int i;
    HABITACION hab;
    FILE *db;
    db=fopen(pathHab, "rb");
    if (db==NULL){
        perror("No se pudo acceder a la base de datos de Habitaciones");
    }else{
        for (i=0; i<(pisosHab*habXPiso); i++){
            fread(&hab, sizeof(HABITACION), 1, db);
            switch (ocupado){
            case 0:
                if (hab.ocupado==0){
                imprimirHabitacion(hab);
                }
            break;
            case 1:
                if (hab.ocupado==1){
                imprimirHabitacion(hab);
                }
            break;
            case 2:
                imprimirHabitacion(hab);
            break;
            default:
                perror("Parametro fuera de rango en funcion listarHabitaciones.");
            break;
            }
        }
    }
    fclose(db);
}
