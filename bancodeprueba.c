#include "headers.h"


void subMenuOpc3(int opc){
    switch(opc){
        case 1:
           imprimirMenuOp1();
        break;
        case 2:
            imprimirMenuOp2();
        break;
        case 3:
            imprimirMenuOp3();
        break;
        default:
            puts("OPCION INCORRECTA.");
            system("pause");
            system("cls");
            imprimirMenuPrincipal();
        break;
    }

}
void menuOp1swt(int op){
    PACIENTE pac[100];
    int cantRegistros;
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


void subMenuSwitchMenuP(int opciones){

    switch(opciones){
        case 1:
           imprimirMenuOp1();
        break;
        case 2:
            imprimirMenuOp2();
        break;
        case 3:
            imprimirMenuOp3();
        break;
        default:
            puts("OPCION INCORRECTA.");
            system("pause");
            system("cls");
            imprimirMenuPrincipal();
        break;
    }
}
int cargaPacientesPrueba (PACIENTE pac[],int dim){
    FILE *db;
    char opc;
    int i=0;
    if ((db=fopen(pathPac,"a+"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO\n");}
    do{
            printf("INGRESE NOMBRE Y APELLIDO\n");
            fflush(stdin);
            gets(pac[i].nombreApellido);
            fwrite(&pac[i].nombreApellido,sizeof(char),sizeNom,db);
            printf("INGRESE DNI\n");
            fflush(stdin);
            scanf("%i",&pac[i].dni);
            fwrite(&pac[i].dni,sizeof(int),1,db);
            printf("INGRESE EDAD\n");
            fflush(stdin);
            scanf("%i",&pac[i].edad);
            fwrite(&pac[i].edad,sizeof(int),1,db);
            printf("Desea continuar? S/N \n");
            fflush(stdin);
            scanf("%c",&opc);
            i++;
        }while (i<100 && (opc=='s'||opc=='S'));
    fclose(db);

    return i;
}
void mostrarPacientes(PACIENTE p[],int dim){
    FILE *db;
    int i=0;
    if((db=fopen(pathPac,"rb"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO\n");
    }
        for (i=0;i<dim;i++){
            fread(p[i].nombreApellido,sizeof(char),sizeNom,db);
            printf("\nNOMBRE Y APELLIDO: %s",p[i].nombreApellido);
            fread(&p[i].dni,sizeof(int),1,db);
            printf("\t\tDNI: %i",p[i].dni);
            fread(&p[i].edad,sizeof(int),1,db);
            printf("\t\tEDAD: %i",p[i].edad);
            fread(&p[i].cantAtendido,sizeof(int),1,db);
            printf("\t\tCANTIDAD DE VECES ATENDIDO: %i",p[i].cantAtendido);
            fread(&p[i].eliminado,sizeof(int),1,db);
            printf("\t\tESTADO: %i 1.ACTIVO 2.ELIMINADO",p[i].eliminado);
        }

    fclose(db);
}


