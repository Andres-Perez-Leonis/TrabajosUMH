/**
 * 
 */
package es.umh.poo.practica1.objetos;

import java.util.Scanner;

/**
 * @author Andrés
 *
 */
public class PartidaJuegoRuleta {
	
	//Atributos
	/**
	 * Los atributos de esta clase y objetos creados son para ell correcto funcionamiento de
	 * la partida
	 * 
	 * "intentosPartida" -> Son los intentos que tiene el jugador para adivinar la frase
	 * "precioVocal" -> Es el valor de una vocal (este se restara a su puntuacion acumulada)
	 * "voocalElegida" -> Almacena la vocal que el jugador quiere comprar
	 * "consonanteElegida" -> Almacena la consonante que quiere buscar en la frase
	 * "respuesta" -> Se utiliza en ciertos puntos para analizar la respuesta a una pregunta
	 * "faseAdivinada" -> Almacena la frase que el jugador introduce (luego comprobamos si son iguales)
	 * "objetoTirada" -> Para acceder a la logica de las tiraadas de la ruleta
	 * "frase" -> Para accceder a la logica de las frases y a las propias frase para la partida
	 * "objetoCaracter" -> Para acceder a toda la logica de los caracteres (saber si se han utilizado, etc)
	 * "ganador" y "perdedor" -> Para determinar cuando el jugador a terminado la partida 
	 * "scanIn" -> Para leer los datos introducidos por el usuario
	 */
	
	private int intentosPartida = 10;
	private int precioVocal = 30;
	private int puntuacion;
	
	private String vocalElegida, consonanteElegida, respuesta, fraseAdivinada = "";
	
	private Tirada objetoTirada = new Tirada(); 
	private Frases frase = new Frases();
	private Caracter objetoCaracter = new Caracter();
	
	
	private Boolean ganador = false, perdedor = false;
	
	private Scanner scanIn = new Scanner(System.in);
	
	//Metodos
	
	/**
	 *  El metodo "solicitarDato" sirve para leer lo introducido por el teclado
	 * @param cadena, este parametro sirve para imrpimir por consola la pregunta
	 * que queremos hacerle al usuario
	 * @return scanIn.nextLine()
	 */
	public String solicitarDato(String cadena)
	{
		System.out.println(cadena);
		return scanIn.nextLine();
	}
	
	
	/**
	 * En el metodo "jugar tendremos todo el procedimiento y logica para que funcione
	 * el programa. 
	 * Revisar cunado se acierte la frase, detectar si alguna letra ya esta repetida,
	 * la gestion de la puntuacion, etc.
	 */
	
	public void jugar(Jugador jugador) {
		frase.FraseAleatoria(Integer.parseInt(solicitarDato("¿En que dificultad quieres jugar? \n1.Facil\n2.Medio\n3.Experto")));
		while(this.perdedor == false || this.ganador == false) {
			System.out.print(frase.getFraseOculta());
			puntuacion = objetoTirada.RealizarTirada();
			if(puntuacion >= this.precioVocal) {
				respuesta = solicitarDato("\n¿Quieres comprar una vocal? (Si/No)");
				comprarVocal(this.respuesta);
			}else{
				
				System.out.println("\nNo tienes suficientes puntos para comprar una vocal");
			
			}
			solicitarConsonante();
			ResolverFrase(solicitarDato("¿Quieres intentar adivinar la frase?"));
			seguirEnPartida(this.intentosPartida);
			respuesta = solicitarDato("¿Quieres mostrar tu informacion acutal? (Si/No)");
			mostrarInformacionResultado(respuesta, jugador.getAlias(), puntuacion, objetoCaracter.getVocales(), objetoCaracter.getConsonantes());
			intentosPartida--;
		}
	}
	
	
	/**
	 * Con el metodo "comprarVocal" comprobaremos con @param respuesta
	 * si el usuario quiere comprar una vocal
	 */
	
	public void comprarVocal(String respuesta) {
		if(respuesta.compareTo("Si") == 0 || respuesta.compareTo("si") == 0) {
			objetoTirada.vocalComprada(precioVocal);
			vocalElegida =  solicitarDato("Introduce una vocal: ");
			objetoCaracter.setVocales(frase, vocalElegida.charAt(0));
			
		}
	}
	
	
	/**
	 * Con el metodo "solicitarConsonante" solicitaremos la consonante
	 */
	
	public void solicitarConsonante() {
		do {
		consonanteElegida = solicitarDato("Introduce una consonante: ");
		}while(consonanteElegida.charAt(0) == ' ' || consonanteElegida == "");
		objetoCaracter.setConsonantes(frase, consonanteElegida.charAt(0));
	}
	
	
	/**
	 * Con el metodo "seguirEnPartida" comprobaremoos si acertó toda la frase
	 *  o si ha perdido todos sus intentos
	 * @param intentos
	 */
	
	public void seguirEnPartida(int intentos) { 
		if(intentos == 0) esPerdedor();
		if(frase.getFraseOculta().compareTo(frase.getFraseObtenida()) == 0) esGanador();
		
	}
	
	
	/**
	 * El metodo "ResolverFrase" sirve para saber si el usuario quiere
	 * adivinar la frase de forma directa y comprobaremos si acertó
	 * @param respuesta
	 */
	
	public void ResolverFrase(String respuesta) {
    	if(respuesta.compareTo("Si") == 0 || respuesta.compareTo("si") == 0) {
    		fraseAdivinada = solicitarDato("Introduce la frase: ");
    		fraseAdivinada = fraseAdivinada.toUpperCase();
    		if(fraseAdivinada.compareTo(frase.getFraseObtenida().toUpperCase()) == 0) esGanador();
    		else if (fraseAdivinada.compareTo(frase.getFraseObtenida()) != 0) System.out.println("Fallaste!!");
    		
    	}
	}
	
	
	/**
	 * Con el metodo "esGanador" indicaremos al jugador que ha ganado
	 * la partida
	 */
	
	public void esGanador() {
		System.out.println("Has acertado la frase.\n Ganaste!!!!");
		this.ganador = true;
	}
	
	
	/**Con el metodo "esPerdedor" indicaremos al jugador que ha perdido
	 * la partida
	 */
	
	public void esPerdedor() {
		System.out.println("Has perdido todos tus intentos");
		this.perdedor = true;
	}
	
	
	/**
	 * Con el metodo "mostrarInformacionResultado" imprimiremos en pantalla todos los 
	 * datos de la partida {
	 * @param respuesta (esta sirve exclusivamente pasa caber si el 
	 * 					usuario quiere ver la informacion)
	 * @param Alias
	 * @param Puntuacion
	 * @param vocalesUsadas
	 * @param consonantesUsadas
	 * }
	 */
	public void mostrarInformacionResultado(String respuesta, String Alias, int Puntuacion, String vocalesUsadas, String consonantesUsadas) {
		if(respuesta.compareTo("Si") == 0|| respuesta.compareTo("si") == 0) {
			System.out.println("Alias: " + Alias);
			System.out.println("\nPuntacion: " + Puntuacion);
			System.out.println("\nVocales usadas: " + vocalesUsadas);
			System.out.println("\nConsonantes usadas: " + consonantesUsadas);
		}
	}
}
