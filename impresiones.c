#include "headers.h"

void imprimirPacientes(PACIENTE pacs[], int dimL){
    int i,j;
    for (i=0; i<dimL; i++){
        if (pacs[i].eliminado==0){
            printf("%c", 201);
            for (j=0; j<50; j++)
                printf("%c", 205);
            printf("\n%c>>> Nombre y apellido: %s", 186, pacs[i].nombreApellido);
            printf("\n%c\tDNI: %i",186,pacs[i].dni);
            printf("\n%c\tEdad: %i",186,pacs[i].edad);
            printf("\n%c\tFue atendido aqui %i vez(es).", 186,pacs[i].cantAtendido);
            printf("\n%c\tFue internado aqui %i vez(es).\n", 186,pacs[i].cantInternado);
            printf("%c", 200);
            for (j=0; j<50; j++)
                printf("%c", 205);
            printf("\n");
        }
    }
}

void imprimirHabitacion(HABITACION hab){
    int j;
    PACIENTE pac;
    printf("%c", 201);
    for (j=0; j<50; j++)
        printf("%c", 205);
    printf("\n%c>>> Habitacion numero %i\n",186 , hab.nroHabitacion);
    if (hab.ocupado==0)
        printf("%c\tHabitacion LIBRE.\n",186);
    else{
        printf("%c\tHabitacion OCUPADA por paciente:\n",186);
        pac=buscarXDNI(hab.dniPac);
        imprimirPacientes(&pac, 1);
        printf("%c\t Fecha de ingreso: %i/%i/%i", 186, hab.ingreso.dia, hab.ingreso.mes, hab.ingreso.ano);
        printf("\n%c\t Fecha de alta prevista: %i/%i/%i\n", 186, hab.alta.dia, hab.alta.mes, hab.alta.ano);
        }
    printf("%c", 200);
    for (j=0; j<50; j++)
        printf("%c", 205);
    printf("\n\n");

}

void imprimirMedicos(MEDICO meds[], int dimL){
    int i, j;
    for (i=0; i<dimL; i++){
        if (meds[i].eliminado==0){
            printf("%c", 201);
            for (j=0; j<50; j++)
                printf("%c", 205);
            printf("\n%c>>> Nombre y apellido: %s\n%c\tMatricula: %i\n%c\tEspecialidad:%s\n", 186, meds[i].nombreApellido, 186, meds[i].matricula, 186, meds[i].especialidad);
            printf("%c", 200);
            for (j=0; j<50; j++)
                printf("%c", 205);
            printf("\n");
        }
    }
}


void indiceADia(char guardar[], int num){
    char diasSemana[][sizeNom] = {{"Lun"},{"Mar"},{"Mier"},{"Jue"},{"Vie"},{"Sab"},{"Dom"}};
    strcpy(guardar, diasSemana[num]);
}

void imprimirTurno(TURNO turno, int op){
    PACIENTE pac;
    char diaSem[sizeNom];
    switch (op){
        case 0:
            if (turno.ocupado==0)
                indiceADia(diaSem,turno.dia);
                printf("%c Turno libre para el %s a las [%.2f]\n", 186, diaSem, turno.hora);
        break;
        case 1:
            if(turno.ocupado==1){
                pac=buscarXDNI(turno.dniPaciente);
                indiceADia(diaSem,turno.dia);
                printf("%c  Turno reservado para el %s a las [%.2f] por:\n", 186, diaSem, turno.hora);
                imprimirPacientes(&pac, 1);
                printf("\n");
            }
        break;
        case 2:
            printf("%c  Turno ", 186);
            if (turno.ocupado==1){
                printf("reservado ");
            }else{ printf("libre ");}
            indiceADia(diaSem,turno.dia);
            printf("%cpara el %s a las [%.2f]", 186, diaSem, turno.hora);
            if (turno.ocupado==1){
                printf("por:");
                pac=buscarXDNI(turno.dniPaciente);
                imprimirPacientes(&pac, 1);
            }
            printf("\n");
        break;
    }
}

