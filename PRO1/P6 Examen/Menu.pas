Program Menu(input,output);
Var
    Eleccion,
    n1, n2, n3, x,
    nmax, nmin, nnum, nact, ntot:integer value 0;
    media:real value 0;
    Salir, fin:boolean value false;

Begin
writeln('Programa con un menu que realiza varias funciones');
Repeat
    Writeln('Opciones del menu:');
    Writeln('(1):Tabla de nº, cuadrados y raices');
    Writeln('(2):Máximo, mínimo y media de una serie');
    Writeln('(3):Salir del programa');
    writeln('');
    
    Repeat
        Write('Escoja una opción válida: ');
        Readln(Eleccion);
    Until (Eleccion=1) or (Eleccion=2) or (Eleccion=3);
    
    Case Eleccion OF
        1:Begin
            Writeln('Escriba dos números enteros psitivos.');
            
            Repeat
                Write('Número uno: ');
                Readln(n1);
                Write('Número dos: ');
                Readln(n2);
            Until (n1>0) and (n2>0);
            
            If (n1>n2) then 
            Begin
                n3:=n1; 
                n1:=n2; 
                n2:=n3;
            end;
            
            For x:= n1 to n2 Do 
            Begin
                Write(x:5);
                Write('  ');
            End;
            
             Writeln('');
            
            For x:= n1 to n2 Do Begin
                Write((x*x):5);
                Write('  ');
            End;
            
            Writeln('');
            
            For x:= n1 to n2 Do Begin
                Write((sqrt(x)):5:0);
                Write('  ');
            End; 
            
            Writeln('');
            
         END;
         
        2:Begin
            Writeln('Escriba una serie de números');
            Writeln('Esta serie acabará al escribir un multiplo de 10');
            
            Repeat
                nnum:=nnum+1;
                Write('Nuevo número: ');
                Readln(nact);
                If nact > nmax then nmax:=nact;
                If nmin = 0 then nmin:= nact;
                If nact < nmin then nmin:= nact;
                ntot:=ntot+nact;
                If (nact Mod 10) = 0 then fin:= true;
            Until fin=true;
            
            Writeln('');           
            Writeln('El número máximo de la serie es: ', nmax:0);
            Writeln('El número mínimo de la serie es: ', nmin:0);
            media:=(ntot/nnum);
            Writeln('La media de la serie es: ', media:0:0);
            Writeln('');
         END;
         
        3:Salir:=true;
     End;
Until Salir=true;
END.                
                
        
