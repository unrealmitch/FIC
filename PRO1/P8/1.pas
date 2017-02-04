program untitled(output,input);

Const
	N=10;
	
Type
	Alumnos=1..N;
	NotasA=ARRAY[Alumnos] of Real;

Var
	Notas:NotasA;
	Opcion:char;
	Fin:Boolean Value False;
	Valor1:Integer Value 1;
	Valor2:Real Value 0;
	
Procedure IntroducirNotas;
	Var i:Alumnos;
	BEGIN
		For i:=1 to N Do Begin
		Write('Alumno ', i, ': ');
		Readln(Notas[i]);
		End;
	End;

Procedure LeerNotas;
	Var i:Alumnos;
	
	Begin
		For i:=1 to N Do Begin
		Writeln('Alumno ', i, ': ' , (Notas(i));
		End;
		
	End;
	
Procedure LeerNotasN(Intervalo:Integer);
	Var 
	i:Alumnos;
	x:integer value 0;
	
	Begin
		For i:=1 to N Do Begin
		Writeln('Alumno ', i, ': ' , (Notas(i)):2:2);
		x:=x+1
		If x=> Intervalo Then Begin
			x:=0
			readln('');
		End;
		End;
	End;

Procedure ModificarNota(Nalum:integer , NNota:real);
	Begin
	Notas((Nalum)):=Nnota;
	End;

Procedure LeerNota(Nalum:integer);
	Begin
	Writeln('Alumno ', i, ': ' , (Notas(Nalum)):2:2);
	End;

Begin
	Repeat
	Writeln('Menu de Gestion de Notas de los alumnos:');
	Writeln('(1):Introducir todas las notas.')
	Writeln('(2):Leer todas las notas.');
	Writeln('(3):Leer todas las notas en intervalos x.');
	Writeln('(4):Modificar la nota de un alumno x.');
	Writeln('(5):Leer la nota de un alumno x.');
	Writeln('');
	Writeln('(0,Q): SALIR DEL PROGRAMA');
	Repeat
		Write('Escoja una opción válida: ');
		Readln(Opcion);
	Until Opcion in ('0','1','2','3','4','5','q','Q');
	
	Case Opcion OF
	
		'1':IntroducirNotas;
		'2':LeerNotas;
		'3':Begin
			Write('Escribe el intervalo en que se mostraran los alumnos');
			readln(valor1);
			LeerNotasN(valor1);
			End;
		'4':Begin
			Write('Escribe el Nº del alumno al que quieres cambiar la nota: ');
			Readln(Valor1);
			Write('Escribe la nueva nota para el alumno ', Valor1:0, ' :');
			Readln(Valor2);
			ModificarNota(Valor1,Valor2);
			End;
		'5':Begin
			Write('Escribe el Nº del alumno del que quieres ver la nota: ');
			readln(Valor1);
			LeerNota(Valor1);
			End;
'0','q','Q':Fin:=true;
	
	End;
Until Fin=true;

End.
