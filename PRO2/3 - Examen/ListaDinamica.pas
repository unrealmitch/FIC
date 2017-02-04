UNIT ListaDinamica;

INTERFACE

Const
	NULO = nil;

Type
	
	tNickUsuario = STRING; {Nombre usuario}
	tNumDenuncias = Integer; {Numero de denuncias}
	tLista = ^tDato; {Puntero que apunta al primer elemento de la lista}
	tPos = tLista; {puntero a una posicion de una lista}
	tDato = Record
	
		Nick: tNickUsuario;
		numDenuncias: tNumDenuncias;
		Siguiente: tPos; {puntero que apunta al siguiente elemento de la lista}
		
	end;
	
	PROCEDURE ListaVacia(VAR Lista:tLista);
	FUNCTION esListaVacia(Lista:tLista):boolean;
	Function Primera(Lista:tLista):tPos;
	Function Ultima(Lista:tLista):tPos;
	Function Siguiente(Lista:tLista; Pos:tPos):tPos;
	Function Anterior(Lista:tLista; Pos:tPos):tPos;
	Function InsertarDato(Dato:tDato; Pos:tPos;VAR Lista:tLista):Boolean;
	PROCEDURE EliminarPosicion(Pos:tPos; Lista:tLista);
	PROCEDURE ObtenerDato (Pos: tPos; Lista: tLista;VAR Nick: tNickUsuario;VAR Denuncias:tNumDenuncias);
	Procedure ActualizarDato( Lista:tLista; Pos:tPos; ND:tNumDenuncias);
	FUNCTION BuscarDato (Nick :tNickUsuario; Lista:tLista):tPos;
	
IMPLEMENTATION

{**********************************************************************}

FUNCTION CrearNodo(Dato:tDato; Var Pos:tPos):Boolean;
{Porceso que crea un nodo con los datos contenidos en Dato}
 
Begin

	new(Pos);
	if Pos<>nulo then begin
		Pos^:=Dato;
		CrearNodo:= true
	end
	else CrearNodo:= false;

End;

{**********************************************************************}

PROCEDURE ListaVacia(VAR Lista:tLista);
{Esta funcion recive una lista de tipo tLista es decir un puntero a tdato y lo
pone apuntado a nil,
Precond: Ha de recibir una Lista sin contenido para evitar memoryLeak}	
 

Begin {ListaVacia}

	Lista:= NULO;

End;{ListaVacia}

{**********************************************************************}
 
FUNCTION esListaVacia(Lista:tLista):Boolean;
{Esta funcion recive una lista y devuelve true si esta vacia y false
si tiene contenido}


Begin {esListaVacia}

	esListaVacia:= Lista = nulo;

End; {esListaVacia}

{**********************************************************************}
 
Function Primera(Lista:tLista):tPos;
{Devuelve la primera posicion de la lista o nulo si esta vacia
Entrada: Lista de tipo tLista
Salidas: Posicion primera de tipo tPos}
 
Begin {Primera}

	Primera:= Lista;

End;{Primera}

{***********************************************************************}

Function Ultima(Lista:tLista):tPos;
{Devuelve la ultima posicion de la Lista o nulo si la lista esta vacia}
 
Begin
	
	if Lista = Nulo then Ultima:= nulo
	else begin
		while Lista^.Siguiente<> Nulo do
			Lista:=Lista^.Siguiente;
		Ultima:= Lista
	end;

End;


{**********************************************************************}
 
Function Siguiente(Lista:tLista; Pos:tPos):tPos;
{Devuelve la siguiente posicion a la posicion Pos, en caso de no haber
siguiente devuelve nulo
Entradas: Lista de tipo tLista, posicion de tipo tPos
Salidas: la Posicion siguiente a la posicion Pos de tipo tPos
PreCD: tPos es una posición válida en la lista.}
 
Begin

	Siguiente:= pos^.siguiente {Si no hay siguiente pos^.siguiente ya vale nulo, pues
								el nodo que esta al final siempre apunta a nulo}

End;

{**********************************************************************}
 
Function Anterior(Lista:tLista; Pos:tPos):tPos;
{Devuelve la posicion anterior a Pos en la lista Lista o nulo en caso de que
No haya anterior
Entradas: Lista, posicion.
Salidas: la posicion anterior de tipo tPos a la posicion Pos o nulo en caso de no haber anterior
PreCD: tPos es una posición válida en la lista.}


