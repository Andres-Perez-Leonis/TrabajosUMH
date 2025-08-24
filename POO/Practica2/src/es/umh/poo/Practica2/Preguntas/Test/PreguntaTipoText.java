/**
 * 
 */
package es.umh.poo.Practica2.Preguntas.Test;

import es.umh.poo.Practica2.Preguntas.Pregunta;

/**
 * @author Andrés
 *
 */


public abstract class PreguntaTipoText extends Pregunta {

	//Atributos 
	
	/**
	 * Atributos para el correcto funcionamiento/definicion de la clase PreguntaTipoText
	 * preguntasResta -> Indica si la pregunta resta nota a la nota general
	 */
	
	private Boolean preguntasResta;
	
	//Constructores
	
	/**
	 * Constructor de la clase PreguntaTipoText para el caso de que este tenga texto Aclarratorio
	 * @param textoPregunta
	 * @param textoAclaratorio
	 * @param Valorpregunta
	 * @param preguntasResta
	 */

	public PreguntaTipoText(String textoPregunta, String textoAclaratorio, float Valorpregunta, Boolean preguntasResta) {
		super(textoPregunta, textoAclaratorio, Valorpregunta);
		this.preguntasResta = preguntasResta;
	}
	
	/**
	 * Constructor de la clase PreguntaTipoText para el caso de que este no tenga texto Aclarratorio
	 * @param textoPregunta
	 * @param Valorpregunta
	 * @param preguntasResta
	 */
	
	public PreguntaTipoText (String textoPregunta, float ValorPregunta, Boolean preguntasResta) {
		super(textoPregunta, ValorPregunta);
		this.preguntasResta = preguntasResta;
	}
	
	/**
	 * Constructor vacio de la clase PreguntaTipoText
	 */
	
	public PreguntaTipoText() {
		
	}
	
	//Getters y Setters
	
	/**
	 * Getter para devolver el valor del atributo preguntasResta
	 * @return
	 */
	
	public Boolean getPreguntasResta() {
		return this.preguntasResta;
	}
	
	
	
}
