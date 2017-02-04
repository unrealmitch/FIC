Unit AG;

Interface

Const 
	MaxUsers=100;
	Nulo=0;

Type
	tNickUsuario=string[9];
	tNumDenuncias=0..MaxInt;
	tDato=Record
		Nick:tNickUsuario;
		Ndenuncias:tNumDenuncias;
	End;
	
	tIndice=1..MaxUsers;
	tPos=Nulo..MaxUsers;
	
	tListaUsuarios=ARRAY[tIndice] OF tDato;
	
	tLista=Record
		lUsuarios:tListaUsuarios;
		Fin:tPos;
	End;
	
Function esListaVacia(CONST Lista:tLista):Boolean;
Function Ultima(Const Lista:tLista):tPos;
Function Anterior(Const Lista:tLista; Pos:tPos):tPos;
Procedure EliminarPosicion (Pos:tPos;Var Lista:tLista);
Procedure ActualizarDato(Var Lista:tLista; Pos:tPos; ND:tNumDenuncias);

IMPLEMENTATION

{**********************************************************************}
		Function esListaVacia(CONST Lista:tLista):Boolean;
		{Funcion que devuelve, en un valor de tipo boleano, si la lista
		esta vacia o no.}
			
			Begin
				If Lista.Fin>0 then
					esListaVacia:=False
				Else
					esListaVacia:=True
			End;
{**********************************************************************}

{**********************************************************************}
		Function Ultima(Const Lista:tLista):tPos;
		{Funcion que devuelve la posicion del último elemento de la
		lista.}
		
		Begin
			If Lista.Fin=Nulo Then
				Ultima:=Nulo
			Else
				Ultima:=Lista.Fin
		End;
{**********************************************************************}

{**********************************************************************}		
		Function Anterior(Const Lista:tLista; Pos:tPos):tPos;
		{Funcion que devuelve la posición anterior de otra dada por el 
		usuario, siempre que la primera válida, y si no, devolverá valor
		nulo.}
		
		Begin
			If (Pos=Nulo) or (Pos=1) Then {El caso del Pos=1, sería
			innecesario ya que ese caso es automático.}
			
				Anterior:=Nulo
			Else
				Anterior:=Pos - 1
		End;
{**********************************************************************}

{**********************************************************************}
		Procedure EliminarPosicion (Pos:tPos;Var Lista:tLista);
		{Este procedimiento elimina un elemento de la lista, dando la 
		posicion de este, siempre que sea válida.}
		
			Var i:tIndice;

			
			Begin 
				If Lista.Fin<>Nulo Then Begin
					Lista.Fin:=(Lista.Fin-1);
					For i:=Pos to Lista.Fin Do
						Lista.lUsuarios[i]:=Lista.lUsuarios[i+1]
				End;
			End;
{**********************************************************************}

{**********************************************************************}
		 Procedure ActualizarDato(Var Lista:tLista; Pos:tPos; ND:tNumDenuncias);
		 {Proceso que modifica el valor del número de denuncias de un
		 usuario dando la posicion en la lista de este.}
		  
			Begin
				If Lista.Fin<>Nulo Then
					Lista.lUsuarios[Pos].Ndenuncias:= ND;
			End;
{**********************************************************************}


BEGIN
END.
