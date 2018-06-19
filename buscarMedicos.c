#include "headers.h"

int Encontrado(char mat[][sizeNom], char buscado[], int dimL){
    int i, encontrado=0;
    for (i=0; i<dimL; i++)
    {
        if (strcmp(mat[i], buscado)==0){
            encontrado=1;
        }
    }
    return encontrado;
}

int determinarEspecialidades (char especialidades[][sizeNom]){
    // Sen determina 30 como el numero maximo de especialidades medicas que atienen en la clinica.
    int encontrados=0;
    FILE *dataMed;
    MEDICO med;
    dataMed=fopen(pathMed, "rb");
    while (dataMed!=NULL&&encontrados<30){
        fread(&med, sizeof(MEDICO), 1, dataMed);
        if (!med.eliminado){
            if (!Encontrado(especialidades, med.especialidad, encontrados))
            {
                strcpy(especialidades[encontrados], med.especialidad);
                encontrados++;
            }
        }
    }
    fclose(dataMed);
    return encontrados;
}

void imprimirMedicos(MEDICO meds[], int dimL){
    int i;
    for (i=0; i<dimL; i++){
        printf("Nombre: %s\n\tMatricula: %i\n\tEspecialidad:%s\n",meds[i].nombreApellido, meds[i].matricula, meds[i].especialidad);
    }
}

void ordenarMedicos(MEDICO meds[], int dimL){
    int i, j;
    for (i=0; i<dimL ;i++){
        for (j=dimL-i; j<0; j++){

        }
    }
}

void imprimirXESPEC(char busqueda[]){
    int hits;
    FILE *dataMed;
    MEDICO med, imprimir[10];
    dataMed=fopen(pathMed, "rb");
    while (dataMed!=NULL && hits<10){
        fread(&med, sizeof(MEDICO), 1, dataMed);
        if(!med.eliminado){
            if (strcmp(med.especialidad, busqueda)==0){
                imprimir[hits]=med;
                hits++;
            }
        }
    }
    ordenarMedicos(imprimir, hits);
    imprimirMedicos(imprimir, hits);
    fclose(dataMed);
}

void imprimirXNOM(char busqueda[]) {
    int hits;
    FILE *dataMed;
    MEDICO med, imprimir[10];
    dataMed=fopen(pathMed, "rb");
    while (dataMed!=NULL && hits<10){
        fread(&med, sizeof(MEDICO), 1, dataMed);
        if(!med.eliminado){
            if (strcmp(med.nombreApellido, busqueda)==0){
                imprimir[hits]=med;
                hits++;
            }
        }
    }
    ordenarMedicos(imprimir, hits);
    imprimirMedicos(imprimir, hits);
    fclose(dataMed);
}

void buscarMed(char busqueda[])
{
    char especialidades[50][sizeNom];
    int cantEspec, esNombre;
    cantEspec=determinarEspecialidades(especialidades);
    esNombre=!Encontrado(especialidades, busqueda, cantEspec);
    if (esNombre){
        imprimirXNOM(busqueda);
    }
    else {
        imprimirXESPEC(busqueda);
    }
}
