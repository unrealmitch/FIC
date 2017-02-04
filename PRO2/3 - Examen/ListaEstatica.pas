Unit ListaEstatica;
{TÍTULO: Prácticas de PROGRAMACION II<br />SUBTÍTULO: Practica 1
AUTOR 1: Gabriel Míguez Míguez LOGIN 1: gabriel.miguez
AUTOR 2: Miguel Mosquera Pérez LOGIN 2: miguel.mosquera.perez
GRUPO: 3.2
FECHA: 13/03/2011
}

Interface

Const

	MaxUsers = 100; {Numero maximo de usuarios}
	Nulo= 0; {Valor que se usa para indicar que una lista esta vacia,
				o para indicar que un elemento no esta en la lista}

Type
	
	tNickUsuario=string[9]; {Nombre de usuario}
	tNumDenuncias= 0..MaxInt; {Tipo del numero de denuncias}
	tDato = RECORD {Tipo que contendra los datos de un usuario concreto}
		
		nick:tNickUsuario;
		numDenuncias:tNumDenuncias;
	
	End;
	
	tIndice = 1..MaxUsers;
	tPos = Nulo..MaxUsers; {es el tipo indice mas el valor nulo para indicar las listas vacias}
	tListaUsuarios = ARRAY[tIndice] of tDato; {Array que contendra todos los usuarios}
	
	tLista = Record
	
		lUsuarios: tListaUsuarios;
		fin: tPos;
	
	End;
	
	PROCEDURE ListaVacia (VAR Lista : tLista);
	FUNCTION Primera (Const Lista: tLista):tPos;
	FUNCTION Siguiente (Const Lista:tLista; Pos:tPos):tPos;
	FUNCTION InsertarDato (Dato: tDato; Pos : tPos; Var Lista : tLista): Boolean;
	PROCEDURE ObtenerDato (Pos: tPos; Const Lista: tLista;VAR Nick: tNickUsuario;VAR Denuncias:tNumDenuncias);
	FUNCTION BuscarDato (Nick :tNickUsuario; Const Lista:tLista):tPos;
	Function esListaVacia(CONST Lista:tLista):Boolean;
	Function Ultima(Const Lista:tLista):tPos;
	Function Anterior(Const Lista:tLista; Pos:tPos):tPos;
	Procedure EliminarPosicion (Pos:tPos;Var Lista:tLista);
	Procedure ActualizarDato(Var Lista:tLista; Pos:tPos; ND:tNumDenuncias);
	
IMPLEMENTATION

{**********************************************************************}

	PROCEDURE ListaVacia (VAR Lista : tLista);
	{Funcion que inicializa una lista sin ningun elemento, en caso de pasar
	una lista no vacia se perdera todo el contenido}
	
	Begin {ListaVacia}
	
		Lista.fin:= Nulo; 
	
	End; {ListaVacia}
	
{**********************************************************************}
 
	FUNCTION Primera (Const Lista: tLista):tPos;
	{Esta funcion devuelve el valor nulo si la lista esta vacia, y si no
	devuelve el valor 1 que es donde se encuentra el primer elemnto del array}
	
	Begin {Primera}
	
		If Lista.Fin = Nulo then
			Primera:= Nulo
		else
			Primera:=1;
	
	End; {Primera}

{**********************************************************************}
 
	FUNCTION Siguiente (Const Lista:tLista; Pos:tPos):tPos;
	{Esta funcion recive una posicion valida y devulve la posicion siguiente,
	en caso de que no tenga siguiente devuelve Nulo}
	 
	Begin {Siguiente}
	
		If (Pos = Lista.Fin) then {En este caso no esisteira un siguiente}
			Siguiente:= Nulo
		else
			Siguiente := Pos + 1;
	
	End; {Siguiente}

{**********************************************************************}

	FUNCTION InsertarDato (Dato: tDato; Pos : tPos; Var Lista : tLista): Boolean;
	{Esta Funcion inserta un dato en una posicion dada, sin destruir la posicion existente
	,es decir corre todos los demas datos una posicion para alante.
	Se supone recivir una posicion correcta o nula, en caso de que la posicion
	sea correcta, se insertara ese elemento en dicha posicion, en caso de nulo,
	se insertara al final de la lista.
	Si se a producido la insercion devuelve true, si la insercion no se produce
	por lista llena devuelve false}
	
	VAR
		Cont:  integer;
	
	Begin {InsertarDato}
	
		
		If Lista.Fin <> MaxUsers then begin
		
			Lista.fin:= Lista.fin + 1; 
			If Pos = Nulo then 
				Lista.lUsuarios[Lista.fin]:= Dato
			
			else begin
		
				For Cont:= Lista.fin Downto Pos + 1 DO
					Lista.lUsuarios[cont]:= Lista.lUsuarios[cont -1];
				Lista.lUsuarios[Pos] := Dato;
			
			end;
			InsertarDato := True;	
		end {Then exterior}
		
		else begin 
			InsertarDato:= false;
			writeln('Lista llena.');
		end;
	
	End; {InsertarDato}

