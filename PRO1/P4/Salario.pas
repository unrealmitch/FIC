{
    Autor:Miguel Mosquera
    Versión:0.1
    Programa: Salario
    Programa en pascal que muestre el salario de un hombre que 
    por cada dia cobra 15 euros y necesita mas de 15 dias al mes, por cada
    dia extra cobrará un 15% mas de lo que cobra al dia. El programa 
    muestra el total de dias trabajados, considerar que la retencion del 
    irpf es de un 17% y de la seguridad social de un 5%}
    
Program Salario(input,output);

Const
    precioh=15;
    extra=1.15;
    IPRF=0.17;
    SS=0.05;
Var
    diastrabajados,
    diasextra,
    salario,
    salarioextra,
    salariototal,
    salariobruto,
    retencion:real value 0;
Begin 
    Write('Escribe el nº de dias trabajados: ');
    Readln(diastrabajados);
    If diastrabajados>15 then diasextra:=diastrabajados-15;
    salario:=(Diastrabajados-diasextra)*precioh;
    salarioextra:=diasextra*(precioh*extra);
    salariototal:=salario+salarioextra;
    retencion:=(salariototal*IPRF)+(salariototal*SS);
    salariobruto:=salariototal-retencion;
    
    Writeln('Total de días trabajados: ',diastrabajados:2);
    If diastrabajados<15 then writeln('No se ha trabajado lo suficiente');
    Writeln('Total de días extra: ',diasextra:2);
    Writeln('Total de días trabajados: ',diastrabajados:2);
    Writeln('Salario de 15 dias: ',salario);
    Writeln('Salario extra: ',salarioextra,' €');
    Writeln('Salario total: ',salariototal,' €');
    Writeln('Rentencion: ',retencion,' €');
    Writeln('Salario bruto: ',salariobruto,' €');
END.
    
