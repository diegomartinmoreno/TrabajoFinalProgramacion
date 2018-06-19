#include "headers.h"

int contarMedicos(){
    FILE *db;
    int resultado;
    db=fopen(pathMed, "rb");
    if(db==NULL){
        resultado=fseek(db, -sizeof(int), SEEK_END)/sizeof(MEDICO);
    }
    else {
    resultado=0
    }
    fclose(db);
    return resultado;
}

void inicializarTurno(MEDICO med){
    int i, j, d;
    for (d=0;d<7;d++){
        float inihorario=10;
        for (i=0;i<10;i++){
            med.listaTurnos[d*i].dia=d+1;
            med.listaTurnos[d*i].hora=inihorario;
            med.listaTurnos[d*i].dniPaciente=0;
            med.listaTurnos[d*i].ocupado=0;
            med.listaTurnos[d*i].matMedico=med.matricula;
            inihorario+=0.3;
            float result=inihorario-(int)inihorario;
            if (result>=0.59){
                inihorario=(int)inihorario+1;
            }
        }
    }
}


/*Al inicio de la base de datos de Medicos hay un dato entero (4bytes), cuyo valor indica 1=los turnos han sido inicializados, 0= los turnos guardan basura.
*/
void inicializadorTurnos (){
    FILE *db;
    MEDICO med;
    int i, cantMed, yaInicializados;
    cantMed=contarMedicos();
    if (fopen(pathMed, "rb")!=NULL){
        db=fopen(pathMed, "wb");
        fread(&yaInicializados, sizeof(int), 1, db);
        if(yaInicializados==0){
            fwrite(1, sizeof(int), 1, db);
            for (i=0; i<cantMed, i++){
                fread(&med, sizeof(MEDICO), 1, db);
                inicializarTurno(med);
            }
        }
    }
    else{
            puts("La base de datos de Medicos se encuentra vacia. Fallo al cargar turnos.");
    }
}

void cargaArchivoMedicos(){
    FILE *db;
    char control;
    if ((db=fopen(pathMed,"a+b"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO");
    }
    while (control!='n'&&control!='N'){
        cargaMedicos();
        fflush(stdin);
        printf("Desea Continuar? S/N\n");
        control=getchar();
    }
}

void cargaMedicos (){
    FILE *db;
    MEDICO m;
    if ((db=fopen(pathMed,"a+b"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO\n");
    }
    printf("INGRESE NOMBRE Y APELLIDO\n");
    fflush(stdin);
    gets(m.nombreApellido);
    fwrite(&m.nombreApellido,sizeof(char),sizeNom,db);
    printf("INGRESE MATRICULA\n");
    fflush(stdin);
    scanf("%i",&m.matricula);
    fwrite(&m.matricula,sizeof(int),1,db);
    printf("INGRESE ESPECIALIDAD\n");
    fflush(stdin);
    scanf("%i",&m.matricula);
    fwrite(&m.matricula,sizeof(int),1,db);
}
