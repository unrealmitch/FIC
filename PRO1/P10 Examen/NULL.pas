Program GestionTienda(input,output);

{
Autor:Miguel Mosquera Ṕerez
Programa: Gestión de Precios
Versión: 0.1
Fecha: 22/12/2010

Descripción: Programa que gestiona los precios de los artículos de una
tienda, permitiendo modificar estes y también da la opción de obtener
el precio del artículo más caro.
}

Const
    Cnart=5;    {Constante que define el nº max de artículos}
    
    Opciones=['s','S','i','I','m','M'];
    Barra='*****************************';
    
Type
    Tartic=Record
        NombreA:String(20) Value 'turrón';
        Caducidad:String(10) Value '31/12/2011';
        PrecioA:Real Value 4.85;
        End;
    Tarticulos:Array[1..Cnart] OF Tartic;

Var
    Articulos:Tactiulos;
    Salir:Boolean Value False;
    
Function NumReal:Real; {Funcion que pide al usuario un numero real y 
                        solo devuelve dicho valor cuando sea > que 0}
    Var realintroducido:real;

    Begin
        Repeat
            Write('Introduzca un precio válido: ');
            Readln(realintroducido);
        Until realintroducido > 0;
        
        NumReal:=realintroducido
    End;
    
Function Menu:Char; {Funcion que muestra un menu, devolviendo la 
                    opcion elejida por el usuario}

    Var opcion:char;
    
    Begin
        Writeln;
        Writeln(Barra);
        Writeln;
        Writeln('Menu Gestión Tienda');
        Writeln;
        Writeln('[S]alir del programa.');
        Writeln('[I[ntroducir precios de los artículos.');
        Writeln('[M]ostrar precio del artículo más caro.');
        Writeln;
        
        Repeat
            Write('Escoja una opción válida: ');
            Readln(opcion);
        Until opcion In Opciones;
        
        Writeln(Barra);
        Writeln;
        Menu:=opcion
    End;
    
Procedure InsertarPrecio; {Proceso que permite introducir un nuevo
                          precio a todos los artículos}
                          
    Var i:integer value 0;
    
    Begin
        Writeln('Introduce los precios de los artículos.');
        
        For i:= 1 to Cnart Do Begin
            With Articulos[i] Do Begin
                Writeln('Artículo Nº ', i:0 , ' : ', NombreA);
                PrecioA:=NumReal
            End
        End;
        
        Writeln('Precios Introducidos');
   End;
   
Function PrecioMax:Real; {Devuelve únicamente el precío mas caro de la
                          tienda}
    Var 
        max:real value 0;
        i:integer value 0;
        
    Begin
        For i:=1 to Cnart Do Begin
            With Articulos[i] Do Begin
                If PrecioA > max then max:=PrecioA
            End
        End;
        
        PrecioMax:=max;
    End;
    
Begin

writeln('Gestion de Artículos de una Tienda');

Repeat
    Case Menu Of
        's','S':Salir:=True;
        'I','i':Insertarprecio;
        'M','m':Writeln('El precio máximo es de: ', PrecioMax:0:2, '€.');
    End;
Until Salir=True;
End.
