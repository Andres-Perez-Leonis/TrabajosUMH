#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#include <errno.h>
#include "librerias.h"

/*
*****************************************************
		Funciones Rutinarias
*****************************************************
													*/


char* MiStrTok(char *cad1, char *sep, bool comillas) {//Trocea una cadena, teniendo en cuanta o no (segun le indiquemos) las commillas de modo que si las hay coja todo lo contenido entre las comillas
	static char *pt1=NULL;
	static char *pt2=NULL;
	static char *ptFinal;

	if(cad1!=NULL)
	{
		pt1 = cad1;
		ptFinal = pt1+strlen(cad1);
	}
	else
	{
		pt1=pt2+1;
	}

	if(comillas)
	{
		while( pt1[0]!='\0' && pt1<ptFinal && strchr(sep, pt1[0])!=NULL && pt1[0]!='"')
			pt1++;
		if(pt1[0]=='"')
		{
			pt1++;
			pt2=pt1+1;
			while( pt2[0]!='\0' && pt2[0]!='"' )
				pt2++;
			if(pt2[0]=='\0')
			{
				pt1=pt2=ptFinal=NULL;
				return NULL;
			}
			else
			{
				pt2[0]='\0';
				return pt1;
			}
		}
	}
	else
	{
		while( pt1[0]!='\0' && pt1<ptFinal && strchr(sep, pt1[0])!=NULL )
			pt1++;
	}

	if(pt1>=ptFinal)
	{
		pt1=pt2=ptFinal=NULL;
		return NULL;
	}

	pt2=pt1+1;
	while( pt2[0]!='\0' &&  strchr(sep, pt2[0])==NULL )
		pt2++;
	pt2[0]='\0';

	return pt1;
}

void EscribirPrompt(char *nombreBD, char *nombreTabla) {//Escribe el prompt detectando cuando utilizas una tabla u Base de Datos
	char prompt[100] = "*";
		if(strcmp(nombreBD, "") != 0 && strcmp(nombreTabla, "") == 0) sprintf(prompt, "[%s]:>", nombreBD);
		else if(strcmp(nombreBD, "") != 0 && strcmp(nombreTabla, "") != 0) sprintf(prompt, "[%s/%s]:>", nombreBD, nombreTabla);
		else strcpy(prompt, "[*]:>");
	printf(prompt);
}

TABLE *inicializarTabla(char *nomTabla, char ** campos, TYPE *tipos, int numCampos) {//Crea la tabla de forma que luego podamos introducirla en la lista

    TABLE *tabla = malloc(sizeof(TABLE));
    if(tabla == NULL){
        return NULL;
    }

    strcpy(tabla->nombre, nomTabla);
    tabla->numCampos = numCampos;
    tabla->campos = campos;
    tabla->tipos = tipos;

    tabla->sig = NULL;
    tabla->ant = NULL;

	
	return tabla;

}

void crearTabla(char *nombreBD, char *nombreTabla, TABLE *t) {//Introduce en el fichero "meta.db" el nombre y los campos de la tabla que le idicamos

	FILE *fichero;
	DIR *dir;
	char aux[10] = ".tab";
	char aux2[10] ="\\";
	char aux3[100] = "";

	strcpy(aux3, nombreBD);
	strcat(aux3, aux2);
	strcat(aux3, nombreTabla);
	strcat(aux3, aux);
	if(access(aux3, F_OK) != 0){
		if(dir = opendir(nombreBD)) {
			fichero = fopen(aux3, "w");
			if(fichero == NULL) {
				printf("ERROR: No se ha podido abrir el fichero\n");
				return;
			}else {
				editar_meta(nombreBD, t);
			}
		}
		fclose(fichero);
	}else {
		printf("ERROR: Tabla ya existente\n");
	}



}

void mostrarTablas(TABLE *t, char *nombreBD){//Muestra por pantalla las tablas que contiene la base de datos

    TABLE *tablaAux = t;
    char aux[10]="";

    if(contar_tablas(nombreBD)==0){
        printf("No hay tablas\n");
        return;
    }

    for(int i=0 ; i < contar_tablas(nombreBD); i++){
        printf("Nombre: %s -> (%d)\n",tablaAux->nombre, tablaAux->numCampos);
        for(int j = 0; j < tablaAux->numCampos; j++){
            printf("Campo: %s, Tipo: %d\n",tablaAux->campos[j], tablaAux->tipos[j]);
        }
        tablaAux = tablaAux->sig;
    }
}

void editar_meta(char *nombre_bd, TABLE *tabla) {//Escribe en el fichero meta los nombres de las tablas y sus campos

    DIR *dir;
    char aux[11]="\\meta.db";
    char aux2[50]="";
    char aux3[50]="";

    int numero_tablas = 0;

    numero_tablas = contar_tablas(nombre_bd);
    printf("Numero de Tablas -> (%d)\n", numero_tablas);

    strcpy(aux2, nombre_bd);
    strcat(aux2, aux);

    if(dir = opendir(nombre_bd)){

        FILE *fichero;
        fichero = fopen(aux2,"w");

        if(fichero != NULL){

            fprintf(fichero, "TABLAS: %d\n", numero_tablas);
            fprintf(fichero, "--------------------------------\n");
            if(numero_tablas == 1){

                fprintf(fichero, "%s: %d\n", tabla->nombre, tabla->numCampos);
				printf("%s:%d\n",tabla -> nombre, tabla -> numCampos);
                for(int i = 0 ; i < tabla->numCampos; i++){

                    if(tabla->tipos[i] == 0){
                        strcpy(aux3, "NUM");
                    }
                    if(tabla->tipos[i] == 1){
                        strcpy(aux3, "DATE");
                    }
                    if(tabla->tipos[i] == 2){
                        strcpy(aux3, "EMAIL");
                    }
                    if(tabla->tipos[i] == 3){
                        strcpy(aux3, "TEXT");
                    }

                    fprintf(fichero,"%s: %s\n", tabla->campos[i], aux3);

                }

            }
            else{

                while(tabla != NULL){

                    fprintf(fichero, "%s: %d\n", tabla->nombre, tabla->numCampos);
					printf("%s:%d\n",tabla -> nombre, tabla -> numCampos);
                    for(int i = 0 ;i < tabla->numCampos; i++){
                   		if(tabla->tipos[i] == 0){
                        	strcpy(aux3, "NUM");
                    	}else if(tabla->tipos[i] == 1){
                        	strcpy(aux3, "DATE");
                    	}else if(tabla->tipos[i] == 2){
                  	      	strcpy(aux3, "EMAIL");
                  	  	}else if(tabla->tipos[i] == 3){
                      	  	strcpy(aux3, "TEXT");
                 	   	}

                   		fprintf(fichero,"%s: %s\n", tabla->campos[i], aux3);

                    }
                    /*
                    if(tabla -> sig == NULL){
						fclose(fichero);
                        return;
                    }
*/
                    fprintf(fichero, "--------------------------------\n");
                    tabla = tabla->sig;
                }

            }
        }
        fclose(fichero);
    }

}

void EscribirTabla(char *nombreTabla, TABLE *t, char *nombreBD) {//Funcion no utilizada hace lo mismo que el "crearTabla"
	DIR *contenidoCarpeta;
	struct dirent *contenido;
	char rutaAbsoluta[100];
	char aux[10];
	char aux2[10] = ".tab";
	FILE *fichero;

	sprintf(rutaAbsoluta, "%s%s/%s%s",direccionArchivos,nombreBD,nombreTabla,aux2);
	if(access(rutaAbsoluta,F_OK) != 0) {
		if(contenidoCarpeta = opendir(rutaAbsoluta)) {
			fichero = fopen(rutaAbsoluta,"w");
			if(fichero == NULL) {
				printf("ERROR: Tabla no creada\n");
				fclose(fichero);
			}else {
				editar_meta(nombreBD, t);
			}
		}else 
			printf("ERROR: No se ha podido crear la tabla\n");
	}else
		printf("ERROR: Ya existe esa tabla\n");

	fclose(fichero);
}

