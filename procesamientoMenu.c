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
    if (inicializarBasesDatos(pathPac)){
        cargarPacsRandom(20);
    }
    if (inicializarBasesDatos(pathMed)){
        cargarMedsRandom (10);
    }
    if (inicializarBasesDatos(pathHab)){
        inicializadorHabitaciones();
    }else{
        actualizarBase();
    }
    SwitchMenuPrincipal();
};


void menuOpPacientes(){
    PACIENTE pac;
    char control='n';
    int op;
    do{
        imprimirMenuOpPacientes();
        fflush(stdin);
        scanf("%i", &op);
        switch(op){
            case 1:
                system("cls");
                imprimirHeader(" Listado de pacientes ");
                listarPacientes();
                system("pause");
                system("cls");
            break;
            case 2:
                system("cls");
                imprimirHeader("  Carga de Pacientes  ");
                cargaPacientes();
                system("pause");
            break;
            case 3:
                system("cls");
                imprimirHeader(" Modificar Pacientes  ");
                modificarPacientes();
                system("pause");
            break;
            case 4:
                system("cls");
                imprimirHeader("  Eliminar Pacientes  ");
                loopEliminarPacientes();
                system("pause");
            break;
            case 5:
                system("cls");
                imprimirHeader(" Busqueda de Pacientes");
                puts("Ingrese nombre o documento del paciente buscado:");
                pac=buscarPaciente();
                imprimirPacientes(&pac,1);
                system("pause");
            break;
            case 6:
                puts("Volver al menu principal? S/N\n");
                fflush(stdin);
                scanf("%c",&control);
            break;
            default:
                puts("OPCION INCORRECTA.");
            break;
        }
    }while (control!='s'&&control!='S');
}

void menuOpInternaciones(){
    char control='n';
    int op;
    do{
        actualizarBase();
        imprimirMenuOpInternaciones();
        fflush(stdin);
        scanf("%i", &op);
        switch(op){
            case 1:
                system("cls");
                imprimirHeader("    Buscar interno    ");
                int internado=0;
                HABITACION impr;
                impr=buscarInterno(&internado);
                if (internado){
                    imprimirHabitacion(impr);
                }
                system("pause");
            break;
            case 2:
                system("cls");
                imprimirHeader("   Internos activos   ");
                listarHabitaciones(1);
                system("pause");
            break;
            case 3:
                system("cls");
                imprimirHeader("   Hab. disponibles   ");
                listarHabitaciones(0);
                system("pause");
            break;
            case 4:
                system("cls");
                imprimirHeader(" Listado habitaciones ");
                listarHabitaciones(2);
                system("pause");
            break;
            case 5:
                system("cls");
                imprimirHeader("     Nuevo interno    ");
                cargarHab();
                system("pause");
            break;
            case 6:
                system("cls");
                imprimirHeader("   Modificar Interno  ");
                modificarInterno();
                system("pause");
            break;
            case 7:
                system("cls");
                imprimirHeader("  Dar interno de Alta ");
                HABITACION h;
                int success=0;
                h=buscarInterno(&success);
                if(success){
                    FILE *db=fopen(pathHab, "r+b");
                    darAlta(h, db);
                    sumarInternacion(h.dniPac);
                    fclose(db);
                    puts("El paciente ha sido dado de alta.");
                } else{
                    puts("Interno no encontrado.");
                }
                system("pause");
            break;
            case 8:
                puts("Volver al menu principal? S/N\n");
                fflush(stdin);
                scanf("%c",&control);
            break;
            default:
                puts("OPCION INCORRECTA.");
            break;
        }
    }while (control!='s'&&control!='S');
}

void menuOpTurnos(){
    char control='n';
    int op;
    do{
        void actualizarTurnos();
        imprimirMenuOpTurnos ();
        fflush(stdin);
        scanf("%i", &op);
        switch(op){
            case 1:
                system("cls");
                imprimirHeader("   Turnos Reservados  ");
                imprimirTurnosXMedico(1);
                system("pause");
            break;
            case 2:
                system("cls");
                imprimirHeader("     Turnos Libres    ");
                imprimirTurnosXMedico(0);
                system("pause");
            break;
            case 3:
                system("cls");
                imprimirHeader("     Cargar Turno     ");
                cargarTurno();
                system("pause");
            break;
            case 4:
                system("cls");
                imprimirHeader("    Cancelar Turno    ");
                cancelarTurno();
                system("pause");
            break;
            case 5:
                system("cls");
                imprimirHeader("   Atender Paciente   ");
                atenderPaciente();
                system("pause");
            break;
            case 6:
                puts("Volver al menu principal? S/N\n");
                fflush(stdin);
                scanf("%c",&control);
            break;
            default:
                puts("OPCION INCORRECTA.");
            break;
        }
    }while (control!='s'&&control!='S');
}

void menuOpMedicos(){
    char control='n';
    int op;
    do{
        imprimirMenuOpMedicos();
        fflush(stdin);
        scanf("%i", &op);
        switch(op){
            case 1:
                system("cls");
                imprimirHeader("   Nomina de Medicos  ");
                listarMedicos();
                system("pause");
            break;
            case 2:
                system("cls");
                imprimirHeader("  Busqueda de Medicos ");
                buscarMed();
                system("pause");
            break;
            case 3:
                system("cls");
                imprimirHeader("   Carga de Medicos   ");
                cargaMedicos();
                system("pause");
            break;
            case 4:
                system("cls");
                imprimirHeader("   Eliminar Medicos   ");
                eliminarMedico();
                system("pause");
            break;
            case 5:
                system("cls");
                imprimirHeader("  Modificar Medicos   ");
                modificarMedicos();
                system("pause");
            break;
            case 6:
                puts("Volver al menu principal? S/N\n");
                fflush(stdin);
                scanf("%c",&control);
            break;
            default:
                puts("OPCION INCORRECTA.");
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
                system("cls");
                menuOpTurnos();
            break;
            case 3:
                system("cls");
                menuOpInternaciones();
            break;
            case 4:
                system("cls");
                menuOpMedicos();
            break;
            case 5:
                puts("\nDesea salir del sistema? S/N");
                fflush(stdin);
                flag=getchar();
                system("cls");
            break;
            default:
                puts("OPCION INCORRECTA.");
            break;
        }
    }while(flag!='s'&&flag!='S');
}
