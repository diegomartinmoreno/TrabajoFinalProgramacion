#include "headers.h"

TURNO buscarTur(TURNO tur[], int dia, float hora){
    int i=0, hit=0;
    TURNO aux;
    aux.ocupado=1;
    while(i<70&&hit==0){
        if(tur[i].dia==dia&&(tur[i].hora<hora+0.1&&tur[i].hora>hora-0.1)){
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
    if (pac.eliminado==0){
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
    if (med.eliminado==0){
        listarTurnos(med.listaTurnos, op);
    }
    else
        puts("No se pudo listar los turnos.");
}