{**********************************************************************}

	PROCEDURE ObtenerDato (Pos: tPos; Const Lista: tLista;VAR Nick: tNickUsuario;VAR Denuncias:tNumDenuncias);
	{Este Proceso devuelve en el argumento Nick el Nick, y en el argumento
	Denuncias el numero de denuncias, de un usuario que ocupa la posicion Pos
	en la lista Lista.
	La Posicion ha de ser valida}
	
	Begin {ObtenerDato}
	
		Nick := Lista.lUsuarios[Pos].nick;
		Denuncias := Lista.lUsuarios[Pos].numDenuncias;
	
	End;{ObtenerDato}

{**********************************************************************}

	FUNCTION BuscarDato (Nick :tNickUsuario; Const Lista:tLista):tPos;
	{funcion que de vuelve la posicion del primer elemento encontrado, con 
	el campo nick igual al argumento Nick , En caso de no ser encontrado se devolvera Nulo}
	
	VAR
		cont: integer;
	
	Begin {BuscarDato}
	
		cont:= 1;
		while (Lista.lUsuarios[cont].Nick <> Nick) And (cont <= Lista.fin ) DO
			cont:=cont + 1;
		If cont <= Lista.fin then
			BuscarDato := cont
		else BuscarDato:= Nulo;
	
	End; {BuscarDato}
	
{**********************************************************************}
		Function esListaVacia (CONST Lista:tLista):Boolean;
		{Funcion que devuelve, en un valor de tipo boleano, si la lista
		esta vacia o no.}
			
			Begin {esListaVacia}
			
				If Lista.Fin>0 then
					esListaVacia:=False
				Else
					esListaVacia:=True
			End; {esListaVacia}

{**********************************************************************}

		Function Ultima (Const Lista:tLista):tPos;
		{Funcion que devuelve la posicion del último elemento de la
		lista o nulo en caso de que la lista este vacia.}
		
		Begin {Ultima}
		
			If Lista.Fin=Nulo Then
				Ultima:=Nulo
			Else
				Ultima:=Lista.Fin
		End; {Ultima}

{**********************************************************************}
		
		Function Anterior (Const Lista:tLista; Pos:tPos):tPos;
		{Funcion que devuelve la posición anterior de otra dada por el 
		usuario, siempre que la posición sea válida, y si no, devolverá valor
		nulo, si se trata del primer elemento también devolvera nnulo.}
		
		Begin {Anterior}
		
			If (Pos=Nulo) or (Pos=1) Then {El caso del Pos=1, sería
			innecesario ya que ese caso es automático.}
			
				Anterior:=Nulo
			Else
				Anterior:=Pos - 1
				
		End; {Anterior}
		
{**********************************************************************}


		Procedure EliminarPosicion (Pos:tPos;Var Lista:tLista);
		{Este procedimiento elimina un elemento de la lista, dando la 
		posicion de este, siempre que sea válida.
		 PostCD: La posicion señalada por la posicion (Pos) recivida ahora esta ocupada por
		la que era la siguiente posicio}
		
			Var i:tIndice;

			
			Begin {EliminarPosicion}
			
				If Lista.Fin<>Nulo Then Begin
					Lista.Fin:=(Lista.Fin-1);
					For i:=Pos to Lista.Fin Do
						Lista.lUsuarios[i]:=Lista.lUsuarios[i+1]
				End;
				
				
			End; {EliminarPosicion}

{**********************************************************************}

		 Procedure ActualizarDato(Var Lista:tLista; Pos:tPos; ND:tNumDenuncias);
		 {Proceso que modifica el valor del número de denuncias de un
		 usuario dando la posicion en la lista de este, esta ultima ha de ser valida.}
		  
			Begin {ActualizarDato}
			
				Lista.lUsuarios[Pos].numdenuncias:= ND;
					
			End; {ActualizarDato}
			
{**********************************************************************}

BEGIN


END.
