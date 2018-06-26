#include "headers.h"

int contarMedicos(FILE *fichero){
    int resultado;
    fseek(fichero, 0, SEEK_END);
    resultado=ftell(fichero)/sizeof(MEDICO);
    fseek(fichero, 0, SEEK_SET);
    return resultado;
};

void listarMedicos(){
    int i, cantMed;
    FILE *fichero;
    MEDICO med;
    system("cls");
    fichero=fopen(pathMed, "rb");
    if (fichero==0){
        perror("No pudo acceder a base de datos de Medicos.");
    }else{
        cantMed=contarMedicos(fichero);
        for (i=0; i<cantMed; i++){
            fread(&med, sizeof(MEDICO), 1, fichero);
            imprimirMedicos(&med, 1);
        }
    }
    fclose(fichero);
};

void inicializarTurno(MEDICO *med){
    int i, d;
    for (d=0;d<7;d++){
        float inihorario=8.8;
        for (i=0;i<10;i++){
            inihorario+=0.2;
            float result=inihorario-(int)inihorario;
            if (result>=0.59){
                inihorario=(int)inihorario+1;
            }
            med->listaTurnos[(d*10)+i].dia=d;
            med->listaTurnos[(d*10)+i].hora=inihorario;
            med->listaTurnos[(d*10)+i].dniPaciente=0;
            med->listaTurnos[(d*10)+i].ocupado=0;
            med->listaTurnos[(d*10)+i].matMedico=med->matricula;
        }
    }
};

MEDICO leerMedico(MEDICO m, int nuevo){ // nuevo=1 para un medico nuevo, nuevo=0 para leer un medico ya cargado.
    printf("INGRESE NOMBRE Y APELLIDO\n");
    fflush(stdin);
    gets(m.nombreApellido);
    if (nuevo==1){
        printf("INGRESE MATRICULA\n");
        fflush(stdin);
        scanf("%i",&m.matricula);
        printf("INGRESE ESPECIALIDAD\n");
        fflush(stdin);
        gets(m.especialidad);
        inicializarTurno(&m);
    }
    m.eliminado=0;
    return m;
};

void cargaMedicos(){
    char control='s';
    char especialidades[pisosHab][sizeNom];
    obtenerEspecialidades(especialidades);
    FILE *db;
    MEDICO m;
    if ((db=fopen(pathMed,"a+b"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO\n");
    }
    else{
        while (control=='s'||control=='S'){
            m=leerMedico(m, 1);
            if (Encontrado(especialidades, m.especialidad))
                fwrite(&m,sizeof(MEDICO),1,db);
            else
                puts("No ingreso una especialidad que se trabaje en esta clinica.");
            fflush(stdin);
            printf("Desea Continuar? S/N\n");
            control=getchar();
        }
    }
    fclose(db);
};

void eliminarMedico(){
    char control='s';
    MEDICO med, aux;
    int cantMed, i=0, encontrado=0;
    FILE *fichero;
    fichero=fopen(pathMed, "r+b");
    if(fichero==NULL){
        perror("Error al acceder a la base de datos de Medicos.");
    }else{
        cantMed=contarMedicos(fichero);
        while (control=='s'||control=='S'){
            fclose(fichero);
            med=buscarMed();
            fichero=fopen(pathMed, "r+b");
            fseek(fichero,0,SEEK_SET);
            if (med.eliminado!=1){
                while (i<cantMed&&encontrado==0){
                    i++;
                    fread(&aux, sizeof(MEDICO), 1, fichero);
                    if (med.matricula==aux.matricula)
                        encontrado=1;
                }
                fseek(fichero, -sizeof(MEDICO), SEEK_CUR);
                strcpy(med.nombreApellido, "ELIMINADO");
                med.eliminado=1;
                fwrite(&med, sizeof(MEDICO), 1, fichero);
                puts("Su seleccion se ha eliminado con exito.");
            } else{
                puts("No se pudo eliminar medico ya que no se encontro en base de datos.");
            }
            puts("Desea eliminar otro medico de la nomina? S/N");
            fflush(stdin);
            scanf("%c", &control);
        }
    }
    fclose(fichero);
};

void modificarMedico(){
    MEDICO med, aux;
    med=buscarMed();
    int cantMed, i=0, encontrado=0;
    FILE *fichero;
    fichero=fopen(pathMed, "r+b");
    if(fichero==NULL){
        perror("Error al acceder a la base de datos de Medicos.");
    }else{
        if (med.eliminado==0){
            cantMed=contarMedicos(fichero);
            while (i<cantMed&&encontrado==0){
                fread(&aux, sizeof(MEDICO), 1, fichero);
                i++;
                if(aux.matricula==med.matricula){
                    encontrado=1;}
            }
            fseek(fichero, -sizeof(MEDICO), SEEK_CUR);
            puts("Ingrese modificaciones:");
            aux=leerMedico(aux, 0);
            fwrite(&aux, sizeof(MEDICO), 1, fichero);
        } else{
            puts("El medico que desea modificar no se encuentra en la base de datos.");
        }
    }
    fclose(fichero);
};

void modificarMedicos(){
    char control='s';
    while (control=='s'||control=='S'){
            modificarMedico();
            puts("Desea modificar otro medico? S/N");
            fflush(stdin);
            scanf("%c", &control);
    }
};