Begin

	if Pos = Lista then
		Anterior:= Nulo
	else begin
	
		Lista:= Lista^.siguiente;
		while Lista^.siguiente <> Pos do
			Lista:= Lista^.siguiente;
		Anterior:= Lista;
	
	end;
	

End;

{**********************************************************************}
 
Function InsertarDato(Dato:tDato; Pos:tPos;VAR Lista:tLista):Boolean;
{Funcion que inserta un dato en una posicion Pos, en caso de posicion nula se inserta al final.
Entradas: un Dato de tipo tDato ,Lista de tipo t Lista, y posicion donde insertar de tipo tPos
Salidas: la Lista modificada y true o false segun se haya insertado el dato o no
PreCD: tPos es una posición válida de la lista o bien una posición nula.}
 
 Var
	NuevaPos,TempPos:tPos; {Variable que apuntara al nuevo nodo creado}
	
Begin

	
	if CrearNodo(Dato,NuevaPos) then begin {then exterior}
		
		if esListaVacia(Lista) then begin
		
			Lista:= NuevaPos;
			Lista^.siguiente:=Nulo;
			InsertarDato:=true;
			
		end	
		else begin {else}
			
			if Pos = Nulo then begin {then anidado}
				
				TempPos:= Lista;
				while TempPos^.siguiente <> Nulo do 
					TempPos:= TempPos^.siguiente;
			
				TempPos^.siguiente:= NuevaPos;
				NuevaPos^.siguiente:=Nulo;
				
			end {then anidado}
			else begin {else anidado}
			
				{inserto una posicion mas alante de la que me piden}
				NuevaPos^.siguiente:= Pos^.siguiente;
				Pos^.siguiente:= NuevaPos;
				{Ahora cambio los datos de lo que inserte con los datos de donde pedian insertar y listo}
				NuevaPos^.nick:= Pos^.nick;
				NuevaPos^.numDenuncias:= Pos^.numDenuncias;
				Pos^.nick:= Dato.nick;
				Pos^.numDenuncias:= Dato.numDenuncias;
				
			end; {else anidado}
			InsertarDato:=true;
		end; {else}
	end {then exterior}
	else begin {else}
	
		writeln('Memoria LLena ha fallado la inserción');
		InsertarDato:= false;
	
	end; {else}

End;

{**********************************************************************}
 
PROCEDURE EliminarPosicion( Pos:tPos; Lista:tLista);
{Proceso que elimina el nodo señalado por Pos
Entrada: Posicion a eliminar tipo tPos, y la Lista
Salida: la Lista sin esa posición
PreCD: tPos es una posición válida en la lista.
PostCD: La posicion señalada por la posicion (Pos) recivida ahora esta ocupada por
la que era la siguiente posicion}

VAR
	tempPos: tPos;

Begin

	TempPos:= Pos^.siguiente;
	Pos^:= TempPos^;
	Dispose(TempPos);

End;

{**********************************************************************}

PROCEDURE ObtenerDato (Pos: tPos; Lista: tLista;VAR Nick: tNickUsuario;VAR Denuncias:tNumDenuncias);
{Obtiene los datos asociados al elemento que ocupa la posicion Pos
Entradas: Una Posicion (Pos), la Lista, una variable Nick y una variable Denuncias para 
* contener el nick y las denuncias.
Salidas: El nick y denuncias del usuario qeu ocupa la posición Pos.
PreCD: La posición tiene que ser válida.}

Begin

	Nick:= Pos^.nick;
	Denuncias:= Pos^.numDenuncias;

End;

{**********************************************************************}

Procedure ActualizarDato( Lista:tLista; Pos:tPos; ND:tNumDenuncias);

Begin

	Pos^.numDenuncias:= ND;

End;

{**********************************************************************}

FUNCTION BuscarDato (Nick :tNickUsuario; Lista:tLista):tPos;
{Funcion que devuelve la posicion de la lista de usuarios cullo nombre
coincida con Nick, si no se encuentra devolvera Nulo.
Entradas: Nick a buscar y Lista.
Salida: Poscion de la lista que contiene ese nick o nulo si no hay nadie en la lista con ese nick.}


Begin

If Lista<> Nulo then begin

	While (Lista^.siguiente <> Nulo) AND (Lista^.nick <> Nick)do
			Lista:= Lista^.siguiente;
	If Lista^.nick = nick then
		BuscarDato:= Lista
	else
		BuscarDato:= Nulo;
end
else BuscarDato:= Nulo; 

End;

{**********************************************************************}

BEGIN


END.
