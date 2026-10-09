#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CARACTER 51

/*	Estructura para el Monitoreo de Tanques	 */
typedef struct {
	char Sector[MAX_CARACTER];
	char name_tanque[MAX_CARACTER];
	int nivel;
}Monitoreo;

/*	Prototipos	*/
void mostrarMenu();
void Lectura(Monitoreo *Tanque,	 int T);
void mostrarMenorNivel(Monitoreo *Tanque,	int T); 
void limpiarBuffer();

int main() {
	int cantidad=0;
	int OPC;
	Monitoreo *Tanques = NULL;

	printf("\n\n\t\t---Monitoreo de Tanques---\n\n");
	
	do{
		printf("Ingrese cantidad de Tanques: ");
		scanf("%d",	&cantidad);
		limpiarBuffer(); 
	} while(cantidad <= 0); //do-while
	
	do{
		mostrarMenu();
		scanf("%d",	&OPC);
		limpiarBuffer();  
		
		switch(OPC){
		case 0:

			printf("Saliendo del programa.\n");
			break;
		case 1:
			/*	Reasigno memoria para todos los tanques a cargar	*/
			Tanques = (Monitoreo *) realloc(Tanques, cantidad * sizeof(Monitoreo));

			if (Tanques == NULL) {
				printf("Error: No se pudo reasignar memoria.\n");
				return 0; 	
			} //if

			/*	Leo todos los datos	actuales	*/
			Lectura(Tanques,	cantidad);
			break;
		case 2:
			/*	Muestro todos los 2 Tanques con menor Nivel de Agua	*/
			mostrarMenorNivel(Tanques,	cantidad);
			break;
		default:

			printf("Opcion no valida. Intente de nuevo.\n");
			break;
		}
		
	} while(OPC != 0);  //do-while

	free(Tanques);
}//main

/*	Muestro todas las opciones para la insercion y mostrado de datos	*/
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

/*	Se leen todos los datos de cada Tanque ->Sector, Nombre y Nivel de Agua Almacenada en %	*/
void Lectura(Monitoreo *Tanque, int T){
	char otroSector[MAX_CARACTER];
	char otroTanque[MAX_CARACTER];
	int i,longitudCadena;

	if(Tanque == NULL){
		printf("Error: puntero de tanques NULL.\n");
		return;
	}	//if
	
	for(i = 0; i < T; i++){
		
		/*	Ingresar Sector	*/
		printf("\nSector %d(hasta %d caracteres): ",	i,	MAX_CARACTER);
		fgets(otroSector, sizeof(otroSector), stdin);

		if (otroSector == NULL) {
			otroSector[0] = '\0';
		} else {
			longitudCadena = strlen(otroSector);
			if (longitudCadena > 0 && otroSector[longitudCadena-1] == '\n'){
				otroSector[longitudCadena-1] = '\0';
			} //if
		} //if-else

		/*	Cargado de Sector en estructura Monitoreo	*/
		strncpy(Tanque[i].Sector, otroSector,sizeof(Tanque[i].Sector)-1);
		Tanque[i].Sector[sizeof(Tanque[i].Sector)-1] = '\0';
		
		/*	Ingresar Nombre del Tanque	*/
		printf("\nNombre %d (hasta %d caracteres): ",	i,	MAX_CARACTER);
		fgets(otroTanque, sizeof(otroTanque), stdin);

		if (otroTanque == NULL) {
			otroTanque[0] = '\0';
		} else {
			longitudCadena = strlen(otroTanque);
			if (longitudCadena > 0 && otroTanque[longitudCadena - 1] == '\n'){
				otroTanque[longitudCadena - 1] = '\0';
			} //if
		} //if-else
		
		/*	Cargado de Nombre del Tanque en estructura Monitoreo	*/
		strncpy(Tanque[i].name_tanque, otroTanque,sizeof(Tanque[i].name_tanque)-1);
		Tanque[i].name_tanque[sizeof(Tanque[i].name_tanque)-1] = '\0';
		
		/*	Ingresar Nivel del Agua para cada Tanque	*/
		do{
			printf("\nIngrese el Nivel de Agua (1%% - 100%%): ");
			scanf("%d",&Tanque[i].nivel);
			limpiarBuffer();
			
		} while(Tanque[i].nivel < 1 || Tanque[i].nivel >100); //do-while

	} //for
}//Lectura
	
/*	Se busca mostrar los 2 Tanques con menor nivel de Agua	*/
void mostrarMenorNivel(Monitoreo *Tanque,	int T){
	int m1 = 0, m2 = 1;
	int i,t;

	if (Tanque == NULL || T == 0) {
    printf("No hay tanques cargados.\n");
    return;
	} //if

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

/*	Se usa para vaciar el buffer de entrada del teclado después de leer datos con scanf		*/
void limpiarBuffer(){
	int c;
	while ((c = getchar()) != EOF && c != '\n');
}//limpiarBuffer
			
