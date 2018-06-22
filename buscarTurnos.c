#include "headers.h"

TURNO buscarDisp(TURNO tur[], int dia, float hora){
    int i=0, hit=0;
    TURNO aux;
    aux.ocupado=1;
    while(i<70&&hit==0){
        if(tur[i].dia==dia&&(tur[i].hora<hora+0.1&&tur[i].hora>hora-0.1)&&tur[i].ocupado==0){
            aux=tur[i];
            hit=1;
        }
        i++;
    }
    return aux;
}

TURNO leerTurno(int matMed, int d, float h){
    PACIENTE pac;
    pac.eliminado=1;
    TURNO tur;
    tur.ocupado=0;
    int op;
    puts("Complete datos del paciente que hace la reserva: ");
    puts("1.- Reservar con paciente conocido.");
    puts("2.- Reservar con un paciente nuevo.");
    fflush(stdin);
    scanf("%i", &op);
    switch(op){
        case 1:
            puts("Ingrese nombre y apellido o DNI del paciente:");
            pac=buscarPaciente();
        break;
        case 2:
            pac=guardarPaciente();
        break;
        default:
            puts("No ha ingresado una opcion valida.");
            system("Pause");
        break;
    }
    if (pac.eliminado!=0){
        tur.dniPaciente=pac.dni;
        tur.matMedico=matMed;
        tur.ocupado=1;
        tur.dia=d;
        tur.hora=h;
    }
    return tur;
}

void imprimirTurnosXMedico (int op){
    MEDICO med;
    med=buscarMed();
    listarTurnos(med.listaTurnos, op);
}

void guardarTurno (TURNO tur, int matMed){
    MEDICO med;
    FILE *db;
    db=fopen(pathMed, "r+b");
    int cantMed, hit=0, i=0;
    cantMed=contarMedicos(db);
    while(i<cantMed&&hit==0){
        fread(&med, sizeof(MEDICO), 1, db);
        if (med.matricula==matMed){
            hit=1;
        }
    }
    if (hit){
        i=0;
        while (tur.dia!=med.listaTurnos[i].dia&&(tur.hora<med.listaTurnos[i].hora+0.1&&tur.hora>med.listaTurnos[i].hora-0.1))
            i++;
        med.listaTurnos[i]=tur;
    }else{puts("Matricula invalida.");}
    fseek(db, -sizeof(MEDICO), SEEK_CUR);
    fwrite(&med, sizeof(MEDICO), 1, db);
    fclose(db);
}

void cargarTurno (){
    MEDICO med;
    printf("Reservacion de turnos. ");
    med=buscarMed();
    TURNO buscado;
    if (med.eliminado==0){
        int dia;
        puts("Ingresar dias restantes para la reserva:");
        fflush(stdin);
        scanf("%i", &dia);
        float hora;
        puts("Ingresar hora del dia (turnos cada 20 minutos).");
        fflush(stdin);
        scanf("%f", &hora);
        buscado=buscarDisp(med.listaTurnos, dia, hora);
        if (buscado.ocupado==0){
            buscado=leerTurno(med.matricula, dia, hora);
            guardarTurno(buscado,med.matricula);
            puts("Turno reservado.");
            system("Pause");
        } else{puts("No se ha reservado. El turno ya se encuentra ocupado.");}
    }
    else{
        puts("El medico solicitado no fue encontrado. No se ha reservado el turno.");
    }
}
