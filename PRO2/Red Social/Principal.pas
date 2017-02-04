Program Principal;
{TÍTULO: Prácticas de PROGRAMACION II<br />SUBTÍTULO: Practica 3
AUTOR 1: Gabriel Míguez Míguez LOGIN 1: gabriel.miguez
AUTOR 2: Miguel Mosquera Pérez LOGIN 2: miguel.mosquera.perez
GRUPO: 3.2
FECHA: 13/03/2011
}

USES sysutils, ColaOrdenes, ListaAmigos,Multilista;

Const
	MaxDenuncias= 3;

VAR

	cola		:tCola;
	MultiList	:tMultiLista;
	orden		:tInfoC;

{**********************************************************************}

	Procedure LeerCola (VAR cola: tCola);
	
	VAR
	   ficheroUsuarios    : TEXT;
	   linea              : STRING;
	   InfoC			  : tInfoC;

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
	  

	END;

{**********************************************************************}

	Procedure ImprimirListaAmigos (Lista: tLista);
	{Funcion que saca por pantalla los datos de un usuario}
	
	VAR
		Amigo: tInfoL;
		Pos: tPosL;
		
	{******************************************************************}
	
		Function EscribirEstado (Estado: tEstado): string;
		{Funcion que devuelve un texto indicando el estadoa de la amistad}
		
		Begin
		
				Case Estado of
				
					espera: EscribirEstado:= 'En espera';
					
					aceptada: EscribirEstado:= 'Aceptada';
				
				end;
		
		End;
	
	{******************************************************************}
		
	Begin
	
		
		Pos:= Primera(Lista);
		
		while Pos <> NULOL  DO begin
		
			Amigo:= ObtenerDato(Lista,Pos);
			writeln('		Amigo ',Amigo.nickUsuario,'	: '+EscribirEstado(Amigo.Estado),'.');
			Pos:= Siguiente(Lista,Pos);
		
		end; {While}
	
	End;

{**********************************************************************}

	Procedure ImprimirMultiLista (MultiLista: tMultiLista);
	
	Var
		PosUser: tPosM;
		User: tInfoM;
	
	Begin
	
		writeln('MULTILISTA:');
		writeln;
		PosUser:= Primeram(MultiLista);
		while PosUser <> NULOM do begin
		
			User:=ObtenerDatoM(MultiLista,PosUser);
			writeln('Nick ',User.Nick,' denuncias ',User.numDenuncias);
			ImprimirListaAmigos(User.ListaAmigos);
			writeln;
			writeln;
			PosUser:= SiguienteM(MultiLista, PosUser);
		
		end; {while}
		writeln('__________________');
		writeln;
	
	End;

{**********************************************************************}

	Procedure ImprimirUsuarioInexistente(Nick: tNickUsuario);
	{Funcion que saca por pantalla un mensaje indicando que el usuario de nick Nick no existe.}
	
	Begin
	
		writeln('**** El usuario ',Nick, ' no existe');
	
	End;

{**********************************************************************}

	Procedure lectura(Var Cola: tCola);
	{Proceso que inicia la cola y pasa todos los datos del fichero de lectura a la cola.
	* Entradas: La cola.
	* Salidas: La cola conteniendo los operaciones a realizar.}


	VAR
	   ficheroUsuarios    : TEXT;
	   linea              : STRING;
	   orden              : tInfoC;


	BEGIN
	  
	   {proceso del fichero operaciones.txt }

	   {$i-} { Desactiva la comprobacion de errores de entrada/salida}
	   Assign(ficheroUsuarios, 'operaciones.txt');
	   Reset(ficheroUsuarios);
	   {$i+} { Activa la comprobacion de errores de entrada/salida}
	   IF (IoResult <> 0) THEN BEGIN
		  writeln('*** lectura.pas: error al acceder al fichero operaciones.txt');
		  halt(1)
	   END;
	   
	   ColaVacia(Cola);
	   
	   WHILE NOT EOF(ficheroUsuarios) DO
	   BEGIN
		  { Lee una linea del fichero y la almacena en tres variables}
		  ReadLn(ficheroUsuarios, linea);
		  orden.op := linea[1];
		  orden.user1    := trim(copy(linea,3,9));  { trim elimina los espacios al comienzo y final de un string }
											  { copy(s, i, j) copia j caracteres del string s a partir de la posicion i }
		  orden.user2 := trim(copy(linea,13,9)); 
		  { Ahora podria realizarse alguna operacion con los elementos leidos }
		  { en este caso mostrarlos por pantalla	                          }
		  InsertarDatoCola(Cola,orden);
	   END;
	   Close(ficheroUsuarios);

	END;

