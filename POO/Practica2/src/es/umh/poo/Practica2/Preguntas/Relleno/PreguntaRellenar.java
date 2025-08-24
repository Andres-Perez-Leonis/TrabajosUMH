/**
 * 
 */
package es.umh.poo.Practica2.Preguntas.Relleno;

import es.umh.poo.Practica2.Preguntas.Pregunta;

/**
 * @author Andrés
 *
 */
public class PreguntaRellenar extends Pregunta {
	
	
	//Atributos
	
	/**
	 * Atributos para el correcto funcionamiento/definicion de la clase PreguntaRellenar
	 * repuesta -> Array de string el cual contiene todas las respuestas a las frases de la pregunta
	 * frases -> Array de string el cual contiene todas las frases a rellenar/responder
	 */
	
	private String[] respuesta;
	private String[] frase;
	//Constructores
	
	/**
	 * Contructore de la clase Pregunta Rellener para el caso de que este tenga texto aclaratorio
	 * @param textoPregunta
	 * @param textoAclaratorio
	 * @param Valorpregunta
	 * @param frase
	 * @param respuesta
	 */
	
	public PreguntaRellenar(String textoPregunta, String textoAclaratorio, float Valorpregunta,
			String[] frase, String[] respuesta, String tipoPregunta) {
		super(textoPregunta, textoAclaratorio, Valorpregunta);
		this.frase = frase;
		this.respuesta = respuesta;
	}
	
	/**
	 * Contructore de la clase Pregunta Rellener para el caso de que este no tenga texto aclaratorio
	 * @param textoPregunta
	 * @param Valorpregunta
	 * @param frase
	 * @param respuesta
	 */
	
	public PreguntaRellenar(String textoPregunta, float Valorpregunta,
			String[] frase, String[] respuesta, String tipoPregunta) {
		super(textoPregunta, Valorpregunta);
		this.respuesta = respuesta;
		this.frase = frase;
	}
	
	/**
	 * Constructor vacio de la clase PreguntaRellenar
	 */
	
	public PreguntaRellenar() {}

	
	//Getters y Setters
	
	/**
	 * Getter para devolver el Array de respuestas 
	 * @return
	 */
	
	public String[] getRespuesta() {
		return this.respuesta;
	}
	
	/**
	 * Getter para devolver el Array de Frases a resolver 
	 * @return
	 */
	
	public String[] getFrase() {
		return this.frase;
	}

	
}
