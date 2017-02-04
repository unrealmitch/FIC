{
        Triangulos.pas
        
        Copyright 2010 Miguel Mosquera Pérez <miguel.mosquera.perez@vao04213.cc.fic.udc.es>
        
		Programa que te dice con que tipo de triangulo estamos tratando
		en funcion de los parametros de este que introducimos.
		
}


program Triaungulos(input,output);


var
	lado1,
	lado2,
	lado3:real;
	
	equi,
	isos,
	escal:boolean value false;

BEGIN
	Write('Introduce el valor del primer lado: ');
	Readln(lado1);
	Write('Introduce el valor del segundo lado: ');
	Readln(lado2);
	Write('Introduce el valor del tercer lado: ');
	Readln(lado3);
	
	If ((lado1+lado2)>lado3) and ((lado1+lado3)>lado2) and ((lado2+lado3)>lado1) then
		Begin
			If (lado1=lado2) and (lado1=lado3) then
				Begin
					equi:=true;
					writeln('Triangulo equilatero');
				End
			Else
				If (lado1=lado2) or (lado2=lado3) then
					Begin
						isos:=true;
						writeln('Triangulo Isosceles');
					End
				Else
					Begin
						escal:=true;
						writeln('Triangulo Escaleno');
					End
		End
	Else
				write('No se trata de un triangulo');
End.
