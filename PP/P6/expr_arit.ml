(*

Practica:   6
Asignatura: Paradigmas de Programacion
Fecha:      12/2014
Autor:      Miguel Mosquera Pérez
Correo:     miguel.mosquera.perez@udc.es
Grupo:      4.2

*)

open Diccionario;;
open Libreria;;

type expresion_aritmetica =
     Constante of float
    | Variable of string
    | Suma of expresion_aritmetica * expresion_aritmetica
    | Resta of expresion_aritmetica * expresion_aritmetica
    | Multiplicacion of expresion_aritmetica * expresion_aritmetica
    | Division of expresion_aritmetica * expresion_aritmetica
    | Opuesto of expresion_aritmetica
    | Funcion of string * expresion_aritmetica;;


let rec evaluar_expresion d exp = match exp with
    Constante x -> x
    | Variable name -> consultar_valor d name
    | Suma(x,y) -> (evaluar_expresion d x) +. (evaluar_expresion d y) 
    | Resta(x,y) -> (evaluar_expresion d x) -. (evaluar_expresion d y) 
    | Multiplicacion(x,y) -> (evaluar_expresion d x) *. (evaluar_expresion d y) 
    | Division(x,y) -> (evaluar_expresion d x) /. (evaluar_expresion d y) 
    | Opuesto x -> 0.0 -. consultar_valor d "x" 
    | Funcion (func, expr) -> (Libreria.funcion func)(evaluar_expresion d expr);;