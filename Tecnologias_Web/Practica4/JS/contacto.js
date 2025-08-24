function  validarFormulario() {
    var fechaNacimiento = new Date(document.getElementById("fechaNacimiento").value);
    var fechaActual = new Date();

    
    if(fechaNacimiento > fechaActual) {
        alert("La fecha indicada es mayor que la fecha actual");
        return false;
    }    

    var edad_minima = 18;
    var edad = fechaActual.getFullYear() - fechaNacimiento.getFullYear();

    if(fechaActual.getMonth() < fechaNacimiento.getMonth() || (
        (fechaActual.getMonth() === fechaNacimiento.getMonth() && fechaActual.getDate() < fechaNacimiento.getDate())))
            edad--; 

    if(edad < edad_minima) {
        alert("Debes tener más de 18 años para acceder a la web");
        return false;
    }
    return true;
} 