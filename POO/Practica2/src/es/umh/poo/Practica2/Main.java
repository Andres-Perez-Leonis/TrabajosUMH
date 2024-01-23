package es.umh.poo.Practica2;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;

import org.w3c.dom.ranges.RangeException;

import es.umh.poo.Practica2.Asignaturas.Asignatura;
import es.umh.poo.Practica2.Examenes.Examen;
import es.umh.poo.Practica2.ImprimiblePDF.ConstructorPDF;
import es.umh.poo.Practica2.Persistencia.Persistencia;
import es.umh.poo.Practica2.Preguntas.Pregunta;
import es.umh.poo.Practica2.Preguntas.Relleno.PreguntaRellenar;
import es.umh.poo.Practica2.Preguntas.Teorico.PreguntaDesarrolloPractico;
import es.umh.poo.Practica2.Preguntas.Teorico.PreguntaTeorica;
import es.umh.poo.Practica2.Preguntas.Test.PreguntaOpciones;
import es.umh.poo.Practica2.Preguntas.Test.PreguntaVF;

public class Main {

	/*
	 * Frases Generales
	 */
	static final String preguntasIniciales = "¿Que desea hacer?\n\n1.Crear Pregunta\n2.Crear Examen\n3.Ver Examenes Guardados\n4.Salir del Programa\n";
	static final String asignaturaInexistente = "Esa asignatura no existe o no se ha encontrado";
	static final String promtp = "[*]:>";
	static final String[] preguntasTipo = { "Opciones", "VF", "Rellenar", "Desorrollo/Practico", "Teorico",
			"Aleatorio" };
	static final String si = "si";
	static final String insuficientesPreguntas = "Hubo un error o no existen suficientes preguntas para crear el examen";
	static final String tiposExamen = "Los examenes creados y sus tipos son: ";
	static final String examenesInexistentes = "No hay examenes creados";
	static final String verExamen = "¿Quiere ver las preguntas de alguno de los examenes? (Si/No)";
	static final String lugarExamen = "Indique cual: (1\2\3\4...)";
	static final String opcionNoValida = "Esa opcion no es valida";

	/*
	 * Frase de Excepciones
	 */
	static final String excepcionInt = "El numero debe ser entero";
	static final String exceptionFloat = "El numero debe ser decimal/entero";
	static final String excepcionFloatFormato = "El formato para poner un numero con decimales es '0,5' (no colocarlo con un punto)";
	static final String exceptionVacio = "Coloque algo no lo deje vacio";
	static final String exceptionRango = "Asignatura no existente";
	static final String excepcionNoNumero = "Debes introducir un numero";
	static final String excepcionFormato = "Por favor, introduca la fecha con el formato correcto";
	static final String numeroEntero = "El numero indicado debe ser un numero entero";

	/*
	 * Frases Preguntas
	 */
	static final String preguntaAsignatura = "¿De que asignatura lo quiere? (1\\2\\3\\4....)";
	static final String preguntaCodigo = "¿Cual es el codigo de la asignatura?";
	static final String preguntaTipoPregunta = "¿Que tipo de pregunta quiere realizar? (1\\2\\3\\4\\5)\n\n1.Tipo Test de Opciones\n2.Tipo Test de V/F\n3.Rellenar\n4.Desarrollo-Practico\n5.Teorico\n";
	static final String preguntaTexto = "¿Cual es la pregunta?";
	static final String preguntaTextoAclaratorio = "¿Cual es el texto aclaratorio de la pregunta?";
	static final String preguntaValorPregunta = "¿Cual es el valor de la pregunta?";
	static final String preguntaResta = "¿La pregunta resta puntos? (Si/No)";
	static final String preguntaNRespuesta = "¿Cuantas opciones/respuestas/frases/apartado tendrá?";
	static final String preguntaRespuestaCorrecta = "¿Esta es la respuesta correcta? (Si/No)";
	static final String preguntaFrase = "Escriba la frase a resolver ";
	static final String preguntaRespuesta = "Escribe la respuesta/opcion/frase/apartado de la pregunta: ";
	static final String preguntaSiTextoAclaratorio = "¿Tendra un texto aclaratorio? (Si/No)";
	static final String preguntaPorcentajes = "¿Cual es el porcentaje del valor total del apartado?";

