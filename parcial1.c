#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char Sector[51];
	char name_tanque[51];
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
		limpiarBuffer(); /* consumir el '\n' que deja scanf */
	} while(TAM <= 0);
	
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
			}
			Lectura(Tanques,TAM);
			break;
		case 2:
			mostrarMenorNivel(Tanques,TAM);
			break;
		default:
			printf("Opcion no valida. Intente de nuevo.\n");
			break;
		}
		
	} while(OPC != 0);
	free(Tanques);
	
}

void mostrarMenu() {
	printf("\n--- Sistema de Tanques ---\n");
	printf("1. Agregar Tanques\n");
	printf("2. Mostrar Tanques con Menor Nivel de Agua\n");
	printf("\n");
	printf("0. Salir\n");
	printf("\n");
	printf("Seleccione una opcion: ");
	return;
}
void Lectura(Monitoreo *Tanque, int T){
	char otroSector[51];
	char otroTanque[51];
	int i,L;

	if(Tanque == NULL){
		printf("Error: puntero de tanques NULL.\n");
		return;
	}
	
	for(i=0;i<T;i++){
		
		printf("\nSector %d(hasta 50 caracteres): ",i);
		fgets(otroSector, sizeof(otroSector), stdin);
		if (otroSector == NULL) {
			otroSector[0] = '\0';
		} else {
			L = strlen(otroSector);
			if (L > 0 && otroSector[L-1] == '\n'){
				otroSector[L-1] = '\0';
			}
		}
		strncpy(Tanque[i].Sector, otroSector,sizeof(Tanque[i].Sector)-1);
		Tanque[i].Sector[sizeof(Tanque[i].Sector)-1] = '\0';
		
		printf("Sector: %s\n", Tanque[i].Sector);  /* imprime el sector para verificar */
		
		printf("\nNombre del Tanque %d (hasta 50 caracteres): ",i);
		fgets(otroTanque, sizeof(otroTanque), stdin);
		if (otroTanque == NULL) {
			otroTanque[0] = '\0';
		} else {
			L = strlen(otroTanque);
			if (L > 0 && otroTanque[L-1] == '\n'){
				otroTanque[L-1] = '\0';
			}
		}
		
		strncpy(Tanque[i].name_tanque, otroTanque,sizeof(Tanque[i].name_tanque)-1);
		Tanque[i].name_tanque[sizeof(Tanque[i].name_tanque)-1] = '\0';
		
		printf("Nom. Tanque: %s\n", Tanque[i].name_tanque);  /* imprime el tanque para verificar */
		
		do{
			printf("\nIngrese el Nivel de Agua (1%% - 100%%): ");
			scanf("%d",&Tanque[i].nivel);
			limpiarBuffer();
			
		} while(Tanque[i].nivel < 1 || Tanque[i].nivel >100);
	}
}
	
	void mostrarMenorNivel(Monitoreo *Tanque,int T){
		int m1 = 0, m2 = 1;
		int i,t;
		if (T == 0) { 
			printf("No hay tanques cargados.\n"); 
			return; 
		}
		if (T == 1) {
			printf("Solo hay un tanque:\n");
			printf("Sector: %s | Nombre: %s | Nivel: %d%%\n", Tanque[0].Sector, Tanque[0].name_tanque, Tanque[0].nivel);
			return;
		}
		
		
		if (Tanque[m2].nivel < Tanque[m1].nivel) {
			t = m1; 
			m1 = m2; 
			m2 = t; 
		}
		
		for (i = 2; i < T; ++i) {
			if (Tanque[i].nivel < Tanque[m1].nivel) {
				m2 = m1;
				m1 = i;
			} else if (Tanque[i].nivel < Tanque[m2].nivel) {
				m2 = i;
			}
		}
		
		printf("Dos tanques con menor nivel:\n");
		printf("1) Sector: %s | Nombre: %s | Nivel: %d%%\n", Tanque[m1].Sector, Tanque[m1].name_tanque, Tanque[m1].nivel);
		printf("2) Sector: %s | Nombre: %s | Nivel: %d%%\n", Tanque[m2].Sector, Tanque[m2].name_tanque, Tanque[m2].nivel);
		
	}
		void limpiarBuffer(){
			int c;
			while ((c = getchar()) != EOF && c != '\n');
		}
			
