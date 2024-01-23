#ifndef __LIB_H__
#define __LIB_H__
//Por convenio se coloca un indenticador parecido al nombre del archivo
#include <stdbool.h>


typedef enum { NUM, DATE, EMAIL, TEXT} TYPE;


char static direccionArchivos[] = "./";



char static separadores[20] = " \n\r\t\b\v\f\0";

typedef struct tab {
	char nombre[100];
	int numCampos;
	char **campos;
	TYPE *tipos;
	struct tab *sig, *ant;
}TABLE;

typedef struct line
{
	char **valores;
	struct line *sig, *ant;
}ROW;


/*
*****************************************************
		Funciones Rutinarias
*****************************************************
													*/
char* MiStrTok(char *cad1, char *sep, bool comillas);
void EscribirPrompt(char *nombreBD, char *nombreTabla);
void intercambioValores(ROW *linea1, ROW *linea2);
TABLE *inicializarTabla(char *nomTabla, char ** campos, TYPE *tipos, int numCampos);
void EliminarTabla(TABLE *t);
void editar_meta(char *nombre_bd, TABLE *tabla);
void *toLoweCase(char *cadena);
void *toUpperCase(char *cadena);
void EscribirTabla(char *nombreTabla, TABLE *t, char *nombreBD);
ROW *cargarLineas(char *nombreBD, char *nombreTabla, int numCampos, TYPE *tipos);
void insertarUltimaLinea(ROW *linea, ROW *fila);
void EscribirTabla(char *nombreTabla, TABLE *t, char *nombreBD);
void crearTabla(char *nombreBD, char *nombreTabla, TABLE *t);
void actualizar_lineas(ROW *linea, TABLE *t, char *nombreBD);
void mostrarTablas(TABLE *t, char *nombreBD);
ROW *crearLinea(char ** valores);
void imprimirTodoDES(int numCampos, ROW *linea, TABLE *t, int campo);
ROW *cambiarCampoValor(ROW *linea, int posicion, char *campo, char *simbolo, char *valorNuevo, TYPE tipo);




													/*
*****************************************************
		Funciones de Impresion
*****************************************************
*/
void imprimirTodo(int numCampos, ROW *linea);
void imprimirEncabezados(TABLE *t);
void funcionamientoComandoList();
void funcionamientoComandoListVariante(char *nombreBD);
void imprimirTodoASC(int numCampos, ROW *lineaa, TABLE *t, int campo);
void imprimirValoresDeCampo(int numCampos, ROW *linea, TYPE tipos, char *valor, char *simbolo, int posicion);
/*
****************************************************
		Funciones de las Carpetas (Bases de Datos)
****************************************************
													*/

void CrearBD(char *nombreBD);
bool ComprobarBDExistente(char *nombreBD);
char *BuscarBDExistente(char *nombreBD);


/*
*********************************************
		Funciones de Ficheros
**********************************************
											*/
											

void EscribirEnFichero(char *nombreFichero, char *cadena);
int contar_tablas(char *nombre_bd);
void EscribirMETA(TABLE *primeraTabla, int numTablas, char *NombreBDEnUso);
char *ObtenerCampos(char *lin, char *sep, int id, char *val);
void Trim(char *cad);
TABLE *cargarTablas(char *nombreBD);
TABLE *BuscarTablaExistente(char *nombreTabla, TABLE *t);
void insertarUltimaTabla(TABLE *t, TABLE *tAux);
TABLE *renombrarTabla (TABLE *t,  char *nombreTabla, char *nombreNuevo, char *nombreBD);

/*
**************************************************
		Funciones de Validacion/Identificacion
**************************************************
												*/

bool ValidarNumero(char *cadena);
bool ValidarFecha(char *cadena);
TYPE DeterminarTipo(char *cadena);
TYPE IdentificarTipo(char *cadena);
bool ValidarEmail(char *cadena);
bool ValidarNombre(char *cadena);
bool ValidarRepeticionCampos(char **cadena, int numCampos);
bool ComprobarExistenciaTabla(char *nombreBD, char *nombreTabla);
/*
******************************************
		Funciones de Comparacion
******************************************
										*/
int numcmp(char *cadena,char* cadena2);
int datecmp(char *cadena, char *cadena2);
void ordenarASC(int campos, ROW *linea, TABLE *t);
void ordenarDES(int campo, ROW *linea, TABLE *t);

													/*
*****************************************************
		Liberacion De Memoria
*****************************************************
*/

void liberarMemoriaTabla(TABLE *t);
void liberarMemoriaLinea(ROW *linea, int numCampos);
ROW *eliminarLineaValor(int numCampos, ROW *linea, TYPE tipo, char *valor, char *simbolo, int posicion);
TABLE *borrarTabla(TABLE *t, char *nombreBD, char *nombreTabla);
TABLE *borrarBD (TABLE *t, char *nombreBD);




#endif 