	/*
	 * Frases Examenes
	 */
	static final String preguntaTipoExamen = "¿Que tipo de examen quiere hacer? (1\\2\\3\\4\\5\\6)\n\n1.Tipo Test de Opciones\n2.Tipo Test de V/F\n3.Rellenar\n4.Desarrollo-Practico\n5.Teorico\n6.Aleatorio\n";
	static final String preguntaFecha = "¿Caunto se realizara el examen? (dd/mm/yyyy)\n";
	static final String preguntaAutor = "¿Quien esta creando el examen?";
	static final String preguntaCurso = "¿En que curso se realizara el examen?";
	static final String preguntaConvocatoria = "¿En que convocatoria se realizará el examen? (1\\2\\3\\4)\n\n1.Junio\n2.Septienmbre\n3.Diciembre\n4.Enero\n";
	static final String preguntaExamenValor = "¿Respecto a que valor estará el examen?";
	static final String preguntaExamen = "¿Cual examen quiere ver?";

	/*
	 * Frases de Impresion
	 */

	static final String creadorExamen = "Examen creado por: ";
	static final String cursoExamen = "Examen realizado en el curso: ";
	static final String dateExamen = "Examen realizado en: ";
	static final String generalExamen = "Preguntas del examen: \n";
	static final String verPreguntasExamen = "¿Quieres ver la respuesta de las preguntas? (Si/No)\n";
	static final String valorExamen = "Valor: ";
	static final String porcentajePreguntaExamen = "PorcentajeApartado = ";
	static final String examenesInexitentes = "No hay examenes creados";
	static final String imprimirExamen = "¿Quiere crear un pdf del examen? (Si/No)";
	static final String imprimirExamenRespeustas = "¿Quiere el examen con las respuastas? (Si/No)";

	// Variable Global

	static Boolean[] VF;
	static Scanner scanIn = new Scanner(System.in);

