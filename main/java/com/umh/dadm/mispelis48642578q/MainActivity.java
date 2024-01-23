package com.umh.dadm.mispelis48642578q;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        EditText Boxcorreo = (EditText) findViewById(R.id.BoxTxtCorreoCrear);
        EditText Boxpassword = (EditText) findViewById(R.id.BoxTxtContraCrear);
        Button btnInciarSesion = (Button) findViewById(R.id.BtnInicioSesion);
        Button btnCrearCuenta = (Button) findViewById(R.id.BtnCrearCuenta);

        btnInciarSesion.setOnClickListener(new View.OnClickListener() {
            public void onClick(View view) {
                String TxtCorreo =  Boxcorreo.getEditableText().toString();
                String TxtPassword =  Boxpassword.getEditableText().toString();



                /*
                if(!ComprobacionParametros(TxtCorreo, TxtPassword)) {
                    /*TODO
                        Hay que comprobar que los datos que introdujo el usuario existen
                        (SQLite)
                     */
                    /*TODO
                        Aqui hay que añadir el intent que llame a la siguiente "pantalla"
                        donde el usuario podra moverse por la aplicacion
                     */
                //}
            }
        });

        btnCrearCuenta.setOnClickListener(new View.OnClickListener() {

            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, CrearCuenta.class);
                startActivity(intent);
            }
        });

    }


    private boolean ComprobacionParametros(String correo, String password) {
        Toast toast;
        int duration = Toast.LENGTH_SHORT;
        boolean datosCorrectos = true;
        if(correo == null || password == null) {
            if(correo == null && password == null) {
                toast = Toast.makeText(getApplicationContext(), getString(R.string.SinDatos), duration);
            } else if(correo == null) {
                toast = Toast.makeText(getApplicationContext(), getString(R.string.SinCorreo), duration);
            } else {
                toast = Toast.makeText(getApplicationContext(), getString(R.string.SinPassword), duration);
            }
            datosCorrectos = false;
            toast.show();
        }
        return datosCorrectos;
    }


}