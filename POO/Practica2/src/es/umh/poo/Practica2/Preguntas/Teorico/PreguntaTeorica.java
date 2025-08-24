/**
 * 
 */
package es.umh.poo.Practica2.Preguntas.Teorico;

import es.umh.poo.Practica2.Preguntas.Pregunta;

/**
 * @author Andrés
 *
 */
public class PreguntaTeorica extends Pregunta {
	
	//Atributos
	
	/**
	 * Atributos para el correcto funcionamiento/definicion de la clase PreguntaTeorica
	 * respuestaCorrecta -> Indica la pregunta correcta de la pregunta
	 */
	
	private String respuestaCorrecta;
	
	//Constructores 
	
	/**
	 * Constructor de la clase PreguntaTeorica para el caso de que tenga texto aclaratorio
	 * @param textoPregunta
	 * @param textoAclaratorio
	 * @param Valorpregunta
	 * @param respuestaCorrecta
	 */
	
	public PreguntaTeorica(String textoPregunta, String textoAclaratorio, float Valorpregunta,
			String respuestaCorrecta) {
		super(textoPregunta, textoAclaratorio, Valorpregunta);
		this.respuestaCorrecta = respuestaCorrecta;
	}
	
	/**
	 * Constructor de la clase PreguntaTeorica para el caso de no tener texto aclaratorio
	 * @param textoPregunta
	 * @param Valorpregunta
	 * @param respuestaCorrecta
	 */
	
	public PreguntaTeorica(String textoPregunta, float Valorpregunta, String respuestaCorrecta) {
		super(textoPregunta, Valorpregunta);
		this.respuestaCorrecta = respuestaCorrecta;
	}
	
	/**
	 * Contructor vacio de la clase PreguntaTeorica
	 */
	
	public PreguntaTeorica() {
	}

	
	
	//Getters y Setters
	
	/**
	 * Getter para devolver el valor del atributo respuestaCorrecta
	 * @return this.respuestaCorrecta
	 */
	
	public String getRespuestaCorrecta() {
		return this.respuestaCorrecta;
	}
	
}
