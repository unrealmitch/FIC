PROGRAM Palabras(input,output);

Const 

    Separador=[';',',',' ','|','.'];
    Vocal=['a','e','i','o','u']
    
Type
    TFLetra=Array [0..125] Of Integer; 
    TPalabra=Array [0..256] Of String(25);
  
Var
    Palabra:TPalabra;
    PalabraAct:String(25);
    C:Char;
    NPalabra:Integer Value 0;
    Fin:Boolean Value False;
    NumPalabras:Integer Value 0;
    i,i2:Integer Value 0;
    Vocales:Integer Value 0;
Begin

Writeln('Escribe un mínimo de 20 palabras, pulsando enter cuando acabe');
Writeln('Posteriormente podrá ver información acerca de las palabras escritas:');

While NOT EOLN DO BEGIN
    Read(C);
    
    If C IN Separador Then 
        Npalabra:=Npalabra + 1  
    Else
    Palabra[NPalabra]:= Palabra[Npalabra] + C;

END;

Writeln('Palabras Escritas : ');

For i:= 0 To Npalabra Do 
    Writeln(NumPalabras, ' -> ' , Palabra[NumPalabras]);

Writeln('Vocales que contiene cada palabra');
For i:= 0 To Npalabra Do Begin
    Vocales:=0
    PalabraAct:=Palabra[i];
    
    For i2:= 0 To Length(PalabraAct) Do
        If (PalabraAct[i2]) IN Vocal Then Vocales:=Vocales + 1;
    
    Writeln(i, ' : ', PalabraAct, ' : ', Vocales, ' Vocales.');
End;

END.
