ction validarFormulario() {

    var valido = true;

    var dni_elemento = document.getElementById("dni");
    valido = validarDNI(dni_elemento);

    var password_elemento = document.getElementById("password");
    var r_password_elemento = document.getElementById("r_password");

    if(password.value != r_password.value){
        password_elemento.style.border = '1px solid red';
        r_password_elemento.style.border = '1px solid red';
        document.getElementById("mensaje_error_password").style.display = 'block';
        valido = false;
    } else {
        password_elemento.style.border = '';
        r_password_elemento.style.border = '';
        document.getElementById("mensaje_error_password").style.display = 'none';
    }

    return valido;
}

function validarDNI(dni_elemento) {
    var dni = dni_elemento.value;
    var letras = ['T', 'R', 'W', 'A', 'G', 'M', 'Y', 'F', 'P', 'D', 'X', 'B', 'N', 'J', 'Z', 'S', 'Q', 'V', 'H', 'L', 'C', 'K', 'E', 'T'];

    var numero = dni.match(/\d+/)[0];
    var dni_letra = dni.match(/[a-zA-Z]/)[0];

    var letra = letras[numero%23]; 

    if(dni_letra != letra) {
        dni_elemento.style.border = '1px solid red'; 
        document.getElementById("mensaje_error_dni").style.display = 'block';
        return false;
    } else {
        dni_elemento.style.border = ''; 
        document.getElementById("mensaje_error_dni").style.display = 'none';
    }

    
    //alert("DNI correcto");
    return true;

}