Program MenuNum(input,output);
	Var
	num,num2:integer value 0;
	opcion:char;
	fin:boolean value false;
	
Function CifrasEntero(Entero:Integer):Integer;
	Begin
		Var ncif:integer value 0;
		Repeat
		ncif:=ncif+1;
		Until (entero Div (10**(ncif))) < 1;
	CifrasEntero:=ncif;
	End;
	
Function CifraI(Entero,i:Integer):Integer;
	Begin
	i:=(Entero MOD(10 POW i)) DIV (10 POW (i-1));
	CifraI:=i;
	End;
	
Procedure Sum(Entero:integer);
	Var
	Contador,
	Suma:integer value 0;
	
	Begin
	
	For Contador:= 1 to CifrasEntero(Entero) Do
		suma:= suma + CifraI(Entero,Contador);
	Writeln('La suma total del numero ', Entero , ' es de: ', suma);
	
	End;
	
Procedure EspejoNum(Entero:Integer);
	
	Var
	Contador,
	Suma:Integer Value 0;
	
	Begin
	
	For Contador:= 1 to CifrasEntero(Entero) Do
	Suma:= (Suma*10) + CifraI(Entero,(CifrasEntero(Entero) - Contador);
	
	Writeln('El número espejo de ', Entero, ' es: ', Suma);
	
	End;
	

Procedure NumPrimo(Entero:Integer);

	Var
	Contador:Integer value 0;
	Primo:Boolean Value True;
	
	Begin
	
	If Entero > 2 Then
	Begin
		For Contador:= Entero DownTo 2
		If (Entero Mod Contador)=0 then primo:=false;
	End;
	
	If primo then
	writeln('El número ', Entero, ' es primo.')
	Else
	writeln('El número ', Entero, ' no es primo.');
	
	End;
	
Function MCD (Num1, Num2: Integer):Integer;
	Begin
	
	if (Num1 mod Num2)=0 then
		begin
		MCD:=Num2;
		end;
    Else
    MCD:=MCD(Num2,Num1 mod Num2);
	End;

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
	
		For Contador:= 0 to 10 Do
		Write((Entero*Contador):8);
		End;
		
	Procedure Tdiv(Entero:Integer);
		Var Contador:Integer Value 0;
		
		Begin
		
		
		For Contador:= 0 to 10 Do
		Write(Contador:8);
		
		Writeln('');
	
		For Contador:= 0 to 10 Do
		Write((Entero Div Contador):8);
		
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
		CifrasEntero(num);
	END;
	  
	'2':Begin
		Writeln('Mirar la cifra Iesima de un número entero.');
		Write('Escriba un nº entero: ');
		Readln(num);
		Write('Escriba la cifra que desea mirar (Valor de I).');
		Readln(num2);
		CifraI(num,num2);
	END;	
		
	'3':Begin
		Writeln('Sumar las cifras separadas de un nº entero.');
		Write('Escriba un nº entero: ');
		Readln(num);
		Sum(num);
	END;
	  
	'4':Begin
		Writeln('Calcula la Imagen Espejo de un nº entero.');
		Write('Escriba un nº entero: ');
		Readln(num);
		EspejoNum(num);
	END;
	
	'5':Begin
		Writeln('Comprobar si un nº entero es primo o no.');
		Write('Escriba un nº entero: ');
		Readln(num);
		NumPrimo(num);
	END;
	
	'6':Begin
		Writeln('Máximo Común Divisor de 2 enteros.');
		Write('Escriba un nº entero: ');
		Readln(num);
		Write('Escriba un segundo nº entero: ');
		Readln(num2);
		MCD(num,num2);
	END;
	
	'7':Begin
		Writeln('Tablas de Sumar | Restar | Multiplicar | Dividir| de un entero.');
		Write('Escriba un nº entero: ');
		Tablas(num);
		END;
	END.
Until fin=true;

END;
