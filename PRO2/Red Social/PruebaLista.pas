PROGRAM PruebaLista;
{Programa que comprobara que la Unit ListaAmigos funciona correctamente.}

USES ListaAmigos,sysutils;

Type
   
   tListaInfoL= Array [1..9] of tInfoL;

VAR 
   ficheroUsuarios: TEXT;
   Lista          :tLista;
   Linea          :String;
   operacion      : char;
   InfoL          :tInfoL;
   ListaInfoL     :tListaInfoL;
   i              :integer;
   
{**********************************************************************}

   Procedure Imprimir(Lista: tLista);
   
   VAR
      TempPos: tPosL;
      TempInfoL: tInfoL;
      Estado: string;
   
   Begin
   
      TempPos:= Primera(Lista);
      
      while TempPos <> NULOL do begin
      
         TempInfoL:= ObtenerDato(Lista,TempPos);
         
         Case TempInfoL.Estado of
         
            espera: Estado:='espera';
            
            aceptada: Estado:= 'aceptada';
         
         end;
         
         writeln('Amistad con el usuario ',TempInfoL.NickUsuario,' ',Estado,'.');
         
         TempPos:= siguiente(Lista,TempPos);
      
      
      end;
   
   End;
   
{**********************************************************************}

PROCEDURE AnnadirAmigo(VAR Lista:tlista; InfoL: tInfoL);
	{Proceso que comprueba que se haya introducido un nick y que este disponible,
	en caso de que ambas sean afirmativas llama a la funcion IsertarDato, para
	* insertar al nuevo usuario}
	
	
	Begin
		
		if length(InfoL.NickUsuario) <> 0  then begin
		
			if BuscarDato (Lista,InfoL.NickUsuario)=NULOL then begin
            
            InfoL.estado:= espera;
				if InsertarDatoLista(Lista,InfoL) then
					writeln('Nueva amistad: ',InfoL.NickUsuario)
					
			end
			else writeln('Error: El usuario ', InfoL.NickUsuario,' ya es amigo');
		end
		else
			writeln('No pueden anñadir usuarios sin nick.');
	
	end;
   
{**********************************************************************}

   Procedure BorrarAmigo(VAR Lista: tLista; Nick: tNickUsuario);
   
   VAR
      TempPos: tPosL;
     
   
   Begin
   
      TempPos:= BuscarDato(Lista,Nick);
      If TempPos <> NULOL then begin
      
           
         EliminarPosicion(Lista,TempPos);
         writeln('Se a eliminado al usuario ',nick);
         
         
         
      end
      else
         writeln('No existe el amigo a eliminar');
   
   end;

{**********************************************************************}

   Procedure Modificar(Lista: tLista; InfoL: tInfoL);
   
   VAR
      TempPos: tPosL;
   
   Begin
   
      TempPos:= BuscarDato(Lista,InfoL.NickUsuario);
      if TempPos <> NULOL then begin
      
         InfoL.estado:= aceptada;
         ActualizarDato(Lista,TempPos,InfoL);
         writeln('Se a actualizado los datos del amigo ',InfoL.NickUsuario);
      
      end
      else writeln('Amigo no existe')
   
   End;

{**********************************************************************}
	

BEGIN

   ListaVacia(Lista);
   For i:=1 to 9 do begin
   
      ListaInfoL[i].NickUsuario:=('User' + char(i+ord('0')));
      ListaInfoL[i].Estado:= espera;
   
   end;
   {proceso del fichero operaciones.txt }

   {$i-} { Desactiva la comprobacion de errores de entrada/salida}
   Assign(ficheroUsuarios, 'Lectura/usuarios.txt');
   Reset(ficheroUsuarios);
   {$i+} { Activa la comprobacion de errores de entrada/salida}
   IF (IoResult <> 0) THEN BEGIN
	  writeln('*** lectura.pas: error al acceder al fichero usuarios.txt');
	  halt(1)	
   END;

   WHILE NOT EOF(ficheroUsuarios) DO
   BEGIN
	  { Lee una linea del fichero y la almacena en tres variables}
	  ReadLn(ficheroUsuarios, linea);
     operacion := linea[1];
	  InfoL.NickUsuario    := trim(copy(linea,3,12));  { trim elimina los espacios al comienzo y final de un string }
										  { copy(s, i, j) copia j caracteres del string s }                                                         
										  { a partir de la posicion i }
     writeln('########################################');
     writeln('operacion ',operacion,' sobre ',InfoL.NickUsuario,'.');
     writeln('#########################################');
     writeln;
                                
      case operacion of
      
         'A': AnnadirAmigo(Lista,InfoL);
         
         'B': BorrarAmigo(Lista,InfoL.NickUsuario);
         
         'M': Modificar(Lista,InfoL);
         
         otherwise writeln('Opción no valida.');
      
      
      end;
      
      writeln('____________________________');
      Imprimir(Lista);
      writeln('____________________________');
      writeln;

   
   end;
	  
   
END.
