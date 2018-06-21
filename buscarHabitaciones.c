#include "headers.h"

int obtenerNumHab(){
    int hit=0, numHab;

    do{
        puts("Ingrese numero de habitacion valido:");
        fflush(stdin);
        scanf("%i", &numHab);
        if ((numHab%100)>habXPiso||((numHab%100)<=0)){
            puts("\nEl numero de habitacion ingresado excede la cantidad de habitaciones del piso");
            printf("Intente un valor entre 1 y %i\n", habXPiso);
        } else{
            if(numHab>(((pisosHab-1)*100)+habXPiso)){
                puts("\nEl numero de habitacion ingresado excede el numero de pisos en la clinica");
                printf("Intente un valor entre 1 y %i\n", (((pisosHab-1)*100)+habXPiso));
            }else{
                hit=1;
            }
        }
    } while(hit==0);
    return numHab;
}

PACIENTE obtenerInternado(){
    PACIENTE pac;
    int hit=0, op;
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
    if(pac.eliminado==1){
        puts("El paciente que intenta internar se encuentra eliminado de la base de datos.");
    }
    return pac;
}

int comprobarYaInternado(int dni, FILE *db){ //Retorna 1 si el paciente ya fue internado
    fseek(db, 0, SEEK_SET);
    int i=0, hit=0;
    HABITACION aux;
    while (i<(habXPiso*pisosHab)&&hit==0){
        i++;
        fread(&aux, sizeof(HABITACION), 1, db);
        if (aux.dniPac==dni)
            hit=1;
    }
    return hit;
}

HABITACION buscarHabXPac(PACIENTE buscado, FILE *db){
    int i=0, hit=0;
    HABITACION aux;
    fseek(db, 0, SEEK_SET);
    while (i<(habXPiso*pisosHab)&&hit==0){
        i++;
        fread(&aux, sizeof(HABITACION), 1, db);
        if (aux.dniPac==buscado.dni)
            hit=1;
    }
    return aux;
}

HABITACION buscarHabXNum(int buscado, FILE *db){
    fseek(db, 0, SEEK_SET);
    int i=0, hit=0;
    HABITACION aux;
    while (i<(habXPiso*pisosHab)&&hit==0){
        i++;
        fread(&aux, sizeof(HABITACION), 1, db);
        if (aux.nroHabitacion==buscado)
            hit=1;
    }
    return aux;
}

//La funcion reconoce si se ingresa un numero de habitacion, documento o nombre de paciente.
HABITACION buscarInterno(int *hit){
    *hit=0;
    HABITACION resultado;
    PACIENTE aux;
    char input[sizeNom];
    FILE *db;
    ;
    if ((db=fopen(pathHab,"r+b"))==NULL){
        perror("No se pudo acceder a la base de datos de Habitaciones.");
    }else {
        puts("Ingrese numero de habitacion, DNI o nombre del internado.");
        fflush(stdin);
        gets(input);
        if (input[4]>48 && input[4]<57){ // SI ES UN DNI
            int dni = atoi(input);
            if(comprobarYaInternado(dni, db)){
                aux=buscarXDNI(dni);
                fseek(db, 0, SEEK_SET);
                resultado=buscarHabXPac(aux,db);
                *hit=1;
            }else{ puts("El paciente ingresado no se encuentra internado."); }
        }
        else {
            if (input[0]>48 && input[0]<57){ // SI ES UNA HABITACION
                int nroHab=atoi(input);
                if (((nroHab%100)>habXPiso)||(nroHab>((pisosHab*100)+habXPiso))||((nroHab%100)<=0))
                    nroHab=obtenerNumHab(nroHab);
                fseek(db, 0, SEEK_SET);
                resultado=buscarHabXNum(nroHab,db);
                *hit=1;
            }
            else { // SI ES UN NOMBRE
                aux=buscarXNombreApellido(input);
                fseek(db, 0, SEEK_SET);
                    if(comprobarYaInternado(aux.dni, db)){
                    fseek(db, 0, SEEK_SET);
                    resultado=buscarHabXPac(aux,db);
                    *hit=1;
                }else{ puts("El paciente ingresado no se encuentra internado."); }
            }
        }
    }
    return resultado;
}

void darAlta(HABITACION aux, FILE *db){
    aux.ocupado=0;
    buscarHabXNum(aux.nroHabitacion, db);
    fseek(db, -sizeof(HABITACION), SEEK_CUR);
    fwrite(&aux, sizeof(HABITACION), 1, db);
}

void modificarAltaPrevista(HABITACION hab, FILE *db){
    fseek(db, 0, SEEK_SET);
    puts("Ingresar dia");
    fflush(stdin);
    scanf("%i", &hab.alta.dia);
    puts("Ingresar mes");
    fflush(stdin);
    scanf("%i", &hab.alta.mes);
    puts("Ingresar ano");
    fflush(stdin);
    scanf("%i", &hab.alta.ano);
    buscarHabXNum(hab.nroHabitacion, db);
    fseek(db, -sizeof(HABITACION), SEEK_CUR);
    fwrite(&hab, sizeof(HABITACION), 1, db);
}

void reemplazarPaciente(HABITACION hab, FILE *db){
    fseek(db, 0, SEEK_SET);
    PACIENTE aux;
    aux=buscarPaciente();
    hab.dniPac=aux.dni;
    buscarHabXNum(hab.nroHabitacion, db);
    fseek(db, -sizeof(HABITACION), SEEK_CUR);
    fwrite(&hab, sizeof(HABITACION), 1, db);
}


void opModificacion(HABITACION hab, FILE *db){
    int op;
    puts("¿Que desea hacer?");
    puts("\t1.- Dar de alta.");
    puts("\t2.- Modificar alta prevista.");
    puts("\t3.- Reemplazar por otro paciente.");
    fflush(stdin);
    scanf("%i", &op);
    fseek(db, 0, SEEK_SET);
    switch (op){
        case 1:
            puts("El paciente ha sido dado de alta.");
            darAlta(hab, db);
            sumarAtencion(hab.dniPac);
        break;
        case 2:
            modificarAltaPrevista(hab, db);
        break;
        case 3:
            reemplazarPaciente(hab, db);
        break;
        default:
            puts("Ingreso una opcion invalida.");
        break;
    }
}

void modificarInterno(){
    HABITACION hab;
    int hit=0;
    hab=buscarInterno(&hit);
    puts("Busque un interno para modificar:");
    FILE *db;
    db=fopen(pathHab,"r+b");
    if(hit){
        if (db==NULL){
            perror("No se pudo acceder a la base de datos de Habitaciones.");
        }else {
            opModificacion(hab, db);
        }
    }else{
        puts("No se ha encontrado un interno valido.");
    }
    fclose(db);
}
