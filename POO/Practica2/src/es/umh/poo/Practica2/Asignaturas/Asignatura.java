/**
 * 
 */
package es.umh.poo.Practica2.Asignaturas;

import java.util.ArrayList;

import es.umh.poo.Practica2.Preguntas.Pregunta;

/**
 * @author Andrés
 *
 */
public class Asignatura {
	
	//Atributos
	/**
	 * Atributos para el correcto funcionamiento/definicion de la clase Asignatura
	 * codigoAsig -> Indica el codigo/siglas de la asignatura 
	 * titulo -> Indica el nombre de la asignatura
	 * arrayPreguntas -> Indica las preguntas que tienen relacion con esta asignatura
	 */
	private String codigoAsig;
	private String titulo;
	private ArrayList<Pregunta> arrayPreguntas = new ArrayList<Pregunta>();
	
	
	//Constructores
	
	/**
	 * Constructor de la clase Asignatura 
	 * @param codigoAsig
	 * @param titulo
	 * @param pregunta
	 */
	
	public Asignatura(String codigoAsig, String titulo, Pregunta pregunta) {
		this.codigoAsig = codigoAsig;
		this.titulo = titulo;
		arrayPreguntas.add(pregunta);
	}
	
	/**
	 * Constructor de la clase asignatura para el caso de que no tengamos ningun array de preguntas
	 * @param codigoAsig
	 * @param titulo
	 */
	
	public Asignatura(String codigoAsig, String titulo) {
		this.codigoAsig = codigoAsig;
		this.titulo = titulo;
	}
	
	/**
	 * Constructor vacio de la clase asignatura
	 */
	
	public Asignatura() {
		
	}
	
	
	
	//Metodos 
	
	/**
	 * El metodo addPregunta añade un objeto de la clase pregunta al Array List arrayPreguntas
	 * @param pregunta
	 */

	public void addPregunta(Pregunta pregunta) {
		arrayPreguntas.add(pregunta);
	}
	
	
	//Getters y Setters
	
	/**
	 * Getter para devolver el valor contenido en el atributo codigoAsig
	 * @return this.codigoAsig
	 */
	
	public String getCodigoAsig() {
		return this.codigoAsig;
	}
	
	/**
	 * Getter para devolver el valor contenido  en el atributo titulo
	 * @return this.titulo
	 */
	public String getTitulo() {
		return this.titulo;
	}
	/**
	 * Getter para devolver el Array List de objetos Pregunta arrayPregunta
	 * @return this.arrayPreguntas
	 */
	public ArrayList<Pregunta> getArrayPreguntas() {
		return this.arrayPreguntas;
	}

	
}