	public static void main(String[] args) {
		
		

		int opcionElegida = -1, opcionElegida2 = -1, elccionTipoExamen = -1;
		int nPreguntas;
		int[] porcentajes;
		int asigElegida = -1;

		int examElegido;
		float valor;

		Pregunta pregunta = null;
		Persistencia persistencia = Persistencia.getPersistencia();
		Asignatura asignaturaObjeto = null;
		Examen examen;

		String[] frases;
		String[] respuestas;

		SimpleDateFormat formato = new SimpleDateFormat("dd/mm/yyyy");
		Date fechaRealizacion = null;

		ArrayList<Examen> arrayExamenes;
		ArrayList<Asignatura> arrayAsig;
		ArrayList<Pregunta> arrayPreguntas;

		persistencia.leerDeFichero();
		arrayAsig = persistencia.asigCreadas();
		while (true) {
			
			opcionElegida = solicitarOpcion(preguntasIniciales, 6);
			asigElegida = -1;
			while ((asigElegida < 0 || asigElegida > arrayAsig.size()) && opcionElegida != 4) {
				try {

					System.out.println(preguntaAsignatura);
					for (int i = 0; i < arrayAsig.size(); i++) {
						System.out.printf("\n%d.%s (%s)\n", i, arrayAsig.get(i).getTitulo(),
								arrayAsig.get(i).getCodigoAsig());
					}

					asigElegida = solicitarOpcion("", arrayAsig.size() - 1);
					asignaturaObjeto = arrayAsig.get(asigElegida);

				} catch (RangeException e) {
					System.out.println(exceptionRango);

				} catch (IndexOutOfBoundsException bound) {
					System.out.println(exceptionRango);
				}
			}

			switch (opcionElegida) {
			case 1:
				opcionElegida2 = solicitarOpcion(preguntaTipoPregunta, 6);
				switch (opcionElegida2) {
				case 1:

					valor = solicitarValor(preguntaValorPregunta);

					if (solicitarBool(preguntaSiTextoAclaratorio)) {
						pregunta = new PreguntaOpciones(solicitarDato(preguntaTexto),
								solicitarDato(preguntaTextoAclaratorio), valor, solicitarBool(preguntaResta),
								nPreguntas = Integer.parseInt(solicitarDato(preguntaNRespuesta)),
								solicitarOpciones(nPreguntas), VF);
					} else {
						pregunta = new PreguntaOpciones(solicitarDato(preguntaTexto), valor,
								solicitarBool(preguntaResta),
								nPreguntas = Integer.parseInt(solicitarDato(preguntaNRespuesta)),
								solicitarOpciones(nPreguntas), VF);
					}
					break;
				case 2:

					valor = solicitarValor(preguntaValorPregunta);
					nPreguntas = solicitarOpcion(preguntaNRespuesta, 6);

					if (solicitarBool(preguntaSiTextoAclaratorio)) {
						pregunta = new PreguntaVF(solicitarDato(preguntaTexto), solicitarDato(preguntaTextoAclaratorio),
								valor, solicitarBool(preguntaResta), nPreguntas, solicitarOpciones(nPreguntas), VF);
					} else {
						pregunta = new PreguntaVF(solicitarDato(preguntaTexto), valor, solicitarBool(preguntaResta),
								nPreguntas, solicitarOpciones(nPreguntas), VF);
					}
					break;
				case 3:
					nPreguntas = solicitarOpcion(preguntaNRespuesta, 6);
					frases = new String[nPreguntas];
					respuestas = new String[nPreguntas];
					valor = solicitarValor(preguntaValorPregunta);

					for (int i = 0; i < nPreguntas; i++) {
						frases[i] = solicitarDato(preguntaFrase);
						respuestas[i] = solicitarDato(preguntaRespuesta);
					}
					if (solicitarBool(preguntaSiTextoAclaratorio)) {
						pregunta = new PreguntaRellenar(solicitarDato(preguntaTexto),
								solicitarDato(preguntaTextoAclaratorio), valor, frases, respuestas,
								preguntasTipo[opcionElegida2 - 1]);
					} else {
						pregunta = new PreguntaRellenar(solicitarDato(preguntaTexto), valor, frases, respuestas,
								preguntasTipo[opcionElegida2 - 1]);
					}
					break;
				case 4:
					valor = solicitarValor(preguntaValorPregunta);
					nPreguntas = solicitarOpcion(preguntaNRespuesta, 6);
					frases = new String[nPreguntas];
					porcentajes = new int[nPreguntas];

					for (int i = 0; i < nPreguntas; i++) {
						frases[i] = solicitarDato(preguntaFrase);
						porcentajes[i] = solicitarOpcion(preguntaPorcentajes, 1000);
					}
					if (solicitarBool(preguntaSiTextoAclaratorio)) {
						pregunta = new PreguntaDesarrolloPractico(solicitarDato(preguntaTexto),
								solicitarDato(preguntaTextoAclaratorio), valor, frases, porcentajes);
					} else {

						pregunta = new PreguntaDesarrolloPractico(solicitarDato(preguntaTexto), valor, frases,
								porcentajes);
					}
					break;
				case 5:
					valor = solicitarValor(preguntaValorPregunta);
					if (solicitarBool(preguntaSiTextoAclaratorio)) {
						pregunta = new PreguntaTeorica(solicitarDato(preguntaTexto),
								solicitarDato(preguntaTextoAclaratorio), valor, solicitarDato(preguntaRespuesta));
					} else {

						pregunta = new PreguntaTeorica(solicitarDato(preguntaTexto), valor,
								solicitarDato(preguntaRespuesta));
					}
					break;
				}
				if (pregunta != null) {
					asignaturaObjeto.addPregunta(pregunta);
					persistencia.convertirAsigGson();
				}

				break;

			case 2:
				elccionTipoExamen = solicitarOpcion(preguntaTipoExamen, 7);

				while (fechaRealizacion == null) {
					try {
						fechaRealizacion = formato.parse(solicitarDato(preguntaFecha));
					} catch (ParseException e) {
						System.out.println(excepcionFormato);
						fechaRealizacion = null;
					}
				}
				if (asignaturaObjeto != null) {
					examen = new Examen(fechaRealizacion, solicitarDato(preguntaAutor),
							solicitarOpcion(preguntaConvocatoria, 4) - 1, solicitarDato(preguntaCurso),
							elccionTipoExamen - 1, asignaturaObjeto);

					persistencia.addExamen(examen.crearExamen(conocerClase(elccionTipoExamen),
							solicitarOpcion(preguntaExamenValor, 1000)));
				} else {
					System.out.println(asignaturaInexistente);
				}
				persistencia.convertirExamenGson();
				break;
			case 3:
				// TODO imprimir todas las preguntas del examen
				arrayExamenes = persistencia.getExamenes();
				if (!arrayExamenes.isEmpty()) {
					System.out.println(tiposExamen);
					for (int i = 0; i < arrayExamenes.size(); i++) {
						examen = arrayExamenes.get(i);
						System.out.printf("\n%d.%s (%s)\n", i, examen.getAsignatura().getTitulo(), examen.getTipoExamen());
					}
					examElegido = -1;
					while (examElegido < 0 || examElegido >= arrayExamenes.size()) {
						try {
							examElegido = Integer.parseInt(solicitarDato(preguntaExamen));
							examen = arrayExamenes.get(examElegido);
							System.out.printf("%s %s\n", creadorExamen, examen.getAutor());
							System.out.printf("%s\n", examen.getCurso());
							System.out.printf("%s\n", examen.getFechaRealizacion());
							arrayPreguntas = examen.getArrayPreguntas();
							System.out.println(generalExamen);
							if (!solicitarBool(verPreguntasExamen)) {
								imprimirGeneralSinRespuestas(arrayPreguntas);
								System.out.println("\n");
								crearPdf(examen);
							} else {
								imprimirTodo(arrayPreguntas);
								System.out.println("\n");
								crearPdf(examen);
							}

						} catch (NumberFormatException parse) {
							if (!Character.isDigit(examElegido) || !Character.isLetter(examElegido)) {
								System.out.println(excepcionNoNumero);
								System.out.println(exceptionVacio);
							}
						} catch (RangeException e) {
							System.out.println(exceptionRango);

						} catch (IndexOutOfBoundsException bound) {
							System.out.println(exceptionRango);
						}
					}

				} else {
					System.out.println(examenesInexistentes);
				}
				break;
			case 4:
				return;

			}
		}
	}

