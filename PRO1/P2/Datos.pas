Program Persona (input, output);

{Programa dedicado a obtener ciertos datos de una persona, para luego
mostrarlos en pantalla}

Var Nombre : string(20);
    Edad : integer;
	Altura : real;
Begin


	Write('Escriba su nombre:');
Readln(Nombre);
Write('Escriba su edad:');
Readln(Edad);

Write('Escriba su altura en cm:');
Readln(Altura);

Altura:=((Altura / 100000));

Write(Nombre + ' con ');
Write(Edad);
Write( ' años ');
Write(' mide un total de ');
Write(Altura:5);
Write(' km.');

END.
