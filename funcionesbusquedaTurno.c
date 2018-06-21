#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define pathTurn ".\\dataTurn"

typedef struct{
    int dniPaciente;
    int dia;
    float hora;
    int ocupado;
    int matMedico;
}TURNO;

void cargaTurno ();
int control ();
void muestraTurnos();

int main()
{
    printf("Hello world!\n");
    cargaTurno();
    return 0;
}

void cargaTurno ()
{
    FILE *db;
    TURNO tur;
    int d,h,opc=0;
    float inicioTurnos,cambioHoras;
    db=fopen(pathTurn,"rb");
    if (db==NULL){
        db=fopen(pathTurn,"r+b");
    }
    if (db!=NULL){
        for (d=0;d<7;d++){
            fwrite(&tur,sizeof(TURNO),1,db);
            for (h=0;h<10;h++){
                inicioTurnos=8;
                opc=control();
                if (opc==1)
                {
                    puts("DNI DE PACIENTE:");
                    fflush(stdin);
                    scanf("%i",&tur.dniPaciente);
                    tur.hora=inicioTurnos;
                    tur.dia=d+1;
                    cambioHoras=inicioTurnos-(int)inicioTurnos;
                    tur.ocupado=1;
                    if (cambioHoras>=0.59){
                        inicioTurnos=(int)inicioTurnos+1;
       }
                }

            }
        }

    }
    fclose(db);
}
int control ()
{
    int opc;
    printf("Desea registrar el turno con este horario? 1.Si/2.No \n");
    fflush(stdin);
    scanf("%i",&opc);
    return opc;
}
void muestraTurnos()
{
    FILE *db;
    TURNO tur;
    int d,h;
    db=fopen(pathTurn,"rb");
    if(db!=NULL){
        for (d=0;d<7;d++){
            for (h=0;h<10;h++){
                    if (tur.ocupado==1){
                            printf("DNI PACIENTE: i%",tur.dniPaciente);
                            printf("HORA: %2.f",tur.hora);
                            printf("ESTADO: %i",tur.ocupado);
                        }
                }
        }
    }
    fclose(db);
}
void buscarTurno (){
    FILE *db;
    int dni;
    db=fopen(pathTurn,"rb");
    if (db!=NULL){
        puts("Ingrese DNI del paciente con el cual esta registrado el turno.");
        fflush(stdin);
        scanf("%i",dni);
        buscarXDni(dni);
    }
    fclose(db);
}
void buscarXDni (int id){
    FILE *db;
    TURNO tur;
    int d,h,busc;
    db=fopen(pathTurn,"rb");
    if (db!=NULL){

            for (d=0;d<7;d++){
                fread(&tur,sizeof(TURNO),1,db);
                for (h=0;h<10*(d+1);d++){
                        if (tur.ocupado==0 &&(id==tur.dniPaciente)){
                            busc+=1;
                        }
                }
            }
    }
     else{
        puts("Error en apertura de archivo.");
     }
     if (busc<=0){
         puts("No se encontro registro de paciente con el dni ingresado.");
     }
     fclose(db);
}
void modificarTurno (){
    FILE *db;
    TURNO tur;
    int d,h,busc;
    db=fopen(pathTurn,"rb");
    if (db!=NULL){
            if (tur.ocupado==1){
                for (d=0;d<7;d++){
                    fread(&tur,sizeof(TURNO),1,db);
                    for (h=0;h<10*(d+1);d++){


                        }
                }
            }
    }
}