{**********************************************************************}

	Procedure AltaUsuario (orden: tInfoC;Var Multilista: tMultilista);
	{Proceso que inserta un nuevo usuario en lla multilista.
	* Entradas: La orden que contiene el nick del usuario a insertar,
		la multilista donde se inserta.
	* Salidas: La multilista con un nuevo usuario insertado en orden alfavetico
		por nombre, con nick igual al nick contenido en la orden, numero de denuncias
		igual a 0 , y la lista de amigos iniciada a vacia.}
	
	Var
	
		NuevoUser: tInfoM;
	
	Begin
	
		if length(trim(orden.User1))<>0 then begin {if exterior} {Solo se añadira un usuario si el nick contiene algun caracter 
																	distinto al espacio}
		
			if BuscarM(Multilista,orden.User1)=NULOM then begin {if anidado} {Solo se añadira si el nick no esta en uso}
			
				NuevoUser.Nick:= orden.User1;
				NuevoUser.numDenuncias:=0;
				ListaVacia(NuevoUser.ListaAmigos);
				
				if InsertarDatoM(Multilista,NuevoUser) then
					writeln('**** Alta de Usuario: Nick ',orden.User1)
				else writeln('**** Fallo Alta Usuario ',orden.User1,', memoria insuficiente');
			
			end	
			else writeln('**** Fallo Alta Usuario ',orden.User1,' nick ya se encuentra en uso');
		
		end{if exterior}
		else writeln('Fallo alta, no se ha introducido ningun nick');
	
	End;

{**********************************************************************}

	Procedure IncrementarDenuncias (Orden: tInfoC;VAR MultiLista: tMultilista);
	{Proceso que incremmenta en 1 el numero de denuncia del usuario indicado por
	la orden.
	* Entradas: Una orden que contiene el nick del usuario denunciado y la multilista
	* Salidas: La multilista con el nnumero de denuncias del usuario indicado incrementado en 1.}
	
	
	Var
		Pos: tPosM;
		Usuario: tInfoM;
	
	Begin
	
		Pos:= BuscarM(Multilista,Orden.User1);
		if pos <> NULOL then begin
		
			Usuario:= ObtenerDatoM(Multilista,Pos);
			Usuario.numDenuncias:= Usuario.numDenuncias + 1;
			ActualizarDatoM(Multilista,Pos,Usuario.numDenuncias,Usuario.ListaAmigos);
			writeln('**** Denuncia Usuario: Nick ',Orden.User1,' – Nuevo num denuncias ',Usuario.numDenuncias,'.');
			
		end
		else ImprimirUsuarioInexistente(orden.User1);
	
	End;

{**********************************************************************}

	Procedure InvitarAmistad (orden: tInfoC;VAR Multilista: tMultiLista);
	{Funcion que añade a la lista de amigos de primer usuario contenido en orden
	el segundo usuario, en estado de espera.
	* Entradas: La orden que contiene los dos usuarios implicados y la multilista.
	* Salidas: la Multilista con el campo Lista amigos del usuario uno modificado,
		de modo que contendra al usuario dos en estado de espera.}
		
	VAR
		Pos: tPosM;
		Usuario: tInfoM;
		Amigo: tInfoL;
	
	Begin
	
		if (length(orden.User1) <> 0) AND (length(orden.User2) <> 0) then begin {If exterior}
													{verifico que se hayan recibido dos nombres}
		
			Pos:= BuscarM(MultiLista,Orden.User1);
			if (Pos <> NULOM) AND (BuscarM(MultiLista,Orden.User2)<> NULOM) then begin {Primer if anidado}
																{verifico que ambos usuarios implicado existan.}
			
				Usuario:= ObtenerDatoM(MultiLista, Pos);
				
				if BuscarDato(Usuario.ListaAmigos, Orden.User2)= NULOL then begin {Segundo then anidado}
				
					Amigo.NickUsuario:=Orden.User2;
					Amigo.Estado:= espera;
					if InsertarDatoLista(Usuario.ListaAmigos,Amigo) then begin
					
						if Usuario.ListaAmigos<>NULOL then writeln('**** Usuario ',orden.User1,' manda peticion de amistad a ',orden.User2,'.');
						ActualizarDatoM(MultiLista,Pos,Usuario.numDenuncias,Usuario.ListaAmigos);
						
					end
					else writeln('**** Error mandando peticion amistad, memoria insuficiente.');
					
				end {Segundo then anidado}
				else writeln('**** Invitacion ya realizada con anterioridad.');
				
				
			end{Primer if anidado}
			else begin {else}
			
				writeln('**** Invitacion de amistad dallida.');
				if Pos=NULOM then
					ImprimirUsuarioInexistente(Orden.User1)
				else ImprimirUsuarioInexistente(Orden.User2);
			
			end; {else}
		
		end {if exterior}
		else begin {else}
		
			writeln('**** Invitacion de amistad fallida, los dos campos de usuarios');
			writeln('han de completarse.');
			
		end; {else}
		
		
	
	End;

