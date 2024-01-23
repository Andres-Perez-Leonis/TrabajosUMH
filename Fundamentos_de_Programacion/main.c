#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <conio.h>

#include <unistd.h>
#include <dirent.h>

#include "librerias.h"


int main()
{
	char cadena[1000], cadenaAux[1000];
	char *token = '\0';
	char *token2 = '\0';
	char *token3 = '\0';
	char *nombreBD, *nombreTabla;
	char NombreBDEnUso[100] = "", nombreTablaEnUso[100] = "";
	char **elementos = NULL;
	char **parametrosSelect = NULL;
	char **parrametrosDelete = NULL;
	char **parametrosList = NULL;
	char **parametrosRemove = NULL;
	char **parametrosOrder = NULL;
	char **parametrosImport = NULL;
	int errores = 0;
	int errorDelete = 0;
	int campoExistente = 0;
	char *campos[100];
	int numErrores = 0;
	TYPE tipos[100];
	int numCampos = 0;
	int numElementos = 0;
	char *auxNombres = NULL;
	char *aux2;
	int numTablas = 0;
	TABLE *t = NULL, *tabla = NULL, *tablaActual = NULL, *tCopia = NULL, *tImport = NULL;
	FILE *f;
	ROW *lineaEnUso = NULL, *linea = NULL, *lineaImport = NULL, *lineaCopia = NULL;
	int numComillas = 0;


	printf("-Nombre: Andres Perez Leonis\n-Email: andres.perez05@goumh.umh.es\n\n----------------------------\n\n");
	printf("Examen Fundamentos de Programcion\n\nEjercicio 1 -> HECHO\nEjercicio 2 -> HECHO\nEjercicio 3 -> HECHO\nEjercicio 4 -> HECHO\n\n");

	while (true)
	{
		EscribirPrompt(NombreBDEnUso, nombreTablaEnUso);
		gets(cadenaAux);
		strcpy(cadena, cadenaAux);

		token = MiStrTok(cadena, separadores, false);
		if (token == NULL || strcmp(token, "") == 0)
		{
			continue;
		}
		
		token2 = MiStrTok(NULL, separadores, true);

		if (strcmp(token, "exit") == 0)
		{
			if (token2 != NULL)
				printf("Error: El comando exit no tiene parametros\n");
			else
			{
				//Liberamos de memoria toda la memoria que hemmos podido reservar durante la ejecucion del programa
				if(parametrosSelect != NULL) { 
					for(int i = 0; i < 5; i++) {
						free(parametrosSelect[i]);
					}
					free(parametrosSelect);
				}



				if(parrametrosDelete != NULL) {
					for(int i = 0; i < 5; i++) {
						free(parrametrosDelete[i]);
					}
					free(parrametrosDelete);
				}

				if(elementos != NULL) {
					for(int i = 0; i < numElementos; i++) {
						free(elementos[i]);
					}
					free(elementos);
				}
				if (auxNombres != NULL)
				{
					free(auxNombres);
					auxNombres = NULL;
				}
				if (linea != NULL)
				{
					liberarMemoriaLinea(linea, t -> numCampos);
				}

				if (lineaEnUso != NULL)
				{
					liberarMemoriaLinea(lineaEnUso, t-> numCampos);
				}
				if(tablaActual != NULL) {
					liberarMemoriaTabla(tablaActual);
					tablaActual = NULL;
				}
				if (t != NULL)
				{
					liberarMemoriaTabla(t);
					t = NULL;
				}
				if (t == NULL && tablaActual == NULL)
				{
					return 0;
				}
				else
				{
					printf("ERROR: No se ha podido liberar la memoria de las tablas\n");
				}
			}
		}
		else if (strcmp(token, "new") == 0)
		{

			if (token2 != NULL)
			{
				if (strcmp(token2, "db") == 0)
				{
					auxNombres = MiStrTok(NULL, separadores, false);
					nombreBD = auxNombres;
					if (nombreBD != NULL)
					{
						if (ValidarNombre(nombreBD))
						{
							token2 = MiStrTok(NULL, separadores, false);

							if (token2 == NULL)
							{
								if (ComprobarBDExistente(nombreBD))
								{
									CrearBD(nombreBD);
								}
								else
								{
									printf("ERROR: Esa Base de Datos ya existe\n");
								}
							}
							else
							{
								printf("ERROR: Demasiados parametros\n");
							}
						}
						else
						{
							printf("ERROR: Nombre no admitido\n");
						}
					}
					else
					{
						printf("ERROR: 'New db' debe tener un parametro\n");
					}
				}
				else if (strcmp(token2, "table") == 0)
				{
					if (strcmp(NombreBDEnUso, "") != 0)
					{
						auxNombres = MiStrTok(NULL, separadores, false);
						if (auxNombres != NULL)
						{
							nombreTabla = auxNombres;
						}
						else
						{
							printf("No has escrito el nombre\n");
							continue;
						}
						if (!ComprobarExistenciaTabla(NombreBDEnUso, nombreTabla))
						{
							if (ValidarNombre(nombreTabla))
							{
								numCampos = 0;
								errores = 0;
								while ((token = MiStrTok(NULL, separadores, false)) != NULL)
								{
									campos[numCampos] = strdup(token);
									token2 = MiStrTok(NULL, separadores, false);
									if (token2 == NULL)
									{
										printf("ERROR: Numero de parametros incorrectos\n");
										break;
									}
									tipos[numCampos] = IdentificarTipo(token2);
									if (tipos[numCampos] == -1)
									{
										printf("ERROR: Parametro 'tipo' incorrecto\n");
										errores++;
										break;
									}
									printf("Campo: %s Tipo: %d\n", campos[numCampos], tipos[numCampos]);
									numCampos++;
									
								}
								

								if (ValidarRepeticionCampos(campos, numCampos))
								{
									printf("ERROR: Campos Repetidos\n");
									for (int i = 0; i < numCampos; i++)
									{
										campos[i] = "";
										tipos[i] = -1;
									}
									continue;
								}
								else if (numCampos == 0)
								{
									printf("ERROR: Numero de parametros erroneos\n");
									continue;
								}
								else if(errores != 0) {
									for (int i = 0; i < numCampos; i++)
									{
										campos[i] = "";
										tipos[i] = -1;
									}
									continue;
								}
								else
								{
									
									tabla =	inicializarTabla(nombreTabla, campos,tipos, numCampos);
									if (tabla != NULL)
									{
										if (t == NULL)
										{
											t = tabla;
											crearTabla(NombreBDEnUso, nombreTabla, t);
										}
										else
										{
											insertarUltimaTabla(t, tabla);
											crearTabla(NombreBDEnUso, nombreTabla, t);
											//editar_meta(NombreBDEnUso, t);
										}
										numTablas++;
										for (int i = 0; i < numCampos; i++)
										{
											campos[i] = "";
											tipos[i] = -1;
										}
									}
									else
									{
										printf("ERROR inesperado\n");
									}
								}
							}
							else
							{
								printf("ERROR: No es un nombre valido\n");
							}
						}
						else
						{
							printf("ERROR: Tabla ya creada\n");
						}
					}
					else
					{
						printf("ERROR: No se ha indicado una Base de Datos\n");
					}
				}
				else
				{
					printf("ERROR: Comando  Incorrecto\n");
				}
			}
			else
			{
				printf("ERROR: Comando Incorrecto\n");
			}
		}
		else if (strcmp(token, "use") == 0)
		{
			if (token2 != NULL)
			{
				if (strcmp(token2, "db") == 0)
				{
					auxNombres = MiStrTok(NULL, separadores, false);
					nombreBD = auxNombres;
					if (nombreBD != NULL)
					{
						aux2 = BuscarBDExistente(nombreBD);
						token3 = MiStrTok(NULL, separadores, false);
						if(token3 == NULL) {
							if (aux2 == NULL)
								printf("ERROR: La base de datos NO existe\n");
							else
							{
								
								if (t != NULL)
								{
									if(linea != NULL) {
										liberarMemoriaLinea(linea, t -> numCampos);
										linea = NULL;
									}
									
									liberarMemoriaTabla(t);
									t = NULL;
								}
								if(strcmp(nombreTablaEnUso, "") != 0) {
									strcpy(nombreTablaEnUso,"");
								}
								t = cargarTablas(nombreBD);
								strcpy(NombreBDEnUso, nombreBD);
								if(t != NULL) {
									mostrarTablas(t, nombreBD);
								}else {
									printf("No se ha encontrado ninguna tabla\n");
								}
							}
						}else {
							printf("ERROR: Parametros incorrectos\n");
						}
					}
					else
					{
						printf("ERROR: El comando 'use db' debe tener un parametro\n");
					}
				}
				else if (strcmp(token2, "table") == 0)
				{
					if (strcmp(NombreBDEnUso, "") != 0)
					{
						nombreTabla = MiStrTok(NULL, separadores, false);
						if (nombreTabla != NULL)
						{
							if (ComprobarExistenciaTabla(NombreBDEnUso, nombreTabla))
							{
								token = MiStrTok(NULL, separadores, false);
								if (token == NULL)
								{
									if (linea != NULL)
									{
										liberarMemoriaLinea(linea, t->numCampos);
										linea = NULL;
									}
									tablaActual = BuscarTablaExistente(nombreTabla, t);
									linea = malloc(sizeof(ROW));
									lineaEnUso = cargarLineas(NombreBDEnUso, nombreTabla, tablaActual -> numCampos, tablaActual -> tipos);
									linea = lineaEnUso; 
									if (tablaActual != NULL)
										strcpy(nombreTablaEnUso, nombreTabla);
									else
										printf("ERROR: No existe la tabla\n");
								}
								else
								{
									printf("ERROR: Demasiados parametros introducidos\n");
								}
							}
							else
							{
								printf("ERROR: Tabla no creada\n");
							}
						}
						else
						{
							printf("ERROR: No se ha introducido el nombre de la tabla\n");
						}
					}
					else
					{
						printf("ERROR: No hay ninguna Base de Datos en Uso\n");
					}
				}
				else
				{
					printf("ERROR: Comando Incorrecto\n");
				}
			}
			else
			{
				printf("ERROR: Comando Incorrecto\n");
			}
		}
		else if (strcmp(token, "insert") == 0)
		{
			if (strcmp(NombreBDEnUso, "") != 0)
			{
				if (tablaActual != NULL)
				{
					numComillas = 0;
					elementos = malloc(sizeof(char *) * tablaActual->numCampos);
					for (int i = 0; i <= strlen(cadenaAux); i++)
					{
						if (cadenaAux[i] == '"')
							numComillas++;
					}
					if (numComillas % 2 == 0 && numComillas != 0)
					{
						numElementos = 0;
						elementos[numElementos] = strdup(token2);
						numElementos++;
						if (token2 == NULL)
						{
							printf("ERROR: No has introducido parametros\n");
							continue;
						}
						while ((token2 = MiStrTok(NULL, separadores, true)) != NULL)
						{
							elementos[numElementos] = strdup(token2);
							numElementos++;
						}
						if (numElementos == tablaActual->numCampos)
						{
							numErrores = 0;
							for (int j = 0; j < tablaActual -> numCampos; j++)
							{
								if (tablaActual->tipos[j] == NUM)
								{
									if (!ValidarNumero(elementos[j]))
									{
										printf("ERROR: Numero no valido\n");
										numErrores++;
										break;
									}
								}
								else if (tablaActual->tipos[j] == DATE)
								{
									if (!ValidarFecha(elementos[j]))
									{
										printf("ERROR: Fecha no valida\n");
										numErrores++;
										break;
									}
								}
								else if (tablaActual->tipos[j] == EMAIL)
								{
									if (!ValidarEmail(elementos[j]))
									{
										printf("ERROR: E-mail no valido\n");
										numErrores++;
										break;
									}
								}
								else if (tablaActual->tipos[j] == TEXT)
								{
									//Aqui no hay que poner nada ya que con el text todo esta permitido
								}
							}
						}
						else
						{
							printf("ERROR: Numero de parametros incorrecto\n");
							continue;
						}
					}
					else if (numComillas == 0)
					{
						numElementos = 0;
						numErrores = 0;
						elementos[numElementos] = strdup(token2);
						numElementos++;
						if (token2 == NULL)
						{
							printf("ERROR: No has introducido parametros\n");
							continue;
						}
						while ((token2 = MiStrTok(NULL, separadores, false)) != NULL)
						{
							elementos[numElementos] = strdup(token2);
							numElementos++;
						}
						if (numElementos == tablaActual->numCampos)
						{
							numErrores = 0;
							for (int j = 0; j < tablaActual -> numCampos; j++)
							{
								if (tablaActual->tipos[j] == NUM)
								{
									if (!ValidarNumero(elementos[j]))
									{
										printf("ERROR: Numero no valido\n");
										numErrores++;
										break;
									}
								}
								else if (tablaActual->tipos[j] == DATE)
								{
									if (!ValidarFecha(elementos[j]))
									{
										numErrores++;
										printf("ERROR: Fecha no valida\n");
										break;
									}
								}
								else if (tablaActual->tipos[j] == EMAIL)
								{
									if (!ValidarEmail(elementos[j]))
									{
										numErrores++;
										printf("ERROR: E-mail no valido\n");
										break;
									}
								}
								else if (tablaActual->tipos[j] == TEXT)
								{
									//Aqui no hay que poner nada ya que con el text todo esta permitido
								}
							}
						}
						else
						{
							printf("ERROR: Numero de parametros incorrecto\n");
							continue;
						}
					}
					else
					{
						printf("ERROR: Las comillas van a pares\n");
						continue;
					}
					if(numErrores != 0) {
						continue;
					}
					lineaEnUso = crearLinea(elementos);
					if (lineaEnUso != NULL)
					{
						if (linea == NULL)
						{
							linea = lineaEnUso;
							actualizar_lineas(linea, tablaActual, NombreBDEnUso);
						}
						else
						{
							insertarUltimaLinea(linea, lineaEnUso);
							actualizar_lineas(linea, tablaActual, NombreBDEnUso);
						}
					}
					else
					{
						printf("ERROR de punteros\n");
					}
				}
				else
				{
					printf("ERROR: Tabla no activada\n");
				}
			}
			else
			{
				printf("ERROR: Debe de haber una Base de Datos activa\n");
			}
		}
		else if (strcmp(token, "list") == 0)
		{
			if(parametrosList != NULL) {
				for(int i = 0; i < numElementos; i++) {
					free(parametrosList[i]);
				}
				free(parametrosList);
			}
			numElementos = 0;
			parametrosList = malloc(sizeof(char*) * 2);
			if(token2 == NULL) {
				printf("ERROR: Numero de parametros incorrecto\n");
				continue;
			}
			parametrosList[numElementos] = strdup(token2);
			numElementos++;
			while((token2 = MiStrTok(NULL, separadores, false)) != NULL && numElementos < 2) {
				parametrosList[numElementos] = strdup(token2);
				numElementos++;
			}

			if (numElementos == 1)
			{
				if(strcmp(parametrosList[0], "db") == 0) {
					funcionamientoComandoList();
				}
				else if(strcmp(parametrosList[0], "table") == 0) {
					if(strcmp(NombreBDEnUso, "") != 0) {
						funcionamientoComandoListVariante(NombreBDEnUso);
					}
					else {
						printf("ERROR: Base de Datos no Activada\n");
					}
				}else {
					printf("ERROR: El comando list solo acepta los parametros (db/table)\n");
				}
			}
			else
			{
				printf("ERROR: Numero de parametros incorrecto\n");
			}
		}
		else if (strcmp(token, "select") == 0)
		{
			if(strcmp(nombreTablaEnUso, "") != 0 && strcmp(NombreBDEnUso, "") != 0) {
				
				numComillas = 0;
				errores = 0;
				campoExistente = 0;
				parametrosSelect = malloc(sizeof(char*) * 5);

				if(token2 != NULL) {
					for(int i = 0; i < strlen(cadenaAux); i++) {
						if(cadenaAux[i] == '"') 
							numComillas++;
					}
				
					if(tablaActual == NULL || tablaActual -> numCampos == 0) {
						printf("ERROR: Algo ha pasado\n");
						continue;
					}
					numElementos = 0;

					parametrosSelect[numElementos] = strdup(token2);
				
					numElementos++;
					
				}else {//SELECT
					imprimirTodo(tablaActual -> numCampos, linea);
					continue;
				}
				if(numComillas%2 == 0 && numComillas != 0 && parametrosSelect[0] != NULL) {
					
					while((token2 = MiStrTok(NULL, separadores, true)) != NULL) {
							parametrosSelect[numElementos] = strdup(token2);
							numElementos++;
						}
				
					if(numElementos == 1) { //SELECT ASC/DES
						if(strcmp(parametrosSelect[0], "ASC") == 0) {
							imprimirTodoASC(tablaActual -> numCampos, linea, tablaActual, 0); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
						}else if(strcmp(parametrosSelect[0], "DES") == 0) {
							imprimirTodoDES(tablaActual -> numCampos, linea, tablaActual, 0);
						}else {
							printf("ERROR: Parametros admitidos para este caso (ASC/DES)\n");
						}

					}else if(numElementos == 3) {//SELECT CAMPO >/</= DATO 
						for(int i = 0; i < tablaActual -> numCampos; i++) {
							if(strcmp(tablaActual -> campos[i], parametrosSelect[0]) == 0) {
								campoExistente++;
								if(tablaActual -> tipos[i] == NUM && ValidarNumero(parametrosSelect[2])) {
									imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);
									break;
								}else if(tablaActual -> tipos[i] == DATE && ValidarFecha(parametrosSelect[2])) {
									
									imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);
									break;
								}else if(tablaActual -> tipos[i] == EMAIL && ValidarEmail(parametrosSelect[2])) {
									imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);

									break;
								}else if(tablaActual -> tipos[i] == TEXT && ValidarNombre(parametrosSelect[2])) {
									imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);

									break;
								}
							}
						}

					}else if(numElementos == 4) {//SELECT CAMPO >/</= DATO ASC/DES
						if(strcmp(parametrosSelect[3], "ASC") == 0) {
							for(int i = 0; i < tablaActual -> numCampos; i++) {
								if(strcmp(tablaActual -> campos[i], parametrosSelect[0]) == 0) {
									campoExistente++;
									if(tablaActual -> tipos[i] == NUM && ValidarNumero(parametrosSelect[2])) {
										ordenarASC(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);
										break;
									}else if(tablaActual -> tipos[i] == DATE && ValidarFecha(parametrosSelect[2])) {
										ordenarASC(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);
										break;
									}else if(tablaActual -> tipos[i] == EMAIL && ValidarEmail(parametrosSelect[2])) {
										ordenarASC(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)

										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);

										break;
									}else if(tablaActual -> tipos[i] == TEXT && ValidarNombre(parametrosSelect[2])) {
										ordenarASC(0,linea, t); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);

										break;
									}else {
										printf("ERROR: Tipos erroneos\n");
									}
								}
							}
					    }else if(strcmp(parametrosSelect[3], "DES") == 0)  {
							for(int i = 0; i < tablaActual -> numCampos; i++) {
								if(strcmp(tablaActual -> campos[i], parametrosSelect[0]) == 0) {
									campoExistente++;
									if(tablaActual -> tipos[i] == NUM && ValidarNumero(parametrosSelect[2])) {
										ordenarDES(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);
										break;
									}else if(tablaActual -> tipos[i] == DATE && ValidarFecha(parametrosSelect[2])) {
										ordenarDES(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);
										break;
									}else if(tablaActual -> tipos[i] == EMAIL && ValidarEmail(parametrosSelect[2])) {
										ordenarDES(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)

										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);

										break;
									}else if(tablaActual -> tipos[i] == TEXT && ValidarNombre(parametrosSelect[2])) {
										ordenarDES(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);

										break;
									}else {
										printf("ERROR: Tipos erroneos\n");
									}
								}
							}
						}else {
							printf("ERROR: Parametros erroneos\n");
						}
					}else {
						printf("ERROR: Numero de parametros incorrecto\n");
					}
					


				}else if(numComillas == 0 && parametrosSelect[0] != NULL) {
					while((token2 = MiStrTok(NULL, separadores, false)) != NULL && numElementos <= 5) {
						parametrosSelect[numElementos] = strdup(token2);
						numElementos++;
					}


					if(numElementos == 1) { //SELECT ASC/DES
						if(strcmp(parametrosSelect[0], "ASC") == 0) {
							imprimirTodoASC(tablaActual -> numCampos, linea, tablaActual, 0); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
						}else if(strcmp(parametrosSelect[0], "DES") == 0) {
							imprimirTodoDES(tablaActual -> numCampos, linea, tablaActual, 0);

						}else {
							printf("ERROR: Parametros admitidos para este caso (ASC/DES)\n");
						}

					}else if(numElementos == 3) { //SELECT CAMPO >/</= DATO 
						for(int i = 0; i < tablaActual -> numCampos; i++) {
							if(strcmp(tablaActual -> campos[i], parametrosSelect[0]) == 0) {
								campoExistente++;
								if(tablaActual -> tipos[i] == NUM && ValidarNumero(parametrosSelect[2])) {
									
									imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);
									break;
								}else if(tablaActual -> tipos[i] == DATE && ValidarFecha(parametrosSelect[2])) {
									
									imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);
									break;
								}else if(tablaActual -> tipos[i] == EMAIL && ValidarEmail(parametrosSelect[2])) {
									imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);

									break;
								}else if(tablaActual -> tipos[i] == TEXT && ValidarNombre(parametrosSelect[2])) {
									imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);

									break;
								}else {
									printf("ERROR: Tipos erroneos\n");
								}
							}
						}
					}else if(numElementos == 4) {//SELECT CAMPO >/</= DATO ASC/DES
						if(strcmp(parametrosSelect[3], "ASC") == 0) {
							for(int i = 0; i < tablaActual -> numCampos; i++) {
								if(strcmp(tablaActual -> campos[i], parametrosSelect[0]) == 0) {
									campoExistente++;
									if(tablaActual -> tipos[i] == NUM && ValidarNumero(parametrosSelect[2])) {
										ordenarASC(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);
										break;
									}else if(tablaActual -> tipos[i] == DATE && ValidarFecha(parametrosSelect[2])) {
										ordenarASC(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);
										break;
									}else if(tablaActual -> tipos[i] == EMAIL && ValidarEmail(parametrosSelect[2])) {
										ordenarASC(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)

										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);

										break;
									}else if(tablaActual -> tipos[i] == TEXT && ValidarNombre(parametrosSelect[2])) {
										ordenarASC(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);

										break;
									}else {
										printf("ERROR: Tipos erroneos\n");
									}
								}
							}
					    }else if(strcmp(parametrosSelect[3], "DES") == 0)  {
							for(int i = 0; i < tablaActual -> numCampos; i++) {
								if(strcmp(tablaActual -> campos[i], parametrosSelect[0]) == 0) {
									campoExistente++;
									if(tablaActual -> tipos[i] == NUM && ValidarNumero(parametrosSelect[2])) {
										ordenarDES(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);
										break;
									}else if(tablaActual -> tipos[i] == DATE && ValidarFecha(parametrosSelect[2])) {
										ordenarDES(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);
										break;
									}else if(tablaActual -> tipos[i] == EMAIL && ValidarEmail(parametrosSelect[2])) {
										ordenarDES(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)

										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);

										break;
									}else if(tablaActual -> tipos[i] == TEXT && ValidarNombre(parametrosSelect[2])) {
										ordenarDES(0,linea, tablaActual); //Si en el examen nos piden que el selec funcione para cualquier campo de la table cambiar el 0 por el campo requerido (se tendra que guaardar en una variable)
					
										imprimirValoresDeCampo(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parametrosSelect[2], parametrosSelect[1], i);

										break;
									}else {
										printf("ERROR: Tipos erroneos\n");
									}
								}
							}
						}else {
							printf("ERROR: Parametros erroneos\n");
						}
						if(campoExistente == 0) printf("ERROR: Campo NO existente\n");
					}else {
						printf("ERROR: Numero de parametros incorrecto\n");
					}
				}else if(numComillas != 0 && numComillas%2 != 0){
					printf("ERROR: Las comillas van a pares\n");
				}
				
				if(campoExistente == 0 && (numElementos	== 3 || numElementos == 4)) printf("ERROR: Campo NO existente\n");
			}else {
				printf("ERROR: No hay Base de Datos o una Tabla activa\n");
			}
		}
		else if (strcmp(token, "delete") == 0)
		{
			if(strcmp(NombreBDEnUso,"") != 0) {
				if(t != NULL || strcmp(nombreTablaEnUso, "") != 0) {
					numComillas = 0;
					numElementos = 0;
					errorDelete = 0;
					campoExistente = 0;

					parrametrosDelete = malloc(sizeof(char*) * 4);
					if(token2 != NULL) {
						for(int i = 0; i < strlen(cadenaAux); i++) {
							if(cadenaAux[i] == '"') numComillas++;
						
						}
						parrametrosDelete[numElementos] = strdup(token2);
						numElementos++;


						
						if(numComillas == 0) {
							while((token2 = MiStrTok(NULL, separadores, false)) != NULL && numElementos <= 4) {
								parrametrosDelete[numElementos] = strdup(token2);
								numElementos++;
							}

							for(int i = 0; i < numElementos; i++) {
								if(parrametrosDelete[i] == NULL) {
									errorDelete++;
								}
							}


						}else if(numComillas%2 == 0 && numComillas != 0) {
							while((token2 = MiStrTok(NULL, separadores, true)) != NULL && numElementos <= 4) {
								parrametrosDelete[numElementos] = strdup(token2);
								numElementos++;
							}

							for(int i = 0; i < numElementos; i++) {
								if(parrametrosDelete[i] == NULL) {
									errorDelete++;
								}
							}


						}else {
							printf("ERROR: Las comillas van a pares\n");
						}


					
						if(errorDelete != 0 || numElementos == 4) {
							printf("ERROR: Parametros incorrectos\n");
							continue;
						}



						for(int i = 0; i < tablaActual -> numCampos; i++) {//delete campo "simbolo" valor

							if(strcmp(tablaActual -> campos[i], parrametrosDelete[0]) == 0) {

								if(tablaActual -> tipos[i] == NUM && ValidarNumero(parrametrosDelete[2])) {
									campoExistente++;
									linea = eliminarLineaValor(tablaActual -> numCampos, linea,tablaActual -> tipos[i] ,parrametrosDelete[2], parrametrosDelete[1], i);
									actualizar_lineas(linea, tablaActual, NombreBDEnUso);
									break;
								}else if(tablaActual -> tipos[i] == DATE && ValidarFecha(parrametrosDelete[2])) {
									linea = eliminarLineaValor(tablaActual -> numCampos, linea,tablaActual -> tipos[i],parrametrosDelete[2], parrametrosDelete[1], i);
									actualizar_lineas(linea, tablaActual, NombreBDEnUso);
									break;
								}else if(tablaActual -> tipos[i] == EMAIL && ValidarEmail(parrametrosDelete[2])) {
									linea = eliminarLineaValor(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parrametrosDelete[2], parrametrosDelete[1], i);
									actualizar_lineas(linea, tablaActual, NombreBDEnUso);
									break;
								}else if(tablaActual -> tipos[i] == TEXT && ValidarNombre(parrametrosDelete[2])) {
									linea = eliminarLineaValor(tablaActual -> numCampos, linea, tablaActual -> tipos[i], parrametrosDelete[2], parrametrosDelete[1], i);
									actualizar_lineas(linea, tablaActual, NombreBDEnUso);
									break;
								}else {
									printf("ERROR: Tipos erroneos\n");
								}
							}
							
						}
					}else {
						printf("ERROR: Parametros erroneos\n");
					}

					if(campoExistente == 0) printf("ERROR: Campo NO Existente\n");


				}else {
					printf("ERROR: Active una tabla \n");
				}

			}else {
				printf("ERROR: Active una base de datos\n");
			}
		}
		else if(strcmp(token, "remove") == 0)
		{
			if(token2 != NULL) {
				if(strcmp(NombreBDEnUso, "") != 0) {
					if(parametrosRemove != NULL) {
						for(int i = 0; i < numElementos; i++) {
							free(parametrosRemove[i]);
						}
						free(parametrosRemove);
					}
					parametrosRemove = malloc(sizeof(char*) * 2);
					numElementos = 0;
					parametrosRemove[numElementos] = strdup(token2);
					numElementos++;
					while((token2 = MiStrTok(NULL, separadores, false)) != NULL && numElementos < 2) {
						parametrosRemove[numElementos] = strdup(token2);
						numElementos++;
					}
					if(numElementos == 1) {
						nombreTabla = strdup(parametrosRemove[0]);
						if(ComprobarExistenciaTabla(NombreBDEnUso, nombreTabla)) {
							liberarMemoriaLinea(linea, tablaActual -> numCampos);
							linea = NULL;
							actualizar_lineas(linea, tablaActual, NombreBDEnUso);
							t = borrarTabla(t, NombreBDEnUso, nombreTabla);
							t = cargarTablas(NombreBDEnUso);
							if(strcmp(nombreTablaEnUso, nombreTabla) == 0)
								strcpy(nombreTablaEnUso, "");
						}else {
							printf("ERROR: Tabla no Existente\n");
						}
					}else {
						printf("ERROR: Numero de parametros incorrecto\n");
					}
				}
				else {
					printf("ERROR: Base de Datos no Activada\n");
				}
			}else {
				printf("ERROR: Numero de parametros incorrecto\n");
			}
		}
		else if(strcmp(token, "order") == 0) {
			if(strcmp(NombreBDEnUso, "") != 0) {
				if(strcmp(nombreTablaEnUso, "") != 0) {
					if(parametrosOrder != NULL) {
						for(int i = 0; i < numElementos; i++) {
							free(parametrosOrder[i]);
						}
						free(parametrosOrder);
					}
					if(token2 == NULL) {
						printf("ERROR: Numero de parametros incorrecto\n");
						continue;
					}
					parametrosOrder = malloc(sizeof(char*) * 3);
					numElementos = 0;
					campoExistente = 0;
					parametrosOrder[numElementos] = strdup(token2);
					numElementos++;
					while((token2 = MiStrTok(NULL, separadores, false)) != NULL && numElementos < 3) {
						parametrosOrder[numElementos] = strdup(token2);
						numElementos++;
					}
					if(numElementos == 2) {
						if(strcmp(parametrosOrder[1], "ASC") == 0) {
							for(int i = 0; i < tablaActual -> numCampos; i++) {
								if(strcmp(tablaActual -> campos[i], parametrosOrder[0]) == 0) {
									campoExistente++;
									ordenarASC(i, linea, tablaActual);
									actualizar_lineas(linea, tablaActual, NombreBDEnUso);
								}
							}
							if(campoExistente == 0) printf("ERROR: Campo no Existente\n");
						}else if(strcmp(parametrosOrder[1], "DES") == 0) {
							for(int i = 0; i < tablaActual -> numCampos; i++) {
								if(strcmp(tablaActual -> campos[i], parametrosOrder[0]) == 0) {
									campoExistente++;
									ordenarDES(i, linea, tablaActual);
									actualizar_lineas(linea, tablaActual, NombreBDEnUso);
								}
							}
							if(campoExistente == 0) printf("ERROR: Campo no Existente\n");
						}else {
							printf("ERROR: El comando remove <campo> solo acepta como parametro (ASC/DES)\n");
						}
					}
					else {
						printf("ERROR: Numero de parametros incorrecto\n");
					}
				}else {
					printf("ERROR: Tabla no Activa\n");
				}
			}else {
				printf("ERROR: Base de Datos NO Activa\n");
			}
		}
		else if(strcmp(token, "import") == 0) {
			if(parametrosImport != NULL) {
				for(int i = 0; i < numElementos; i++) {
					free(parametrosImport[i]);
				}
				free(parametrosImport);
			}
			if(token2 == NULL) {
				printf("ERROR: Numero de parametros incorrecto\n");
				continue;
			}
			numElementos = 0;
			parametrosImport = malloc(sizeof(char*) * 5);
			parametrosImport[numElementos] = strdup(token2);
			numElementos++;
			while((token2 = MiStrTok(NULL, separadores, false)) != NULL && numElementos < 5) {
				parametrosImport[numElementos] = strdup(token2);
				numElementos++;
			}

			if(numElementos == 4) {
				if(strcmp(NombreBDEnUso, "") != 0) {
					if(strcmp(parametrosImport[0], "table") == 0 && strcmp(parametrosImport[2], "from") == 0) {
						if(!ComprobarBDExistente(parametrosImport[3])) {
							if(strcmp(NombreBDEnUso, parametrosImport[3]) != 0) {
								if(!ComprobarExistenciaTabla(NombreBDEnUso, parametrosImport[1])) {
									if(ComprobarExistenciaTabla(parametrosImport[3], parametrosImport[1])) {
										tImport = cargarTablas(parametrosImport[3]);
										if(tImport != NULL) {
											tCopia = BuscarTablaExistente(parametrosImport[1], tImport);
											if(tCopia != NULL) {
												printf("Intenta insertar la tabla con las demas\n");
												if(t == NULL) {
													t = tCopia;
												}else {
													insertarUltimaTabla(t, tCopia);
												}

												printf("Supuestamente lo inserta\n");
												crearTabla(NombreBDEnUso, parametrosImport[1], t);
												printf("Crea la tabla\n");
												lineaCopia = malloc(sizeof(ROW));
												printf("Intenta cargar lineas de la otra tabla\n");
												lineaImport = cargarLineas(parametrosImport[3], parametrosImport[1], tCopia -> numCampos, tCopia ->tipos);
												if(lineaImport == NULL) printf("TABLA VACIA\n");
												lineaCopia = lineaImport;
												actualizar_lineas(lineaCopia, t, NombreBDEnUso);
												editar_meta(NombreBDEnUso, t);
											}else {
												printf("ERROR: Algo ocurrio tabla no encontrada\n");
											}
										}else {
											printf("ERROR: Algo ocurrio Base de Datos Vacia\n");
										}
									}else {
										printf("ERROR: La tabla no existe en la Base de Datos indicada\n");
									}
								}else {
									printf("ERROR: Ya existe una tabla con ese nombre\n");
								}
							}else {
								printf("ERROR: Te situas en esa Base de Datos\n");
							}
						}else {
							printf("ERROR: La Base de Datos de origen no existente\n");
						}	
					}else {
						printf("ERROR: Comando incorrecto\n");
					}
				}else {
					printf("ERROR: Base de Datos no Activa\n");
				}
			}else {
				printf("ERROR: Numero de parametros incorrecto\n");
			}
		}
		else
		{
			printf("ERROR: Comando Incorrecto\n");
		}
	}
	return 0;
}