void actualizar_lineas(ROW *linea, TABLE *t, char *nombreBD) {//Funcion que escribe en fihero los datos introducidos (en el fichero de la tabla creada)
	DIR *dir;
	int i;
	char aux[11] = ".tab";
	char aux2[5] = "\\";
	char aux3[100] = "";
	strcpy(aux3, nombreBD);
	strcat(aux3, aux2);
	strcat(aux3, t -> nombre);
	strcat(aux3, aux);
	if(dir = opendir(nombreBD)) 
	{
		FILE *fichero;
		fichero = fopen(aux3, "w");
		
		if(fichero != NULL) 
		{
			while(linea != NULL)
			{
				for(i = 0; i < t -> numCampos - 1; i++) 
				{
					if(t -> tipos[i] == TEXT)
					{
						fprintf(fichero, "\"%s\", ",linea -> valores[i]); 
					}
					else
					{
						fprintf(fichero, "%s, ", linea -> valores[i]);
					}
				}
				if(t -> tipos[i] == TEXT)
				{
					fprintf(fichero, "\"%s\"\n",linea -> valores[t -> numCampos-1]); 
				}
				else
				{
					fprintf(fichero, "%s\n", linea -> valores[t -> numCampos-1]);
				}
				if(linea -> sig == NULL) break;
				linea = linea -> sig;
			}
			fclose(fichero);
		}else {
			printf("ERROR: No se abrio el fichero\n");
		}
	}
}

void insertarUltimaLinea(ROW *linea, ROW *fila) {//Funcion que introduce al final de la lista la linea creada 
	ROW *filaAux;
	filaAux = linea;

	while(filaAux -> sig != NULL) 
	{
		filaAux = filaAux -> sig;
	}
	fila -> ant = filaAux;
	fila -> sig = NULL;
	filaAux -> sig = fila;
}

ROW *cargarLineas(char *nombreBD, char *nombreTabla, int numCampos, TYPE *tipos){//Funcion la cual introduce en memoria los datos introducidos en el fichero (la tabla)
	
    char aux1[5]=".tab";
    char aux2[5]="\\";
    char aux3[100]="";

    FILE *fichero;
    char linea[1000];
    int i, comillas;
    long final;
    char *token, *lineaaux;
    char **valores;
    ROW *fila = NULL, *filanueva = NULL;

    strcat(aux3,nombreBD);
    strcat(aux3, aux2);
    strcat(aux3, nombreTabla);
    strcat(aux3, aux1);

    if(access(aux3, F_OK) == 0){
        fichero = fopen(aux3, "r");

        fseek(fichero, 0, SEEK_END); // colocamos el cursor en la ultima posicion del fichero

        if(ftell(fichero)==0){
            fclose(fichero);
            return fila;
        }

        final = ftell(fichero); // Guardamos en final la posicion en la q se encuentra el cursor
        fseek(fichero, 0, SEEK_SET); // colocamos el cursor al principio del fichero

        while(final != ftell(fichero)){
            
            fgets(linea, 1000, fichero);

            valores = malloc(sizeof(char*)*numCampos);

            for(i=0; i<numCampos;i++){

                comillas = (tipos[i] == TEXT); // si hay un campo de tipo texto comillas valdra 1

                if(i==0){
                    lineaaux = linea;
                }
                else{
                    lineaaux = NULL;
                }

                token = MiStrTok(lineaaux, ",\n", comillas);
                valores[i]=strdup(token);
            }

            filanueva = crearLinea(valores);

            if(fila == NULL){
                fila = filanueva;
            }
            else{
                insertarUltimaLinea(fila, filanueva);
            }

        }


    }
    else{
        printf("ERROR");
        return NULL;
    }

    fclose(fichero);
    return fila;
}


ROW *crearLinea(char ** valores) {//Funcion que inicializa uno de los datos introducidos de manera que este pueda ser introducido en la lista de "datos"
	ROW *linea = malloc(sizeof(ROW));

	if(linea == NULL) {
		return NULL;
	}
	linea -> valores = valores;
	linea -> sig = NULL;
	linea -> ant = NULL;
}


void EliminarTabla(TABLE *t) {//Funcion no utilizada
	if(t == NULL) {
		printf("Tabla no encontrada. \n");
		return;
	}
	for(int i = 0; i < t -> numCampos; i++) free(t-> campos[i]);
	free(t -> campos);
	free(t -> tipos);
	free(t);
}

void *toLoweCase(char *cadena) {//Funcion no utilizada que pasa todas la letras de una cadena a minusculas
	for(int i = 0; i < strlen(cadena); i++) {
		if(cadena[i] >= 'A' && cadena[i] <= 'Z') {
			cadena[i] = cadena[i] - 'A' + 'a';
		}
	}
	return cadena;
}

void *toUpperCase(char *cadena) {//Funcion no utilizada que pasa todas la letras de una cadena a mayusculas
	for(int i = 0; i < strlen(cadena); i++) {
		if(cadena[i] >= 'a' && cadena[i] <= 'z') {
			cadena[i] = cadena[i] + 'A' - 'a';
		}
	}
	return cadena;
}

