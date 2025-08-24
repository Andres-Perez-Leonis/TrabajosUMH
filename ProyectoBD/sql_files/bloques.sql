
create or replace FUNCTION GenerarReporteIngresos RETURN NUMBER
IS
    ingresosMesInternet NUMBER(10,3);
    ingresosMesTelefeno NUMBER(10,3);
BEGIN
    SELECT SUM(ti.precio)
    INTO ingresosMesInternet FROM CONTRATO contr, CLIENTE cli, OFICINISTA ofi, SERVICIO ser, INTERNET inter, TARIFA_INTERNET ti
    where contr.dnicliente = cli.dni and ofi.codigo = contr.cod and ser.numcontrato = contr.ncontrato and inter.id = ser.id and inter.nomtarifa = ti.nombre;

    SELECT SUM(tl.precio)
    INTO ingresosMesTelefeno FROM CONTRATO contr, CLIENTE cli, OFICINISTA ofi, SERVICIO ser, TELEFONO tel, TARIFA_TELEFONO tl
    where contr.dnicliente = cli.dni and ofi.codigo = contr.cod and ser.numcontrato = contr.ncontrato and tel.id = ser.id and tel.nomtarifa = tl.nombre;

    return (ingresosMesInternet+ingresosMesTelefeno);
END;
/

create or replace FUNCTION IngresosOfertas(codcomercial VARCHAR)RETURN NUMBER
IS
    CURSOR precioOferta IS
        SELECT precio 
        FROM COMERCIAL C, OFERTA O, PROMOCION P 
        WHERE C.CODIGO = O.CODIGO AND IDPROM = ID AND O.CODIGO = codcomercial;
    suma NUMBER;
BEGIN
    suma := 0;
    IF codcomercial is null OR LENGTH(TRIM(codcomercial)) IS NULL THEN
        RAISE_APPLICATION_ERROR(-20000,'No se permiten datos vacios');
    ELSIF LENGTH(TRIM(codcomercial)) < 10 OR LENGTH(TRIM(codcomercial)) > 10 THEN
        RAISE_APPLICATION_ERROR(-20001,'Longitud del codigo del comercial es incorrecto');
    ELSE
        FOR j IN precioOferta LOOP
            suma := suma + j.precio;
        END LOOP;
    END IF; 
    
    RETURN suma;
END;
/

CREATE OR REPLACE FUNCTION GastosCliente(gastoTelefono IN OUT NUMBER, gastoInternet IN OUT NUMBER, gastoOfertas IN OUT NUMBER, dniCliente IN VARCHAR2) RETURN NUMBER 
AS 
    CURSOR lineasTelefonicas IS
        SELECT tl.nombre, tl.precio
        FROM CONTRATO contr, CLIENTE cli, OFICINISTA ofi, SERVICIO ser, TELEFONO tel, TARIFA_TELEFONO tl
        WHERE contr.dnicliente = cli.dni and ofi.codigo = contr.cod and ser.numcontrato = contr.ncontrato and tel.id = ser.id and tel.nomtarifa = tl.nombre and cli.dni = GASTOSCLIENTE.dniCliente;
        
    CURSOR internet IS
        SELECT ti.nombre, ti.precio
        FROM CONTRATO contr, CLIENTE cli, OFICINISTA ofi, SERVICIO ser, INTERNET inter, TARIFA_INTERNET ti
        WHERE contr.dnicliente = cli.dni and ofi.codigo = contr.cod and ser.numcontrato = contr.ncontrato and inter.id = ser.id and inter.nomtarifa = ti.nombre and cli.dni = GASTOSCLIENTE.dniCliente;

    CURSOR tipoOfertas IS
        SELECT P.nombre, P.precio
        FROM CLIENTE C, OFERTA O, PROMOCION P
        WHERE C.dni = O.dni AND IDPROM = ID and C.dni = GASTOSCLIENTE.dniCliente;
        
    totalServicio NUMBER := 0;
