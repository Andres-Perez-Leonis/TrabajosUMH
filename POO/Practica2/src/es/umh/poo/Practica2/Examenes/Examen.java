/**
 * 
 */
package es.umh.poo.Practica2.Examenes;

import java.util.ArrayList;
import java.util.Date;

import es.umh.poo.Practica2.Asignaturas.Asignatura;
import es.umh.poo.Practica2.Preguntas.Pregunta;

/**
 * @author Andrés
 *
 */
public class Examen {

	// Atributos

	/**
	 * Atributos necesarios para el correcto funcionamiento/definicion de la clase
	 * Examen
	 * 
	 * fechaRealizacion -> Indicara cuando se ha realizado o se realizará el examen
	 * autor -> Indicara quien ha creado el examen asignatura -> Indicara de que
	 * asignatura es el examen convocatoria -> Indicara en que convocatoria se
	 * realizó o realizara el examen curso -> Indicara en que curso se hizo el
	 * examen tipoExamenes -> Indicara el tipo de examen que se esta realizando
	 * arrayPreguntas -> Array que indicara las preguntas que contiene el examen
	 */

	private Date fechaRealizacion;
	private String autor;
	private Asignatura asignatura;
	private String convocatoria;
	private String curso;
	private String tipoExamen;
	private ArrayList<Pregunta> arrayPreguntas = new ArrayList<Pregunta>();

	// Constructores

	/**
	 * Constructor de la clase pregunta, determina los valores de los atributos de
	 * la clase Examen
	 * 
	 * @param fechaRealizacion
	 * @param autor
	 * @param convocatoria
	 * @param curso
	 * @param tipoExamen
	 * @param asignatura
	 */
	public Examen(Date fechaRealizacion, String autor, int convocatoria, String curso, int tipoExamen,
			Asignatura asignatura) {

		String convocatoriasPosibles[] = { "Junio", "Septiembre", "Diciembre", "Enero" };
		String[] tiposPosibles = { "Opciones", "VF", "Rellenar", "Desorrollo/Practico", "Teorico", "Aleatorio" };
		// TODO Preguntar al profesor si utilizar variables dentro del constructor esta
		// mal

		this.fechaRealizacion = fechaRealizacion;
		this.curso = curso;
		this.autor = autor;
		this.convocatoria = convocatoriasPosibles[convocatoria];
		this.tipoExamen = tiposPosibles[tipoExamen];
		this.asignatura = asignatura;
	}

	// Metodos
	/**
	 * El metodo addPreguntas añade al array de Preguntas un objeto de la clase
	 * pregunta indicada
	 * 
	 * @param pregunta
	 */
	public void addPreguntas(Pregunta pregunta) {
		arrayPreguntas.add(pregunta);
	}

	/**
	 * El metodo crearExamen añade todas las preguntas al examen del tipo indica, a
	 * menos que sea de tipo aleatorio por lo que introduce preguntas aleatorias y
	 * devuelve el objeto Examen
	 * 
	 * @param tipoExamen
	 * @param valor
	 * @return this
	 */

	public Examen crearExamen(Class<?> tipoExamen, int valor) {
		ArrayList<Pregunta> arrayPreguntas = asignatura.getArrayPreguntas();
		int nPregunta;
		int contador = 0;
		float valorExamen = 0;
		Pregunta pregunta;
		if (tipoExamen == null) {
			while (valorExamen < valor) {
				if (contador > 50)
					break;
				nPregunta = (int) Math.random() * arrayPreguntas.size();
				pregunta = arrayPreguntas.get(nPregunta);
				valorExamen += pregunta.getValorPregunta() * valor / 10;
				addPreguntas(pregunta);
				contador++;
			}
		} else {
			while (valorExamen < valor) {
				if (contador > 50)
					break;
				nPregunta = (int) Math.random() * arrayPreguntas.size();
				pregunta = arrayPreguntas.get(nPregunta);
				if (pregunta.getClass() == tipoExamen) {
					valorExamen += pregunta.getValorPregunta() * valor / 10;
					addPreguntas(pregunta);
				}
				contador++;
			}
		}

		if (valorExamen < valor)
			return null;

		return this;
	}

	// Getters y Setters

	/**
	 * Getter que devuelve el valor del atributo fecchaRealizacion
	 * 
	 * @return this.fechaRealizacion
	 */
	public Date getFechaRealizacion() {
		return this.fechaRealizacion;
	}

	/**
	 * Getter que devuelve el valor del atributo autor
	 * 
	 * @return this.autor
	 */

	public String getAutor() {
		return this.autor;
	}

	/**
	 * Getter que devuelve el valor del atributo asignatura
	 * 
	 * @return this.asignatura
	 */
	public Asignatura getAsignatura() {
		return this.asignatura;
	}

	/**
	 * Getter que devuelve el valor del atributo convocatoria
	 * 
	 * @return this.convocatoria
	 */

	public String getConvocatoria() {
		return this.convocatoria;
	}

	/**
	 * Getter que devuelve el valor del atributo curso
	 * 
	 * @return this.curso
	 */

	public String getCurso() {
		return this.curso;
	}

	/**
	 * Getter que devuelve el valor del atributo tipoExamen
	 * 
	 * @return this.tipoExamen
	 */

	public String getTipoExamen() {
		return this.tipoExamen;
	}

	/**
	 * Getter que devuelve el array List de arrayPreguntas
	 * 
	 * @return this.arrayPreguntas
	 */

	public ArrayList<Pregunta> getArrayPreguntas() {
		return this.arrayPreguntas;
	}

}
