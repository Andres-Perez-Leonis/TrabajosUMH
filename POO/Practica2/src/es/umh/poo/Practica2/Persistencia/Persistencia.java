/**
 * 
 */
package es.umh.poo.Practica2.Persistencia;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import es.umh.poo.Practica2.Asignaturas.Asignatura;
import es.umh.poo.Practica2.Examenes.Examen;
import es.umh.poo.Practica2.Preguntas.Pregunta;
import es.umh.poo.Practica2.Preguntas.Relleno.PreguntaRellenar;
import es.umh.poo.Practica2.Preguntas.Teorico.PreguntaDesarrolloPractico;
import es.umh.poo.Practica2.Preguntas.Teorico.PreguntaTeorica;
import es.umh.poo.Practica2.Preguntas.Test.PreguntaOpciones;
import es.umh.poo.Practica2.Preguntas.Test.PreguntaVF;
import es.umh.poo.Practica2.runTime.RuntimeTypeAdapterFactory;

/**
 * @author Andrés
 *
 */
public class Persistencia {

	// Atributos

	/**
	 * Atributos para el correcto funcionamiento/definicion de la clase pregunta
	 * RUTA_CARPETA_FICHERO -> Indica la ubicacion del archivo gson donde se
	 * guardaran los datos de los Examenes y Asignaturas arrayAsignatura -> Indica
	 * las asignaturas existentes arrayExamenes -> Indica los examenes creados
	 */

	private static final String RUTA_CARPETA_FICHERO = "./files/Persistencia.json";
	private ArrayList<Asignatura> arrayAsignaturas;
	private ArrayList<Examen> arrayExamenes;
	private static Persistencia persistencia = null;
	
	/**
	 * Constructor privado para poder implementar el patron Singleton
	 */
	
	private Persistencia() {};
	

	// Metodos

	/**
	 * El metodo addAsignatura añade al array List arrayAsignaturas un objeto de
	 * tipo Asignatura
	 * 
	 * @param asignatura
	 */
	public void addAsignatura(Asignatura asignatura) {
		this.arrayAsignaturas.add(asignatura);
	}

	/**
	 * El metodo addAsignatura añade al array List arrayExamenes un objeto de tipo
	 * Examen
	 * 
	 * @param asignatura
	 */
	public void addExamen(Examen examen) {
		this.arrayExamenes.add(examen);
	}

	/**
	 * El metodo asigCreadas comprueba si hay asignaturas dentro del ArrayList de
	 * asignaturas y si esta vacio añade las asignaturas de POO y DADM y devuelve el
	 * arrayList
	 * 
	 * @return arrayAsignaturas
	 */

	public ArrayList<Asignatura> asigCreadas() {
		if (arrayAsignaturas.isEmpty()) {
			Asignatura asigPOO = new Asignatura("POO", "Programacion Orientada a Objetos");
			Asignatura asigDADM = new Asignatura("DADM", "Desarrollo de aplicaciones para dispositivos moviles");
			addAsignatura(asigPOO);
			addAsignatura(asigDADM);
		}
		return arrayAsignaturas;
	}

	/**
	 * El metodo convertirExamenGson, convierte el ArrayList de examenes en gson de
	 * forma que pueda introducirse dentro de un archivo .json y luego esos datos
	 * puedan ser leidos y utilizados
	 */

