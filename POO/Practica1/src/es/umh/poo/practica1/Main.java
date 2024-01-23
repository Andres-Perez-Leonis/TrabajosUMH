package es.umh.poo.practica1;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import es.umh.poo.practica1.objetos.Jugador;
import es.umh.poo.practica1.objetos.Partida;
import es.umh.poo.practica1.objetos.PartidaJuegoRuleta;
import es.umh.poo.practica1.objetos.Persistencia;

/**
 * @author Andrés
 * Practica 1 Programación Orientada Objetos 
 * Juego de Ruleta
 */
public class Main {

	
	/**
	 * @param args
	 * @throws ParseException 
	 */
	
	public static void main(String[] args) throws ParseException {
		
		String nombre, contrasena, alias, formatoFechaNacimiento;
		
		SimpleDateFormat formato = new SimpleDateFormat("dd/mm/yyyy");
		
		PartidaJuegoRuleta partidaJuego = new PartidaJuegoRuleta();
		Partida partida;
		Jugador jugador = null;
		Persistencia persistencia = new Persistencia();
		
		int numeroPartida = 0, intentoPartida = 0;
		

		persistencia.leerDeFichero(jugador);
		System.out.println("-------------------------------------- Ruleta de la Fortuna------------------------------------------\n\n\n");
		
		 
		int opcion = Integer.parseInt(partidaJuego.solicitarDato("¿Como quiere jugar? \n1.Usuario \n2.Invitado\n3.Cargar Jugador"));
		
		if(opcion == 1) {
				nombre = partidaJuego.solicitarDato("Ponga su nombre: ");
		
				contrasena = partidaJuego.solicitarDato("Ponga una password: ");
		
				alias = partidaJuego.solicitarDato("Coloque un alias: ");
		
				formatoFechaNacimiento = partidaJuego.solicitarDato("Fecha de Nacimiento (dd/mm/yyyy): ");
				Date fechaNacimiento = formato.parse(formatoFechaNacimiento);
		
			if(nombre != null || nombre == "") {
					jugador = new Jugador(alias, contrasena, fechaNacimiento, nombre);
					
			}else {
					jugador = new Jugador(alias, contrasena, fechaNacimiento);
			}
		}else if(opcion == 2) {
			
			jugador = new Jugador();
		}else {
			jugador = persistencia.buscarJugador(partidaJuego.solicitarDato("Introduce tu alias: "), 
										partidaJuego.solicitarDato("Introduce tu contraseña: "));
			if(jugador == null) { 
				System.out.println("Jugador no existente o contraseña erronea");
				System.out.println("Introduzca los datos correctamente");
			}
			
		}
		
		intentoPartida = Integer.parseInt(partidaJuego.solicitarDato("¿Cuantas partidas quieres jugar?"));
		
		if(intentoPartida == 0) partida = new Partida();
		else partida = new Partida(intentoPartida);
		
		if(opcion != 3) {
			String respuesta = partidaJuego.solicitarDato("¿Quieres guardar tu jugador?");
			if(respuesta.compareTo("Si") == 0
					|| respuesta.compareTo("si") == 0) {
					
						persistencia.addJugador(jugador);
						persistencia.convertirAJson();
				}
		}
		
		while(numeroPartida < partida.getPartidasAJugar()) {
			
			partidaJuego.jugar(jugador);
			numeroPartida++;
			
		}
	}
	
}