{**********************************************************************}

	Procedure AceptarInvitacion (Orden: tInfoC;VAR MultiLista: tMultiLista);
	{Proceso que establece una relacionde amistad entre los usuarios
		User1 y User2 contenidos en Orden previa invitacion de User2 a User1.
	* Entradas: Orden con los usuarios a insertar, y la multilista.
	* Salidas: La multilista con la lista de amigos de user2 y User1 modificadas
		de modo que uno es amigo dle otro.}
	
	VAR
		PosAcepta, PosInvita: tPosM;
	
	{******************************************************************}
	
		Procedure CompletarAceptacion(PosAcepta,PosInvita: tPosM;Multilista: tMultiLista);
		{Proceso que recive dos posiciones correctas, y establece una
		relacion de amistad entre el usuario de la posicion PosInvita, el
		cual previamente debio peticion de amistad al usuario PosAcepta, y
		este último, en caso contrario imprime un aviso de error.}
		
		VAR
			UserAcepta, UserInvita: tInfoM;
			AmigoAcepta, AmigoInvita: tInfoL;
			PosAmigoAcepta: tPosL;
		
		Begin {CompletarAceptacion}
		
			UserAcepta:= ObtenerDatoM(Multilista, PosAcepta);
			UserInvita:= ObtenerDatoM(MultiLista, PosInvita);
			PosAmigoAcepta:= BuscarDato(UserInvita.ListaAmigos,UserAcepta.nick);
			if PosAmigoAcepta <> NULOL then begin {Compruebo que el amigo que acepta haya recibido tal invitacion}
			
				AmigoAcepta.nickUsuario:= UserAcepta.Nick;
				AmigoAcepta.Estado:= aceptada;
				AmigoInvita.NickUsuario:= UserInvita.Nick;
				AmigoInvita.Estado:= aceptada;
				ActualizarDato(UserInvita.ListaAmigos,PosAmigoAcepta,AmigoAcepta);
				InsertarDatoLista(UserAcepta.ListaAmigos,AmigoInvita);
				ActualizarDatoM(MultiLista,PosAcepta,UserAcepta.numDenuncias,UserAcepta.ListaAmigos);
				writeln('**** Amistad Establecida: ',UserAcepta.Nick,' – ' , UserInvita.Nick,'.');
			
			end
			else writeln('**** Error: El usuario ',UserInvita.nick,' no ha mandado peticion de amistad al usuario',UserAcepta.nick,'.');
		
		End; {CompletarAceptacion}
	
	{******************************************************************}
	
	Begin
	
		if (Length(orden.User1) <> 0 ) AND (Length(orden.User2) <> 0 ) then begin {then exterior}
		
			PosAcepta:= BuscarM(MultiLista,Orden.User1);
			if PosAcepta <> NULOM then begin {Primer then anidado}
			
				PosInvita:= BuscarM(MultiLista,Orden.User2);
				if PosInvita <> NULOL then begin{Segundo then anidado}
				
					CompletarAceptacion(PosAcepta,PosInvita,MultiLista);
				
				end {Segundo then anidado}
				else ImprimirUsuarioInexistente(orden.User2);
			
			end {Primer then anidado}
			else ImprimirUsuarioInexistente(Orden.User1);
			
		end {then exterior}
		else writeln('**** Error los campos users han de ser rellenados ambos.');
	
	End;

