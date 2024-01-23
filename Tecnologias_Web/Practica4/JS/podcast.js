// variables globales
var navegadorOferta = "mozilla"; // Puedes cambiarlo al navegador específico que desees
var tiempoBannerMin = 5000; // 5 segundos en milisegundos
var tiempoBannerMax = 10000; // 10 segundos en milisegundos

// Función para desplazar y hacer visible la capa de banner
function mostrarPrograma() {
    alert("¡Programa de podcast visible!");
    // Aquí podrías realizar acciones adicionales al hacer clic en la capa
    let Programa = document.getElementById("mobile");
    let banner = document.getElementById("banner");
    banner.style.display = "none";
    Programa.style.display = "grid";
}

function mostrarBanner() {
  let banner = document.getElementById("banner");
  banner.style.position = 'absolute';
  banner.style.display = "grid";
  // Posición aleatoria

  let t = setInterval(move, 2000);

    function move(){
        let posX = Math.random() * (window.innerWidth - banner.clientWidth);
        let posY = Math.random() * (window.innerHeight - banner.clientHeight);

        banner.style.left = posX + "px";
        banner.style.top = posY + "px";
        
        setTimeout(function() {
            banner.style.display = "none";
            clearInterval(t);
        }, Math.floor(Math.random() * (tiempoBannerMax - tiempoBannerMin + 1)) + tiempoBannerMin);
    }
}

window.onload = function() {
    let userAgent = navigator.userAgent.toLowerCase();
   
    if (userAgent.includes(navegadorOferta.toLowerCase())) {
      mostrarBanner();
    }
  };