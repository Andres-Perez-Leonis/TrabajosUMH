ALTER TRIGGER ASIGNACION_TECNICO DISABLE;
INSERT INTO EMPLEADO (codigo, nombre, apellidos, tlf, horario, sueldo) VALUES ('1111111111','Pepe','Viyuela Gonzalez','999999999','Mañana',800);
INSERT INTO EMPLEADO (codigo, nombre, apellidos, tlf, horario, sueldo) VALUES ('1111111112','Perico','Roca Del Rio','999666333','Mañana',800);
INSERT INTO EMPLEADO (codigo, nombre, apellidos, tlf, horario, sueldo) VALUES ('1111111113','Pepe','Gotera Fernandez','999444111','Tarde',1600);
INSERT INTO EMPLEADO (codigo, nombre, apellidos, tlf, horario, sueldo) VALUES ('1111111114','Luis','Perez','134436456','Completo',2600);
INSERT INTO EMPLEADO (codigo, nombre, apellidos, tlf, horario, sueldo) VALUES ('1111111115','Jose','Rodriguez','123436456','Completo',2400);
INSERT INTO EMPLEADO (codigo, nombre, apellidos, tlf, horario, sueldo) VALUES ('1111111116','Pablo','Gomez','123459256','Mañana',1400);
INSERT INTO EMPLEADO (codigo, nombre, apellidos, tlf, horario, sueldo) VALUES ('1111111117','Alvaro','Muñoz','121234456','Tarde',2000);
INSERT INTO EMPLEADO (codigo, nombre, apellidos, tlf, horario, sueldo) VALUES ('1111111118','Vicente','Herrera','123456456','Completo',2300);
INSERT INTO EMPLEADO (codigo, nombre, apellidos, tlf, horario, sueldo) VALUES ('1111111119','Maria','Cortes','123786456','Mañana',2100);
INSERT INTO EMPLEADO (codigo, nombre, apellidos, tlf, horario, sueldo) VALUES ('1111111110','Lucia','Garrido','123445456','Completo',2250);
INSERT INTO EMPLEADO (codigo, nombre, apellidos, tlf, horario, sueldo) VALUES ('1111111123','Miguel','Gil','123876556','Mañana',2670);
INSERT INTO EMPLEADO (codigo, nombre, apellidos, tlf, horario, sueldo) VALUES ('1111111124','Marta','Ferrer Arias','123109456','Tarde',2120);

INSERT INTO SEDE VALUES ('ALICANTE14F', 'C/ Manuel Iradier, 98', 'Alicante', 'Alicante', 'Comunitat Valenciana', '6213135412');
INSERT INTO SEDE VALUES ('VALENCIA41F', 'C/ Cañada del Rosal, 48', 'Valencia', 'Valencia', 'Comunitat Valenciana', '6621309893');
INSERT INTO SEDE VALUES ('ELCHE52C', 'Avda. Generalísimo, 53', 'Elche', 'Alicante', 'Comunitat Valenciana', '6567787843');

INSERT INTO TARIFA_INTERNET (nombre,precio,vsubida,vbajada) VALUES ('TARINT1',32,60,20);
INSERT INTO TARIFA_INTERNET (nombre,precio,vsubida,vbajada) VALUES ('TARINT2',60,600,600);
INSERT INTO TARIFA_INTERNET (nombre,precio,vsubida,vbajada) VALUES ('TARINT3',65,600,700);
INSERT INTO TARIFA_INTERNET (nombre,precio,vsubida,vbajada) VALUES ('TARINT4',70,700,600);

INSERT INTO TARIFA_TELEFONO VALUES ('TARTLF1', 54.66, 64, 0.39, 7);
INSERT INTO TARIFA_TELEFONO VALUES ('TARTLF2', 82.34, 74, 0.34, 10);    
INSERT INTO TARIFA_TELEFONO VALUES ('TARTLF3', 73.25, 70, 0.44, 5);    
INSERT INTO TARIFA_TELEFONO VALUES ('TARTLF4', 99.34, 100, 0.40, 5);    

INSERT INTO CLIENTE (dni,nombre,apellidos) VALUES ('11111111N','Juan','Lopez Albí');
INSERT INTO CLIENTE (dni,nombre,apellidos) VALUES ('22222233N','María','Perez Rios');
INSERT INTO CLIENTE (dni,nombre,apellidos) VALUES ('22222244N','María','Martinez Gea');
INSERT INTO CLIENTE (dni,nombre,apellidos) VALUES ('22222255N','Mariano','Ramirez Garcia');

INSERT INTO PROMOCION (id, nombre, descripc, precio) values ('1231231234','Felices fiestas','20% de descuento en llamadas a móviles nacionales, 2GB de datos y ADSL de 10MB',45.99);
INSERT INTO PROMOCION (id, nombre, descripc, precio) values ('1231231235','Pack de extensión de datos','2GB de datos por 5 euros',5.49);
INSERT INTO PROMOCION (id, nombre, descripc, precio) values ('7731231235','Pack de pareja','2 lineas de telefono estándar con un 10% de descuento en el precio, precio de llamadas entre si reducido',27);
INSERT INTO PROMOCION (id, nombre, descripc, precio) values ('7771231235','Pack familiar','3 lineas de telefono estándar con un 10% de descuento en el precio',68);