	// Funciones

	
	public static void crearPdf(Examen examen) {
		ConstructorPDF constructor = new ConstructorPDF();
		if(solicitarBool(imprimirExamen)) {
				constructor.CrearPDF(examen, solicitarBool(imprimirExamenRespeustas));
		}
	}
	
	public static void imprimirTodo(ArrayList<Pregunta> arrayPreguntas) {
		Pregunta pregunta;
		String[] frases, respuestas;
		int[] porcentajes;
		for (int i = 0; i < arrayPreguntas.size(); i++) {
			pregunta = arrayPreguntas.get(i);
			imprimirGeneralSinRespuestas(arrayPreguntas);
			if (pregunta instanceof PreguntaOpciones) {
				imprimirRespuestaTest(((PreguntaOpciones) pregunta).getRespuesta(),
						((PreguntaOpciones) pregunta).getRespuestaCorrecta());
			} else if (pregunta instanceof PreguntaVF) {
				imprimirRespuestaTest(((PreguntaVF) pregunta).getPosiblesRespuestas(),
						((PreguntaVF) pregunta).getRespuestacorrecta());
			} else if (pregunta instanceof PreguntaDesarrolloPractico) {
				frases = ((PreguntaDesarrolloPractico) pregunta).getTexto();
				porcentajes = ((PreguntaDesarrolloPractico) pregunta).getPorcentaje();
				for (int j = 0; j < frases.length; j++) {
					System.out.printf("%d. %s\n%s%d\n", j, porcentajePreguntaExamen, frases[j], porcentajes[j]);
				}
			} else if (pregunta instanceof PreguntaTeorica) {
				System.out.println(((PreguntaTeorica) pregunta).getRespuestaCorrecta());
			} else if (pregunta instanceof PreguntaRellenar) {
				frases = ((PreguntaRellenar) pregunta).getFrase();
				respuestas = ((PreguntaRellenar) pregunta).getRespuesta();
				for (int j = 0; j < frases.length; j++) {
					System.out.printf("%d. %s\n%s%d\n", j, porcentajePreguntaExamen, frases[j], respuestas[j]);
				}
			}
		}
	}

	public static void imprimirTituloExamenes(ArrayList<Examen> arrayExamenes) {
		Examen examen;
		if (!arrayExamenes.isEmpty()) {
			System.out.println(tiposExamen);
			for (int i = 0; i < arrayExamenes.size(); i++) {
				examen = arrayExamenes.get(i);
				System.out.println("\n");
				System.out.printf("%d.%s (%s)", i, examen.getAsignatura().getTitulo(), examen.getTipoExamen());
				System.out.println("\n");
			}
		}
	}

