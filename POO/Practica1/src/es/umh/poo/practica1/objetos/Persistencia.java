/**
 * 
 */
package es.umh.poo.practica1.objetos;

import java.util.ArrayList;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.lang.reflect.Type;

/**
 * @author Andrés
 *
 *	Esta clase servirá para controlar toda la parte del guardado y la carga de archivos
 *de la partida
 */
public class Persistencia {

	//Atributos
	
	public static ArrayList<Jugador> arrayJugadores = new ArrayList<Jugador>();
	
	/**
	 * Estos atributos estan para el correcto funcionamiento de la persistencia
	 * 
	 * "fraseAGuardar" -> Almacena el arrayList de jugadores cuando esta la convertimos en string
	 * "cadena" -> Almacena el string del arrayList que hemmos guardado con anterioridad
	 * "jugadorExistente" -> Determina una vez comprobado si los datos introducidos por el usuario ya existe
	 * "jugador" -> Almacena el jugador que ell usuario ha determinado
	 * "RUTA_FICHERO" -> Ruta a la que el programa debe acceder para encontrar el archivo .json
	 */
	
	private String fraseAGuardar;
	private String cadena;

	private Boolean jugadorExistente = false;
	
	Jugador jugador = null;
	
	private static final String RUTA_FICHERO = "./Jugadores.json";
	
	//Metodos
	
	
	/**
	 * Con el metodo "addJugador" añadimos el @param jugador al arraylist 
	 */
	
	public void addJugador(Jugador jugador) {
		arrayJugadores.add(jugador);
	}
	
	
	/**
	 * Con el metodo "convertirAJson" convertirmos @param jugador en tipo json, de manera que podamos introducirlo al fichero
	 */
	
	public void convertirAJson() {
		
		Gson gson = new GsonBuilder().create();
		fraseAGuardar = gson.toJson(arrayJugadores);

        try{
        	
            FileOutputStream ficheroSalida;
            File fichero = new File(RUTA_FICHERO);
			ficheroSalida = new FileOutputStream(fichero);
            OutputStreamWriter salida = new OutputStreamWriter(ficheroSalida);
            
            salida.write(fraseAGuardar);
            
            salida.close();

        }
        catch (IOException e){
            e.printStackTrace();
        }
        
    }
	
	
	/**
	 * Con el metodo "escribirEnFichero" escribimos en el fichero @param frase
	 */
	
	public void escribirEnFichero(String frase) {
		try {
			PrintWriter escribir = new PrintWriter(new File(RUTA_FICHERO));
			escribir.write(frase);
			escribir.flush();
			escribir.close();
		} catch(FileNotFoundException exception) {
			exception.printStackTrace();
		}
	}
	
	
	/**
	 * Con el metodo "leerDeFichero" leemos lo que esta escrito dentro del fichero de modo que lo convertimos en un objeto java
	 * @param jugador
	 */
	
	public void leerDeFichero(Jugador jugador) {
		String fraseFichero = "";
		StringBuilder sb = new StringBuilder();
		try {
			FileReader fr =new FileReader(RUTA_FICHERO);
			BufferedReader leer = new BufferedReader(fr);
			while((fraseFichero = leer.readLine()) != null) {
				sb.append(fraseFichero);
			}
			leer.close();
			cadena = sb.toString();
		} catch (FileNotFoundException exception) {
			exception.printStackTrace();
		} catch (IOException exception) {
			System.out.println(exception.getCause());
		}
		
		Type listType = new TypeToken<ArrayList<Jugador>>(){}.getType();
		Gson gson = new Gson();
		arrayJugadores = gson.fromJson(cadena.split("\\n")[0], listType);
	}
	
	
	/**
	 *  El metodo "buscarJugador" comprobaremos si los datos del jugadores introducidos 
	 * por el usuario *@param alias / @param contrasena* coinciden con alguno de los jugadores 
	 * guardados y si coincide con alguno  @return jugador
	 */
	
	public Jugador buscarJugador(String alias, String contrasena) {
		for(int i = 0; i < arrayJugadores.size(); i++) {
			jugador = arrayJugadores.get(i);
			if(jugador.getAlias().compareTo(alias) == 0 && jugador.getContrasena().compareTo(contrasena) == 0) break; 
		}	
		return jugador;
	}
	
	
	/**
	 *  Con el metodo "comprobarJugador" comprobamos los datos del nuevo jugador *@param alias*
	 * para que estos no coincidan con un jugador ya existente y si existe devolvemos
	 * @return jugadorExistente = true
	 */
	
	public Boolean comprobarJugador(String alias) {
		for (int i = 0; i < arrayJugadores.size(); i++) {
			jugador = arrayJugadores.get(i);
			if(jugador.getAlias().compareTo(alias) == 0) jugadorExistente = true;
		}
		return jugadorExistente;
	}
}
