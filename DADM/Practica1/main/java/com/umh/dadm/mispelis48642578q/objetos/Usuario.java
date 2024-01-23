package com.umh.dadm.mispelis48642578q.objetos;

import android.provider.ContactsContract;

import java.util.Date;

public class Usuario {

    private String nombre;
    private ContactsContract.CommonDataKinds.Email email;
    private String apellidos;
    private String password;
    private Date nacimiento;
    private int preguntaSeleccionada;
    private String respuesta;
    private boolean[] intereses = new boolean[5];
    private String otroInteres;
    private boolean segundoFactor;

    public Usuario(String nombre, ContactsContract.CommonDataKinds.Email email,
                        String apellidos, String password, Date nacimiento, int preguntaSeleccionada,
                        String respuesta, boolean interesTecno, boolean interesDeporte,
                        boolean interesRedes, boolean interesCine, boolean interesOtros,
                        String otroInteres, boolean segundoFactor) {
       this.nombre = nombre;
       this.apellidos = apellidos;
       this.email = email;
       this.intereses[0] = interesTecno;
       this.intereses[1] = interesDeporte;
       this.intereses[2] = interesRedes;
       this.intereses[3] = interesCine;
       this.intereses[4] = interesOtros;
       this.otroInteres = otroInteres;
       this.preguntaSeleccionada = preguntaSeleccionada;
       this.respuesta = respuesta;
       this.segundoFactor = segundoFactor;
       this.nacimiento = nacimiento;
       this.password = password;
    }


    public static boolean ParametrosNulos(String nombre, String apellidos, String password) {
        boolean nulos = true;

        if(nombre != null && apellidos != null && password != null) nulos = false;

        return nulos;
    }

}
