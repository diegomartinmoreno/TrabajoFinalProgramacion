#include "headers.h"


int Encontrado(char mat[][sizeNom], char buscado[]){
    int i, encontrado=0;
    for (i=0; i<pisosHab; i++)
    {
        if (strcmp(mat[i], buscado)==0){
            encontrado=1;
        }
    }
    return encontrado;
}

void ordenarMedicos(MEDICO meds[], int dimL){ //COMPLETAR!!!!
    int i, j;
    for (i=0; i<dimL ;i++){
        for (j=dimL-i; j<0; j++){

        }
    }
}

MEDICO imprimirXESPEC(char busqueda[]){
    int hits=0, seleccion, cantMed, i=0;
    FILE *dataMed;
    MEDICO med, imprimir[10];
    dataMed=fopen(pathMed, "rb");
    cantMed=contarMedicos(dataMed);
    while (i<cantMed && hits<10){
        i++;
        fread(&med, sizeof(MEDICO), 1, dataMed);
        if(!med.eliminado){
            if (strcmp(med.especialidad, busqueda)==0){
                imprimir[hits]=med;
                hits++;
            }
        }
    }
    printf("Se han encontrado %i coincidencias\n", hits);
    imprimirMedicos(imprimir, hits);
    if (hits>1){
        puts("Seleccione el numero de medico buscado.");
        do{
            fflush(stdin);
            scanf("%i", &seleccion);
            seleccion--;
            if (seleccion>=hits || seleccion<0){
                printf("Ha ingresado una opcion incorrecta. Ingrese una opcion entre 1 y %i\n", hits);
            }
        }while (seleccion>=hits || seleccion<0);
    }else {
        seleccion=0;
    }
    if (hits==0){
        med.eliminado=1;
        puts("No se encontro ninguna coincidencia.");
    }else{
        med=imprimir[seleccion];
    }
    fclose(dataMed);
    return med;
}

MEDICO imprimirXNOM(char busqueda[]) {
    int hits=0, seleccion, cantMed, i=0;
    FILE *dataMed;
    MEDICO med, imprimir[10];
    dataMed=fopen(pathMed, "rb");
    cantMed=contarMedicos(dataMed);
    while (i<cantMed && hits<10){
        i++;
        fread(&med, sizeof(MEDICO), 1, dataMed);
        if(!med.eliminado){
            if (strcmp(med.nombreApellido, busqueda)==0){
                imprimir[hits]=med;
                hits++;
            }
        }
    }
    imprimirMedicos(imprimir, hits);
    if (hits>1){
        puts("Seleccione el numero de medico buscado.\n");
        do{
            fflush(stdin);
            scanf("%i", &seleccion);
            seleccion--;
            if (seleccion>=hits || seleccion<0){
                printf("Ha ingresado una opcion incorrecta. Ingrese una opcion entre 1 y %i\n", hits);
            }
        }while (seleccion>=hits || seleccion<0);
    }else {
        seleccion=0;
    }
    if (hits==0){
        med.eliminado=1;
        puts("No se encontro ninguna coincidencia.");
    }else{
        med=imprimir[seleccion];
    }
    fclose(dataMed);
    return med;
}

MEDICO buscarMed()
{
    MEDICO med;
    char especialidades[50][sizeNom], busqueda[sizeNom];
    int noEsNombre;
    puts("Ingrese nombre del medico o especialidad buscada:\n");
    fflush(stdin);
    gets(busqueda);
    obtenerEspecialidades(especialidades);
    noEsNombre=Encontrado(especialidades, busqueda);
    if (noEsNombre){
        med=imprimirXESPEC(busqueda);
    }
    else {
        med=imprimirXNOM(busqueda);
    }
    return med;
}
