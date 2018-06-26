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

void actualizarBase(){
    int i;
    time_t origen;
    struct tm *fecha;
    HABITACION hab;
    time(&origen);
    fecha=localtime(&origen);
    FILE *db;
    db=fopen(pathHab, "r+b");
    for (i=0; i<(pisosHab*habXPiso); i++){
        fread(&hab, sizeof(HABITACION), 1, db);
        if (hab.ocupado==1){
            if (fecha->tm_mday>hab.alta.dia){
                if (fecha->tm_mon>=hab.alta.mes){
                    if ((fecha->tm_year+1900)>=hab.alta.ano){
                        hab.ocupado=0;
                        guardarHabitacion(hab, db);
                    }
                }
            }
        }
    }
}

void guardarHabitacion(HABITACION guardar, FILE *db){
    time_t origen;
    struct tm *fecha;
    time(&origen);
    fecha=localtime(&origen);
    guardar.ingreso.ano=fecha->tm_year+1900;
    guardar.ingreso.mes=fecha->tm_mon+1;
    guardar.ingreso.dia=fecha->tm_mday;
    puts("Ingrese fecha prevista de alta:");
    do{
        printf("Dia: \n");
        fflush(stdin);
        scanf("%i", &guardar.alta.dia);
    } while (guardar.alta.dia<1||guardar.alta.dia>31);
    do{
        printf("Mes: \n");
        fflush(stdin);
        scanf("%i", &guardar.alta.mes);
    } while (guardar.alta.mes<1||guardar.alta.mes>12);
    do{
        printf("Ano: \n");
        fflush(stdin);
        scanf("%i", &guardar.alta.ano);
    } while (guardar.alta.ano<(fecha->tm_year+1900));
    int i=0, hit=0;
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
                guardarHabitacion(aux, db);
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