BEGIN
   FOR i IN lineasTelefonicas LOOP
        dbms_output.put_line('Tarifa de telefono contratada: ' || i.nombre || ', cuyo coste es de ' || i.precio || ' €');
        gastoTelefono := gastoTelefono + i.precio;
        totalServicio := totalServicio + 1;
    END LOOP;
     dbms_output.put_line(' ');
    
    FOR j IN internet LOOP
        dbms_output.put_line('Tarifa de internet contratada: ' || j.nombre || ', cuyo coste es de ' || j.precio || ' €');
        gastoInternet := gastoInternet + j.precio;
        totalServicio := totalServicio + 1;
    END LOOP;
     dbms_output.put_line(' ');
    
    FOR k IN tipoOfertas LOOP
        dbms_output.put_line('Oferta contratada : ' || k.nombre || ', cuyo coste es de ' || k.precio || ' €');
        gastoOfertas := gastoOfertas + k.precio;
    END LOOP;
    dbms_output.put_line(' ');
    
    RETURN totalServicio; 
END;
/

create or replace PROCEDURE AsignarTecnico(codigo_averia VARCHAR, provincia_averia VARCHAR2) is

    CURSOR tecnicos is select codigo from SEDE s, TECNICO t where t.nsede = s.nsede and provincia_averia = s.provincia;
    total_tecnicos NUMBER;
    tecnico_aleatorio NUMBER;
    codigo_tecnico VARCHAR2(10);
    contador NUMBER := 1;
    tecnico_nulo EXCEPTION;
BEGIN
    select count(*) into total_tecnicos from SEDE s, TECNICO t where t.nsede = s.nsede and provincia_averia = s.provincia;
    
    tecnico_aleatorio := FLOOR(DBMS_RANDOM.VALUE(1, total_tecnicos + 1));
    FOR tecnico IN tecnicos LOOP
        IF contador = (tecnico_aleatorio) THEN
            codigo_tecnico := tecnico.codigo;
            EXIT;
        END IF;
        contador := contador + 1;
    END LOOP;

    if codigo_tecnico is null then
        RAISE tecnico_nulo;
    else 
        INSERT INTO REPARA VALUES(codigo_tecnico, codigo_averia);
    end if;

    EXCEPTION 
        when tecnico_nulo then
            dbms_output.put_line('No se asigno ningun tecnico a la averia ya que no hay ninguno en la provincia');
            dbms_output.put_line('Se asignara otro en la medida de lo posible');
END;
/

create or replace PROCEDURE ImprimirIngresos
IS
    resultado NUMBER;
BEGIN
    resultado := GenerarReporteIngresos;
    dbms_output.put_line('Los ingresos seguros son: ' || resultado);
    dbms_output.put_line('No se tiene en cuenta el precio de los minutos de las tarifas del telefono');

END;
/

create or replace PROCEDURE InformeCliente(dniCliente VARCHAR2)
IS
    gastoInternet NUMBER;
    gastoTelefono NUMBER;
    gastoOfertas NUMBER;
    gastoTotal NUMBER;
    totalServicios NUMBER;
    nombreCliente VARCHAR(30);
    nombrePromocion VARCHAR(100);
BEGIN 
    SELECT nombre
    INTO nombreCliente
    FROM CLIENTE C
    WHERE c.dni = dniCliente;
    gastoInternet := 0;
    gastoTelefono := 0;
    gastoOfertas := 0;
    
    dbms_output.put_line('Cliente ' || nombreCliente || 'con DNI ' || dniCliente);
    dbms_output.put_line(' ');
    
    totalServicios := gastoscliente(gastoTelefono, gastoInternet, gastoOfertas, dniCliente);
    
    dbms_output.put_line('Coste total en tarifas telefonicas: '|| gastoTelefono || ' €');
    dbms_output.put_line(' ');
    
    dbms_output.put_line('Coste total en tarifas de internet: '|| gastoInternet || ' €');
    dbms_output.put_line(' ');
    
    dbms_output.put_line('Coste total en ofertas: '|| gastoOfertas || ' €');
    dbms_output.put_line(' ');
    
    gastoTotal := gastoInternet + gastoTelefono + gastoOfertas;
    
    dbms_output.put_line('Total de servicios contratados: '|| totalServicios);
    dbms_output.put_line(' ');

    dbms_output.put_line('Coste final: '|| gastoTotal || ' €');

