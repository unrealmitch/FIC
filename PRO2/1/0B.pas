program Practica_0B;

type
tRegistro = record
titulo: string;
unidades: integer;
end;
tPregistro = ^tRegistro;
var
p, q, r: tPRegistro;

Procedure Inicializar(p,q,r:tPRegistro);
Begin
	New(p);
	New(q);
	New(r);
End;

Procedure PedirDatos(Var x,y,z: tRegistro);
Begin
	Writeln('Registro 1');
	Write('Título: ');
	Readln(x.titulo);
	Write('Unidades: ');
	Readln(x.unidades);
	
	Writeln('Registro 2');
	Write('Título: ');
	Readln(y.titulo);
	Write('Unidades: ');
	Readln(y.unidades);
	
	Writeln('Registro 3');
	Write('Título: ');
	Readln(z.titulo);
	Write('Unidades: ');
	Readln(z.unidades)
End;

Procedure ConsultarDatos(x,y,z: tRegistro);
Begin
	Writeln('Registro 1');
	Write('Título: ');
	Writeln(x.titulo);
	Write('Unidades: ');
	Writeln(x.unidades);
	
	Writeln('Registro 2');
	Write('Título: ');
	Writeln(y.titulo);
	Write('Unidades: ');
	Readln(y.unidades);
	
	Writeln('Registro 3');
	Write('Título: ');
	Writeln(z.titulo);
	Write('Unidades: ');
	Writeln(z.unidades)
End;

Procedure Ordenar(Var p,q,r:tPRegistro);

	Procedure Cambio(Var a,b:tPRegistro);
	Var i:tPRegistro;
	Begin
		i:=a;
		a:=b;
		b:=i;
	End;
	
Begin
	If p^.titulo> q^.titulo then
		If p^.titulo > r^.titulo then
		cambio(p,r)
		Else
		cambio(p,q);
		
	If q^.titulo > r^.titulo then
		cambio(q,r);

End;

Function Menu:Char;
	Var Elec:Char;
	
	Begin
		Repeat
			Writeln('****MENU****');
			Writeln('[I]:Inicializar Registros.');
			Writeln('[A]:Pedir Datos.');
			Writeln('[B]:Visualizar Datos.');
			Writeln('[C]:Ordenar Datos.');
			Writeln('[S]:Salir.');
			Writeln;
			Write('Elija una opción válida: ');
			Readln(Elec);
		Until Elec In ['a','A','b','B','c','C','s','S','i','I'];
		
		Menu:=Elec;
	End;
		
BEGIN

Repeat
	Case Menu OF
		'i','I':Inicializar(p,q,r);
		'a','A':PedirDatos(p^,q^,r^);
		'b','B':ConsultarDatos(p^,q^,r^);
		'c','C':Ordenar(p,q,r)
	End;
Until Menu In ['s','S']
		
END.
