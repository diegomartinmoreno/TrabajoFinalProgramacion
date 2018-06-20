#include "headers.h"


int inicializarBasesDatos(char path[]){
    int creado=0;
    FILE *fichero;
    fichero=fopen(path, "rb");
    if (fichero==NULL){
        fclose(fichero);
        fichero=fopen(path, "wb");
        creado=1;
    }
    fclose (fichero);
    return creado;
};


void iniciarSistema(){
    puts("Bienvenido/a al trabajo final de Laboratorio 1.");
    puts ("Integrantes del grupo: Lautaro Toledo y Diego Moreno.");
    system("Pause");
    system("cls");
    inicializarBasesDatos(pathPac);
    inicializarBasesDatos(pathMed);
    if (inicializarBasesDatos(pathHab)){
        inicializadorHabitaciones();
    }
    SwitchMenuPrincipal();
};


void menuOpPacientes(){
    PACIENTE pac;
    char control;
    int op;
    do{
        imprimirMenuOpPacientes();
        fflush(stdin);
        scanf("%i", &op);
        switch(op){
            case 1:
                imprimirHeader(" Busqueda de Pacientes");
                pac=buscarPaciente();
                imprimirPacientes(&pac,1);
                system("pause");
                system("cls");
            break;
            case 2:
                imprimirHeader("  Carga de Pacientes  ");
                cargaPacientes();
                system("pause");
                system("cls");
            break;
            case 3:
                imprimirHeader(" Modificar Pacientes  ");
                modificarPacientes();
                system("pause");
                system("cls");
            break;
            case 4:
                imprimirHeader("  Eliminar Pacientes  ");
                eliminarPacientes();
                system("pause");
                system("cls");
            break;
            case 5:
                imprimirHeader(" Listado de pacientes ");
                listarPacientes();
                system("pause");
                system("cls");
            break;
            case 6:
                puts("Volver al menu principal? S/N\n");
                fflush(stdin);
                scanf("%c",&control);
                if (control=='s'||control=='S'){
                    imprimirMenuPrincipal();
                }else{
                    system("pause");
                    system("cls");
                    imprimirMenuOpPacientes();
                }
            break;
        }
    }while (control!='s'&&control!='S');
}

void menuOpMedicos(){
    char control;
    int op;
    do{
        imprimirMenuOpMedicos();
        fflush(stdin);
        scanf("%i", &op);
        switch(op){
            case 1:
                imprimirHeader("   Nomina de Medicos  ");
                listarMedicos();
                system("pause");
                system("cls");
            break;
            case 2:
                imprimirHeader("  Busqueda de Medicos ");
                buscarMed();
                system("pause");
                system("cls");
            break;
            case 3:
                imprimirHeader("   Carga de Medicos   ");
                cargaMedicos();
                system("pause");
                system("cls");
            break;
            case 4:
                imprimirHeader("   Eliminar Medicos   ");
                eliminarMedico();
                system("pause");
                system("cls");
            break;
            case 5:
                puts("Volver al menu principal? S/N\n");
                fflush(stdin);
                scanf("%c",&control);
                if (control=='s'||control=='S'){
                    imprimirMenuPrincipal();
                }else{
                    system("pause");
                    system("cls");
                    imprimirMenuOpPacientes();
                }
            break;
        }
    }while (control!='s'&&control!='S');
}

void SwitchMenuPrincipal(){
    char flag='n';
    int op;
    do{
        imprimirMenuPrincipal();
        fflush(stdin);
        scanf("%i", &op);
        switch(op){
            case 1:
                system("cls");
                menuOpPacientes();
            break;
            case 2:
            break;
            case 3:
            break;
            case 4:
                system("cls");
                menuOpMedicos();
            break;
            case 5:
                system("cls");
                puts("\nSeguro desea salir del sistema? S/N");
                fflush(stdin);
                flag=getchar();
            break;
            default:
                puts("OPCION INCORRECTA.");
                system("pause");
                system("cls");
                imprimirMenuPrincipal();
            break;
        }
    } while (flag!='S'&&flag!='s');
}