INSERT INTO COMERCIAL VALUES ('1111111111','VALENCIA41F');
INSERT INTO COMERCIAL VALUES ('1111111112','ALICANTE14F');
INSERT INTO COMERCIAL VALUES ('1111111113','ELCHE52C');
INSERT INTO COMERCIAL VALUES ('1111111114','VALENCIA41F');

INSERT INTO TECNICO VALUES('1111111115', 'VALENCIA41F', 'ROUTER');
INSERT INTO TECNICO VALUES('1111111116', 'ALICANTE14F', 'INSTALACION');
INSERT INTO TECNICO VALUES('1111111117', 'ELCHE52C', 'LINEA');
INSERT INTO TECNICO VALUES('1111111118', 'VALENCIA41F', 'CABLEADO');

INSERT INTO OFICINA (codigo, nsede, direccion, ciudad, tlf) VALUES ('1111111152','VALENCIA41F','C/ Avenida de los Magros 22', 'Elche','111444999');
INSERT INTO OFICINA VALUES('123456789', 'ALICANTE14F', 'C/ Pintor Fernandez 34', 'Alicante', '843251198');
INSERT INTO OFICINA VALUES('121212121', 'ELCHE52C', 'C/ Fernández de Leceta, 75', 'Murcia', '123125198');
INSERT INTO OFICINA VALUES('675456789', 'ALICANTE14F', 'C/ Coronel Juan Dominguez 56', 'Valencia', '921123298');

INSERT INTO OFICINISTA VALUES ('1111111119','675456789');
INSERT INTO OFICINISTA VALUES ('1111111110','121212121');
INSERT INTO OFICINISTA VALUES ('1111111123','123456789');
INSERT INTO OFICINISTA VALUES ('1111111124','1111111152');

INSERT INTO CONTRATO VALUES ('0792483584', '11111111N', '1111111119');
INSERT INTO CONTRATO VALUES ('9078213458', '22222233N', '1111111110');
INSERT INTO CONTRATO VALUES ('4784213042', '22222244N', '1111111123');
INSERT INTO CONTRATO VALUES ('6987234783', '22222255N', '1111111124');

INSERT INTO SERVICIO VALUES ('2870983741', '0792483584');
INSERT INTO SERVICIO VALUES ('9873571230', '9078213458');
INSERT INTO SERVICIO VALUES ('7486327868', '4784213042');
INSERT INTO SERVICIO VALUES ('1237784998', '6987234783');

INSERT INTO AVERIA VALUES ('7342809797', '2870983741', 'ROUTER', 'CAMBIO DE ROUTER', '01/10/2018', '01/11/2018', 'C/ Cuevas de Ambrosio', 'Alicante');
INSERT INTO AVERIA VALUES ('3428482741', '9873571230', 'INSTALACION', 'INSTALACION DE INFRAESTRUCTURAS', '04/07/2018', '09/07/2018', 'C/ Manuel Iradier', 'Valencia');
INSERT INTO AVERIA VALUES ('6857983276', '7486327868', 'LINEA', 'INSTALACION NUEVO TELEFONO FIJO', '10/05/2018', '17/05/2018', 'C/ Escritor Garcia Alvez', 'Castellon');
INSERT INTO AVERIA VALUES ('4905263427', '1237784998', 'CABLEADO', 'CAMBIO CABLEADO A FIBRA', '10/01/2019', '16/01/2019', 'C/ Los Herrán', 'Valencia');

INSERT INTO REPARA VALUES ('1111111115', '7342809797');
INSERT INTO REPARA VALUES ('1111111116', '3428482741');
INSERT INTO REPARA VALUES ('1111111117', '6857983276');
INSERT INTO REPARA VALUES ('1111111118', '4905263427');

INSERT INTO TELEFONO VALUES ('2870983741', '982378759', 'Fijo', 'TARTLF1');
INSERT INTO TELEFONO VALUES ('9873571230', '665448759', 'Movil', 'TARTLF2');
INSERT INTO TELEFONO VALUES ('7486327868', '937878759', 'Fijo', 'TARTLF3');
INSERT INTO TELEFONO VALUES ('1237784998', '689765759', 'Movil', 'TARTLF4');

INSERT INTO INTERNET VALUES ('2870983741', '000000001', 'ADSL', 'TARINT1');
INSERT INTO INTERNET VALUES ('9873571230', '000000002', 'Fibra', 'TARINT2');
INSERT INTO INTERNET VALUES ('7486327868', '000000003', 'ADSL', 'TARINT3');
INSERT INTO INTERNET VALUES ('1237784998', '000000004', 'Fibra', 'TARINT4');

INSERT INTO OFERTA VALUES ('1231231234', '1111111111', '11111111N');
INSERT INTO OFERTA VALUES ('1231231235', '1111111112', '22222233N');
INSERT INTO OFERTA VALUES ('7731231235', '1111111113', '22222244N');
INSERT INTO OFERTA VALUES ('7771231235', '1111111114', '22222255N');

ALTER TRIGGER ASIGNACION_TECNICO ENABLE;
COMMIT;