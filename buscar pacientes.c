#include "headers.h"

int contarPacientes (FILE *fichero){
    int cantPac=0;
    fseek(fichero, 0L, SEEK_END);
    cantPac=ftell(fichero)/sizeof(PACIENTE);
    fseek(fichero, 0L, SEEK_SET);
    return cantPac;
}

PACIENTE buscarXDNI (int buscado){
    FILE *fichero;
    PACIENTE pac, encontrado;
    fichero = fopen(pathPac, "r");
    int cantPac, i, rep;
    cantPac=contarPacientes(fichero);
    if (fichero!=NULL && cantPac>0){
        for(i=1; i<cantPac; i++){
            fread(&pac, sizeof(PACIENTE), 1, fichero);
            if (pac.eliminado==0 && pac.dni==buscado){
                encontrado=pac;
                rep++;
            }
        }
    }
    else {
        printf("Directorio de fichero %s incorrecto.", pathPac);
    }
    if (rep>1)
        puts("ERROR EN LA BASE DE DATOS, EL DNI SE ENCUENTRA INGRESADO EN MAS DE UN PACIENTE");
    fclose(fichero);
    return encontrado;
}

PACIENTE buscarXNombreApellido (char nomApe[]){
    FILE *fichero;
    PACIENTE pac, coincidencias[10];
    int hits=0, cantPac, i, seleccion;
    fichero = fopen(pathPac, "r");
    cantPac=contarPacientes(fichero);
    if (fichero!=NULL && cantPac>0){
        while (hits<10, fichero!=EOF){
            fread(&pac, sizeof(PACIENTE), 1, fichero);
            if (strcmp(nomApe, pac.nombreApellido)==0){
                coincidencias[hits]=pac;
                hits++;
            }
        }
        if(hits>1){
            printf("Se han encontrado %i coincidencia/s:\n", hits);
            for (i=0; i<hits; i++){
                printf("%i.- ", i+1);
                imprimirPaciente(coincidencias[i]);
            }
            printf("Seleccione el numero de paciente buscado");
            do{
                fflush(stdin);
                scanf("%i", &seleccion);
                seleccion--;
                if(seleccion>hits||seleccion<0){
                    printf("Ingreso una opcion invalida. Intente otra vez entre 0 y %i.\n", hits);
                }
            }while (seleccion>hits||seleccion<0);
            hits=seleccion;
        }

    }
    else {
        printf("Directorio de fichero %s incorrecto.", pathPac);
    }
    return coincidencias[hits];
}

PACIENTE buscarPaciente(){
    imprimirHeader(" Busqueda de Pacientes");
    PACIENTE pac;
    char input[sizeNom];
    fflush(stdin);
    gets(input);
    if (input[0]>48 && input[0]<57){
        int dni = atoi(input);
        pac=buscarXDNI(dni);
    } else {
        pac=buscarXNombreApellido(input);
    }
    return pac;
}