{**********************************************************************}

	Procedure RechazarInvitacion (Orden: tInfoC;VAR Multilista: tMultiLista);
	{Proceso que rechaza la peticion del User2, contenido en Orden, al User1.
	* Entradas: Orden donde se encuentran los usuarios implicados y la multilista.
	* Salidas: La multilista con la peticion de amistad rechazada.}
	
	VAR
		PosInvita: tPosM;
		UserInvita: tInfoM;
		PosAmigo: tPosL;
	
	Begin {RechazarInvitacion}
	
		if (Length(orden.User1) <> 0 ) AND (Length(orden.User2) <> 0 ) then begin {then exterior}
		
			if BuscarM(MultiLista,Orden.User1) <> NULOM then begin {Primer then anidado}
			
				PosInvita:= BuscarM(MultiLista,Orden.User2);
				if PosInvita <> NULOL then begin{Segundo then anidado}
				
					UserInvita:= ObtenerDatoM(MultiLista, PosInvita);
					PosAmigo:= BuscarDato(UserInvita.ListaAmigos,Orden.User1);
					if PosAmigo <> NULOL then begin {tercer then anidado}
					
						EliminarPosicion(UserInvita.ListaAmigos,PosAmigo);
						ActualizarDatoM(MultiLista,PosInvita,UserInvita.numDenuncias,UserInvita.ListaAmigos);
						writeln('**** Invitacion Rechazada: ',orden.User1,' – ',orden.User2);
					
					end {tercer then anidado}
					else writeln('**** Error user ', UserInvita.nick,' no habia mandado invitacion a ',Orden.User2);
				
				end {Segundo then anidado}
				else ImprimirUsuarioInexistente(orden.User2);
			
			end {Primer then anidado}
			else ImprimirUsuarioInexistente(Orden.User1);
			
		end {then exterior}
		else writeln('**** Error los campos users han de ser rellenados ambos.');
	
	
	End; {RechazarInvitacion}

{**********************************************************************}

	Procedure TerminarAmistad (orden: tInfoC; Var MultiLista: tMultiLista);
	{Este proceso borra de la lista de amigos de los Usuarios contenidos en orden,
	al otro usuario.
	* Entradas: Orden la cual contiene los usuarios implicados, la Multilista
	* Salidas: La multilista con la relacion de amistad borrada entra ambos usuarios.}
	
	VAR
		User1, User2	: tInfoM;
		PosUser1,PosUser2: tPosM;
		PosAmigo1, PosAmigo2: tPosL;
	
	Begin {Terminar Amistad}
	
		PosUser1:=BuscarM(MultiLista,Orden.User1);
		if PosUser1 <> NULOM then begin
		
			User1:= ObtenerDatoM(MultiLista,PosUser1);
			PosAmigo1:= BuscarDato(User1.ListaAmigos,Orden.User2);
			if PosAmigo1 <> NULOL then begin
			
				EliminarPosicion(User1.ListaAmigos, PosAmigo1);
				ActualizarDatoM(MultiLista,PosUser1,User1.numDenuncias,User1.ListaAmigos);
				
			end;
			
		end
		else ImprimirUsuarioInexistente(Orden.User1);
		PosUser2:=BuscarM(MultiLista,Orden.User2);
		if PosUser2 <> NULOM then Begin
		
			User2:= ObtenerDatoM(MultiLista,PosUser2);
			PosAmigo2:= BuscarDato(User2.ListaAmigos,Orden.User1);
			if PosAmigo2 <> NULOL then begin
				
				
				EliminarPosicion(User2.ListaAmigos, PosAmigo2);
				ActualizarDatoM(MultiLista,PosUser2,User2.numDenuncias,User2.ListaAmigos);
				
			end
			
		end
		else ImprimirUsuarioInexistente(Orden.User2);
	End; {Terminar Amistad}

