/**
 * 
 */
package es.umh.poo.practica1.objetos;

import java.util.Arrays;

/**
 * @author Andrés
 *En esta clase estarátoda la gestión de los frases y caracteres que se utilicen
 *Si acierta o no alguna letra, etc...
 */

public class Caracter {
	
	//Atributos
	/**
	 * Atributos para el correcto funcionamiento de la clase Caracter
	 * 
	 * "vocalesUtilizadas" -> Almacena todas la vocales que el usuario a intentado utilizar
	 * "consonantesUtilizadas" -> Almacena todas las consonantes que el usuario a intentado utilizar
	 * "iteracionVocales" y "iteracionConsonantes" -> Almacena la posicion en la que esta en los vectores "vocalesUtilizadas" y "consonantesUtilizada"
	 * "vocales" -> Vector que almacena las vocales existentes para que el usuario no intente colocar una vocal cuando le pedimos una consonante
	 * "letraValida" y "vocalValida" -> Determina si la consonante o vocal que el usuario a introducido no la ha utilizado antes
	 */
	
	private char[] vocalesUtilizadas = new char[5];
	private char[] consonantesUtilizadas = new char[24];
	private char[] vocales = {'a','A','e','E','i','I','o','O','u','U'};
	
	private int iteracionVocales = 0, iteracionConsonantes = 0;
	
	private Boolean letraValida = true;
	private Boolean vocalValida = true;
	
	//Metodos
	
	
	/**
	 * Con el metodo "revisionConsonantes" comprobamos que la consonante introducida 
	 * por el jugador no haya sido introducida anteriormente y esta no sea una vocal
	 * @param consonante
	 */
	
	private void revisionConsonantes(char consonante) {
		for(int i = 0; i < vocales.length-1; i++) {
			if(consonante == vocales[i]) {
				letraValida = false;
				return;
			}
		}
		for(int i = 0; i < consonantesUtilizadas.length-1 ; i++) {
			
			if(consonante == consonantesUtilizadas[i]) {
				letraValida = false;
			}
		}
	}
	
	
	/**
	 * Con el metodo "revisionVocales" comprobamos que la vocal introducida por el 
	 * jugador no haya sido introducida anteriormente
	 * @param vocal
	 */
	
	private void revisionVocales(char vocal) {
		for(int i = 0; i < vocalesUtilizadas.length-1 ; i++) {
			if(vocal == vocalesUtilizadas[i]) {
				vocalValida = false;
			}
		}
	}
	
	//Getters y Setters
	
	
	/**
	 * Setter que introduce la vocal utilizada en la frase y en "vocalesUtilizadas"
	 * @param objetoFrase
	 * @param vocal
	 */
	
	public void setVocales(Frases objetoFrase, char vocal) {
		revisionVocales(vocal);
		if(vocalValida) {
			this.vocalesUtilizadas[iteracionVocales] = vocal;
			iteracionVocales++;
			objetoFrase.GeneradorFraseIncognita(vocal);
		}else {
			System.out.println("Letra no valida");
		}
		vocalValida = true;
	}
	
	
	/**
	 * Setter que introduce la consonante introducida en "consonantesUtilizadas"  y la envia a la frase oculta
	 * @param objetoFrase
	 * @param consonante
	 */
	
	public void setConsonantes(Frases objetoFrase, char consonante) {
		revisionConsonantes(consonante);
		if(letraValida) {
				this.consonantesUtilizadas[iteracionConsonantes] = consonante;
				iteracionConsonantes++;
				objetoFrase.GeneradorFraseIncognita(consonante);
		}else {
			System.out.println("Letra no valida");
		}
		letraValida = true;
	}
	
	
	/**
	 * Getter que devuelve el array de vocalesUtilizadas
	 * @return Arrays.toString(vocalesUtilizadas)
	 */
	
	public String getVocales() {
		return Arrays.toString(vocalesUtilizadas);
	}
	
	
	/**
	 * Getter que devuelve el array de consonantesUtilizadas
	 * @return Arrays.toString(consonantesUtilizadas)
	 */
	
	public String getConsonantes() {
		return Arrays.toString(consonantesUtilizadas);
	}
}
