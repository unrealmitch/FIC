{
        Prestamo.pas
        
        Copyright 2010 Miguel Mosquera Pérez <miguel.mosquera.perez@vao04213.cc.fic.udc.es>
        
        Programa que te permite si se puede conceder un prestamo en
        funcion de los inresos, del valor de coactivos y de las deudas.

}


program Prestamo (input,output);


var 
	Ingresos,
	Vcoactivos,
	Deudas:integer;

BEGIN
	write('Escribe el valor de tus ingresos: ');
	readln(Ingresos);
	write('Escribe el valor de tus coactivos: ');
	readln(Vcoactivos);
	write('Escribe el valor de tus deudas: ');
	readln(Deudas);
	
If ((Ingresos>25000) or (Vcoactivos>100000)) and (deudas<50000) then
	write('Si se te puede conceder el crédito')
else
	write('No se te puede conceder el crédito');
	
END.
