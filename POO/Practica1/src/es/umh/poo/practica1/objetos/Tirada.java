/**
 * 
 */
package es.umh.poo.practica1.objetos;

/**
 * @author Andrés
 *
 */
public class Tirada {
	
	
	//Atributos
	
	
	/**
	 * Atributos para el correcto funcionamiento de la clase Tirada
	 * 
	 * "posiblesValores" -> Array que almacena los posibles puntos que el jugador consigue en la tirada
	 * "valor" -> Almacena la posicion del array "posiblesValores" en el cual esta los puntos que consigue el usuario
	 * "puntuacionAcumulada" -> Almacena la puntuacion acumulado durante la partida
	 * "objetoPartida" -> Para acceder a la logica de la clase partida
	 */
	
	private int[] posiblesValores = {0,10,20,30,40};
	
	private int valor;
	
	private Partida objetoPartida = new Partida();
	
	//Metodos
	
	
	/**
	 * El metodo "RealizarTirada" nos proporciona la puntuacion que gana el jugador
	 * en su tirada
	 * @return porsiblesValores[valor]
	 */

	public int RealizarTirada() {
		valor = (int) (Math.random()*5);
		if(valor == 0) {
			System.out.println("\nBancarrota");
			 objetoPartida.setPuntuacion(0);
		}else {
		objetoPartida.setPuntuacion(posiblesValores[valor]);
		}
		return objetoPartida.getPuntuacion();
	}
	
	
	/**
	 * Con el metodo vocalComprada quitamos los puntos que vale una vocal 
	 * a la puntuacion acumulada
	 * @param precioVocal, este es el precio de las vocales
	 */
	
	public void vocalComprada(int precioVocal) {
		objetoPartida.setPuntuacion(-precioVocal);
	}
}
