Program Triangular(input,output);

Var
	Z,X,Y,K: integer;
    
Begin

Write('Escriba el nº de lineas del triangulo: ');
Readln(Z);
For K:= 1 to Z Do Write(K:4);

writeln('');

For X:= 1 to Z Do Begin
	For Y:= 1 to X Do write(x*y:4);
writeln('');
End;
End.
		

