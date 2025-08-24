package com.umh.dadm.mispelis48642578q;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.umh.dadm.mispelis48642578q.objetos.Usuario;

public class CrearCuenta extends AppCompatActivity  {



    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_crear_cuenta);

        /*TODO
            Falta poner el boton de cancelar y su funcionalidad

         */

        EditText boxCorreo = (EditText) findViewById(R.id.BoxTxtCorreoCrear);
        EditText boxContra = (EditText) findViewById(R.id.BoxTxtContraCrear);
        EditText boxNombre = (EditText) findViewById(R.id.BoxTxtNombre);
        EditText boxApeliidos = (EditText) findViewById(R.id.BoxTxtApellidos);
        EditText boxNacimiento = (EditText) findViewById(R.id.BoxTxtNacimiento);
        EditText boxRespuesta = (EditText) findViewById(R.id.BoxTxtRespuesta);



        Spinner spinner = findViewById(R.id.SeleccionPreguntas);

        setupSpinnerBasic(spinner);
        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
            }

            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                ((TextView) findViewById(R.id.BoxTxtRespuesta)).setVisibility(View.VISIBLE);
            }
        });


        Button btnSiguiente = (Button) findViewById(R.id.BtnSiguiente);
        /*
           Esta burrada de trozo de codigo simplemente comprueba cual de los layout esta visible y una vez
           pulsado el boton de siguiente muestra el siguiente layout para que siga haciendo el formulario
           para crear la cuenta nueva
        */
        btnSiguiente.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(((LinearLayout) findViewById(R.id.LayoutFormulario)).getVisibility() == View.VISIBLE) {

                    String nombre = boxNombre.getEditableText().toString();
                    String correo = boxCorreo.getEditableText().toString();
                    String contra = boxContra.getEditableText().toString();
                    String apellidos = boxApeliidos.getEditableText().toString();

                    if(Usuario.ParametrosNulos(nombre, correo, apellidos)) {
                        mostrarToast(getString(R.string.FaltanDatos), Toast.LENGTH_SHORT);
                        return;
                    }

                    ((LinearLayout) findViewById(R.id.LayoutFormulario)).setVisibility(View.INVISIBLE);
                    ((LinearLayout) findViewById(R.id.LayoutFormulario2)).setVisibility(View.VISIBLE);


                } else if(((LinearLayout) findViewById(R.id.LayoutFormulario2)).getVisibility() == View.VISIBLE) {

                    String fecha = boxNacimiento.getEditableText().toString();
                    String respuesta = boxRespuesta.getEditableText().toString();
                    if(respuesta == null) {
                        mostrarToast(getString(R.string.FaltaRespuesta), Toast.LENGTH_SHORT);
                        return;
                    }


                    ((LinearLayout) findViewById(R.id.LayoutFormulario2)).setVisibility(View.INVISIBLE);
                    ((LinearLayout) findViewById(R.id.LayoutFormulario3)).setVisibility(View.VISIBLE);
                    ((Button) findViewById(R.id.BtnSiguiente)).setVisibility(View.INVISIBLE);
                    ((Button) findViewById(R.id.BtCrearCuenta)).setVisibility(View.VISIBLE);
                }
            }
        });

        CheckBox checkOtros = findViewById(R.id.CheckOtros);
        checkOtros.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                ((EditText) findViewById(R.id.BoxTxtOtros)).setVisibility(View.VISIBLE);
            }
        });


        Button button = (Button) findViewById(R.id.BtCrearCuenta);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                /*TODO
                    Falta hacer la parte de sql
                 */
                String interesOtro = boxRespuesta.getEditableText().toString();
                if(checkOtros.isChecked() && interesOtro == null) {
                    mostrarToast(getString(R.string.FaltaInteres), Toast.LENGTH_SHORT);
                    return;
                }
            }
        });

        Button btnCancelar = (Button) findViewById(R.id.BtnCancelar);
        btnCancelar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

            }
        });

    }


    private void setupSpinnerBasic(Spinner spinner) {
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.ListaPreguntas, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);
    }


    private void mostrarToast(String frase, int duracion) {
        Toast toast;
        toast = Toast.makeText(getApplicationContext(), frase, duracion);
        toast.show();
    }

}