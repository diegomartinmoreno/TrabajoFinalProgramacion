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


void cargarHab(){
    int i=0, hit=0;
    HABITACION cargar, aux;
    FILE *db;
    db=fopen(pathHab, "r+b");
    if (db==NULL){
        perror("Fallo al cargar la base de datos de Habitaciones.");
    }else{
        cargar=obtenerHab();
        while (i<(habXPiso*pisosHab)&&hit==0){
            i++;
            fread(&aux, sizeof(HABITACION), 1, db);
            if (aux.nroHabitacion==cargar.nroHabitacion)
                hit=1;
        }
        fseek(db, -sizeof(HABITACION), SEEK_CUR);
        fwrite(&cargar, sizeof(HABITACION), 1, db);
        puts("Se ha internado al paciente exitosamente.");
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
