PROGRAM Lectura;
{TÍTULO: Prácticas de PROGRAMACION II<br />SUBTÍTULO: Practica 1
AUTOR 1: Gabriel Míguez Míguez LOGIN 1: gabriel.miguez
AUTOR 2: Miguel Mosquera Pérez LOGIN 2: miguel.mosquera.perez
GRUPO: 3.2
FECHA: 13/03/2011
}

USES ListaDinamica, {Unic creada para este ejercicio}
	sysutils; {proporciona la funcion TRIM }

VAR
	
	ficheroUsuarios    : TEXT;
    linea              : STRING;
    operacion          : CHAR;
    numDenuncias       : STRING;
	TempPos            : tPos;	{Variable que sera usada para almacenar temporalmente una posicion
								y sera usada tanto desde programa como desde procesos}
	Lista			   : tLista; {Nuestra lista}
	TempDato		   : tDato; {Variable que su usara para almacenar temporalmente los datos d eun usuario}

{**********************************************************************}
	
	PROCEDURE Annadir(VAR Lista:tlista; TempDato: tDato);
	
	
	
	Begin
	
		if BuscarDato (tempDato.nick,Lista)=Nulo then begin
				
			if InsertarDato(TempDato,Nulo,Lista) then
				writeln('**** Alta de Usuario: ',TempDato.nick);

			end
		else writeln('Error de Alta: El nick de usuario ', TempDato.nick,' no esta disponible');
	
	end;
	
{**********************************************************************}

	Procedure Borrado (Var Lista:tLista;VAR TempDato: tDato);
	
	var tempPos:tPos;
	
	
	begin
		If length(TempDato.nick) > 0 then begin {en caso de que se mande borrar un usuario en concreto}
		
			if BuscarDato(TempDato.nick,Lista) <> Nulo then begin
				TempPos:= BuscarDato(TempDato.nick,Lista);
				ObtenerDato(TempPos,Lista,TempDato.nick,TempDato.numDenuncias);
				If TempPos<> nulo then begin
					EliminarPosicion(TempPos,Lista);
					writeln('Baja de Usuario: Nick ',TempDato.nick ,'  Denuncias ', TempDato.numDenuncias);
							
				end
				else writeln('Error en Baja: No existe el usuario con nick ',TempDato.nick);
			end
			else writeln('Usuario con nick ',TempDato.nick,' no existe');
		end
		else begin {en caso de que se mande borrrar usuarios con más de 5 denuncias}
			
			if primera(Lista) <> nulo then begin {then exterior}
					
				TempPos:= Primera(Lista);
				ObtenerDato(TempPos,Lista,TempDato.nick,TempDato.numDenuncias);
				while (TempPos <> Nulo) And (TempDato.numDenuncias<=5) Do Begin
					TempPos:=Siguiente(Lista,TempPos);
					ObtenerDato(TempPos,Lista,TempDato.nick,TempDato.numDenuncias);
				end;
				IF TempPos <> Nulo then begin {solamente si se encuentra a alguien a eliminar se entra}
						
					writeln('**** Eliminacion de Usuarios por Denuncias acumuladas');
					writeln('Usuario: nick ':22,TempDato.nick);
					EliminarPosicion(TempPos,Lista);
					while TempPos<> Nulo DO begin {Se sigue eliminando a partir del siguiente
																					al ya eliminado}
							
						ObtenerDato(TempPos,Lista,TempDato.nick,TempDato.numDenuncias);
						If TempDato.numDenuncias > 5 then begin
								
							EliminarPosicion(TempPos,Lista);
							writeln('Usuario: nick ':22,TempDato.nick);
								
						end;{then anidado}
						
						TempPos:= siguiente(Lista,TempPos);
							
					end;{while}
				end{then exterior}
							
				else writeln('Ningun usuario acumula el máximo de denuncias permitido');
				
			end {Then exterior}
			
			else writeln('No hay usuarios en la lista');
							
		end; {Else exterior}
	end;
{**********************************************************************}

	Procedure Modificado (VAR Lista:tLista;VAR TempDato:tDato);
	
	VAR TempPos:tPos;
	
	begin
				
		TempPos:=BuscarDato(TempDato.nick,Lista);
		If TempPos <> nulo then begin
			ActualizarDato(Lista,TempPos,TempDato.numDenuncias);
			writeln('**** Modificacion Usuario: Nick ', TempDato.nick ,' – Nuevo num denuncias ', TempDato.numDenuncias);
		end
		else writeln('Error en Modificacion: No existe el usuario ',tempDato.nick);
				
	end;

{**********************************************************************}

	PROCEDURE ImprimirLista (Const Lista:tLista;VAR TempDato:tDato);
	
	Var TempPos: tPos;
	
	Begin
	
		TempPos:=Primera(Lista);
		writeln('*******************************');
		writeln;
		While TempPos<>Nulo do begin
			
			ObtenerDato(TempPos,Lista,TempDato.nick,TempDato.numDenuncias);
			writeln('Usuario con Nick ',TempDato.Nick ,' Denuncias ',TempDato.numDenuncias);
			TempPos:=siguiente(Lista,TempPos);
			
		end;
		
		writeln('***********************************');
		writeln;
	
	end;

{**********************************************************************}

BEGIN {Lectura}
	  
	{proceso del fichero operaciones.txt }

   {$i-} { Desactiva la comprobacion de errores de entrada/salida}
   Assign(ficheroUsuarios, 'lectura/Usuarios.txt');
   Reset(ficheroUsuarios);
   {$i+} { Activa la comprobacion de errores de entrada/salida}
   IF (IoResult <> 0) THEN BEGIN
	  writeln('*** lectura.pas: error al acceder al fichero usuarios.txt');
	  halt(1)	
   END;
   
   ListaVacia(Lista);

   WHILE NOT EOF(ficheroUsuarios) DO
   BEGIN
	  { Lee una linea del fichero y la almacena en tres variables}
	  ReadLn(ficheroUsuarios, linea);
	  operacion := linea[1];
	  tempDato.nick    := trim(copy(linea,3,12));  { trim elimina los espacios al comienzo y final de un string }
										  { copy(s, i, j) copia j caracteres del string s }                                                         
										  { a partir de la posicion i }
	  numDenuncias  := trim(copy(linea,16,20)); 
	  { Ahora podria realizarse alguna operacion con los elementos leidos }
	  { en este caso mostrarlos por pantalla	                          }
	  writeln(operacion, ' --> ', TempDato.nick, ' | ',numDenuncias);
	  if length(numDenuncias) = 0 then 
			numDenuncias := '0';
	  readstr(numDenuncias,TempDato.numDenuncias);
	  
	  Case operacion of
	  
		'A': Annadir(Lista,TempDato);
		
		'B': Borrado(Lista,TempDato);
		
		'M': modificado(Lista,TempDato);
	  
	  end; {case}
	  writeln();
	  ImprimirLista(Lista,TempDato);
   END;{While}
   Close(ficheroUsuarios);
	
	ImprimirLista(Lista,TempDato);

End. {Lectura}
