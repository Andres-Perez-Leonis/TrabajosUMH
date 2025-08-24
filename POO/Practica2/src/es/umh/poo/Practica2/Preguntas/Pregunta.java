/**
 * 
 */
package es.umh.poo.Practica2.Preguntas;

/**
 * @author Andrés
 *
 */
public class Pregunta {
	
	//Atributos
	
	/**
	 * Atributos para el correcto funcionamiento/definicion de la clase Pregunta 
	 * textoPregunta -> Indica el texto principal de la pregunta
	 * textoAclaratorio -> Indica el texto secundario de la pregunta (si este lo necesita
	 * valorPregunta -> Indica el valor numero del la pregunta en el examen
	 * tipoPregunta -> Indica el tipo de pregunta respecto a las posibles opciones 
	 */
	private String textoPregunta;
	private String textoAclaratorio;
	private float valorPregunta;
	
	//Constructores
	
	/**
	 * Constructor de la clase pregunta para el caso de que este tenga texto aclaratorio
	 * 
	 * @param textoPregunta
	 * @param textoAclaratorio
	 * @param Valorpregunta
	 */
	
	public Pregunta(String textoPregunta, String textoAclaratorio, float Valorpregunta) {
		this.textoPregunta = textoPregunta;
		this.textoAclaratorio = textoAclaratorio;
		this.valorPregunta = Valorpregunta;
	}
	
	/**
	 * Constructor de la clase pregunta para el caso de que este no tenga texto aclaratorio
	 * @param textoPregunta
	 * @param Valorpregunta
	 */
	
	public Pregunta(String textoPregunta, float valorPregunta) {
		this.textoPregunta = textoPregunta;
		this.valorPregunta = valorPregunta;
	}
	
	/**
	 * Contructor vacio
	 */
	
	public Pregunta() {}
	
	
	//Metodos

	
	//Getters y Setters
	
	/**
	 * Getter para devolver el valor del atributo textoPrgunta
	 * @return this.textoPregunta
	 */
	
	public String getTextoPregunta() {
		return this.textoPregunta;
	}
	
	/**
	 * Getter para devolver el valor del atributo textoAclaratorio
	 * @return this.textoAclaratorio
	 */
	
	public String getTextoAclaratorio() {
		return this.textoAclaratorio;
	}
	
	/**
	 * Getter para devoler el valor numerico del atributo valorPregunta
	 * @return this.valorPregunta
	 */
	
	public float getValorPregunta() {
		return this.valorPregunta;
	}
	
}
