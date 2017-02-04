Program Billetes (input, output);

{Pasar una cantidad de dinero a billetes}

Var b1 : integer value 500;
        b2 : integer value 200;
        b3 : integer value 100;
        b4 : integer value 50;
        b5 : integer value 20;
        b6 : integer value 10;
        b7 : integer value 5;
Var   bb1 : integer value 0;
        bb2 : integer value 0;
        bb3 : integer value 0;
        bb4 : integer value 0;
        bb5 : integer value 0;
        bb6 : integer value 0;
        bb7 : integer value 0;
        cantidad : integer value 0;


Begin
Write('Escriba cantidad: ');
Readln(cantidad);

bb1:= cantidad div b1;
cantidad:= cantidad - (bb1 * b1);

bb2:= cantidad div b2;
cantidad:= cantidad - (bb2 * b2);

bb3:= cantidad div b3;
cantidad:= cantidad - (bb3 * b3);

bb4:= cantidad div b4;
cantidad:= cantidad - (bb4 * b4);

bb5:= cantidad div b5;
cantidad:= cantidad - (bb5* b5);

bb6:= cantidad div b6;
cantidad:= cantidad - (bb6* b6);

bb7:= cantidad div b7;
cantidad:= cantidad - (bb7* b7);

Writeln('Billetes de 500: ',bb1);
Writeln('Billetes de 200: ',bb2);
Writeln('Billetes de 100: ',bb3);
Writeln('Billetes de 50: ',bb4);
Writeln('Billetes de 20: ',bb5);
Writeln('Billetes de 10: ',bb6);
Writeln('Billetes de 5: ',bb7);
Writeln('En Monedas: ', cantidad);

END.



