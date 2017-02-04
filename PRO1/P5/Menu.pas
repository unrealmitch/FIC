Program Menu(input,output);

Var
	Fin: Boolean;
	Opcion: CHAR;
	
	{Variables Tipo Número}
	num1,
	num2,
	Y,
	X,
	Z:integer;
	
	{Variables Triangulo Multiplicador}
	Zi,Xi,Yi,Ki: integer;
	
    
Begin
Writeln('Menu: ');

Repeat

	Repeat
	Writeln('Elija una de las siguientes funciones: ');
	Writeln('1 (m): Triangulo multiplicador:');
	{Writeln('	Función que genera un tringualo al estilo tabla de multiplicar.');}
	Writeln('2 (c): Tipo de Número:');
	{Writeln('	Función que determina las numeros abundantes, perfectos o deficientes entre dos numeros.');}
	Writeln('3 (t,q,e): SALIR.');

	write('Elija una opción valida: ');
	readln(Opcion);
	Until (Opcion='1') or (Opcion='2') or (Opcion='3') or (Opcion='m') or 
	(Opcion='c') or (Opcion='t') or (Opcion='q') or (Opcion='e');
		  
Case Opcion Of
	'm','1':  Begin
			Write('Escriba el nº de lineas del triangulo: ');
			Readln(Zi);
			For Ki:= 1 to Zi Do Write(Ki:4);

			writeln('');

			For Xi:= 1 to Zi Do Begin
				For Yi:= 1 to Xi Do write(Xi*Yi:4);
				writeln('');
				End;
			End;
	
	'c','2':  Begin
	
	
			REPEAT
			write('Ìntroduzca dos números enteros positivos: ');
			Readln(num1);
			Readln(num2);
			UNTIL ((num1>0) and (num2>0));
	
			For X:= num1 to num2 Do Begin
				Y:=0;
				For Z:= 1 to (X-1) Do If (X MOD Z) = 0 THEN Y:=X+Z;
				If Y=Z then Writeln(X, ' es un nº perfecto')
				Else If (Y>X) then Writeln(X, ' es un nº abundante')
				Else writeln(X,' es un nº deficiente')
			End;
			End;
	
	't','q','e','3':Fin:=TRUE
End;

UNTIL Fin
End.