ROW *cambiarCampoValor(ROW *linea, int posicion, char *valor, char *simbolo, char *valorNuevo, TYPE tipo) {//Una de las funciones extras, todo lo que confirme una condicion sera cambiado por el valor introducido 
    ROW *lineaAux = linea, *lineaSig = NULL, *lineaAnt = NULL;

    if(linea == NULL) {
        printf("ERROR: Linea vacia\n");
        return linea;
    }

    if(tipo == NUM) {
        if(strcmp(simbolo, "=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarNumero(valorNuevo)) {
                    if(atof(valor) == atof(lineaAux -> valores[posicion])) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, ">") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarNumero(valorNuevo)) {
                    if(atof(valor) < atof(lineaAux -> valores[posicion]))
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, "<") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarNumero(valorNuevo)) {
                    if(atof(valor) > atof(lineaAux -> valores[posicion])) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, "<=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarNumero(valorNuevo)) {
                    if(atof(valor) >= atof(lineaAux -> valores[posicion])) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, ">=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarNumero(valorNuevo)) {
                    if(atof(valor) <= atof(lineaAux -> valores[posicion])) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, "!=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarNumero(valorNuevo)) {
                    if(atof(valor) != atof(lineaAux -> valores[posicion]))
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else {
            printf("ERROR: Simbolo no valido\n");
        }
    }else if(tipo == DATE) {
        lineaSig = lineaAux -> sig;
        lineaAnt = lineaAux -> ant;
        if(strcmp(simbolo, "=") == 0) {
            while(lineaAux != NULL) {
                if(ValidarFecha(valorNuevo)) {
                    if(datecmp(valor, lineaAux -> valores[posicion]) == 0) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, "<") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarFecha(valorNuevo)) {
                    if(datecmp(valor, lineaAux -> valores[posicion]) == 1) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, ">") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarFecha(valorNuevo)) {
                    if(datecmp(valor, lineaAux -> valores[posicion]) == -1) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, "<=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarFecha(valorNuevo)) {
                    if(datecmp(valor, lineaAux -> valores[posicion]) != -1) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, ">=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarFecha(valorNuevo)) {
                    if(datecmp(valor, lineaAux -> valores[posicion]) != 1) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, "!=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarFecha(valorNuevo)) {
                    if(datecmp(valor, lineaAux -> valores[posicion]) != 0) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else {
            printf("ERROR: Simbolo no valido\n");
        }
    }else if(tipo == EMAIL) {
        if(strcmp(simbolo, "=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarEmail(valorNuevo)) {
                    if(strcmp(valor, lineaAux -> valores[posicion]) == 0) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, "<") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarEmail(valorNuevo)) {
                    if(strcmp(valor, lineaAux -> valores[posicion]) == -1) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }  
            return linea;
        }else if(strcmp(simbolo, ">") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarEmail(valorNuevo)) {
                    if(strcmp(valor, lineaAux -> valores[posicion]) == 1) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, "<=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarEmail(valorNuevo)) {
                    if(strcmp(valor, lineaAux -> valores[posicion]) != 1) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, ">=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarEmail(valorNuevo)) {
                    if(strcmp(valor, lineaAux -> valores[posicion]) == -1) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, "!=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarEmail(valorNuevo)) {
                    if(strcmp(valor, lineaAux -> valores[posicion]) != 0) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else {
            printf("ERROR: Simbolo no valido\n");
        }
    }else if(tipo == TEXT) {
        if(strcmp(simbolo, "=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarEmail(valorNuevo)) {
                    if(strcmp(valor, lineaAux -> valores[posicion]) == 0) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, "<") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarEmail(valorNuevo)) {
                    if(strcmp(valor, lineaAux -> valores[posicion]) == -1) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }  
            return linea;
        }else if(strcmp(simbolo, ">") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarEmail(valorNuevo)) {
                    if(strcmp(valor, lineaAux -> valores[posicion]) == 1) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, "<=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarEmail(valorNuevo)) {
                    if(strcmp(valor, lineaAux -> valores[posicion]) != 1) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, ">=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarEmail(valorNuevo)) {
                    if(strcmp(valor, lineaAux -> valores[posicion]) == -1) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else if(strcmp(simbolo, "!=") == 0) {
            while(lineaAux != NULL) {
                lineaSig = lineaAux -> sig;
                lineaAnt = lineaAux -> ant;
                if(ValidarEmail(valorNuevo)) {
                    if(strcmp(valor, lineaAux -> valores[posicion]) != 0) 
                        lineaAux -> valores[posicion] = strdup(valorNuevo);
                }else {
                    printf("ERROR: Valor nuevo no valido\n");
                }
                lineaAux = lineaSig;
            }
            return linea;
        }else {
            printf("ERROR: Simbolo no valido\n");
        }
    }else {
        printf("ERROR: Tipo erroneo\n");
    }
}


void intercambioValores(ROW *linea1, ROW *linea2) {//Funcion que intercambia los valores de posicion en la lista
	char **lineaAux;
	lineaAux = linea1 -> valores;
	linea1 -> valores = linea2 -> valores;
	linea2 -> valores = lineaAux;
}

/*
*****************************************************
		Funciones de Impresion
*****************************************************
*/

void imprimirValoresDeCampo(int numCampos,ROW *linea, TYPE tipos, char *valor, char *simbolo, int posicion) { //Funcion que muestra por pantalla los valores de una tabla que confirmen una condicion
	ROW *lineaAux = linea;
	int numero = 1;
    int elementoEncontrado = 0;
	if(linea == NULL) {
		printf("No hay datos\n");
	}else {
		if(tipos == NUM) {
			if(strcmp(simbolo, "=") == 0) {
				while(lineaAux != NULL) {
					if(atof(valor) == atof(lineaAux ->valores[posicion])) {
                        elementoEncontrado++;
						printf("%d. ",numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s\n", lineaAux -> valores[numCampos-1]);
						numero++;
					}
					
					lineaAux = lineaAux -> sig;
				}
			}else if(strcmp(simbolo, "<") == 0) {
				while(lineaAux != NULL) {
					if(atof(valor) > atof(lineaAux ->valores[posicion])) {
                        elementoEncontrado++;
						printf("%d. ",numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s\n", lineaAux -> valores[numCampos-1]);
						numero++;
					}
					
					lineaAux = lineaAux -> sig;
				}
			}else if(strcmp(simbolo, ">") == 0) {
				while(lineaAux != NULL) {
					if(atof(valor) < atof(lineaAux ->valores[posicion])) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s\n", lineaAux -> valores[numCampos-1]);
						numero++;
					}
					
					lineaAux = lineaAux -> sig;
				}
                /*
            }else if(strcmp(simbolo, ">=") == 0) {
                while(lineaAux != NULL) {
					if(atof(valor) <= atof(lineaAux ->valores[posicion])) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s\n", lineaAux -> valores[numCampos-1]);
						numero++;
					}
					
					lineaAux = lineaAux -> sig;
				}
            } else if(strcmp(simbolo, "<=") == 0) {
                while(lineaAux != NULL) {
					if(atof(valor) >= atof(lineaAux ->valores[posicion])) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s\n", lineaAux -> valores[numCampos-1]);
						numero++;
					}
					
					lineaAux = lineaAux -> sig;
				}
            }else if(strcmp(simbolo, "!=") == 0) {
                
                while(lineaAux != NULL) {
					if(atof(valor) != atof(lineaAux ->valores[posicion])) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s\n", lineaAux -> valores[numCampos-1]);
						numero++;
					}
					
					lineaAux = lineaAux -> sig;
				}
                */

			}else {
				printf("ERROR: Simbolo no valido\n");
			}
		
		
		}else if(tipos == DATE) {
			if(strcmp(simbolo, "=") == 0) {
				while(lineaAux != NULL) {
					
					if(datecmp(valor, lineaAux -> valores[posicion]) == 0) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s\n", lineaAux -> valores[numCampos-1]);
						numero++;
					}
					
					lineaAux = lineaAux -> sig;
				}
				
			}else if(strcmp(simbolo, "<") == 0) {
				while(lineaAux != NULL) {
					if(datecmp(valor, lineaAux -> valores[posicion]) == 1) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s\n", lineaAux -> valores[numCampos-1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
			}else if(strcmp(simbolo, ">") == 0) {
				while(lineaAux != NULL) {
					if(datecmp(valor, lineaAux -> valores[posicion]) == -1) {
                        elementoEncontrado++;
						printf("%d. ",numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s\n", lineaAux -> valores[numCampos-1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
                /*
            }else if(strcmp(simbolo, ">=") == 0) {
                while(lineaAux != NULL) {
					if(datecmp(valor, lineaAux -> valores[posicion]) != 1) {
                        elementoEncontrado++;
						printf("%d. ",numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s\n", lineaAux -> valores[numCampos-1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
            }else if(strcmp(simbolo, "<=") == 0) {
                while(lineaAux != NULL) {
					if(datecmp(valor, lineaAux -> valores[posicion]) != -1) {
                        elementoEncontrado++;
						printf("%d. ",numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s\n", lineaAux -> valores[numCampos-1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
            }else if(strcmp(simbolo, "!=") == 0) {
                while(lineaAux != NULL) {
					if(datecmp(valor, lineaAux -> valores[posicion]) != 0) {
                        elementoEncontrado++;
						printf("%d. ",numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s\n", lineaAux -> valores[numCampos-1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
                */

			}else {
				printf("ERROR: Simbolo no valido\n");
			}
		}else if(tipos == EMAIL) {
			if(strcmp(simbolo , "=") == 0) {
				while(lineaAux != NULL) {
					if(strcmp(valor, lineaAux -> valores[posicion]) == 0) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s, ", lineaAux -> valores[numCampos -1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
			}else if(strcmp(simbolo, ">") == 0) {
				while(lineaAux != NULL) {	
					if(strcmp(valor, lineaAux -> valores[posicion]) == 1) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s, ", lineaAux -> valores[numCampos -1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
			}else if(strcmp(simbolo, "<") == 0) {
				while(lineaAux != NULL) {
					if(strcmp(valor, lineaAux -> valores[posicion]) == -1) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s, ", lineaAux -> valores[numCampos -1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
                /*
            }else if(strcmp(simbolo, "<=") == 0) {
                while(lineaAux != NULL) {
					if(strcmp(valor, lineaAux -> valores[posicion]) != 1) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s, ", lineaAux -> valores[numCampos -1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
            }else if(strcmp(simbolo, ">=") == 0) {
                while(lineaAux != NULL) {
					if(strcmp(valor, lineaAux -> valores[posicion]) != -1) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s, ", lineaAux -> valores[numCampos -1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
            }else if(strcmp(simbolo, "!=") == 0) {
                while(lineaAux != NULL) {
					if(strcmp(valor, lineaAux -> valores[posicion]) != 0) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s, ", lineaAux -> valores[numCampos -1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
                */
			}else {
				printf("ERROR: Simbolo no valido\n");
			}
		}else if(tipos == TEXT) {
			if(strcmp(simbolo , "=") == 0) {
				while(lineaAux != NULL) {
					if(strcmp(valor, lineaAux -> valores[posicion]) == 0) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s, ", lineaAux -> valores[numCampos -1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
			}else if(strcmp(simbolo, ">") == 0) {
				while(lineaAux != NULL) {	
					if(strcmp(valor, lineaAux -> valores[posicion]) == 1) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s, ", lineaAux -> valores[numCampos -1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
			}else if(strcmp(simbolo, "<") == 0) {
				while(lineaAux != NULL) {
					if(strcmp(valor, lineaAux -> valores[posicion]) == -1) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s, ", lineaAux -> valores[numCampos -1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
                /*
            }else if(strcmp(simbolo, "<=") == 0) {
                while(lineaAux != NULL) {
					if(strcmp(valor, lineaAux -> valores[posicion]) != 1) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s, ", lineaAux -> valores[numCampos -1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
            }else if(strcmp(simbolo, ">=") == 0) {
                while(lineaAux != NULL) {
					if(strcmp(valor, lineaAux -> valores[posicion]) != -1) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s, ", lineaAux -> valores[numCampos -1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
            }else if(strcmp(simbolo, "!=") == 0) {
                while(lineaAux != NULL) {
					if(strcmp(valor, lineaAux -> valores[posicion]) != 0) {
                        elementoEncontrado++;
						printf("%d. ", numero);
						for(int i = 0; i < numCampos -1; i++) {
							printf("%s, ", lineaAux -> valores[i]);
						}
						printf("%s, ", lineaAux -> valores[numCampos -1]);
						numero++;
					}
					lineaAux = lineaAux -> sig;
				}
                */
			}else {
				printf("ERROR: Simbolo no valido\n");
			}
		}
	}
    if(elementoEncontrado == 0) printf("ERROR: Ningun valor encontrado\n");

}

void imprimirTodo(int numCampos, ROW *linea) {//Funcion que muestra por pantalla todos los valores de una tabla
	ROW *lineaAux = linea;
	int numero = 1;
	if(linea == NULL)
		printf("No se han encontrado datos\n");
	else {
		while(lineaAux != NULL) {
			printf("%d. ", numero);
			for(int i = 0; i < numCampos-1; i++) {
				printf("%s, ", lineaAux -> valores[i]);
			}
			printf("%s\n", lineaAux -> valores[numCampos-1]);
			numero++;
            if(lineaAux -> sig == NULL) break;
			lineaAux = lineaAux -> sig;
		}
	}
}

void imprimirTodoASC(int numCampos, ROW *linea, TABLE *t, int campo) {//Funcion que muestra por pantalla los valores de una tabla de forma ascendente

	int numero = 1;
	ROW *lineaAux = linea;
	if(linea == NULL) {
		printf("No hay datos dentro de la tabla\n");
	}else {
		ordenarASC(campo, lineaAux, t);
		while(lineaAux != NULL) {
			printf("%d. ",numero);
			for(int i = 0; i < numCampos - 1; i++) {
				printf("%s, ", lineaAux->valores[i]);
			}
			printf("%s\n", lineaAux -> valores[numCampos - 1]);
			numero++;
			lineaAux = lineaAux -> sig;
		}
	}
}


void imprimirTodoDES(int numCampos, ROW *linea, TABLE *t, int campo) {//Funcion que muestra por pantalla los valores de una tabla de forma descendente

	int numero = 1;
	ROW *lineaAux = linea;
	if(linea == NULL) {
		printf("No hay datos dentro de la tabla\n");
	}else {
		ordenarDES(campo, lineaAux, t);
		while(lineaAux != NULL) {
			printf("%d. ",numero);
			for(int i = 0; i < numCampos - 1; i++) {
				printf("%s, ", lineaAux->valores[i]);
			}
			printf("%s\n", lineaAux -> valores[numCampos - 1]);
			numero++;
			lineaAux = lineaAux -> sig;
		}
	}
}



void imprimirEncabezados(TABLE *t) {// Funcion no utilizada, imprime los nombres de los campos de la tabla 
	for(int i = 0; i < t -> numCampos; i++)
	{
		printf("%s \t", t -> campos[i]);
	}
	printf("\n");
}

void funcionamientoComandoList() {//Funcion que imprime todos los nombres de las bases de datos creadas
	DIR *contenidoCarpeta;
	struct dirent *contenido;
	struct stat st;
	char nombre[100];
	int i = 0;
	contenidoCarpeta = opendir(direccionArchivos);
	if(contenidoCarpeta == NULL) {
		printf("No se ha podido abrir la carpeta contenedora de las Bases de Datos\n");
	}else {
		while((contenido = readdir(contenidoCarpeta)) != NULL) {
			if(strcmp(contenido -> d_name,"..") != 0 && strcmp(contenido -> d_name, "meta.db") != 0 && strcmp(contenido -> d_name,".") != 0 && strcmp(contenido -> d_name,".vscode") != 0) {
				sprintf(nombre, "%s%s",direccionArchivos,contenido -> d_name);
				stat(nombre, &st);
				if(S_ISDIR(st.st_mode) == 1) {
                    i++;
					printf("Nombre Base de Datos: %s\n",contenido -> d_name);
				}
			}
		}
    }
    if(i == 0) printf("No hay bases de datos\n");
	closedir(contenidoCarpeta);
}

void funcionamientoComandoListVariante(char *nombreBD) {//Esta funcion es un comando para que si el usuario introduce el nombre de una base de datos se imrpimian por pantalla los nombres de las tablas que hay dentro de  la base de datos
    TABLE *tAux = NULL;
    if(!ComprobarBDExistente(nombreBD)) {
        tAux = cargarTablas(nombreBD);
        while(tAux != NULL) {
            printf("Nombre: %s\n", tAux -> nombre);
            tAux = tAux -> sig;
        }

    }else {
        printf("ERROR: Base de Datos no existente\n");
    }
}

/*
******************************************************
			Funciones de las Ficheros
******************************************************
*/

void EscribirMETA(TABLE *primeraTabla, int numTablas, char *NombreBDEnUso) {//Funcion que crea el fichero meta.db
	FILE *f;
	char rutaMeta[100];

	sprintf(rutaMeta,"%s%s/meta.db",direccionArchivos,NombreBDEnUso);
	f = fopen(rutaMeta, "w");

	if(f != NULL){
		fprintf(f, "Tablas: %d\n", numTablas);
		TABLE *pTabla;
		for(pTabla = primeraTabla; pTabla != NULL; pTabla = pTabla -> sig){
			fprintf(f,"-------------------------------\n");
			fprintf(f,"%s: %d\n", pTabla -> nombre, pTabla -> numCampos);
			for(int i = 0; i < pTabla -> numCampos; i++) {
				fprintf(f, "%s: ", pTabla -> campos[i]);
				if( (pTabla -> tipos[i]) == NUM)
					fprintf(f,"NUM\n");
				else if( (pTabla -> tipos[i]) == DATE)
					fprintf(f,"DATE\n");
				else if( (pTabla -> tipos[i]) == EMAIL)
					fprintf(f,"EMAIL\n");
				else
					fprintf(f,"TEXT\n");
			}	
		}
	}else {
		printf("ERROR: No se ha podido crear el fichero meta.db\n");
	}

	fclose(f);
}

int contar_tablas(char *nombre_bd){//Funcion que cuanta las tablas introducidas dentro de la base de datos

    DIR *d;
    struct dirent *f;
    int num = 0;

    if(d = opendir(nombre_bd)){

        while(f = readdir(d)){
            num++;
        }
    }

    num = num - 3;

    return num;
}

/*
****************************************************
		Funciones de las Carpetas (Bases de Datos)
****************************************************
													*/


void CrearBD(char *nombreBD) {//Funcion que crea la carpeta de la base de datos
	char rutaAbsoluta[100];
	strcpy(rutaAbsoluta,direccionArchivos);
	strcat(rutaAbsoluta,nombreBD);
	if(access(rutaAbsoluta, F_OK) != 0) {
		if(mkdir(rutaAbsoluta) == 0) { 
			printf("La Base de datos se ha creado de forma correcta\n");
		
			strcpy(rutaAbsoluta,direccionArchivos);
			EscribirMETA(NULL, 0, nombreBD);

		}else printf("ERROR: No se ha creado la Base de Datos\n");
	}else {
		printf("ERROR: La Base de Datos ya ha sido creada\n");
	}
	
}


char *BuscarBDExistente(char *nombreBD){//Funcion que busca la direccion de la base de datos que buscamos si la encuentra devuelve su direccion
	char rutaAbsoluta[100];
	char *aux;
	DIR *BasesDeDatos;
    struct dirent *contenido;
	if(!ComprobarBDExistente(nombreBD)) {
		BasesDeDatos = opendir(direccionArchivos);
		if(BasesDeDatos == NULL) {
			printf("ERROR: No se ha podido abrir la carpeta contenedora de las Bases de Datos\n");
		}else {
			while((contenido = readdir(BasesDeDatos)) != NULL) {
				if(strcmp(contenido -> d_name, nombreBD) == 0) {
					strcpy(rutaAbsoluta,direccionArchivos);
					strcat(rutaAbsoluta,nombreBD);
					closedir(BasesDeDatos);
					return aux = rutaAbsoluta;
				}
			}
		}
	}
}

/*
*********************************************
		Funciones de Ficheros
**********************************************
											*/
											


void EscribirEnFichero(char *nombreFichero, char *cadena) {//Funion que escribe en fichero
	
    FILE* fichero;
	if(cadena == "" || nombreFichero == "") {
		printf("ERROR");
		return;
	}
	   strcat(nombreFichero, ".db");
       strcat(nombreFichero, ".txt");
       if ((fichero = fopen(nombreFichero,"a")) == NULL) printf("ERROR AL ABRIR EL FICHERO");
       else { 
        fprintf(fichero, cadena);
        fprintf(fichero, "\n");   
       }
       fclose(fichero);
}


char *ObtenerCampos(char *lin, char *sep, int id, char *val) {//Funcion que obtiene los campos introducidos

    int i, tamSep=1;
    char *p1, *p2;

    if(lin == NULL || lin[0] == '\0'){
        return NULL;
    } 

    p1=lin;
    p2=strstr(lin, sep);

    for(i=0;i<id;i++){

        p1 = p2+tamSep;
        p2 = strstr(p1, sep);

    }

    if(p2 == NULL){
        strcpy(val, p1);
    }
    else{
        strncpy(val, p1, p2-p1);
        val[p2-p1] = '\0';
    }

    return val;
}

void Trim(char *cad) {//Funcion que elminia los espacios de una cadena

    int c, i, j, n=strlen(cad);

    if(cad == NULL || n < 1){
        return;
    }

    n--;
    while(n>=0 && ((c = cad[n])==' ' || c == '\t' || c == '\n' || c == '"')){
        n--;
    }
    cad[n+1]='\0';
    i=0;

    while(i<=n && ((c=cad[i])==' ' || c == '\t' || c == '\n' || c == '"')){
        i++;
    }

    for(j=0; j<=n-i+1; j++){
        cad[j]=cad[j+i];
    }

}

TABLE *BuscarTablaExistente(char *nombreTabla, TABLE *t) {//Funcion que busca una tabla y si la encuntra la devuelve
	if(t != NULL) {
		while(t != NULL) {
			if(strcmp(t -> nombre, nombreTabla) == 0) {
				return t;
			}
			t = t -> sig;
		}
	}else
		return t;
}

TABLE *cargarTablas(char *nombreBD) {//Funcion que introduce en memoria las tablas que hay en una base de datos
	FILE *fichero;
	TABLE *t = NULL, *tAux = NULL;
	char aux[10] = "\\meta.db";
	char aux2[10] = "";
	TYPE *tipos;
	char linea[1000], lineaAux[100];
	int numTablas, numCampos;
	char *nombreTabla;
	char **nombreCampo;

	strcpy(aux2, nombreBD);
	strcat(aux2, aux);
	fichero = fopen(aux2, "r");

	if(fichero == NULL) {
		printf("ERROR: No se ha podido abrir el meta.db \n");
		return NULL;
	}

	fgets(linea,1000, fichero);
	ObtenerCampos(linea, ":", 1, lineaAux);
	Trim(lineaAux);
	numTablas = atoi(lineaAux);
	printf("Tablas: %d\n", numTablas);

	for(int i = 0; i < numTablas; i++) {
		fgets(linea, 1000, fichero);
		fgets(linea, 1000, fichero);
		ObtenerCampos(linea,":", 0, lineaAux);
		Trim(lineaAux);
		nombreTabla = strdup(lineaAux);
		ObtenerCampos(linea, ":", 1, lineaAux);
		Trim(lineaAux);
		numCampos = atoi(lineaAux);

		nombreCampo = malloc(sizeof(char*) * numCampos);
		tipos = malloc(sizeof(TYPE *) *numCampos);

		for(int j = 0; j < numCampos; j++) {
			fgets(linea, 1000, fichero);
			ObtenerCampos(linea, ":", 0, lineaAux);
			Trim(lineaAux);
			nombreCampo[j] = strdup(lineaAux);
			ObtenerCampos(linea, ":", 1, lineaAux);
			Trim(lineaAux);
			tipos[j] = IdentificarTipo(lineaAux);
		}
		tAux = inicializarTabla(nombreTabla, nombreCampo, tipos, numCampos);
		if(t == NULL) {
			t = tAux;
		}else {
			insertarUltimaTabla(t, tAux);
		}
	}
	fclose(fichero);
	return t;
}

void insertarUltimaTabla(TABLE *t, TABLE *tAux) {//Funcion que introduce una tabla en la ultima posicion 
	TABLE *tNueva = t;
	while(tNueva -> sig != NULL) {
		tNueva = tNueva -> sig;
	}
	tNueva -> sig = tAux;
	tAux -> ant = tNueva;
}


TABLE *renombrarTabla (TABLE *t,  char *nombreTabla, char *nombreNuevo, char *nombreBD) {//Funcion extra para cambiarle el nombre a una tabla
    TABLE *tAux = t;
    DIR *dir;
    char aux[100];
    char aux2[100];

    strcpy(aux, nombreBD);  
    strcat(aux, "\\");
    strcat(aux, nombreTabla);
    strcat(aux, ".tab");

    strcpy(aux2, nombreBD);  
    strcat(aux2, "\\");
    strcat(aux2, nombreNuevo);
    strcat(aux2, ".tab");


    if(dir = opendir(nombreBD)) {
        if(rename(aux, aux2) != 0) {
            printf("ERROR: No se ha podido renombrar la tabla\n");
            return t;
        }
        else {
            tAux = BuscarTablaExistente(nombreTabla, tAux);
            strcpy(tAux -> nombre, nombreNuevo);
            return t;
        }

    }

}


/*
**************************************************
		Funciones de Validacion/Identificacion
**************************************************
												*/

bool ValidarFecha(char *cad) {//Funcion que indica si una fecha es correcta o no
    int dia, mes, ano;
    bool bisiesto = false;
    bool fechaValida;
    if(strlen(cad) != 10){
		return fechaValida = false;
    }else if((cad[2] == '/' && cad[5] == '/')){
        for(int i = 0; i < strlen(cad); i++){
            if(i == 2 || i == 5 ) continue;
            else if(!isdigit(cad[i])){
                return false;
            }
        }
        dia = (cad[0] - '0')*10 + (cad[1]-'0');
        mes = (cad[3] - '0')*10 + (cad[4]-'0');
        ano = (cad[6] - '0')*1000 + (cad[7]-'0')*100 + (cad[8] - '0')*10 + (cad[9] - '0');
    }



    /* 
    }else if((cad[4] == '/' && cad[7] == '/') || (cad[4] == '-' && cad[7] == '-')) {
        for(int i = 0; i < strlen(cad); i++){
            if(i == 4 || i == 7 ) continue;
            else if(!isdigit(cad[i])){
                return false;
            }
        }

        dia = (cad[8] - '0')*10 + (cad[9] - '0');
        mes = (cad[5] - '0')*10 + (cad[6] - '0');
        ano = (cad[0] - '0')*1000 + (cad[1]-'0')*100 + (cad[2] - '0')*10 + (cad[3] - '0');
    }
    */
    



    if(dia < 0 || mes < 0 || ano < 0) return fechaValida = false;
    if(ano % 4 == 0 || (ano % 100 == 0 && ano % 400 == 0)) bisiesto=true;
    if(bisiesto != true){
        if(mes == 2 && dia <= 28) return fechaValida = true;
        else if(mes > 12) return fechaValida = false;
        else if(mes%2 != 0 && dia <= 30 && mes != 2) fechaValida = true;
        else if(dia <= 31 && mes != 2) fechaValida = true;
        else fechaValida = false;
        
    }else{
        if(mes == 2 && dia <= 29) fechaValida = true;
        else if(mes > 12) return fechaValida = false;
        else if(mes%2 != 0 && dia <= 30) fechaValida = true;
        else if(dia <= 31) fechaValida = true;
        else fechaValida = false;
    }
    return fechaValida;
}

bool ValidarNumero(char *cadena) {//Funcion que indica si un numero es correcto o no
	bool numeroValido = true;
	int puntosEnNumero = 0, numeroPuntosAceptado = 1;
	int simbolosEnNumero = 0, simbolosAceptados = 1; 

	if(isdigit(cadena[0]) || cadena[0] == '+' || cadena[0] == '-') {
		if(cadena[0] == '-' || cadena[0] == '+') 
			if(!isdigit(cadena[1])) 
				return numeroValido = false;

		for(int i = 0; i < strlen(cadena); i++) {
			if(isdigit(cadena[i]) == false) {
				if(cadena[i] == '-' || cadena[i] == '+') 
					if(isdigit(cadena[i-1])) 
						return numeroValido = false;
				if(cadena[i] == '.') 
					puntosEnNumero++;
				else if(isalpha(cadena[i])) 
					return numeroValido = false;
				else if(cadena[i] == '+' || cadena[i] == '-') 
					simbolosEnNumero++;
			}
		}
	}else numeroValido = false;	

	if(simbolosEnNumero > simbolosAceptados) numeroValido = false;
	if(puntosEnNumero > numeroPuntosAceptado) numeroValido = false;
	
	return numeroValido;	
}


bool ValidarEmail(char *cadena) { //Funcion que indica si un email es correcto o no
	bool emailValido = true;
	int nArrobasValido = 0, nPuntosValido = 0;

	for(int i = 0; i < strlen(cadena); i++) {
		
		if(cadena[i] == '@') {
			nArrobasValido++;

			if((isdigit(cadena[i-1]) || isalpha(cadena[i-1])) && (isdigit(cadena[i+1]) || isalpha(cadena[i+1]))) 

				continue;

			else {
				emailValido = false;
			}

		} else if(cadena[i] == '.') {
			nPuntosValido++;
				
			if((isdigit(cadena[i-1]) || isalpha(cadena[i-1])) && (isdigit(cadena[i+1]) || isalpha(cadena[i+1]))) 

				continue;

			else {
				emailValido = false;
			}
		
		} else if (isdigit(cadena[i]) || isalpha(cadena[i])) {
			continue;
		
		} else {
			emailValido = false;
		}
	}
	if(cadena[strlen(cadena)-1] == '.' || cadena[strlen(cadena)-1] == '@') emailValido = false;
	if(nArrobasValido == 1 && nPuntosValido == 1);
	else emailValido = false;

	return emailValido;

}

bool ValidarNombre(char *cadena){//Funcion que indica si un nombre es correcto o no
	bool validacion = true;
	for(int i = 0; i < strlen(cadena); i++) {
		if(cadena[i] >= 'A' && cadena[i] <= 'Z') continue;
		else if((cadena[i] >= 'a' && cadena[i] <= 'z')) continue;
		else if(cadena[i] >= '0' && cadena[i] <= '9') continue;
		else if(cadena[i] == '_') continue;
		else validacion = false;
	}
	return validacion;
}

TYPE DeterminarTipo(char *cadena) {//Funcion que determina el tipo de dato introducido
	if (ValidarNumero(cadena) == true) return NUM;
	if (ValidarFecha(cadena) == true) return DATE;
	if (ValidarEmail(cadena) == true) return EMAIL;
	else return TEXT;
}

TYPE IdentificarTipo(char *cadena) {//Funcion que indica el tipo de campo introducido
	if(strcmp(cadena, "NUM") == 0) return NUM;
	else if(strcmp(cadena, "DATE") == 0) return DATE;
	else if(strcmp(cadena,"EMAIL") == 0) return EMAIL;
	else if(strcmp(cadena, "TEXT") == 0) return TEXT;
	else return -1;
}

bool ValidarRepeticionCampos(char **cadena, int numCampos) {//Funcion que comprueba si uno de los campos esta  repetido
	int i, j;
	bool Validacion = false;
	for(i = 0; i < numCampos; i++){
		for(j = i+1; j < numCampos; j++){
			if(strcmp(cadena[i],cadena[j]) == 0) {
				Validacion = true;
			}
		}
	}
	return Validacion;
}

/*
	La funcion "ComprobarBDExistente" comprueba si el nombre que se ha introducido para la base de datos ya esta siendo utilizada
	Si ya esta siendo utilizada devolvemos false, sino true
*/

bool ComprobarBDExistente(char *nombreBD){ 
		DIR *contenidoCarpeta; 
		struct dirent *contenido;
		contenidoCarpeta = opendir(direccionArchivos); //Abrimos la carpeta donde estan las bases de datos
		if(contenidoCarpeta == NULL) { 
			printf("No se ha podido abrir la carpeta contenedora de las Bases de Datos\n");
		}else {
			while((contenido = readdir(contenidoCarpeta)) != NULL) { //Leemos uno por uno todas las bases de datos
				if(strcmp(contenido -> d_name, nombreBD) == 0){
					closedir(contenidoCarpeta);
					return false; //Comprobamos si el nombre introducido
				}															 // ya existe (d_name es el nombre de la Base de datos)
			}
		}
		closedir(contenidoCarpeta);
		return true;
}

bool ComprobarExistenciaTabla(char *nombreBD, char *nombreTabla) {//Funcion que comprueba si una tabla existe o no
	DIR *dir;

    char aux3[100] = "";
    
    strcat(aux3,nombreBD);
    strcat(aux3, "\\");
    strcat(aux3,nombreTabla);
    strcat(aux3, ".tab");

    if(access(aux3,F_OK) == 0 ){

        if(dir = opendir(nombreBD)){
            return true;
        }

    }
    else{
        return false;
    }
}

/*
*************************************************************
		Funciones de Comparacion y Ordenacion
*************************************************************
															*/

void ordenarASC(int campo, ROW *linea, TABLE *t) {//Funcion que ordena los valores de menos a mayor
	ROW *linea1, *linea2;
	int numero = 0;
	for(linea1 = linea; linea1 != NULL; linea1 = linea1 ->sig) {
		for(linea2 = linea1; linea2 != NULL; linea2 = linea2 -> sig) {
			if(t -> tipos[campo] == NUM) {
				if(atof(linea1 ->valores[campo]) > atof(linea2 -> valores[campo])) {
					intercambioValores(linea1,linea2);
				}
			}else if(t -> tipos[campo] == DATE) {
				if(datecmp(linea1 -> valores[campo],linea2 -> valores[campo]) > 0) {
					intercambioValores(linea1,linea2);
				}
			}else if(t -> tipos[campo] == EMAIL) {
				if(strcmp(linea -> valores[campo], linea2 -> valores[campo]) > 0) {
					intercambioValores(linea1,linea2);
				}
			}else if(t -> tipos[campo] == TEXT) {
				if(strcmp(linea -> valores[campo], linea2 -> valores[campo]) > 0) {
					intercambioValores(linea1,linea2);
				}
			}
		}
	}
}


void ordenarDES(int campo, ROW *linea, TABLE *t) {//Funcion que ordena los valores de mayor a menor
	ROW *linea1, *linea2;
	int numero = 0;
	for(linea1 = linea; linea1 != NULL; linea1 = linea1 ->sig) {
		for(linea2 = linea1; linea2 != NULL; linea2 = linea2 -> sig) {
			if(t -> tipos[campo] == NUM) {
				if(atof(linea1 ->valores[campo]) < atof(linea2 -> valores[campo])) {
					intercambioValores(linea1,linea2);
				}
			}else if(t -> tipos[campo] == DATE) {
				if(datecmp(linea1 -> valores[campo],linea2 -> valores[campo]) < 0) {
					intercambioValores(linea1,linea2);
				}
			}else if(t -> tipos[campo] == EMAIL) {
				if(strcmp(linea -> valores[campo], linea2 -> valores[campo]) < 0) {
					intercambioValores(linea1,linea2);
				}
			}else if(t -> tipos[campo] == TEXT) {
				if(strcmp(linea -> valores[campo], linea2 -> valores[campo]) < 0) {
					intercambioValores(linea1,linea2);
				}
			}
		}
	}
}

int datecmp(char *cad1, char *cad2) {//FUncion que compara dos fechas e indica cual es mayor o menor
	int dia, mes, ano;
	int dia2, mes2, ano2;
	Trim(cad2);
	Trim(cad1);
	dia=((cad1[0]-'0')*10)+cad1[1]-'0';
    mes=((cad1[3]-'0')*10)+cad1[4]-'0';
    ano=((cad1[6]-'0')*1000)+((cad1[7]-'0')*100)+((cad1[8]-'0')*10)+(cad1[9]-'0');
	dia2=((cad2[0]-'0')*10)+cad2[1]-'0';
    mes2=((cad2[3]-'0')*10)+cad2[4]-'0';
    ano2=((cad2[6]-'0')*1000)+((cad2[7]-'0')*100)+((cad2[8]-'0')*10)+(cad2[9]-'0');

	if(ano2 > ano) 
	{
		return -1;
	}
	else if(ano > ano2)
	{
		 return 1;
	}
	else {
		if(mes2 > mes) {
			return -1;
		}
		else if(mes > mes2) {
			return 1;
		}
		else {
			if(dia2 > dia) {
				return -1;
			}
			else if(dia > dia2) {

				 return 1;
			}
			else  {
				return 0;
			}
		} 
		return 0;
	}
	return 0;
}

int numcmp(char *cadena1,char* cadena2) {//Funcion que compara dos numeros e indica cual es mayor y cual menor
	int numero1, numero2;
	numero1 = atof(cadena1);
	numero2 = atof(cadena2);
	if(cadena1 > cadena2) return 1;
	else if(cadena2 > cadena1) return -1;
	else return 0;
}


													/*
*****************************************************
		Liberacion De Memoria
*****************************************************
*/


void liberarMemoriaLinea(ROW *linea, int numCampos) { //Funcion que libera  de memoria una linea
	ROW *lineaSiguiente;
	if(linea == NULL)
	{
		return;
	}

	while(linea != NULL)
	{
		lineaSiguiente = linea -> sig;
		
		for(int i = 0; i < numCampos; i++)
		{
			free(linea -> valores[i]);
		}
		free(linea -> valores);
		free(linea);
		linea = lineaSiguiente;	
	}
}

void liberarMemoriaTabla(TABLE *t) {//Funcion que libera de memoria una tabla

	TABLE *tablaSiguiente;
	if(t == NULL){
		return;
	}

	while(t != NULL) {
		tablaSiguiente = t -> sig;
		for(int i = 0; i < t -> numCampos; i++) {
			free(t -> campos[i]);
		}
		free(t -> campos);
		free(t -> tipos);
		free(t);
		t = tablaSiguiente;
	}

}

ROW *eliminarLineaValor(int numcampos, ROW *linea, TYPE tipo, char *valor, char *simbolo, int posicion) {//Funcion que borra el valor que confirma una condicion
	int i, j=1, k;
    int elementoEncontrado = 0;
    ROW *lineaaux = linea, *lineasiguiente, *lineaanterior;

    if(linea == NULL){
        printf("No se han encontrado datos\n");
    }
    else{

        if(tipo == NUM){

            if(strcmp("=", simbolo) == 0){

                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(atof(lineaaux->valores[posicion]) == atof(valor)){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;

            }
            else if(strcmp(">", simbolo) == 0){

                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(atof(lineaaux->valores[posicion]) > atof(valor)){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;


            }
            else if(strcmp("<", simbolo) == 0){

                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(atof(lineaaux->valores[posicion]) < atof(valor)){
                        elementoEncontrado++;

                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;

            /*
            else if(strcmp("<=", simbolo) == 0) {
                 while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(atof(lineaaux->valores[posicion]) <= atof(valor)){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;

            }
            else if(strcmp(">=", simbolo) == 0) {
                
                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(atof(lineaaux->valores[posicion]) >= atof(valor)){
                        elementoEncontrado++;

                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;

            }
            else if(strcmp("!=", simbolo) == 0) {
                
                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(atof(lineaaux->valores[posicion]) != atof(valor)){
                        elementoEncontrado++;

                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;
                */
            }
            else{
                printf("ERROR: SImbolo no valido\n");
            }

        }
        else if(tipo == DATE){

            if(strcmp("=", simbolo) == 0){

                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(datecmp(lineaaux->valores[posicion],valor) == 0){
                        elementoEncontrado++;

                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;

            }
            else if(strcmp(">", simbolo) == 0){

                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(datecmp(lineaaux->valores[posicion],valor) == 1){
                        elementoEncontrado++;

                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;


            }
            else if(strcmp("<", simbolo) == 0){

                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(datecmp(lineaaux->valores[posicion],valor) == -1){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;
                /*
            }
            else if(strcmp("<=", simbolo) == 0) {
                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(datecmp(lineaaux->valores[posicion],valor) != 1){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;

            }
            else if(strcmp(">=", simbolo) == 0) {
                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(datecmp(lineaaux->valores[posicion],valor) != -1){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;

            }
            else if(strcmp("!=", simbolo) == 0) {
                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(datecmp(lineaaux->valores[posicion],valor) != 0){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;
                */
            }
            else{
                printf("ERROR: SImbolo no valido\n");
            }

        }
        else if(tipo == EMAIL){
            
            if(strcmp("=", simbolo) == 0){

                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(strcmp(lineaaux->valores[posicion],valor) == 0){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;

            }
            else if(strcmp(">", simbolo) == 0){

                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(strcmp(lineaaux->valores[posicion],valor) > 0 ){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;


            }
            else if(strcmp("<", simbolo) == 0){

                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(strcmp(lineaaux->valores[posicion], valor) < 0){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;
/*
            }
            else if(strcmp("<=", simbolo) == 0) {
                 while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(strcmp(lineaaux->valores[posicion], valor) != 1){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;

            }
            else if(strcmp(">=", simbolo) == 0) {
                 while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(strcmp(lineaaux->valores[posicion], valor) != -1){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;

            }
            else if(strcmp("!=", simbolo) == 0) {
                 while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(strcmp(lineaaux->valores[posicion], valor) != 0){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;
                */
            }
            else{
                printf("ERROR: SImbolo no valido\n");
            }
        }
        else if(tipo == TEXT){

            if(strcmp("=", simbolo) == 0){

                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(strcmp(lineaaux->valores[posicion],valor) == 0){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");

                return linea;

            }
            else if(strcmp(">", simbolo) == 0){

                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(strcmp(lineaaux->valores[posicion],valor) > 0){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");

                return linea;


            }
            else if(strcmp("<", simbolo) == 0){

                while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(strcmp(lineaaux->valores[posicion],valor) < 0){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;
                /*
            }
            else if(strcmp("<=", simbolo) == 0) {
                 while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(strcmp(lineaaux->valores[posicion], valor) != 1){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");

                return linea;

            }
            else if(strcmp(">=", simbolo) == 0) {
                 while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(strcmp(lineaaux->valores[posicion], valor) != -1){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;

            }
            else if(strcmp("!=", simbolo) == 0) {
                 while(lineaaux != NULL){
                  

                    lineasiguiente = lineaaux->sig;
                    lineaanterior = lineaaux->ant;

                    if(strcmp(lineaaux->valores[posicion], valor) != 0){
                        elementoEncontrado++;
                        //UNICO NODO
                        if(lineaaux == linea && lineaaux->sig == NULL){

                            linea = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux == linea && lineaaux->ant == NULL){ //BORRAR PRIMER NODO

                            linea = linea->sig;
                            linea->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);
                        }
                        else if(lineaaux->sig == NULL){ //BORRAR ULTIMO NODO

                            lineaanterior->sig = NULL;
                            lineaaux->ant = NULL;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                        else{

                            lineaanterior->sig = lineasiguiente;
                            lineasiguiente->ant = lineaanterior;

                            for(i=0; i<numcampos; i++){
                                free(lineaaux->valores[i]);
                            }
                            free(lineaaux->valores);
                            free(lineaaux);

                        }
                    }
                    //apuntar puntero a siguiente
                    lineaaux = lineasiguiente;
                }
                
                if(elementoEncontrado == 0) printf("ERROR: Ningun elemento con ese valor encontrado\n");
                return linea;
                */
            }
            else{
                printf("ERROR: SImbolo no valido\n");
            }
        }
    }
}

TABLE *borrarTabla(TABLE *t, char *nombreBD, char *nombreTabla) {//Funcion que elimina una table de la base de datos
    TABLE *tAux;
    TABLE *tSig, *tAnt;
    DIR *dir;
    char Aux[100];
    int aux;
    strcpy(Aux, nombreBD);
    strcat(Aux, "\\");
    strcat(Aux, nombreTabla);
    strcat(Aux, ".tab");
    if(dir = opendir(nombreBD)) {
        if(t == NULL) {
            printf("ERROR: Tabla Vacia\n");
            return t;
        }
        if(ComprobarExistenciaTabla(nombreBD, nombreTabla)) {
            tAux = BuscarTablaExistente(nombreTabla, t);
            tSig = tAux -> sig;
            tAnt = tAux -> ant;


            if(tAux == t && tSig == NULL) {
                t = NULL;
              
            }
            else if(tAux == t && tAnt == NULL) {
                t = t -> sig;
                tSig -> ant = NULL;
                tAux -> sig = NULL;

            }else if(tAux -> sig == NULL) {
                tAnt -> sig = NULL;
                tAux -> ant = NULL;
              
            }else {
                tAnt -> sig = tAux -> sig;
                tSig -> ant = tAux -> ant;

                
            }

            for(int i = 0; i < tAux -> numCampos; i++) {
                free(tAux -> campos[i]);
            }
            free(tAux -> campos);
            free(tAux -> tipos);
            free(tAux);
            remove(Aux);
        }else {
            printf("ERROR: Tabla no existente\n");
        }
    }
    editar_meta(nombreBD, t);
    return t;
}

TABLE *borrarBD (TABLE *t, char *nombreBD) {//Funcion que elimina una base de datos
    DIR *dir;
    TABLE *tAux = t, *tSig = NULL, *tAnt = NULL;
    char aux[100];

    if(dir = opendir(nombreBD)) {
        if(t == NULL) {
            return NULL;
        }
        else {
            while(t != NULL) {

                tAux = t;
                tSig = tAux -> sig;
                tAnt = tAux -> ant;


                strcpy(aux, nombreBD);
                strcat(aux, "\\");
                strcat(aux, tAux -> nombre);
                strcat(aux, ".tab");
                t = borrarTabla(t, nombreBD, tAux -> nombre);
            }
            closedir(dir);
            strcpy(aux, nombreBD);
            strcat(aux, "\\meta.db");
            remove(aux);
            rmdir(nombreBD);
        }
    }
    return NULL;
}

