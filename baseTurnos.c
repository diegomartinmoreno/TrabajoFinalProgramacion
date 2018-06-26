#include "headers.h"

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

void obtenerDiaYHora(int *dia, float *hora){
    float minutos;
    do{
        puts("Ingresar dia de la reserva 1 = Lun // 7 = Sab");
        fflush(stdin);
        scanf("%i", dia);
        *dia--;
    }while (!(*dia<7&&*dia>=0));
    do{
    puts("Ingresar hora del dia (Turnos cada 20 minutos, de 9.00 a 12.00hs).");
    fflush(stdin);
    scanf("%f", hora);
    minutos=*hora-(int)*hora;
    } while (!(*hora>=8.9&&*hora<12.1&&((minutos<0.1&&minutos>-0.1)||(minutos<0.21&&minutos>0.19)||(minutos<0.41&&minutos>0.39))));
}

void cargarTurno (){
    MEDICO med;
    printf("Reservacion de turnos. ");
    med=buscarMed();
    TURNO buscado;
    if (med.eliminado==0){
        int dia;
        float hora;
        obtenerDiaYHora(&dia, &hora);
        buscado=buscarTur(med.listaTurnos, dia, hora);
        if (buscado.ocupado==0){
            buscado=leerTurno(med.matricula, dia, hora);
            guardarTurno(buscado,med.matricula);
            puts("Turno reservado.");
        } else{puts("No se ha reservado. El turno ya se encuentra ocupado.");}
    }
    else{
        puts("El medico solicitado no fue encontrado. No se ha reservado el turno.");
    }
}

void cancelarTurno(){
    MEDICO med;
    TURNO buscado;
    med=buscarMed();
    if (med.eliminado==0){
        puts("Seleccione la reserva que desea cancelar:");
        int dia;
        float hora;
        obtenerDiaYHora(&dia, &hora);
        buscado=buscarTur(med.listaTurnos, dia, hora);
        if (buscado.ocupado==1){
            buscado.ocupado=0;
            guardarTurno(buscado, med.matricula);
            puts("El turno ha sido cancelado.");
        }else{puts("El turno que desea cancelar no se encuentra reservado.");}
    }else {puts("No se pudo cancelar reserva por no encontrarse el medico.");}

}
/*
void actualizarTurnos(){
    time_t origen;
    struct tm *fecha;
    time(&origen);
    fecha=localtime(&origen);
    MEDICO med;
    TURNO aux;
    HABITACION hab;
    FILE *db;
    db=fopen(pathMed, "r+b");
    int cantMed=contarMedicos(), i;
    for (i=0; i<cantMed; i++){
        if (fecha->tm_)
    }
}
*/
void atenderPaciente(){
    MEDICO med;
    TURNO aux;
    HABITACION hab;
    hab.ocupado=0;
    med=buscarMed();
    char especs[pisosHab-1][sizeNom];
    int i=0, hit=0, internar, nroHab;
    char atender;
    if (med.eliminado==0){
        while (hit==0&&i<70){
            if (med.listaTurnos[i].ocupado==1)
                hit=1;
            else
                i++;
        }
        if (i<70){
            puts("El proximo turno del medico es:");
            imprimirTurno(med.listaTurnos[i],1);
            puts("Atender? S/N");
            fflush(stdin);
            scanf("%c", &atender);
            if(atender=='s'||atender=='S'){
                puts("El paciente sera atendido.");
                aux=med.listaTurnos[i];
                aux.ocupado=0;
                guardarTurno(aux, med.matricula);
                internar=rand() % 100;
                if (internar>60){
                    system("cls");
                    imprimirHeader("   Internar Paciente  ");
                    puts("El paciente requiere ser internado!");
                    obtenerEspecialidades(especs);
                    hit=0;
                    i=0;
                    while (i<pisosHab&&hit==0){
                        if (strcmp(med.especialidad, especs[i])==0)
                            hit=1;
                        else
                            i++;
                    }
                    printf("El paciente sera internado en el piso %i especialidad %s\n", i, especs[i]);
                    FILE *db;
                    db=fopen(pathHab, "r+b");
                    do{
                        printf("Ingrese numero de habitacion entre %i y %i\n", i*100+1, i*100+habXPiso);
                        fflush(stdin);
                        scanf("%i", &nroHab);
                        hab=buscarHabXNum(nroHab, db);
                    }while (nroHab>=(i*100+habXPiso)&&nroHab<=(i*100+1)&&hab.ocupado==1);
                    hab.ocupado=1;
                    hab.dniPac=aux.dniPaciente;
                    guardarHabitacion(hab, db);
                    fclose(db);
                    printf("El paciente ha sido internado exitosamente en la habitacion %i", nroHab);
                }else{puts("El paciente fue atendido exitosamente.");}
            }
        }else{puts("El medico no tiene turnos reservados.");}
    }else {puts("No se pudo atender al paciente por no encontrarse el medico.");}
}
