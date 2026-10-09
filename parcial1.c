#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CARACTER 51

typedef struct {
	char Sector[MAX_CARACTER];
	char name_tanque[MAX_CARACTER];
	int nivel;
}Monitoreo;

void mostrarMenu();
void Lectura(Monitoreo *,int );
void mostrarMenorNivel(Monitoreo *,int); 
void limpiarBuffer();

int main() {
	int TAM=0;
	int OPC;
	Monitoreo *Tanques = NULL;

	printf("\n\n\t\t---Monitoreo de Tanques---\n\n");
	
	do{
		printf("Ingrese cantidad de Tanques: ");
		scanf("%d",&TAM);
		limpiarBuffer(); 
	} while(TAM <= 0); //do-while
	
	do{
		mostrarMenu();
		scanf("%d",&OPC);
		limpiarBuffer();  
		system("cls");
		
		switch(OPC){
		case 0:

			printf("Saliendo del programa.\n");
			break;
		case 1:

			Tanques = (Monitoreo *) realloc(Tanques, TAM * sizeof(Monitoreo));

			if (Tanques == NULL) {
				printf("Error: No se pudo asignar memoria para la cantidad de tanques.\n");
				return 0; 	
			} //if

			Lectura(Tanques,TAM);
			break;
		case 2:

			mostrarMenorNivel(Tanques,TAM);
			break;
		default:

			printf("Opcion no valida. Intente de nuevo.\n");
			break;
		}
		
	} while(OPC != 0);  //do-while

	free(Tanques);
}//main

void mostrarMenu() {
	printf("\n--- Sistema de Tanques ---\n");
	printf("1. Agregar Tanques\n");
	printf("2. Mostrar Tanques con Menor Nivel de Agua\n");
	printf("\n");
	printf("0. Salir\n");
	printf("\n");
	printf("Seleccione una opcion: ");
	return;
}//mostrarMenu

void Lectura(Monitoreo *Tanque, int T){
	char otroSector[MAX_CARACTER];
	char otroTanque[MAX_CARACTER];
	int i,L;

	if(Tanque == NULL){
		printf("Error: puntero de tanques NULL.\n");
		return;
	}	//if
	
	for(i=0;i<T;i++){
		
		printf("\nSector %d(hasta %d caracteres): ",	i,	MAX_CARACTER);
		fgets(otroSector, sizeof(otroSector), stdin);

		if (otroSector == NULL) {
			otroSector[0] = '\0';
		} else {
			L = strlen(otroSector);
			if (L > 0 && otroSector[L-1] == '\n'){
				otroSector[L-1] = '\0';
			} //if

		} //if-else

		strncpy(Tanque[i].Sector, otroSector,sizeof(Tanque[i].Sector)-1);
		Tanque[i].Sector[sizeof(Tanque[i].Sector)-1] = '\0';
		
		printf("\nNombre del Tanque %d (hasta %d caracteres): ",	i,	MAX_CARACTER);
		fgets(otroTanque, sizeof(otroTanque), stdin);

		if (otroTanque == NULL) {
			otroTanque[0] = '\0';
		} else {
			L = strlen(otroTanque);
			if (L > 0 && otroTanque[L-1] == '\n'){
				otroTanque[L-1] = '\0';
			} //if

		} //if-else
		
		strncpy(Tanque[i].name_tanque, otroTanque,sizeof(Tanque[i].name_tanque)-1);
		Tanque[i].name_tanque[sizeof(Tanque[i].name_tanque)-1] = '\0';
		
		do{
			printf("\nIngrese el Nivel de Agua (1%% - 100%%): ");
			scanf("%d",&Tanque[i].nivel);
			limpiarBuffer();
			
		} while(Tanque[i].nivel < 1 || Tanque[i].nivel >100); //do-while

	} //for
}//Lectura
	
void mostrarMenorNivel(Monitoreo *Tanque,	int T){
	int m1 = 0, m2 = 1;
	int i,t;

	if (T == 0) { 
		printf("No hay tanques cargados.\n"); 
		return; 
	} //if

	if (T == 1) {
		printf("Solo hay un tanque:\n");
		printf("Sector: %s | Nombre: %s | Nivel: %d%%\n", Tanque[0].Sector, Tanque[0].name_tanque, Tanque[0].nivel);
		return;
	} //if
	
	
	if (Tanque[m2].nivel < Tanque[m1].nivel) {
		t = m1; 
		m1 = m2; 
		m2 = t; 
	} //if
	
	for (i = 2; i < T; ++i) {
		if (Tanque[i].nivel < Tanque[m1].nivel) {
			m2 = m1;
			m1 = i;
		} else if (Tanque[i].nivel < Tanque[m2].nivel) {
			m2 = i;
		} //if-else if

	} //for
	
	printf("Dos tanques con menor nivel:\n");
	printf("1) Sector: %s | Nombre: %s | Nivel: %d%%\n", Tanque[m1].Sector, Tanque[m1].name_tanque, Tanque[m1].nivel);
	printf("2) Sector: %s | Nombre: %s | Nivel: %d%%\n", Tanque[m2].Sector, Tanque[m2].name_tanque, Tanque[m2].nivel);
	
}//mostrarMenorNivel

void limpiarBuffer(){
	int c;
	while ((c = getchar()) != EOF && c != '\n');
}//limpiarBuffer
			
