Unit ListaAmigos;
{TÍTULO: Prácticas de PROGRAMACION II<br />SUBTÍTULO: Practica 3
AUTOR 1: Gabriel Míguez Míguez LOGIN 1: gabriel.miguez
AUTOR 2: Miguel Mosquera Pérez LOGIN 2: miguel.mosquera.perez
GRUPO: 3.2
FECHA: 13/03/2011
}

Interface

CONST
	NULOL= nil;
	
TYPE

	tEstado = (espera, aceptada);
	tNickUsuario = string[9];
	tInfoL = record
	
		NickUsuario: tNickUsuario;
		Estado: tEstado;
	
	End;
	tPosL= ^tNodo;
	tLista= tPosL;
	tNodo= record
	
		InfoL: tInfoL;
		siguiente: tPosL;
	
	end;
	
	Procedure ListaVacia (VAR Lista: tLista);
	Function EsListaVacia (Lista: tLista):boolean;
	Function Primera (Lista: tLista): tPosL;
	Function Ultima (Lista: tLista): tPosL;
	Function Siguiente (Lista: tLista; Pos: tPosL): tPosL;
	Function Anterior (Lista: tLIsta; Pos: tPosL): tPosL;
	Function InsertarDatoLista (VAR Lista:tLista; Dato:tInfoL):boolean;
	Procedure EliminarPosicion (VAR Lista:tLista; Pos:tPosL);
	Function ObtenerDato (Lista:tLista; Pos:tPosL): tInfoL;
	Procedure ActualizarDato(Lista:tLista; Pos:tPosL; Dato:tInfoL);
	Function BuscarDato (Lista:tLista; Nick:tNickUsuario): tPosL;
	

Implementation



{**********************************************************************}

	PROCEDURE ListaVacia(VAR Lista:tLista);
	{Esta funcion recive una lista de tipo tLista es decir un puntero a tdato y lo
	pone apuntado a nil,
	Precond: Ha de recibir una Lista sin contenido para evitar memoryLeak}	
	 

	Begin {ListaVacia}

		Lista:= NULOL;

	End;{ListaVacia}

{**********************************************************************}
	 
	FUNCTION esListaVacia(Lista:tLista):Boolean;
	{Esta funcion recive una lista y devuelve true si esta vacia y false
	si tiene contenido}


	Begin {esListaVacia}
		
		esListaVacia:= Lista = NULOL;

	End; {esListaVacia}

{**********************************************************************}
	 
	Function Primera(Lista:tLista):tPosL;
	{Devuelve la primera posicion de la lista o NULOL si esta vacia
	Entrada: Lista de tipo tLista
	Salidas: Posicion primera de tipo tPosL}
	 
	Begin {Primera}

		Primera:= Lista;

	End;{Primera}

{***********************************************************************}

	Function Ultima(Lista:tLista):tPosL;
	{Devuelve la ultima posicion de la Lista o NULOL si la lista esta vacia}
	 
	Begin
		
		if Lista = NULOL then Ultima:= NULOL
		else begin
			while Lista^.Siguiente<> NULOL do
				Lista:=Lista^.Siguiente;
			Ultima:= Lista
		end;

	End;


{**********************************************************************}
	 
	Function Siguiente(Lista:tLista; Pos:tPosL):tPosL;
	{Devuelve la siguiente posicion a la posicion Pos, en caso de no haber
	siguiente devuelve NULOL
	Entradas: Lista de tipo tLista, posicion de tipo tPosL
	Salidas: la Posicion siguiente a la posicion Pos de tipo tPosL
	PreCD: tPosL es una posición válida en la lista.}
	 
	Begin

		Siguiente:= pos^.siguiente {Si no hay siguiente pos^.siguiente ya vale NULOL, pues
									el nodo que esta al final siempre apunta a NULOL}

	End;

{**********************************************************************}
	 
	Function Anterior(Lista:tLista; Pos:tPosL):tPosL;
	{Devuelve la posicion anterior a Pos en la lista Lista o NULOL en caso de que
	No haya anterior
	Entradas: Lista, posicion.
	Salidas: la posicion anterior de tipo tPosL a la posicion Pos o NULOL en caso de no haber anterior
	PreCD: tPosL es una posición válida en la lista.}


	Begin

		if Pos = Lista then
			Anterior:= NULOL
		else begin
		
			while Lista^.siguiente <> Pos do
				Lista:= Lista^.siguiente;
			Anterior:= Lista;
		
		end;
		

	End;

