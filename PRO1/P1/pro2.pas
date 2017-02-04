PROGRAM HelloWord(input, output); 
Var num1:
	integer;
Var num2:
	integer;
BEGIN
  {Para compilar el programa tecleamos desde el terminal:
  gpc --extended-pascal #file}
  writeln('Escriba el primer número a sumar');
  readln(num1); {Imprimir en pantalla el mensaje Hello Word}
  writeln('Escriba el segundo número a sumar');
  readln(num2); {Imprimir en pantalla el mensaje Hello Word}
  writeln(num1,' & ',num2,(num1 + num2));
END.
