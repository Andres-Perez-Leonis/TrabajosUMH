/**
 * 
 */
package es.umh.poo.Practica2.Preguntas.Test;

/**
 * @author Andrés
 *
 */
public class PreguntaOpciones extends PreguntaTipoText {
	

	//Atributos
	
	/**
	 * Atributos para el correcto funcionamiento/deficion de la clase PreguntaOpciones
	 * nRespuestas -> Indica el numero de posibles respuestas que tiene la pregunta
	 * respuestaCorrecta -> Indica si una pregunta es correcta o no
	 * respuesta -> Array que contiene las posibles respuestas
	 */
	
	private int nRespuestas;
	private Boolean[] respuestaCorrecta;
	private String[] respuesta;
	
	//Constructores
	
	/**
	 * Constructor de la clase PreguntaOpciones para el caso de tener texto aclaratorio
	 * @param textoPregunta
	 * @param textoAclaratorio
	 * @param Valorpregunta
	 * @param preguntasResta
	 * @param nRespuestas
	 * @param respuesta
	 * @param respuestaCorrecta
	 */
	
	public PreguntaOpciones(String textoPregunta, String textoAclaratorio, float Valorpregunta, Boolean preguntasResta,
			int nRespuestas, String[] respuesta ,Boolean[] respuestaCorrecta) {
		super(textoPregunta, textoAclaratorio, Valorpregunta, preguntasResta);
		this.nRespuestas = nRespuestas;
		this.respuestaCorrecta = respuestaCorrecta;
		this.respuesta = respuesta;
	}
	
	/**
	 * Constructor de la clase PreguntaOpciones para el caso de no tener texto aclaratorio
	 * @param textoPregunta
	 * @param Valorpregunta
	 * @param preguntasResta
	 * @param nRespuestas
	 * @param respuesta
	 * @param respuestaCorrecta
	 */
	
	public PreguntaOpciones(String textoPregunta, float Valorpregunta, Boolean preguntasResta,
			int nRespuestas, String[] respuesta, Boolean[] respuestaCorrecta) {
		super(textoPregunta, Valorpregunta, preguntasResta);
		this.nRespuestas = nRespuestas;
		this.respuestaCorrecta = respuestaCorrecta;
		this.respuesta = respuesta;
	}
	
	/**
	 * Constructor vacio de la clase PreguntaOpciones
	 */
	
	public PreguntaOpciones() {
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
	 * Getter que devuelve el array respuestaCorrecta
	 * @return this.respuestaCorrecta
	 */
	public Boolean[] getRespuestaCorrecta() {
		return this.respuestaCorrecta;
	}
	
	/**
	 * Getter que devuelva el array respuestas
	 * @return this.respuesta
	 */
	public String[] getRespuesta() {
		return this.respuesta;
	}
	
	
}
