#include "headers.h"

void menuOp1(int op){
    PACIENTE pac;
    char opc;
    switch(op){
        case 1:
            system("pause");
            system("cls");
            buscarPaciente();
            break;
        case 2:
            system("pause");
            system("cls");
            cargaPacientesPrueba(pac,100);
            break;
        case 3:
            system("pause");
            system("cls");
            modificarPac();
            break;
        case 4:
            system("pause");
            system("cls");
            eliminarPac();
            break;
        case 5:
            system("pause");
            system("cls");
            puts("Volver al menu principal? \n");
            fflush(stdin);
            scanf("%c",&opc);
            if (opc=='s'||opc=='S'){
                imprimirMenuPrincipal();
            }else{
                system("pause");
                system("cls");
                imprimirMenuOp1();
            }
            break;
    }
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
                imprimirMenuOp1();
            break;
            case 2:
                imprimirMenuOp2();
            break;
            case 3:
                imprimirMenuOp3();
            break;
            case 4:
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
    } while (flag!='S'||flag!='s');
}
