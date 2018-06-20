#include "headers.h"


void inicializadorHabitaciones(){
    FILE *db;
    int h=0, p;
    HABITACION hab;
    if (fopen(pathHab, "rb")!=NULL)
    {
        db=fopen(pathHab, "a+b");
        for (p=0;p<5;p++)
        {
            for (h=0;h<10;h++)
            {
                hab.nroHabitacion=(p*100)+h;
                hab.ocupado=0;
                fwrite(&hab, sizeof(HABITACION), 1, db);
            }
        }
    }
}


