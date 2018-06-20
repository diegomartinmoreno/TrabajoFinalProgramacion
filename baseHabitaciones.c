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
