#include "headers.h"

int contarPacientes (FILE *fichero){
    int cantPac=0;
    fseek(fichero, 0, SEEK_END);
    cantPac=ftell(fichero)/sizeof(PACIENTE);
    fseek(fichero, 0, SEEK_SET);
    return cantPac;
}

PACIENTE buscarMayorDNI(PACIENTE pacs[], int dimL){
    int i;
    PACIENTE mayor;
    mayor=pacs[0];
    for (i=0; i<dimL; i++){
        if (mayor.dni<pacs[i].dni)
            mayor=pacs[i];
    }
    return mayor;
}

PACIENTE buscarMayorNom(PACIENTE pacs[], int dimL){
    int i;
    PACIENTE mayor;
    mayor=pacs[0];
    for (i=0; i<dimL; i++){
        if (strcmp(mayor.nombreApellido, pacs[i].nombreApellido)==-1)
            mayor=pacs[i];
    }
    return mayor;
}

void ordenarPacientesXNom(PACIENTE pacs[], int dimL){
    PACIENTE aux;
    int ordenados=0, posMayor, hit=0, i, j;
    for (i=0; i<dimL; i++){
        posMayor=0;
        aux=buscarMayorNom(pacs, dimL-ordenados);
        hit=0;
        while (posMayor<dimL-ordenados&&hit==0){
            if (pacs[posMayor].dni==aux.dni)
                hit=1;
            else
                posMayor++;
        }
        for (j=posMayor; j<dimL-ordenados-1; j++){
            pacs[j]=pacs[j+1];
        }
        pacs[dimL-ordenados-1]=aux;
        ordenados++;
    }
}

void ordenarPacientesXDNI(PACIENTE pacs[], int dimL){
    PACIENTE aux;
    int ordenados=0, posMayor, hit=0, i, j;
    for (i=0; i<dimL; i++){
        posMayor=0;
        aux=buscarMayorDNI(pacs, dimL-ordenados);
        hit=0;
        while (posMayor<dimL-ordenados&&hit==0){
            if (pacs[posMayor].dni==aux.dni)
                hit=1;
            else
                posMayor++;
        }
        for (j=posMayor; j<dimL-ordenados-1; j++){
            pacs[j]=pacs[j+1];
        }
        pacs[dimL-ordenados-1]=aux;
        ordenados++;
    }
}

void listarPacientes(){
    FILE *fichero;
    PACIENTE pacs[100]; // Se toma 100 como el maximo de pacientes que habran en la base de datos
    int i, cantPac, op;
    PACIENTE pac;
    system("cls");
    imprimirHeader(" Listado de Pacientes ");
    fichero=fopen(pathPac, "rb");
    if (fichero!=NULL){
        cantPac=contarPacientes(fichero);
        for (i=0; i<cantPac; i++){
            fread(&pac, sizeof(pac), 1, fichero);
            pacs[i]=pac;
        }
        puts("Seleccione una opcion:");
        puts("1.- Ordenar por nombre.");
        puts("2.- Ordenar por DNI.");
        do{
            fflush(stdin);
            scanf("%i", &op);
        }while (op!=1&&op!=2);
        switch(op){
            case 1:
                ordenarPacientesXNom(pacs, cantPac);
            break;
            case 2:
                ordenarPacientesXDNI(pacs, cantPac);
            break;
        }
        imprimirPacientes(pacs, i);
    }else {puts("No se pudo acceder a la base de datos de pacientes.");}
    fclose(fichero);
}

PACIENTE buscarXDNI (int buscado){
    FILE *fichero;
    PACIENTE pac, encontrado;
    encontrado.eliminado=1;
    fichero = fopen(pathPac, "r+b");
    int cantPac, i;
    if (fichero!=NULL){
        cantPac=contarPacientes(fichero);
        if (cantPac>0){
            for(i=0; i<cantPac; i++){
                fread(&pac, sizeof(PACIENTE), 1, fichero);
                if (pac.eliminado==0 && pac.dni==buscado){
                    encontrado=pac;
                }
            }
        }
    }
    else {
        printf("Directorio de fichero %s incorrecto.", pathPac);
    }
    fclose(fichero);
    return encontrado;
}

PACIENTE buscarXNombreApellido (char nomApe[]){
    FILE *fichero;
    PACIENTE pac, coincidencias[10];
    int hits=0, cantPac, seleccion=0, i=0;
    fichero=fopen(pathPac, "r+b");
    if (fichero!=NULL){
        cantPac=contarPacientes(fichero);
        if (cantPac>0){
            while (hits<10 && i<cantPac){
                fread(&pac, sizeof(PACIENTE), 1, fichero);
                if (strcmp(nomApe, pac.nombreApellido)==0&&pac.eliminado==0){
                    coincidencias[hits]=pac;
                    hits++;
                }
                i++;
            }
            if(hits>1){
                printf("Se han encontrado %i coincidencia/s:\n", hits);
                imprimirPacientes(coincidencias, hits);
                printf("Seleccione el numero de paciente buscado\n");
                do{
                    fflush(stdin);
                    scanf("%i", &seleccion);
                    seleccion--;
                    if(seleccion>hits||seleccion<0){
                        printf("Ingreso una opcion invalida. Intente otra vez entre 1 y %i.\n", hits);
                    }
                }while (seleccion>hits||seleccion<0);
            }
            if (hits==0){
                puts("No se han encontrado coincidencias.");
                coincidencias[seleccion].eliminado=1;
            }
        }
    }
    else {
        printf("Directorio de fichero %s incorrecto.", pathPac);
    }
    fclose(fichero);
    return coincidencias[seleccion];
}

PACIENTE buscarPaciente(){
    PACIENTE pac;
    char input[sizeNom];
    fflush(stdin);
    gets(input);
    //La funcion detecta si se ha ingresado un numero o una letra, para buscar por nombre o DNI respectivamente.
    if (input[0]>48 && input[0]<57){
        int dni = atoi(input);
        pac=buscarXDNI(dni);
    } else {
        pac=buscarXNombreApellido(input);
    }
    if (pac.eliminado==0)
        puts("Paciente encontrado.");
    return pac;
}