END;
/

create or replace PROCEDURE InformeComercial(codcomercial VARCHAR)
IS
    cantidadOfertas NUMBER;
    ingresosTotales NUMBER;
BEGIN

   ingresostotales := ingresosofertas(codcomercial);
   SELECT count(*)
   INTO cantidadOfertas
   FROM OFERTA O, COMERCIAL C
   WHERE C.CODIGO = O.CODIGO AND O.CODIGO = codcomercial;
   
   dbms_output.put_line('Informe descriptivo sobre el rendimiento laboral');
   dbms_output.put_line('---------------------------------------------------------------------------');
   dbms_output.put_line('Comercial con cod: ' || codcomercial);
   dbms_output.put_line('Ha conseguido ofertar de manera exitosa un total de ' || cantidadOfertas || ' ofertas');
   dbms_output.put_line('Dicha cantidad de acuerdos generan un ingreso de ' || ingresostotales || ' €');
END;
/

create or replace PROCEDURE InformeEmpresa
IS
    
    CURSOR c_comerciantes IS
        SELECT codigo
        FROM COMERCIAL;
        
    gastoEmpleados NUMBER;
    beneficiosOfertas NUMBER;
    beneficiosServicios NUMBER;
    balanceEmpresa NUMBER;
BEGIN
    gastoEmpleados := 0;
    beneficiosOfertas := 0;
    beneficiosServicios := 0; 
    balanceEmpresa := 0;
    
    SELECT SUM(sueldo)
    INTO gastoEmpleados
    FROM Empleado;
   
    beneficiosServicios := GenerarReporteIngresos;
    
    FOR i IN c_comerciantes LOOP
        beneficiosOfertas := beneficiosOfertas + ingresosofertas(i.codigo);
    END LOOP;
    
    balanceEmpresa := (beneficiosServicios + beneficiosOfertas) - gastoEmpleados;
    
    dbms_output.put_line('Informe de balance de la empresa');
    dbms_output.put_line('---------------------------------------');
    dbms_output.put_line('Gastos destinados al sueldo de los empleados : ' || TO_CHAR(gastoempleados) || ' €');
    dbms_output.put_line('Dinero recaudado mediante las ofertas: ' || TO_CHAR(beneficiosOfertas) || ' €');
    dbms_output.put_line('Dinero recaudado mediante los servicios telefonicos y de internet : ' || TO_CHAR(beneficiosServicios) || ' €');
    dbms_output.put_line(' ');
    dbms_output.put_line('Balance de la empresa : ' || TO_CHAR(balanceEmpresa) || ' €');
    
    IF balanceEmpresa < 0 THEN
        dbms_output.put_line('Balance de la empresa negativo, hay que mejorar!!!!');
    ELSE
        dbms_output.put_line('Balance de la empresa positivo, enhorabuena!!');
    END IF;

END;
/

create or replace trigger ReparacionAveria
before update on AVERIA
for each row
DECLARE
    fecha_averia DATE;
    fecha_reparacion DATE;
begin

    fecha_averia := :OLD.faveria;
    fecha_reparacion := :new.frepara;

    if fecha_reparacion > fecha_averia THEN
        RAISE_APPLICATION_ERROR(-20001, 'Es imposible que la reparacion se realice antes de que produzca la averia');
    end if;
end;
/

create or replace trigger asignacion_tecnico
before insert on AVERIA
for each row
begin
    AsignarTecnico(:NEW.cod, :NEW.provincia);
end;
/