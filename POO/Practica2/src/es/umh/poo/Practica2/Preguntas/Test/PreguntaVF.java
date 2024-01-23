/**
 * 
 */
package es.umh.poo.Practica2.Preguntas.Test;

/**
 * @author Andrés
 *
 */

public class PreguntaVF extends PreguntaTipoText {

	//Atributo
	
	/**
	 * Atributos para el correcto funcionamiento/deficion de la clase PreguntaOpciones
	 * nRespuestas -> Indica el numero de posibles respuestas que tiene la pregunta
	 * respuestaCorrecta -> Indica si una pregunta es correcta o no
	 * posiblesRespuestas -> Array que contiene las posibles respuestas
	 */
	private int nRespuestas;
	private Boolean[] respuestaCorrecta;
	private String[] posiblesRespuestas;


	//Constructores
	
	/**
	 * Constructor de la clase PreguntaVF para el caso de tener texto aclaratorio
	 * @param textoPregunta
	 * @param textoAclaratorio
	 * @param Valorpregunta
	 * @param preguntasResta
	 * @param nRespuestas
	 * @param posiblesRespuestas
	 * @param respuestaCorrecta
	 */
	
	public PreguntaVF(String textoPregunta, String textoAclaratorio, float Valorpregunta, Boolean preguntasResta, 
			int nRespuestas, String[] posiblesRespuestas ,Boolean[] respuestaCorrecta) {
		super(textoPregunta, textoAclaratorio, Valorpregunta, preguntasResta);
		this.nRespuestas = nRespuestas;
		this.posiblesRespuestas = posiblesRespuestas;
		this.respuestaCorrecta = respuestaCorrecta;
	}

	/**
	 * Constructor de la clase PreguntaVF para el caso de no tener texto aclaratorio
	 * @param textoPregunta
	 * @param Valorpregunta
	 * @param preguntasResta
	 * @param nRespuestas
	 * @param posiblesRespuestas
	 * @param respuestaCorrecta
	 */

	public PreguntaVF(String textoPregunta, float Valorpregunta, Boolean preguntasResta,
			int nRespuestas, String[] posiblesRespuestas ,Boolean[] respuestaCorrecta) {
		super(textoPregunta, Valorpregunta, preguntasResta);
		this.nRespuestas = nRespuestas;
		this.posiblesRespuestas = posiblesRespuestas;
		this.respuestaCorrecta = respuestaCorrecta;
		
	}
	
	
	/**
	 * Constructor vacio de la clase PreguntaVF
	 */
	
	public PreguntaVF() {
		
	}

	//Getters y Setters
	
	
	/**
	 * Getter que devuelve el valor numerico del atributo nRespuestas
	 * @return this.nRespuestas
	 */
	
	public int getnRespuestas() {
		return this.nRespuestas;
	}

	/**
	 * Getter que devuleve el Array del atributo respuestaCorrecta
	 * @return this.respuestaCorrecta
	 */
	
	public Boolean[] getRespuestacorrecta() {
		return this.respuestaCorrecta;
	}
	
	
	/**
	 * Getter que devuleve el Array del atributo de posiblesRespuestas
	 * @return this.posiblesRespuestas
	 */
	public String[] getPosiblesRespuestas() {
		return this.posiblesRespuestas;
	}



}
