/**
 * 
 */
package es.umh.poo.Practica2.Preguntas.Teorico;

import es.umh.poo.Practica2.Preguntas.Pregunta;

/**
 * @author Andrés
 *
 */
public class PreguntaDesarrolloPractico extends Pregunta {

	//Atributos
	
	/**
	 * Atributos para el correcto funcionamiento/definicion de la clase PreguntaDesarrolloPractico
	 * textoApartado -> Array que contiene los textos de los apartados de la pregunta
	 * porcentajeApartado -> Array que contiene los porcentajes que vale cada apartado respecto del valor de la pregunta
	 */
	
	private String[] textoApartado;
	private int[] porcentajeApartado;
	
	//Constructores
	
	/**
	 * Constructor de la clase PreguntaDesarrolloPractico para el caso de que la pregunta tenga texto aclaratorio
	 * @param textoPregunta
	 * @param textoAclaratorio
	 * @param Valorpregunta
	 * @param textoApartado
	 * @param porcentajeApartado
	 */
	
	public PreguntaDesarrolloPractico(String textoPregunta, String textoAclaratorio, float Valorpregunta,
			String[] textoApartado, int[] porcentajeApartado) {
		super(textoPregunta, textoAclaratorio, Valorpregunta);
		this.textoApartado = textoApartado;
		this.porcentajeApartado = porcentajeApartado;
	}

	/**
	 * Constructor de la clase PreguntaDesarrolloPractico para el caso de que no tenga texto Aclaratorio 
	 * @param textoPregunta
	 * @param Valorpregunta
	 * @param textoApartado
	 * @param porcentajeApartado
	 */

	public PreguntaDesarrolloPractico(String textoPregunta, float Valorpregunta, String[] textoApartado,
			int[] porcentajeApartado) {
		super(textoPregunta, Valorpregunta);
		this.textoApartado = textoApartado;
		this.porcentajeApartado = porcentajeApartado;
	}

	
	/**
	 * Constructor vacio de la clase PreguntaDesarrolloPractico
	 */
	
	public PreguntaDesarrolloPractico() {}
	
	//Getters y Setters
	
	/**
	 * Getter para devolver el Array de textoApartado
	 * @return this.textoApartado
	 */
	
	public String[] getTexto() {
		return this.textoApartado;
	}
	
	/**
	 * Getter para devolver el Array de porcentajesApartado
	 * @return this.porcentajeApartado
	 */
	
	public int[] getPorcentaje() {
		return this.porcentajeApartado;
	}
	
	
	
}