	public void convertirExamenGson() {
		RuntimeTypeAdapterFactory<Pregunta> runTimeTypeAdapter = RuntimeTypeAdapterFactory.of(Pregunta.class, "tipo")
				.registerSubtype(PreguntaRellenar.class, PreguntaRellenar.class.getName())
				.registerSubtype(PreguntaDesarrolloPractico.class, PreguntaDesarrolloPractico.class.getName())
				.registerSubtype(PreguntaTeorica.class, PreguntaTeorica.class.getName())
				.registerSubtype(PreguntaOpciones.class, PreguntaOpciones.class.getName())
				.registerSubtype(PreguntaVF.class, PreguntaVF.class.getName());

		Gson gson = new GsonBuilder().registerTypeAdapterFactory(runTimeTypeAdapter).create();

		String cadena = gson.toJson(this);

		OutputStreamWriter osw = null;
		try {

			FileOutputStream archivoSalida;
			File archivo = new File(RUTA_CARPETA_FICHERO);
			archivoSalida = new FileOutputStream(archivo);
			osw = new OutputStreamWriter(archivoSalida);

			osw.write(cadena);
			osw.close();

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (osw != null) {
					osw.close();
				}
			} catch (IOException y) {
				y.printStackTrace();
			}
		}

	}

	/**
	 * El metodo convertirAsigGson, convierte el ArrayList de Asignaturas en gson de
	 * forma que pueda introducirse dentro de un archivo .json y luego escribe los
	 * datos convertidos en el fichero
	 */

	public void convertirAsigGson() {

		RuntimeTypeAdapterFactory<Pregunta> runTimeTypeAdapter = RuntimeTypeAdapterFactory.of(Pregunta.class, "tipo")
				.registerSubtype(PreguntaRellenar.class, PreguntaRellenar.class.getName())
				.registerSubtype(PreguntaDesarrolloPractico.class, PreguntaDesarrolloPractico.class.getName())
				.registerSubtype(PreguntaTeorica.class, PreguntaTeorica.class.getName())
				.registerSubtype(PreguntaOpciones.class, PreguntaOpciones.class.getName())
				.registerSubtype(PreguntaVF.class, PreguntaVF.class.getName());

		Gson gson = new GsonBuilder().registerTypeAdapterFactory(runTimeTypeAdapter).create();

		String cadena = gson.toJson(this);

		OutputStreamWriter osw = null;
		try {

			FileOutputStream archivoSalida;
			File archivo = new File(RUTA_CARPETA_FICHERO);
			archivoSalida = new FileOutputStream(archivo);
			osw = new OutputStreamWriter(archivoSalida);

			osw.write(cadena);
			osw.close();

		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (osw != null) {
					osw.close();
				}
			} catch (IOException y) {
				y.printStackTrace();
			}
		}

	}

	/**
	 * El metodo leerDeFichero lee los datos del fichero .json y los transforma para
	 * que puedan ser utilizados por el programa
	 */

	public void leerDeFichero() {
		String fraseFichero = "";
		String cadena = "";
		StringBuilder sb = new StringBuilder();
		try {
			FileReader fr = new FileReader(RUTA_CARPETA_FICHERO);
			BufferedReader leer = new BufferedReader(fr);
			while ((fraseFichero = leer.readLine()) != null) {
				sb.append(fraseFichero);
			}
			leer.close();
			cadena = sb.toString();
		} catch (FileNotFoundException exception) {
			exception.printStackTrace();
		} catch (IOException exception) {
			System.out.println(exception.getCause());
		}

		RuntimeTypeAdapterFactory<Pregunta> runTimeTypeAdapter = RuntimeTypeAdapterFactory.of(Pregunta.class, "tipo")
				.registerSubtype(PreguntaRellenar.class, PreguntaRellenar.class.getName())
				.registerSubtype(PreguntaDesarrolloPractico.class, PreguntaDesarrolloPractico.class.getName())
				.registerSubtype(PreguntaTeorica.class, PreguntaTeorica.class.getName())
				.registerSubtype(PreguntaOpciones.class, PreguntaOpciones.class.getName())
				.registerSubtype(PreguntaVF.class, PreguntaVF.class.getName());

		Gson gson = new GsonBuilder().registerTypeAdapterFactory(runTimeTypeAdapter).create();
		Persistencia pers = gson.fromJson(cadena.split("\\n")[0], Persistencia.class);

		if (pers != null) {
			this.arrayAsignaturas = pers.arrayAsignaturas;
			this.arrayExamenes = pers.arrayExamenes;
		}

		if (arrayAsignaturas == null) {
			arrayAsignaturas = new ArrayList<Asignatura>();
		}

		if (arrayExamenes == null) {
			arrayExamenes = new ArrayList<Examen>();
		}
	}

	// Getter y Setter
	
	/**
	 * Getter que devuelve el acceso a esta clase 
	 * @return persistencia
	 */
	
	public static Persistencia getPersistencia() {
		if(persistencia == null) {
			persistencia = new Persistencia();
		}
		return persistencia;
	}
	
	
	
	/**
	 * Getter que devuelve el Array List arrayAsignaturas
	 * 
	 * @return this.arrayAsignaturas
	 */

	public ArrayList<Asignatura> getAsignaturas() {
		return this.arrayAsignaturas;
	}

	/**
	 * Getter que devuelve el Array List arrayExamenes
	 * 
	 * @return this.arrayExamenes
	 */

	public ArrayList<Examen> getExamenes() {
		return this.arrayExamenes;
	}

}
