/**
 * 
 */
package es.umh.poo.practica1.objetos;

/**
 * @author Andrés
 *
 */
public class Frases {
	
	//Atributos
	
	
	/**
	 * Atributos para el correcto funcionamiento de la clase Frases
	 * 
	 * "fraseAleatoria" -> Almacena la posicion de la frase que  el jugador debera adivinar
	 * "fraseOculta" -> Almacena la frase producida de ocultar la fraseObtenida
	 * "fraseObtenida" -> Almacena la frase que el jugador debe adivinar
	 * "frasesNovato", "frasesMedio" y "fraseExperto" -> Almacenan las frase que podrian 
	 * 													tocarle al jugador en sus 
	 * 													distintos niveles de dificultad
	 */
	
	private int fraseAleatoria;
	
	private char[] fraseOculta; 

	private String fraseObtenida;
	
	private String[] frasesNovato = {"el lunes tengo clase",
							"esta frase no es dificil", 
							"soy el mejor del mundo"};
	
	private String[] frasesMedio = {"deja de preocuparte por envejecer y piensa en crecer",
							"incluso los mejores fallan en sus dias mas celebres", 
							"aquel que no es capaz de bailar dice que el piso es pedregoso"}; 
	
    private String[] frasesExperto = {"piensa lo que quieras pensar, pero no olvides que tienes que convivir todos los días con tus propios pensamientos",
    						"la sabiduría es como un árbol de baobab: nadie puede abarcarlo individualmente",
    						"aquel que hace sonar al tambor para que el hombre loco baile, no es mejor que el loco"};
   
    //Metodos
    /**
     * El metodo "FraseAleatoria" obtendrá la frase que el jugador debe adivinar
     * el @param nivelElegido (su valor varia entre [1,3]) indicará el nivel de dificultad
     * De forma aleatoria elegirá la frase y devolvera @return fraseObtenida.
     */
    public String FraseAleatoria(int nivelElegido) {
    	fraseAleatoria = (int) (Math.random()*3);
    	switch(nivelElegido) {
    		case 1: fraseObtenida = frasesNovato[fraseAleatoria]; break;
    		case 2: fraseObtenida = frasesMedio[fraseAleatoria]; break;
    		case 3: fraseObtenida = frasesExperto[fraseAleatoria]; break;
    	}
    	fraseOculta = new char[fraseObtenida.length()];
    	return fraseObtenida;
    }
    /**
     * 	El metodo "GeneradorFraseIncognita" creará la frase que el jugador irá viendo
     * durante toda la partida, está frase sera aquella que ira cambiando en funcion
     * de las letras que acierte el jugador
     */
    public void GeneradorFraseIncognita(char letra) {
    	for(int i = 0; i < fraseObtenida.length(); i++) {
    		if(!Character.isLetter(fraseOculta[i])) {
    			if(fraseObtenida.charAt(i) == ',') {
    					fraseOculta[i] = ',';
    				}else if(fraseObtenida.charAt(i) == ' '){
    					fraseOculta[i] = ' ';
    				}else if (letra == fraseObtenida.charAt(i)) {
    					fraseOculta[i] = letra;
    				}else {
    					fraseOculta[i] = '_';
    			}
    		}
    	}
    }
    
    
    //Getters y Setters
    
    
    /**
     * Getter que devuelve la frase que el jugador debe adivinar
     * @return fraseObtenida
     */
    
    public String getFraseObtenida() {
    	return fraseObtenida;
    }
    
    
    /**
     * Getter que devuelve el valor del array "fraseOculta"
     * @return String.valueOf(fraseOculta)
     */
    
    public String getFraseOculta() {
    	return String.valueOf(fraseOculta);
    }
}