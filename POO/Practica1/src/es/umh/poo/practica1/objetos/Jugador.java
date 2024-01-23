package es.umh.poo.practica1.objetos;
import java.util.Date;
public class Jugador {
	//Atributos
	
	/**
	 *  Atributos de la clase para definir de forma correcta un Jugador y que ete pueda 
	 * volver a utilizarlo
	 */
	
	private String alias = "";
	private String contrasena;
	private Date fechaNacimiento;
	private String Nombre;
	
	
	//Constructores
	
	
	/**
	 * Contructor para aquellos usuarios que no introduzcan un nombre para su jugador
	 * @param alias
	 * @param contrasena
	 * @param fechaNacimiento
	 */
	
	public Jugador(String alias, String contrasena, Date fechaNacimiento) {
		this.alias = alias;
		do {
			this.contrasena = contrasena;
		}while(ValidarContrasena(contrasena) != true);
		this.fechaNacimiento = fechaNacimiento;
	}
	
	
	/**
	 * Contructor para aquellos usuarios que introduzcan todos los datos para su jugador
	 * @param alias
	 * @param contrasena
	 * @param fechaNacimiento
	 * @param Nombre
	 */
	
	public Jugador(String alias, String contrasena, Date fechaNacimiento, String Nombre) {
		this.alias = alias;
		do {
			this.contrasena = contrasena;
		}while(ValidarContrasena(contrasena) != true);
		this.fechaNacimiento = fechaNacimiento;
		this.Nombre = Nombre;
	}
	
	
	/**
	 * Contructor para aquellos usuarios que quieren jugar como invitado
	 */
	
	public Jugador() {} 
	
	//Metodos
	
	
	/**
	 * El metodo "ValidarContrana" sirve para comprobar que la contraseña introducida 
	 * por el jugador tiene mas de 6 caracteres
	 * @param contrasena
	 */
	
	public Boolean ValidarContrasena(String contrasena) {
		PartidaJuegoRuleta partida = new PartidaJuegoRuleta();
		while(contrasena.length() < 6) {
			contrasena = partida.solicitarDato("Contreseña no valida. \nDebe terner 6 caracteres. \nVuelve a colocar el password: ");
		}
		return true;
	}

	
	//Getters y Setters
	
	/**
	 * Getter para devolver el valor que tenga el atributo Alias
	 * @return this.alias
	 */
	
	public String getAlias() {
		return this.alias;
	}
	
	
	/**
	 * Getter para devolver el valor que tenga el atributo contrasena
	 * @return this.contrasena
	 */
	
	public String getContrasena() {
		return this.contrasena;
	}
	
	/**
	 * Getter para devolver el valor que tenga el atributo Nombre
	 * @return this.Nombre
	 */
	
	
	public String getNombre() {
		return this.Nombre;
	}
	
	
	/**
	 * Getter para devolver el valor que tenga el atributo fechaNacimiento
	 * @return this.fechaNacimiento
	 */
	
	public Date getFecha() {
		return this.fechaNacimiento;
	}
	
	
	/**
	 * Setter para introducir el valor del atributo alias
	 * @param alias
	 */ 
	
	public void setAlias(String alias) {
		this.alias = alias;
	}
	
	
	/**
	 * Setter para introducir el valor del atributo Nombre
	 * @param nombre
	 */
	
	public void setNombre(String nombre) {
		this.Nombre = nombre;
	}
	
	
	/**
	 * Setter para introducir el valor del atributo contrasena
	 * @param contrasena
	 */
	
	public void setContrasena(String contrasena) {
		this.contrasena = contrasena;
	}
	
	
	/**
	 * Setter para introducir el valor del atributo fechaNacimiento
	 * @param Fecha
	 */
	
	public void setFecha(Date Fecha) {
		this.fechaNacimiento = Fecha;
	}
}
