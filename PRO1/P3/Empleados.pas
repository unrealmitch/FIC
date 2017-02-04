Program Empleados(input,output);

Var
    Numero,
    Horas,
    Tarifa,
    Salario: real value 0;
    
Begin
    Write('Escribe el nº de empleado: ');
    Readln(Numero);
    Write('Escribe el nº de horas trabajadas: ');
    Readln(Horas);
    Write('Escriba la tarifa del empleado: ');
    Readln(Tarifa);
    
    If (horas<=40) then 
        Salario:=Tarifa*Horas
    else
        Begin
            Salario:=Tarifa*40;
            Horas:=Horas-40;
            Tarifa:=1.5 * Tarifa;
            Salario:=Salario+(Horas*Tarifa);
        End;
        
   write('El empleado nº ', Numero:5:0, ' tiene un salario de ', Salario:5:2, ' €.');
END.
