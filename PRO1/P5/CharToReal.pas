program CharToReal(Input,Output);

Var 
	CharN: Char;
	Cadena: Real Value 0;
	NCAR: Integer Value 0;
	Dec:Integer Value 0;

BEGIN
	
	Repeat
		Read(CharN);
		NCAR:=NCAR+1;
		If CharN <> '.' Then
		Cadena:=(((Cadena)*10) + (ORD(CHARN) - ORD('0')))
		Else
		Dec:=NCAR;
	Until CharN = '*';
	
Cadena:=(Cadena);

Writeln(Cadena);
		
	
END.