{**********************************************************************}

	Procedure Eliminar (orden: tInfoC;VAR  Multilista: tMultiLista);
	{Proceso que borra un usuario concreto o todos los que tengan exceso de denuncias
		en funcion si el canpo User1 de orden esta o no relleno
	* Entradas: Orden con el campo user1 en caso de querer borrar a ese usuario y la multilista.
	* Salidas: La multiLista con el User1 borrado o todos los que excedan el maximo de denuncias
		en caso de no ser indicado ningun usuario a borrar.}
	
	VAR
		PosUser: tPosM;
		BorrarExceso: Boolean;
	
	{******************************************************************}

		Procedure EliminarUsuario (VAR PosUser: tPosM;VAR MultiLista: tMultiLista; BorrarExceso: boolean);
		{Proceso que elimina un usuario.
		* Entradas: La Posicion del usuario a eliminar, la MultiLista, y una variable
			que indica si se esta borrando por exceso de denuncias o no para imprimir
			el mensaje adecuado
		* Salidas: La MultiLista con el usuario borrado y el mensaje correspondiente en pantalla.
		* PostCond: La PosUser ahora apunta al siguiente usuario en caso de haberlo.}
		
		Var
			
			User: tInfoM;
			Pos: tPosM;
			NickEliminado: tNickUsuario;
			PosAmigo: tPosL;
			
		Begin
		
			User:= ObtenerDatoM(MultiLista,PosUser);
			if BorrarExceso then writeln('Usuario: ',User.Nick,'.')
			else begin 
			
				writeln('**** Baja de Usuario: Nick ',User.Nick,' Denuncias ',User.numDenuncias:1,'.');
				ImprimirListaAmigos(User.ListaAmigos);
				
			end;
			BorrarM(MultiLista,PosUser);
			Pos:=PrimeraM(MultiLista);
			NickEliminado:= User.Nick;
			while Pos <> NULOM do begin
			
				User:= ObtenerDatoM(MultiLista,Pos);
				PosAmigo:= BuscarDato(User.ListaAmigos,NickEliminado);
				if PosAmigo <> NULOL then begin
				
					EliminarPosicion(User.ListaAmigos, PosAmigo);
					ActualizarDatoM(MultiLista,Pos,User.numDenuncias,User.ListaAmigos);
					
				end;
				Pos:= SiguienteM(MultiLista, Pos);
			
			end; {while}
			
		
		End;

	{******************************************************************}
	
	Begin
	
		BorrarExceso:= false;
		if length(orden.User1) <> 0 then begin
		
			PosUser:= BuscarM(MultiLista,Orden.User1);
			if PosUser <> NULOM then EliminarUsuario(PosUser, MultiLista,BorrarExceso)
			else writeln('**** El usuario ',orden.User1,' no existe.');
			
		end
		else begin {else}
		
			PosUser:= PrimeraM(MultiLista);
			while (PosUser<> NULOM) AND not BorrarExceso  do begin
				
				if ObtenerDatoM(MultiLista,PosUser).numDenuncias >= MaxDenuncias then 
					BorrarExceso:= true
				else PosUser:= SiguienteM(MultiLista,PosUser)
					
			end; {while}
			
			if BorrarExceso then begin {then}
			
				writeln('**** Eliminacion de Usuarios por Denuncias acumuladas');
				EliminarUsuario(PosUser,MultiLista,BorrarExceso);
				while PosUser <> NULOM do begin
				
					if ObtenerDatoM(MultiLista,PosUser).numDenuncias >= MaxDenuncias then 
						EliminarUsuario(PosUser,MultiLista,BorrarExceso)
					else PosUser:= SiguienteM(MultiLista,PosUser);
				
				end;{while}
			
			end {then}
			else writeln('Ningun usuario acumula el máximo de denuncias permitido');
		
		end; {else}
	
	End;
	
{**********************************************************************}

BEGIN

	LeerCola(Cola);
	MultilistaVacia(MultiList);
	
	while not EsColaVacia(cola) do begin
	
		orden:= FrenteCola(Cola);
		writeln(Orden.op,' --> [',orden.User1,'] [',orden.User2,']');
		EliminarCola(Cola);
		case orden.op of 
		
			'A': AltaUsuario(Orden ,MultiList);
			
			'B': Eliminar(Orden,Multilist);
			
			'D': IncrementarDenuncias(Orden,Multilist);
			
			'I': InvitarAmistad(Orden,Multilist);
			
			'C': AceptarInvitacion(Orden,Multilist);
			
			'R': RechazarInvitacion(Orden,Multilist);
			
			'T': TerminarAmistad(Orden,Multilist);
		
		end;{case}
		writeln;
		
		ImprimirMultiLista(MultiList);
		
	
	end; {while}

END.