/*
//Borrar Tabla (fichero tambien)
					nombreTabla = strdup(token2);
					liberarMemoriaLinea(linea, tablaActual -> numCampos);
					linea = NULL;
					actualizar_lineas(linea, tablaActual, NombreBDEnUso);
					t = borrarTabla(t, NombreBDEnUso, nombreTabla);
					t = cargarTablas(NombreBDEnUso);
					if()
					strcpy(nombreTablaEnUso, "");
					*/







//BORRAR BASE DE DATOS

/*
if(strcmp(nombreTablaEnUso, "") == 0) {//delete bd -> prueba 
				if(strcmp(NombreBDEnUso, "") != 0) {
					if(token2 == NULL) {
						t = borrarBD(t, NombreBDEnUso);
						strcpy(NombreBDEnUso, "");
					}else {
						printf("ERROR: Numero de parametros incorrecto\n");
					}
				}else {
					printf("ERROR: No hay una  Base de datos activa\n");
				}
			}else {
				printf("ERROR: Hay una tabla activa\n");
			}
*/



//BORRAR LINEAS Y TABLA

/*
				if(strcmp(nombreTablaEnUso, "") != 0 && token2 == NULL) {

					//Borrar Lineas (Todas)
					liberarMemoriaLinea(linea, tablaActual -> numCampos);
					linea = NULL;
					actualizar_lineas(linea, tablaActual, NombreBDEnUso);

				}else if(token2 != NULL && (token = MiStrTok(NULL, separadores, false)) == NULL && strcmp(nombreTablaEnUso, "") != 0) {
					//Borrar Tabla (fichero tambien)
					nombreTabla = strdup(token2);
					liberarMemoriaLinea(linea, tablaActual -> numCampos);
					linea = NULL;
					actualizar_lineas(linea, tablaActual, NombreBDEnUso);
					t = borrarTabla(t, NombreBDEnUso, nombreTabla);
					t = cargarTablas(NombreBDEnUso);
					strcpy(nombreTablaEnUso, "");
				}else {
					printf("ERROR: Parametros incorrectos\n");
				}
				*/


				//RENOMBRAR TABLA 

				/*
				if(strcmp(nombreTablaEnUso, "") == 0) {//rename -> "prueba" NombreTablaActual NombreNuevo
					if(token2 != NULL) {
						if(elementos != NULL) {
							for(int i = 0; i < numElementos; i++) {
								free(elementos[i]);
							}	
							free(elementos);
						}
						elementos = malloc(sizeof(char*) * 3);
						numElementos = 0;
						elementos[numElementos] = strdup(token2);
						numElementos++;
						while((token2 = MiStrTok(NULL, separadores, false)) != NULL && numElementos < 3) {
							elementos[numElementos] = strdup(token2);
							numElementos++;
						}
						if(numElementos == 2) {
							if(ComprobarExistenciaTabla(NombreBDEnUso, elementos[0])) {
								if(!ComprobarExistenciaTabla(NombreBDEnUso, elementos[1])) {
									t = renombrarTabla(t, elementos[0], elementos[1], NombreBDEnUso);
									editar_meta(NombreBDEnUso, t);
									mostrarTablas(t, NombreBDEnUso);
								}else {
									printf("ERROR: Ya hay una tabla con ese nombre\n");
								}
							}else {
								printf("ERROR: Tabla no existente\n");
							}
						}else {
							printf("ERROR: Numero de parametros incorrecto\n");
						}
					}else {
						printf("ERROR: Numero de parametros incorrecto\n");
					}
				}else {
					printf("ERROR: Tabla activa\n");
				}
				*/


