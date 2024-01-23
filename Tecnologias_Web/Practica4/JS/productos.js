function crearProductos(){

    if(validarInput() == false){
        return;
    }

    let tabla = document.getElementById("tabla-productos");
    let listaDeProductos = document.getElementById("productos");

    let productoSeleccionado = listaDeProductos.selectedIndex;
    let producto = listaDeProductos[productoSeleccionado].text;
    let precioProducto = listaDeProductos[productoSeleccionado].value;

    let listaDeIvas = document.getElementById("iva");
    let ivaSeleccionado = listaDeIvas.selectedIndex;
    let iva = listaDeIvas[ivaSeleccionado].value;

    let cantidadProducto = document.getElementById("cantidadProducto").value;
    let subtotalActual = precioProducto * iva;

    if(cantidadProducto != 1){
        subtotalActual = (cantidadProducto * precioProducto) * iva;
    }
    
    let respuesta = [0,false];
    respuesta = leer(producto,respuesta);
    let filaProducto = respuesta[0];

    if(respuesta[1] == false){
        tabla.insertRow(-1).innerHTML = "<tr> <td class='cantidad'>" + cantidadProducto + "</td> <td class='nombreProducto'>" + producto + "</td> <td class='precio'>" + precioProducto + "</td> <td class='subtotal'>" + subtotalActual + "</td> </tr>";
        total(tabla);
        return;
    }

    let subtotales = tabla.getElementsByClassName('subtotal');
    let cantidades = tabla.getElementsByClassName('cantidad');
    let cantidadActual = parseInt(cantidades[filaProducto].innerHTML);
    cantidadActual += parseInt(cantidadProducto);
    cantidades[filaProducto].innerHTML = cantidadActual;

    
    subtotalActual = parseInt((precioProducto * cantidadActual) * iva);
    subtotales[filaProducto].innerHTML = subtotalActual;

    total(tabla,listaDeIvas[ivaSeleccionado].text);

}

function total(tabla,nombreIva){

    let subtotales = tabla.getElementsByClassName('subtotal');

    let sumatorio = 0;
    for(let i = 0; i < subtotales.length; i++){
        sumatorio += parseInt(subtotales[i].innerText);
    }
    document.getElementById("total").innerHTML = "Total: " + sumatorio + " €. Se le aplica el " + nombreIva;
}

function leer(producto,respuesta){
    let productosInsertados = document.getElementsByClassName("nombreProducto");

    for(let i = 0; i < productosInsertados.length; i++){
        if(productosInsertados[i].innerText == producto){
            respuesta[0] = i;
            respuesta[1] = true;
        }
    }
    
    return respuesta;
}

function validarInput(){

    let valorinput = document.getElementById("cantidadProducto");
    if(valorinput.value == ""){
        valorinput.placeholder = 'Es necesario poner numeros';
        return false;
    }
    return true;
}

function recalcularCarrito(){
    let tabla = document.getElementById("tabla-productos");
    let cantidades = tabla.getElementsByClassName("cantidad");

    if(cantidades.length == 0){
        return;
    }
    
    let subtotales = tabla.getElementsByClassName("subtotal");
    
    let listaDeProductos = document.getElementById("productos");
    
    let listaDeIvas = document.getElementById("iva");
    let ivaSeleccionado = listaDeIvas.selectedIndex;
    let iva = listaDeIvas[ivaSeleccionado].value;

    for(let i = 0; i < cantidades.length; i++){
        let cantidadActual = parseInt(cantidades[i].innerHTML);
    
        let subtotalActual = parseInt((listaDeProductos[i].value * cantidadActual) * iva);
        subtotales[i].innerHTML = subtotalActual;
    }
    total(tabla,listaDeIvas[ivaSeleccionado].text);

    estiloIVA();
}

function guardar(){
    
    let tabla = document.getElementById("tabla-productos");
    let filas = tabla.getElementsByTagName("tr");

    let listaDeIvas = document.getElementById("iva");
    let ivaSeleccionado = listaDeIvas.selectedIndex;
    let iva = listaDeIvas[ivaSeleccionado].text;

    let tablaEnArray = [];
    for(let i = 1; i < filas.length; i++){
        tablaEnArray.push(filas[i].innerHTML);
    }
    tablaEnArray.push(iva)
    window.localStorage.setItem("carrito",tablaEnArray);
}

function mostrar(){
    let tablaEnMemoria = localStorage.getItem("carrito");

    if(tablaEnMemoria == null){
        return;
    }

    let tablaDeserializada = tablaEnMemoria.split(',');
    let tablaHTML = document.getElementById("tabla-productos");
    let bodytabla = tablaHTML.getElementsByTagName("tbody");

    
    for(let i = 0; i < tablaDeserializada.length-1; i++){
        bodytabla[0].innerHTML += tablaDeserializada[i];
    }

    total(tablaHTML,tablaDeserializada[tablaDeserializada.length - 1])
    estiloIVA()
}

function borrar(){
    localStorage.removeItem("carrito")
}

function estiloIVA(){
    let listaDeIvas = document.getElementById("iva");
    let ivaSeleccionado = listaDeIvas.selectedIndex;
    let iva = listaDeIvas[ivaSeleccionado].value;

    let tabla = document.getElementById("tabla-productos")
    let filas = tabla.getElementsByTagName("tr");
    let colorLetras = "";
    console.log(filas);
    if(iva == 1.21){
        
        colorLetras = 'black';
        
    }
    else if(iva == 1.08){
        
        colorLetras = 'pink';
        
    }
    else if(iva == 1.12){
        
        colorLetras = 'red';
        
    }
    else{
        
        colorLetras = 'cyan';
        
    }

    for(let i = 0; i < filas.length; i++){
        filas[i].style.color = colorLetras;
    }
}