	public static void imprimirGeneralSinRespuestas(ArrayList<Pregunta> arrayPreguntas) {
		Pregunta pregunta;
		for (int i = 0; i < arrayPreguntas.size(); i++) {
			pregunta = arrayPreguntas.get(i);
			System.out.printf("%d. %s\n", i + 1, pregunta.getTextoPregunta());
			System.out.printf("%s%f\n\n", valorExamen, pregunta.getValorPregunta());
		}
	}

	public static String solicitarDato(String cadena) {
		System.out.println(cadena);
		System.out.println(promtp);
		return scanIn.nextLine();
	}

	public static float solicitarValor(String cadena) {
		float valor = -1;
		while (valor < 0) {
			try {
				System.out.println(cadena);
				System.out.println(promtp);
				valor = Float.parseFloat(scanIn.nextLine());
			} catch (NumberFormatException parse) {
				parse.getCause();
				System.out.println(excepcionNoNumero);
				System.out.println(exceptionVacio);
				System.out.println(excepcionFloatFormato);
				System.out.println(exceptionFloat);
				valor = -1;
			}
		}
		return valor;
	}

	public static Boolean solicitarBool(String cadena) {
		System.out.println(cadena);
		System.out.println(promtp);

		if ((scanIn.nextLine()).toUpperCase().compareTo(si.toUpperCase()) == 0) {
			return true;
		}
		return false;
	}

	public static int solicitarOpcionAsig(ArrayList<Asignatura> arrayAsig) {
		int opcionElegida = -1;
		while (opcionElegida < 0 || opcionElegida > arrayAsig.size()) {
			try {
				opcionElegida = Integer.parseInt(solicitarDato(preguntasIniciales));
				if (opcionElegida < 0 || opcionElegida > arrayAsig.size()) {
					System.out.println(exceptionRango);
				}
			} catch (NumberFormatException parse) {
				parse.getCause();
				if (!Character.isDigit(opcionElegida) || !Character.isLetter(opcionElegida)) {
					System.out.println(excepcionNoNumero);
					System.out.println(exceptionVacio);
				}
			}
		}
		return opcionElegida;
	}

	public static int solicitarOpcion(String cadena, int maximo) {
		int opcionElegida2 = -1;
		while (opcionElegida2 < 0 || opcionElegida2 > maximo) {
			try {
				opcionElegida2 = Integer.parseInt(solicitarDato(cadena));
			} catch (NumberFormatException parse) {
				if (!Character.isDigit(opcionElegida2) || !Character.isLetter(opcionElegida2)) {
					System.out.println(excepcionNoNumero);
					System.out.println(exceptionVacio);
				}
			}
		}
		return opcionElegida2;
	}

	public static void imprimirRespuestaTest(String[] respuestas, Boolean[] VF) {
		String[] pCorrectas = new String[VF.length];
		for (int i = 0; i < VF.length; i++) {
			if (VF[i]) {
				pCorrectas[i] = "Correcta";
			} else {
				pCorrectas[i] = "Incorrecta";
			}
		}
		for (int i = 0; i < respuestas.length; i++) {
			System.out.printf("%s (%s)\n", respuestas[i], pCorrectas[i]);
		}
	}

	public static String[] solicitarOpciones(int cantidadPreguntas) {
		String[] opciones = new String[cantidadPreguntas];
		VF = new Boolean[cantidadPreguntas];
		for (int i = 0; i < cantidadPreguntas; i++) {
			opciones[i] = solicitarDato(preguntaRespuesta);
			VF[i] = solicitarBool(preguntaRespuestaCorrecta);
		}
		return opciones;
	}

	public static Class<?> conocerClase(int tipoElegido) {
		if (tipoElegido == 1) {
			return PreguntaOpciones.class;
		} else if (tipoElegido == 2) {
			return PreguntaVF.class;
		} else if (tipoElegido == 3) {
			return PreguntaRellenar.class;
		} else if (tipoElegido == 4) {
			return PreguntaDesarrolloPractico.class;
		} else if (tipoElegido == 5) {
			return PreguntaTeorica.class;
		}

		return null;
	}

}
