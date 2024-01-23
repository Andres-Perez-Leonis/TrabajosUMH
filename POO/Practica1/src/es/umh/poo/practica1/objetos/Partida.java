/**
 * 
 */
package es.umh.poo.practica1.objetos;

/**
 * @author Andrés
 *
 */
public class Partida {
	
	//Atributos
	
	/**
	 * Atributos para el correcto funcionamiento de la clase Partida
	 * 
	 * "numerosPartida" -> Almacena la cantidad de partidas que el jugador quiere jugar
	 * "puntuacion" -> Almacena la puntuacion que el jugador tiene durante la partida
	 */
	
	private int numeroPartidas = 3;
	private int puntuacion = 0;
	
	//Construtores
	
	
	/**
	 * Constructor para cuando el usuario no introduzca ningún número de partidas
	 */
	
	public Partida() {
		this.numeroPartidas = 3;
		this.puntuacion = 0;
	}
	
	
	/**
	 * Constructor para cuando el usuario introduzca un número de partidas 
	 * @param numeroPartidas
	 */
	
	public Partida(int numeroPartidas) {
		this.numeroPartidas = numeroPartidas;
		this.puntuacion = 0;
	}
	
	//Getters y Setters
	
	
	/**
	 * Setter que introoduce el valor de la puntuacion del jugador 
	 * (si el valor introducido = 0 entonces estara en bancarrota)
	 * 
	 * @param valorObtenido
	 */
	
	public void setPuntuacion(int valorObtenido) {
		if(valorObtenido == 0) this.puntuacion = 0;
		else this.puntuacion += valorObtenido;
	}
	
	
	/**
	 * Getter que devuelve el valor de la puntuacion de la partida
	 * @return this.puntuacion
	 */
	
	public int getPuntuacion() {
		return this.puntuacion;
	}
	
	
	/**
	 * Getter que devuelve el valor de numeroPartidas
	 * @return this.numeroPartidas
	 */
	
	public int getPartidasAJugar() {
		return this.numeroPartidas;
	}

}
