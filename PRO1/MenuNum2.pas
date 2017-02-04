Program MenuNum(input,output);
	Var
	num,num2:integer value 0;
	opcion:char;
	fin:boolean value false;

Procedure Pausa;
	Begin
	Writeln('Pulsa Enter para continuar.');
	Readln
	End;

Function CifrasEntero(Entero:Integer):Integer;
	Var ncif:integer value 0;

	Begin
		Repeat
		ncif:=ncif+1;
		Until (entero / (10**(ncif))) < 1;
	CifrasEntero:=ncif;
	End;
	
Function CifraI(Entero,i:integer):Integer;
	Begin
	i:=(Entero DIV(10 POW (CifrasEntero(Entero)-i))) - 
(Entero DIV(10 POW (CifrasEntero(Entero) - (i - 1))))*10;

	CifraI:=i;
	End;
	
Procedure Sum(Entero:integer);
	Var
	Contador,
	suma:integer value 0;

	Begin
	
	For Contador:= 1 to CifrasEntero(Entero) Do
		suma:= suma + CifraI(Entero,Contador);
	Writeln('La suma total del numero ', Entero:0 , ' es de: ', suma:0);
	
	End;
	
Procedure EspejoNum(Entero:Integer);
	
	Var
	Contador,
	suma:Integer Value 0;
	
	Begin
	
	For Contador:= CifrasEntero(Entero) DOWNTO 1 Do
	suma:= suma*10 + CifraI(Entero,Contador);

	Writeln('El número espejo de ', Entero:0, ' es: ', Suma:0);
	
	End;
	

Procedure NumPrimo(Entero:Integer);

	Var
	Contador:Integer value 0;
	Primo:Boolean Value True;
	
	Begin

	If Entero > 2 Then
	Begin
		For Contador:= (Entero-1) DOWNTO 2 DO
		If (Entero Mod Contador)=0 then primo:=false;
	End;
	
	If primo then
	writeln('El número ', Entero:0, ' es primo.')
	Else
	writeln('El número ', Entero:0, ' no es primo.');
	
	End;
	
	Function MCD (x1,x2:integer):integer;
	
	BEGIN
		If x2=0 then
		MCD:=x1
		Else
		MCD:=MCD(x2, x1 mod x2)
end;

Procedure Tablas (Entero:integer);
	
	Procedure Tsumar(Var Entero:integer);
		Var Contador:Integer Value 0;
		
		Begin
		
		For Contador:= 0 to 10 Do
		Write(Contador:8);
		
		Writeln('');
	
		For Contador:= 0 to 10 Do
		Write((Entero+Contador):8);
		
		End;

	Procedure Tresta (Entero:Integer);
		Var Contador:Integer Value 0;
		
				Begin
			
		
		For Contador:= 0 to 10 Do
		Write(Contador:8);
		
		Writeln('');
	
		For Contador:= 0 to 10 Do
		Write((Entero-Contador):8);
		
		End;
		
	Procedure Tmult (Entero:Integer);
		Var Contador:Integer Value 0;
		
		Begin
		
		For Contador:= 0 to 10 Do
		Write(Contador:8);
		
		Writeln('');
	
		Write(Entero:8);

		For Contador:= 1 to 10 Do
		Write((Entero*Contador):8);
		End;
		
	Procedure Tdiv(Entero:Integer);
		Var Contador:Integer Value 0;
		
		Begin
		
		For Contador:= 0 to 10 Do
		Write(Contador:8);
		
		Writeln('');
		
		Write(Entero:8);
	
		For Contador:= 1 to 10 Do
		Write((Entero DIV Contador):8);
		
		End;
	
Begin
	Writeln('Tabla de Sumar:');
	Tsumar(Entero);
	Writeln('');
	Writeln('Tabla de Restar:');
	Tresta(Entero);
	Writeln('');
	Writeln('Tabla de Multiplicar:');
	Tmult(Entero);
	Writeln('');
	Writeln('Tabla de División');
	Tdiv(Entero);
	Writeln('');

End;

{FIN DE DECLARACIÓN DE VARIABLES, PROCESOS}

Begin

Repeat
	Writeln('Menu Del Programa:');
	Writeln('');
	Writeln('(1): Número de Cifras de Un Entero.');
	Writeln('(2): Cifra Iesima de un Entero.');
	Writeln('(3): Sumar las Cifras de un Entero');
	Writeln('(4): Cifra Espejo de un Entero.');
	Writeln('(5): Comprobar si un Entero es primo.');
	Writeln('(6): Máximo Comun Divisor de dos enteros.');
	Writeln('(7): Tablas de Sumar | Restar | Multiplicar | Dividir| de un entero.');
	Writeln('(0): Salir del programa.');
	Writeln('');
	
	Repeat
	Write('Escoja Una Opción Válida (0->7):');
	Readln(opcion);
	Until opcion in['0','1','2','3','4','5','6','7'];
	
	Case opcion Of
	
	'0':fin:=true;
	
	'1':Begin
		Writeln('Calcular el nº de cifras de un entero.');
		Write('Escriba un nº entero: ');
		Readln(num);
		Writeln('Nº de cifras: ',CifrasEntero(num):0);
		Pausa
	END;
	  
	'2':Begin
		Writeln('Mirar la cifra Iesima de un número entero.');
		Write('Escriba un nº entero: ');
		Readln(num);
		Write('Escriba la cifra que desea mirar (Valor de I).');
		Readln(num2);
		Writeln('La cifra ', num2:0 , ' del nº ' , num:0, ' es ',CifraI(num,num2):0);
		Pausa
	END;	
		
	'3':Begin
		Writeln('Sumar las cifras separadas de un nº entero.');
		Write('Escriba un nº entero: ');
		Readln(num);
		Sum(num);
		Pausa
	END;
	  
	'4':Begin
		Writeln('Calcula la Imagen Espejo de un nº entero.');
		Write('Escriba un nº entero: ');
		Readln(num);
		EspejoNum(num);
		Pausa
	END;
	
	'5':Begin
		Writeln('Comprobar si un nº entero es primo o no.');
		Write('Escriba un nº entero: ');
		Readln(num);
		NumPrimo(num);
		Pausa
	END;
	
	'6':Begin
		Writeln('Máximo Común Divisor de 2 enteros.');
		Write('Escriba un nº entero: ');
		Readln(num);
		Write('Escriba un segundo nº entero: ');
		Readln(num2);
		Writeln('El Maximo Comun Divisor es: ', (MCD(num,num2)):0);
		Pausa
		
	END;
	
	'7':Begin
		Writeln('Tablas de Sumar | Restar | Multiplicar | Dividir| de un entero.');
		Write('Escriba un nº entero: ');
		Readln(num);
		Tablas(num);
		Pausa
	    END;
		
	END;
Until fin=true;

END.
