Program Fumigar(input,output);
{Programa que te permite saber si se puede fumigar en condicion de la velocidad del viento, la humedad y la temperatura}

Var
	Humedad,
	Velocidad,
	Temperatura:integer;
	
	Humed,
	Veloc,
	Temp:boolean;
	Resultado:boolean;
	
Begin

Write('Escribe el valor del porcentaje de humedad: ');
Readln(Humedad);
Write('Escribe el valor de la velocidad en Km/h: ');
Readln(Velocidad);
Write('Escribe el valor de la temperatura en ºC: ');
Readln(Temperatura);

If Velocidad=16 then
	Veloc:=true
else
	Veloc:=false;
	
If Temperatura>=21 then 
	Temp:=true
else
	Temp:=false;
	
If Humedad>=15 then
	If Humedad<=35 then
		Humed:=true
	else
		Humed:=false
else
	Humed:=false;

Resultado:=(Veloc and Temp and Humed);

If Resultado then
	writeln('Si se puede fumigar')
else
	writeln('No se puede fumigar');

End.
	