void listarTurnos(TURNO turno[], int op){ //op=0 imprime turnos libres, op=1 imprime turnos reservados y op=2 imprime todos los turnos.
    int d, t;
    if (op>=0&&op<=2){
        for (d=0; d<7; d++){
            for (t=0;t<10;t++){
                imprimirTurno(turno[(d*10)+t], op);
            }
        }
    }else{
        puts("Parametro de impresion de turnos invalido.");
    }
    printf("\n");
}

//PARA QUEDAR CENTRADO DEBE RECIBIR UN STRING DE 22 CARACTERES.
void imprimirHeader(char titulo[]){
    int i;
    printf("\n%c", 201);
    printf("%c", 205);
    for (i=0; i<19; i++){
        printf("%c", 174);
    }
    for (i=0; i<22; i++){
        printf("%c", 205);
    }
    for (i=0; i<19; i++){
        printf("%c", 175);
    }
    printf("%c", 205);
    printf("%c\n", 187);
    printf("%c%42s%21c\n", 186, " ", 186);
    printf("%c%42s%21c\n", 186, titulo, 186);
    printf("%c%42s%21c\n", 186, " ", 186);
    printf("%c", 200);
    printf("%c", 205);
    for (i=0; i<19; i++){
        printf("%c", 174);
    }
    for (i=0; i<22; i++){
        printf("%c", 205);
    }
    for (i=0; i<19; i++){
        printf("%c", 175);
    }
    printf("%c", 205);
    printf("%c\n\n", 188);
};

void imprimirMenuPrincipal (){
    system("cls");
    imprimirHeader("  MENU PRINCIPAL    ");
    printf("Ingrese una opcion para continuar:\n\t1.- Buscar, listar o editar registro de pacientes. \n\t2.- Carga o modificacion de turnos.\n\t3.- Alta/Baja o modificacion de internaciones.\n\t4.- Listar o modificar registro de Medicos.\n\t5.- Salir del sistema\n");
};

void imprimirMenuOpPacientes () {
    system("cls");
    imprimirHeader("Registro de Pacientes ");
    printf("Ingrese una opcion para continuar:\n\t1.- Listado completo de pacientes. \n\t2.- Agregar nuevo paciente(s).\n\t3.- Modificar paciente(s). \n\t4.- Eliminar paciente(s).\n\t5.- Buscar paciente(s).\n\t6.- Volver al Menu Principal.\n");
};

void imprimirMenuOpTurnos () {
    system("cls");
    imprimirHeader("  Administrar Turnos  ");
    printf("Ingrese una opcion para continuar:\n\t1.- Ver turnos reservados. \n\t2.- Ver turnos libres.\n\t3.- Cargar turno(s).\n\t4.- Cancelar turno(s). \n\t5.- Atender paciente. \n\t6.- Volver al Menu Principal.\n");
};

void imprimirMenuOpInternaciones () {
    system("cls");
    imprimirHeader("  Administrar Turnos  ");
    printf("Ingrese una opcion para continuar:\n\t1.- Buscar interno.\n\t2.- Ver internaciones activas. \n\t3.- Ver habitaciones libres.\n\t4.- Ver listado total de habitaciones.\n\t5.- Ingresar nuevo interno. \n\t6.- Modificar interno.\n\t7.- Dar de alta internos.\n\t8.- Volver al Menu Principal.\n");
};

void imprimirMenuOpMedicos () {
    system("cls");
    imprimirHeader("  Administrar Medicos ");
    printf("Ingrese una opcion para continuar:\n\t1.- Listar medicos actualmente en nomina.\n\t2.- Buscar medico.\n\t3.- Cargar nuevo medico(s). \n\t4.- Eliminar medico(s). \n\t5.- Modificar medico(s).\n\t6.- Volver al Menu Principal.\n");
};
