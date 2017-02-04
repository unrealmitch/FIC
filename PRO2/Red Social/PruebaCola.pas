PROGRAM PruebaCola
{Programa que comprobara que la Unit ColaOrdenes funciona correctamente}

USES sysutils,ColaOrdenes;{proporciona la funcion TRIM }

VAR
   ficheroUsuarios    : TEXT;
   linea              : STRING;
	Cola					 : tCola;
	InfoC					 : tInfoC;

BEGIN
  
   {proceso del fichero operaciones.txt }

   {$i-} { Desactiva la comprobacion de errores de entrada/salida}
   Assign(ficheroUsuarios, 'Lectura/operaciones.txt');
   Reset(ficheroUsuarios);
   {$i+} { Activa la comprobacion de errores de entrada/salida}
   IF (IoResult <> 0) THEN BEGIN
      writeln('*** lectura.pas: error al acceder al fichero operaciones.txt');
      halt(1)
   END;
   
   ColaVacia(Cola);
   
   if EsColaVacia(Cola) then
		writeln('La cola esta vacia');

   WHILE NOT EOF(ficheroUsuarios) DO
   BEGIN
   
      { Lee una linea del fichero y la almacena en tres variables}
      ReadLn(ficheroUsuarios, linea);
      InfoC.op := linea[1];
      InfoC.User1    := trim(copy(linea,3,9));  { trim elimina los espacios al comienzo y final de un string }
                                          { copy(s, i, j) copia j caracteres del string s a partir de la posicion i }
      InfoC.User2  := trim(copy(linea,13,9)); 
      { Ahora podria realizarse alguna operacion con los elementos leidos }
      { en este caso mostrarlos por pantalla	                          }
      writeln(InfoC.op, ' --> [', InfoC.User1, '] [', InfoC.User2, ']');
      InsertarDatoCola(Cola,InfoC);
      
   END;
   Close(ficheroUsuarios);
   writeln;
   writeln('############################');
   writeln;
   writeln('COLA:');
   
   while not(EsColaVacia(Cola)) do begin
   
		InfoC:= FrenteCola(Cola);
		writeln(InfoC.op, ' --> [', InfoC.User1, '] [', InfoC.User2, ']');
		EliminarCola(Cola);
   
   end;

END.
