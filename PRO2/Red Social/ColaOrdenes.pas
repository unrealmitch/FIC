Unit ColaOrdenes;
{TÍTULO: Prácticas de PROGRAMACION II<br />SUBTÍTULO: Practica 3
AUTOR 1: Gabriel Míguez Míguez LOGIN 1: gabriel.miguez
AUTOR 2: Miguel Mosquera Pérez LOGIN 2: miguel.mosquera.perez
GRUPO: 3.2
FECHA: 13/03/2011
}

Interface

CONST
	NULOC = nil; {constante que indica un valor no valido de la cola, o 
					que no hay posicion.}

TYPE
	tOp= char;					{Tipo de operacion}
	tNickUsuario= string[9];	{tipo nombre de usuario}
	tPosC= ^tNodo;				{Tipo posicion, (nodo en la cola)}
	tCola= Record				
	
		Primero: tPosC;			{puntero externo a la cola que apunta al primer elemento}
		Ultimo: tPosC;			{puntero extermo que apunta al último elemento de la cola}	
		
	end;
	
	tInfoC = Record				{El tipo de cada nodo de la cola}
	
		Op: tOp;
		User1: tNickUsuario;
		User2: tNickUsuario;
	
	end;
	
	tNodo = Record
	
		InfoC: tInfoC;			{Campo que contiene los datos de la instruccion a realizar}
		siguiente: tPosC;		{Puntero que apunta al siguiente elemento}
	
	end;
	
	
	Procedure ColaVacia(VAR Cola: tCola);
	Function EsColaVacia(Cola: tCola): Boolean;
	Function InsertarDatoCola (VAR Cola: tCola; Dato: tInfoC):Boolean;
	Function FrenteCola (Cola: tCola): tInfoC;
	Procedure EliminarCola (VAR Cola: tCola);
	
Implementation

	Procedure ColaVacia(VAR Cola: tCola);
	{Funcion que inicia una cola
	* Entradas: Una Cola.
	* Salidas: Una Cola inicializada.
	* PreC: La Cola no tiene elementos.}
	
	Begin
	
		Cola.Primero := NULOC;
		Cola.Ultimo := NULOc;
	
	End;
	
{**********************************************************************}
 
	Function EsColaVacia(Cola: tCola): Boolean;
	{Funcion que indica si una cola esta vacia o no
	* Entradas: Una Cola.
	* Salidas: True si la cola esta vacia o false en caso contrario.}
	
	Begin
	
		EsColaVacia:= (Cola.primero = NULOC);
	
	End;

{**********************************************************************}
 
	Function InsertarDatoCola (VAR Cola: tCola; Dato: tInfoC):Boolean;
	{Funcion que inserta un dato y devuelve true solo si la insercion a sido correcta
	* Entradas: Una Cola y un dato a insertar
	* Salidas: La cola con el dato insertado (Siempre en ultima posicion) }
	
	Var
		NuevoNodo: tposC;
		
	{******************************************************************}
	
		Function CrearNodo (Dato: tInfoC): tPosC;
		{Funcion que crea un nodo con el campo InfoC igual al Dato recibido
		* Entradas: un Dato de tipo InfoC
		* Salidas: Un puntero que apunta a un nodo que contiene en el campo InfoC el contenidio del dato recibido
					y el campo siguiente inicializado a NULOC}
		
		Begin
		
			new(CrearNodo);
			CrearNodo^.InfoC := Dato;
			CrearNodo^.Siguiente:= NULOC;
		
		End;
	
	{******************************************************************}
	
	Begin
	
		NuevoNodo:= CrearNodo(Dato);					{creo un nodo que contenga los datos a insertar
														hay que tener en cuenta que el campo siguiente ya esta a NULOC}
														 
		if NuevoNodo <> NULOC then begin
														
			With Cola Do begin
				if esColaVacia(Cola) then
					Primero:= NuevoNodo
				else
					Ultimo^.siguiente:= NuevoNodo;
				ultimo:= NuevoNodo;
			
			end;
			InsertarDatoCola:= true;
			
		end
		else
			InsertarDatoCola:= false;
	
	End;

{**********************************************************************}

	Function FrenteCola (Cola: tCola): tInfoC;
	{Funcion que devuelve el campo InfoC, que contiene la informacion de la ioperacion
	a realizar, del primer elemento de la cola.
	* Entradas: Una Cola, tCola.
	* Salidas: Un dato de tipo tInfoC, que corresponde al campo InfoC del primer
				elemento de la cola.
	* PreCD: la cola no está vacía.}
	
	Begin
	
		FrenteCola:= Cola.primero^.InfoC;
	
	End;

{**********************************************************************}
 
	Procedure EliminarCola (VAR Cola: tCola);
	{Elimina un elemento que este en el frente de la cola
	* Entradas: Una cola.
	* Salidas: La Cola de entrada sin el primer elemento
	* PreCD: la cola no está vacía.}
	
	Var
		TempPos: tPosC; {Variable que se usara para apuntar al primer elemento de la cola
						para luego borrarlo}
	
	Begin
	
		with cola do begin
		
			TempPos:= Cola.Primero;
			primero:= primero^.siguiente;
			if primero = NULOC then
				Ultimo:= NULOC;
			Dispose(TempPos)
		
		end
	
	End;
	

BEGIN




END.
	
