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
            printf("\n%c\tFue atendido aqui %i veces.\n", 186,pacs[i].cantAtendido);
            printf("%c", 200);
            for (j=0; j<50; j++)
                printf("%c", 205);
            printf("\n");
        }
    }
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
    printf("Ingrese una opcion para continuar:\n\t1.- Buscar paciente(s). \n\t2.- Agregar nuevo paciente(s).\n\t3.- Modificar paciente(s). \n\t4.- Eliminar paciente(s).\n\t5.- Listado completo de pacientes.\n\t6.- Volver al Menu Principal.\n");
};

void imprimirMenuOpTurnos () {
    imprimirHeader("  Administrar Turnos  ");
    printf("Ingrese una opcion para continuar:\n\t1.- Ver turnos reservados. \n\t2.- Cancelar turno(s).\n\t3.- Cargar turno(s). \n\t4.- Volver al Menu Principal.\n");
};

void imprimirMenuOpInternaciones () {
    imprimirHeader("  Administrar Turnos  ");
    printf("Ingrese una opcion para continuar:\n\t1.- Ver turnos reservados. \n\t2.- Cancelar turno(s).\n\t3.- Cargar turno(s). \n\t4.- Volver al Menu Principal.\n");
};

void imprimirMenuOpMedicos () {
    imprimirHeader("  Administrar Medicos ");
    printf("Ingrese una opcion para continuar:\n\t1.- Listar medicos actualmente en nomina.\n\t2.- Buscar medico.\n\t3.- Cargar nuevo medico(s). \n\t4.- Eliminar medico(s). \n\t5.- Volver al Menu Principal.\n");
};
