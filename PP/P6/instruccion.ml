(*

Practica:   6
Asignatura: Paradigmas de Programacion
Fecha:      12/2014
Autor:      Miguel Mosquera Pérez
Correo:     miguel.mosquera.perez@udc.es
Grupo:      4.2

*)

open Diccionario;;
open Expr_arit;;
open Libreria;;

type instruccion =
    Asignacion of string * expresion_aritmetica
    | Calculo of expresion_aritmetica
    | Comando of string;;

exception Fin_de_ejecucion;;

exception Comando_no_implementado of string;;


let ejecutar_instruccion d inst = match inst with
    Asignacion (v,exp) -> asignar_valor d v (evaluar_expresion d exp)
    | Calculo expr -> let a = evaluar_expresion d expr in print_float a; d
    | Comando v -> match v with
                    "var" -> mostrar_diccionario d; d
                    | "fun" -> mostrar_libreria (); d
                    | "fin" -> raise(Fin_de_ejecucion);
                    |  _ -> raise(Comando_no_implementado v);;