{**********************************************************************}
	 
	Function InsertarDatoLista (VAR Lista:tLista; Dato:tInfoL):boolean;
	{Funcion que inserta un dato por orden de nick en la lista
	* Entrada: La lista, y un dato
	* Salidas: La lista con el dato insertado, true si se pudo insertar o false si no.
	* PostCN: el nodo se insertara aun que ya haya otro nodo con el mismo dato}

	 Var
		NuevaPos, TempPos: tPosL;
		
	{******************************************************************}
		
		FUNCTION CrearNodo(Dato:tInfoL; Var Pos:tPosL):Boolean;
		{Porceso que crea un nodo con los datos contenidos en Dato}
		 
		Begin

			new(Pos);
			if Pos<>NULOL then begin
				Pos^.InfoL:=Dato;
				Pos^.siguiente:= NULOL;
				CrearNodo:= true
			end
			else CrearNodo:= false;

		End;
		
	{******************************************************************}
		
		Function EncontrarPosicionInsertado ( Lista: tLista; Dato: tInfoL):tPosL;
		{Funcion que devuelve la posicion a continuacion de la cual se debe insertar el dato
		* Entradas: Una Lista ordenada y un dato a insertar.
		* Salidas: La posicion despues de la cual se ha de insertar el dato o nulo en caso de que deba ser el primero a insertar.
		* PreCD: La lista es no vacia.
		* PostCD: El campo siguiente ya se devuelve inivializado a nulo.}
		
		VAR
			TempPos: tPosL;
		
		Begin
			
			TempPos:= NULOL;
			while (Lista^.InfoL.NickUsuario < Dato.NickUsuario) AND (Lista^.siguiente <> NULOL) do begin
			{Saldremos si encontramos un siguiente mayor o si llegamos al final de la lista}
			
				TempPos:=LIsta;
				Lista:= Lista^.siguiente;
				
			end;
			if Dato.NickUsuario > Lista^.InfoL.NickUsuario then {En este caso se insertara como ultimo nodo}
				TempPos:= Lista;
			EncontrarPosicionInsertado:= TempPos;
				
		End;
		
	{******************************************************************}
		
	Begin

		if  CrearNodo(Dato,NuevaPos) then begin {then exterior}
		
			
			If EsListaVacia(Lista) then begin {Then anidado}
			
			
				Lista:=NuevaPos
			
			end {Then anidado}
			else begin
			
				TempPos:= EncontrarPosicionInsertado(Lista,Dato);
				
				If TempPos = NULOL then begin {Se añade como primer nodo}
					
					NuevaPos^.siguiente:= Lista;
					Lista:= NuevaPos;
				
				end
				else begin {Se añade a la posicion correspondiente}
				
					NuevaPos^.siguiente:= TempPos^.siguiente;
					TempPos^.siguiente:=NuevaPos;
				
				end;
			
			end;
			InsertarDatoLista:= true;
			
		end {then exterior}
		else InsertarDatoLista:= false;
		
	End;

{**********************************************************************}
	 
	Procedure EliminarPosicion (VAR Lista:tLista; Pos:tPosL);
	{Proceso que elimina el nodo señalado por Pos
	Entrada: Posicion a eliminar tipo tPosL, y la Lista
	Salida: la Lista sin esa posición
	PreCD: tPosL es una posición válida en la lista.
	PostCD: La posicion señalada por la posicion (Pos) recivida ahora esta ocupada por
	la que era la siguiente posicion}

	VAR
		tempPos: tPosL;

	Begin

	if Pos <> Lista then begin {then exterior}
	
		if Pos^.siguiente <> NULOL then begin {then interior}
		
			TempPos:= Pos^.siguiente;
			Pos^:= TempPos^;
			Dispose(TempPos);
			
		end {then interior}
		else begin
			Anterior(Lista,Pos)^.siguiente:= NULOL;
			Dispose(Pos);
		end;
		
	end {then exterior}
	else begin
	
		Lista:= Pos^.siguiente;
		Dispose(Pos);
		
	end;

	End;
	
{**********************************************************************}

	Function ObtenerDato (Lista:tLista; Pos:tPosL): tInfoL;
	{Obtiene los datos asociados al elemento que ocupa la posicion Pos
	Entradas: Una Posicion (Pos), la Lista, una variable Nick y una variable Denuncias para 
	* contener el nick y las denuncias.
	Salidas: El nick y denuncias del usuario qeu ocupa la posición Pos.
	PreCD: La posición tiene que ser válida.}

	Begin

		ObtenerDato:= Pos^.InfoL

	End;

{**********************************************************************}

	Procedure ActualizarDato(Lista:tLista; Pos:tPosL; Dato:tInfoL);
	{Funcion que actualiza el campo Info del nodo de la posicion Pos
	con el contenido de la variable DATO.
	* PostCN: Para que la lista siga siendo ordenada el campo NickUsuario
	  de Dato debe ser el mismo del nodo donde queremos insertar su contenido, o
	  en caso contrario la lista no estara ordenada.}

	Begin

		Pos^.InfoL:= Dato;

	End;

{**********************************************************************}

	Function BuscarDato (Lista:tLista; Nick:tNickUsuario): tPosL;
	{Funcion que devuelve la posicion de la lista de usuarios cullo nombre
	coincida con Nick, si no se encuentra devolvera NULOL.
	Entradas: Nick a buscar y Lista.
	Salida: Poscion de la lista que contiene ese nick o NULOL si no hay nadie en la lista con ese nick.}


	Begin

		If Lista <> NULOL then begin

			
			While (Lista^.siguiente <> NULOL) AND (Lista^.InfoL.NickUsuario <> Nick)do 
					Lista:= Lista^.siguiente;
			If Lista^.InfoL.NickUsuario = nick then 
				BuscarDato:= Lista
			else
				BuscarDato:= NULOL;
	
		end
		else BuscarDato:= NULOL; 

	End;

{**********************************************************************} 


Begin


End.
