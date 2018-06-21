#include "headers.h"

TURNO buscarDisp(TURNO tur[], int dia, float hora){
    int i=0, hit=0;
    TURNO aux;
    while(i<70&&hit==0){
        if(tur[i].dia==dia&&tur[i].hora==hora){
            aux=tur[i];
            hit=1;
        }
        i++;
    }
    return aux;
}

TURNO leerTurno(int matMed){
    PACIENTE pac;
    TURNO tur;
    int i=0;
    puts("Seleccione el paciente que desea reservar: ");
    do {
        i++;
        pac=buscarPaciente();
    }while(pac.eliminado==0||i<5);
    if (pac.eliminado!=0){
        puts("Ingresar dia");
        fflush(stdin);
        scanf("%i", &tur.dia);
        puts("Ingresar hora");
        fflush(stdin);
        scanf("%f", &tur.hora);
        tur.dniPaciente=pac.dni;
        tur.matMedico=matMed;
        tur.ocupado=1;
    }
    return tur;
}

void imprimirTurnosXMedico (){
    MEDICO med;
    med=buscarMed();
    listarTurnos(med.listaTurnos, 70);
}