//Cambiar campo Valor

/*



if(strcmp(NombreBDEnUso, "") != 0) { //cambiar -> "prueba" nombre = vicente Paco
				if(strcmp(nombreTablaEnUso, "") != 0) {
					if(elementos != NULL) {
						for(int i = 0; i < numElementos; i++) {
							free(elementos[i]);
						}
						free(elementos);
					}
					elementos = malloc(sizeof(char*) * 4);
					if(token2 != NULL) {
						numElementos = 0;
						numComillas = 0;
						elementos[numElementos] = strdup(token2);
						numElementos++;
						for(int i = 0; i < strlen(cadenaAux); i++) {
							if(cadenaAux[i] == '"')
								numComillas++;
						}
						if(numComillas%2 == 0 && numComillas != 0) {
							while((token2 = MiStrTok(NULL, separadores, true)) != NULL && numElementos < 4) {
								elementos[numElementos] = strdup(token2);
								numElementos++;
							}
						}else if(numComillas == 0){
							while((token2 = MiStrTok(NULL, separadores, false)) != NULL && numElementos < 4) {
								elementos[numElementos] = strdup(token2);
								numElementos++;
							}
							if(numElementos == 5) {
								printf("ERROR: Numero de parametros incorrecto\n");
								continue;
							}

							for(int i = 0; i < tablaActual -> numCampos; i++) {
								if(strcmp(tablaActual->campos[i], elementos[0]) == 0){

									if(tablaActual->tipos[i] == NUM && ValidarNumero(elementos[3])){
										linea = cambiarCampoValor(linea, i, elementos[2], elementos[1], elementos[3], tablaActual -> tipos[i]);
										actualizar_lineas(linea, tablaActual, NombreBDEnUso);
										break;
									}
									else if(tablaActual->tipos[i] == DATE && ValidarFecha(elementos[3])){
										linea = cambiarCampoValor(linea, i, elementos[2], elementos[1], elementos[3], tablaActual -> tipos[i]);
										actualizar_lineas(linea, tablaActual, NombreBDEnUso);
										break;
									}
									else if(tablaActual->tipos[i] == EMAIL && ValidarEmail(elementos[3])){
										linea = cambiarCampoValor(linea, i, elementos[2], elementos[1], elementos[3], tablaActual -> tipos[i]);
										actualizar_lineas(linea, tablaActual, NombreBDEnUso);
										break;
									}
									else if(tablaActual->tipos[i] == TEXT){
										linea = cambiarCampoValor(linea, i, elementos[2], elementos[1], elementos[3], tablaActual -> tipos[i]);
										actualizar_lineas(linea, tablaActual, NombreBDEnUso);
										break;
									}
									else{
										printf("ERROR: Tipos incorrecto o valor no valido\n");
									}
								}
							}
						}else {
							printf("ERROR: Numero de parametros incorrecto\n");
						}
					}else {
						printf("ERROR: Numero de parametros incorrecto\n");
					}
				}else {
					printf("ERROR: Tabla no activa\n");
				}
			}else {
				printf("ERROR: Base de Datos no activa\n");
			}
			*/
			