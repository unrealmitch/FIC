UNIT Multilista;
{TÍTULO: Prácticas de PROGRAMACION II<br />SUBTÍTULO: Practica 3
AUTOR 1: Gabriel Míguez Míguez LOGIN 1: gabriel.miguez
AUTOR 2: Miguel Mosquera Pérez LOGIN 2: miguel.mosquera.perez
GRUPO: 3.2
FECHA: 13/03/2011
}

INTERFACE

USES ListaAmigos;

Const
	NuloM = nil;

Type
	
	tNickUsuario = STRING[9]; {Nombre usuario}
	tNumDenuncias = Integer; {Numero de denuncias}
	tMultiLista = ^tNodoM; {Puntero que apunta al primer elemento de la lista}
	tPosM = tMultilista; {puntero a una posicion de una lista}

	tInfoM = Record
	
		Nick: tNickUsuario;
		numDenuncias: tNumDenuncias;
		listaAmigos: tLista;
		
	end;
   
   tNodoM = Record
   
      InfoM: tInfoM;
		Siguiente: tPosM; {puntero que apunta al siguiente elemento de la lista}
   
   end;
	
	PROCEDURE MultilistaVacia(VAR Lista:tMultilista);
	Function esMultilistaVacia(Lista:tMultilista):boolean;
	Function PrimeraM(Lista:tMultilista):tPosM;
	Function UltimaM(Lista:tMultilista):tPosM;
	Function SiguienteM(Lista:tMultilista; Pos:tPosM):tPosM;
	Function AnteriorM(Lista:tMultilista; Pos:tPosM):tPosM;
	Function InsertarDatoM(VAR Lista:tMultilista; Dato:tInfoM):Boolean;
	PROCEDURE BorrarM(VAR Lista:tMultilista; VAR Pos:tPosM);
	Function ObtenerDatoM(Lista: tMultilista; Pos: tPosM):tInfoM;
	Procedure ActualizarDatoM( Lista:tMultilista; Pos:tPosM; ND:tNumDenuncias;ListaA:tLista);
	Function BuscarM( Lista:tMultilista; Nick :tNickUsuario):tPosM;
	
IMPLEMENTATION

{**********************************************************************}

	FUNCTION CrearNodo(Dato:tInfoM; Var Pos:tPosM):Boolean;
	{Porceso que crea un nodo con los datos contenidos en Dato}
	 
	Begin

		new(Pos);
		if Pos<>NuloM then begin
			Pos^.infoM:=Dato;
			Pos^.siguiente:=NULOM;
			CrearNodo:= true
		end
		else CrearNodo:= false;

	End;

{**********************************************************************}

	PROCEDURE MultilistaVacia(VAR Lista:tMultilista);
	{Esta funcion recibe una lista de tipo tMultilista es decir un puntero a tInfoM y lo
	pone apuntado a nil,
	Precond: Ha de recibir una Lista sin contenido para evitar memoryLeak}	
	 

	Begin {ListaVacia}

		Lista:= NuloM;

	End;{ListaVacia}

{**********************************************************************}
	 
	FUNCTION esMultilistaVacia(Lista:tMultilista):Boolean;
	{Esta funcion recive una lista y devuelve true si esta vacia y false
	si tiene contenido}


	Begin {esListaVacia}

		esMultilistaVacia:= Lista = NuloM;

	End; {esListaVacia}

{**********************************************************************}
	 
	Function PrimeraM(Lista:tMultilista):tPosM;
	{Devuelve la primera posicion de la lista o NuloM si esta vacia
	Entrada: Lista de tipo tMultilista
	Salidas: Posicion primera de tipo tPosM, o NuloM si la lista es vacia}
	 
	Begin {Primera}

		PrimeraM:= Lista;

	End;{Primera}

{***********************************************************************}

	Function UltimaM(Lista:tMultilista):tPosM;
	{Devuelve la ultima posicion de la Lista o NuloM si la lista esta vacia}
	 
	Begin
		
		if Lista = NuloM then UltimaM:= NuloM
		else begin
			while Lista^.Siguiente<> NuloM do
				Lista:=Lista^.Siguiente;
			UltimaM:= Lista
		end;

	End;


{**********************************************************************}
	 
	Function SiguienteM(Lista:tMultilista; Pos:tPosM):tPosM;
	{Devuelve la siguiente posicion a la posicion Pos, en caso de no haber
	siguiente devuelve NuloM
	Entradas: Lista de tipo tMultilista, posicion de tipo tPosM
	Salidas: la Posicion siguiente a la posicion Pos de tipo tPosM
	PreCD: tPosM es una posición válida en la lista.}
	 
	Begin

		SiguienteM:= pos^.siguiente {Si no hay siguiente pos^.siguiente ya vale NuloM, pues
									el nodo que esta al final siempre apunta a NuloM}

	End;

{**********************************************************************}
	 
	Function AnteriorM(Lista:tMultilista; Pos:tPosM):tPosM;
	{Devuelve la posicion anterior a Pos en la lista MultiLista o NuloM en caso de que
	No haya anterior
	Entradas: Lista, posicion.
	Salidas: la posicion anterior de tipo tPosM a la posicion Pos o NuloM en caso de no haber anterior
	PreCD: tPosM es una posición válida en la lista.}


	Begin

		if Pos = Lista then
			AnteriorM:= NuloM
		else begin
		
			while Lista^.siguiente <> Pos do
				Lista:= Lista^.siguiente;
			AnteriorM:= Lista;
		
		end;
		

	End;

