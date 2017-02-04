program TipoNumero(input,output);

Var
	num1,
	num2,
	Y,
	X,
	Z:integer;
BEGIN
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

	
END.
