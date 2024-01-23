/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

// Wait for the deviceready event before using any of Cordova's device APIs.
// See https://cordova.apache.org/docs/en/latest/cordova/events/events.html#deviceready





var checkBox = document.getElementById("checkbox-based-flipswitch");
var btnCrearCuenta = document.getElementById("btnCrearCuenta");


//Esto sirve apra detectar si el switch esta activado o no
$("#checkbox-based-flipswitch").on("change", function() {
    if ($(this).prop("checked")) {
        btnCrearCuenta.disabled = false;
    } else {
        btnCrearCuenta.disabled = true;
    }
  });

  document.addEventListener("deviceready", function() {
    // Espera a que el dispositivo esté listo
  
    var crearCuentaBtn = document.getElementById("btnCrearCuenta");
    crearCuentaBtn.addEventListener("click", function() {
      var email = document.getElementById("email").value;
      var mensaje = "Bienvenido " + email;
  
      navigator.notification.alert(mensaje, null, "alert", "[buttonName]");
      /*
      if (navigator.notification && navigator.notification.alert) {
        navigator.notification.alert(mensaje, null, "Mensaje de bienvenida", "Aceptar");
      } else {
        alert(mensaje);
      }
        */
    });
  });

  /*
  document.addEventListener("deviceready", onDeviceReady, true);

    function onDeviceReady() {
        console.log('Running cordova-' + cordova.platformId + '@' + cordova.version);
        //document.getElementById("btnCrearCuenta").addEventListener("click", crearCuenta);
    }


    btnCrearCuenta.addEventListener("click", crearCuenta);

    function crearCuenta(){
        onDeviceReady();
    }
    */