Program Billetes (input, output);

{Pasar una cantidad de dinero a billetes}

Var	cantidad : integer;
	x:integer value 7;
Type
	bil = array(1..7) of integer;
	bil2 = array(1..7) of integer;

Begin
bil(1):=500;
bil(2):=200;
bil(3):=100;
bil(4):=50;
bil(5):=20;
bil(6):=10;
bil(7):=5;

	for := 1 to 7 do
	begin
	bil2(i):= cantidad div bil(i);
	cantidad:= cantidad - (bil(i) * bil2(i));
	writeln(bil2(i),' Billetes de ',bil(i);
	end;
end.