{**********************************************************************}
	 
	Function InsertarDatoM(VAR Lista:tMultilista; Dato:tInfoM):Boolean;
	{Funcion que inserta un dato de forma ordenada (alfabeticamente por el nick).
	Entradas: un Dato de tipo tInfoM y Lista de tipo tMultilista.
	Salidas: la Lista modificada y true o false segun se haya insertado el dato o no}

	 
	  Var
			NuevaPos, TempPos: tPosM;
			
		{******************************************************************}
			
			Function EncontrarPosicionInsertado ( Lista: tMultilista; Dato: tInfoM):tPosM;
			{Funcion que devuelve la posicion a continuacion de la cual se debe insertar el dato
			* Entradas: Una Lista ordenada y un dato a insertar.
			* Salidas: La posicion despues de la cual se ha de insertar el dato o nulo en caso de que deba ser el primero a insertar.
			* PreCD: La lista es no vacia.
			* PostCD: El campo siguiente ya se devuelve inivializado a nulo.}
			
			VAR
				TempPos: tPosM;
			
			Begin
				
				TempPos:= NULOM;
				while (Lista^.InfoM.Nick < Dato.Nick) AND (Lista^.siguiente <> NULOL) do begin
				{Saldremos si encontramos un siguiente mayor o si llegamos al final de la lista}
				
					TempPos:=LIsta;
					Lista:= Lista^.siguiente;
					
				end;
				if Dato.Nick > Lista^.InfoM.Nick then {En este caso se insertara como ultimo nodo}
					TempPos:= Lista;
				EncontrarPosicionInsertado:= TempPos;
					
			End;
			
		{******************************************************************}
			
		Begin

			if  CrearNodo(Dato,NuevaPos) then begin {then exterior}
			
				
				If EsMultiListaVacia(Lista) then begin {Then anidado}
				
					Lista:=NuevaPos
				
				end {Then anidado}
				else begin
				
					TempPos:= EncontrarPosicionInsertado(Lista,Dato);
					
					If TempPos = NULOM then begin {Se añade como primer nodo}
						
						NuevaPos^.siguiente:= Lista;
						Lista:= NuevaPos;
					
					end
					else begin {Se añade a la posicion correspondiente}
					
						NuevaPos^.siguiente:= TempPos^.siguiente;
						TempPos^.siguiente:=NuevaPos;
					
					end;
				
				end;
				InsertarDatoM:= true;
				
			end {then exterior}
			else InsertarDatoM:= false;
			
		End;



{**********************************************************************}

	Function ObtenerDatoM(Lista: tMultilista; Pos: tPosM):tInfoM;
	{Obtiene los datos asociados al elemento que ocupa la posicion Pos
	Entradas: Una Posicion (Pos) y la Lista en la que se encuentra.
	Salidas: El campo InfoM que contiene el Nodo señalado por la posicion Pos.
	PreCD: La posición tiene que ser válida.}

	Begin

		ObtenerDatoM:=Pos^.InfoM

	End;

{**********************************************************************}

	Procedure ActualizarDatoM( Lista:tMultilista; Pos:tPosM; ND:tNumDenuncias;ListaA:tLista);

	Begin

		Pos^.Infom.numDenuncias:= ND;
		Pos^.InfoM.listaAmigos:= ListaA;

	End;

{**********************************************************************}

	 
	PROCEDURE BorrarM(VAR Lista:tMultilista; VAR Pos:tPosM);
	{Proceso que elimina el nodo señalado por Pos
	Entrada: Posicion a eliminar tipo tPosM, y la Lista
	Salida: la Lista sin esa posición
	PreCD: tPosM es una posición válida en la lista.
	PostCD: La posicion señalada por la posicion (Pos) recivida ahora esta ocupada por
	la que era la siguiente posicion,o NuloM si la posicion a eliminar era la última.
	Tambien a quedado eliminada su lista de amigos.}

	VAR
		tempPos: tPosM;

	Begin
		
		if Pos^.siguiente <> NuloM then begin
		
			TempPos:= Pos^.siguiente;
		  while Not esListaVacia(Pos^.InfoM.ListaAmigos) do 
			 EliminarPosicion(Pos^.InfoM.ListaAmigos,Pos^.InfoM.ListaAmigos);
			Pos^:= TempPos^;
			Dispose(TempPos);
			
		end
		else begin {else exterior}
		
			if Pos = Lista then
				Lista:= Lista^.siguiente
			else begin {else interior}
				
				TempPos:= AnteriorM(Lista,Pos);
				TempPos^.siguiente:= NuloM;
				
			end; {else interior}
			
		  while not esListaVacia(Pos^.InfoM.ListaAmigos) do 
			 EliminarPosicion(Pos^.InfoM.ListaAmigos,Pos^.InfoM.ListaAmigos);
			Dispose(Pos);
			Pos:= NuloM;
			
		end; {else exterior}

	End;
	
{********************************************************************}

	FUNCTION BuscarM(Lista:tMultilista; Nick :tNickUsuario):tPosM;
	{Funcion que devuelve la posicion de la lista de usuarios cullo nombre
	coincida con Nick, si no se encuentra devolvera NuloM.
	Entradas: Nick a buscar y Lista.
	Salida: Poscion de la lista que contiene ese nick o NuloM si no hay nadie en la lista con ese nick.}


	Begin

	   If Lista<> NuloM then begin

		  While (Lista^.siguiente <> NuloM) AND (Lista^.InfoM.nick <> Nick)do
				Lista:= Lista^.siguiente;
		  If Lista^.InfoM.nick = nick then
			 BuscarM:= Lista
		  else
			 BuscarM:= NuloM;
	   end
	   else BuscarM:= NuloM; 

	End;

{**********************************************************************}

BEGIN


END.
