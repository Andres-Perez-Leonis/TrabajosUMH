
CREATE TABLE EMPLEADO
(
   codigo        VARCHAR2(10) CONSTRAINT emp_cod_pk PRIMARY KEY,
   nombre        VARCHAR2(30),
   apellidos    VARCHAR2(25),
   tlf            VARCHAR2(30),
   horario        VARCHAR2(25) CONSTRAINT emp_hor_ch CHECK (horario IN ('Mañana', 'Tarde','Completo') ),
   sueldo        NUMBER(8,2)
);


CREATE TABLE SEDE    
(
   nsede        VARCHAR2(20) CONSTRAINT sed_nse_pk PRIMARY KEY,
   direccion    VARCHAR2(50),
   ciudad        VARCHAR2(25),  
   provincia    VARCHAR2(25),
   cautonoma    VARCHAR2(25),
   tlf            VARCHAR2(30)
);
CREATE TABLE TARIFA_INTERNET
(
nombre VARCHAR2(30) CONSTRAINT tarint_nom_pk PRIMARY KEY, 
precio NUMBER(8,2),
vsubida NUMBER(5),
vbajada NUMBER(5)
);

CREATE TABLE TARIFA_TELEFONO
(
nombre VARCHAR2(30) CONSTRAINT tarmov_nom_pk PRIMARY KEY, 
precio NUMBER(8,2),
minutos NUMBER(5),
precio_minuto NUMBER(5),
datos NUMBER(5)
);
CREATE TABLE CLIENTE
(
    dni varchar(9) CONSTRAINT cliente_dni_pk primary key,
    nombre varchar(30),
    apellidos varchar(30),
    email varchar(20),
    direccion VARCHAR2(50)
);
CREATE TABLE PROMOCION
(
    id varchar(10) CONSTRAINT prom_id_pk PRIMARY KEY,
    nombre varchar(30),
    descripc varchar(300),
    precio number(8,2)
);
CREATE TABLE COMERCIAL    
(
    codigo        CONSTRAINT com_emp_fk REFERENCES EMPLEADO CONSTRAINT com_cod_pk PRIMARY KEY,
    nsede        CONSTRAINT com_sed_fk REFERENCES SEDE
);

CREATE TABLE TECNICO    
(
    codigo        CONSTRAINT tec_emp_fk REFERENCES EMPLEADO CONSTRAINT tec_cod_pk PRIMARY KEY,
    nsede        CONSTRAINT tec_sed_fk REFERENCES SEDE,
    especializacion VARCHAR2(25)
);


CREATE TABLE OFICINA    
(
   codigo        VARCHAR2(10) CONSTRAINT ofi_cod_pk PRIMARY KEY,
   nsede        CONSTRAINT ofi_sed_fk REFERENCES SEDE,  
   direccion   VARCHAR2(50),
   ciudad        VARCHAR2(25),  
   tlf            VARCHAR2(30)
);

CREATE TABLE OFICINISTA    
(
    codigo        CONSTRAINT ofic_emp_fk REFERENCES EMPLEADO CONSTRAINT ofic_cod_pk PRIMARY KEY,
    codof        CONSTRAINT ofic_ofi_fk REFERENCES OFICINA
);

CREATE TABLE CONTRATO
(
    ncontrato varchar(10) CONSTRAINT contrato_ncontrato_pk primary key,
    dnicliente  CONSTRAINT cont_cli_fk REFERENCES cliente CONSTRAINT contrato_dni_nn not null,
    cod  CONSTRAINT cont_oficinista_fk REFERENCES oficinista
);
CREATE TABLE SERVICIO
(
id VARCHAR2(10) CONSTRAINT ser_id_pk PRIMARY KEY, 
numcontrato CONSTRAINT ser_num_fk REFERENCES CONTRATO
);

CREATE TABLE AVERIA 
(
    cod varchar(10) CONSTRAINT averia_cod_pk PRIMARY KEY,
    id CONSTRAINT averia_serv_fk REFERENCES servicio CONSTRAINT averia_id_nn not null,
    tipo varchar(20),
    descripc varchar(60),
    faveria date,
    frepara date,
    direccion VARCHAR2(50)
);



CREATE TABLE REPARA 
(
    codt CONSTRAINT rep_tec_fk REFERENCES TECNICO,
    coda CONSTRAINT rep_av_fk REFERENCES AVERIA,
    CONSTRAINT rep_codt_coda_pf PRIMARY KEY(codt,coda)
);


CREATE TABLE TELEFONO
(
id CONSTRAINT tel_id_pk PRIMARY KEY, 
tlf VARCHAR2(30) CONSTRAINT tel_tlf_uq UNIQUE CONSTRAINT tel_tlf_nn NOT NULL,
tipo VARCHAR2(10) CONSTRAINT tel_tip_ch CHECK (tipo IN ('Fijo', 'Movil') ),
nomtarifa CONSTRAINT tel_tartel_fk REFERENCES TARIFA_TELEFONO,
CONSTRAINT tel_ser_fk FOREIGN KEY (id) REFERENCES SERVICIO
);

CREATE TABLE INTERNET
(
id CONSTRAINT int_id_pk PRIMARY KEY, 
idred VARCHAR2(30) CONSTRAINT int_idr_uq UNIQUE CONSTRAINT int_idr_nn NOT NULL,
tipo VARCHAR2(10) CONSTRAINT int_tip_ch CHECK (tipo IN ('ADSL', 'Fibra') ),
nomtarifa CONSTRAINT int_tarint_fk REFERENCES TARIFA_INTERNET,
CONSTRAINT int_ser_fk FOREIGN KEY (id) REFERENCES SERVICIO
);


CREATE TABLE OFERTA
(
idprom CONSTRAINT ofe_pro_fk REFERENCES PROMOCION, 
codigo CONSTRAINT ofe_ofi_fk REFERENCES COMERCIAL CONSTRAINT ofe_cod_nn NOT NULL,
dni CONSTRAINT ofe_cli_fk REFERENCES CLIENTE, 
CONSTRAINT ofe_idp_dni_pk PRIMARY KEY (idprom, dni)
);

COMMIT;

ALTER TABLE averia ADD provincia VARCHAR2(25) NOT NULL;

COMMIT;