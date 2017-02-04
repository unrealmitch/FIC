(*

Practica:   6
Asignatura: Paradigmas de Programacion
Fecha:      12/2014
Autor:      Miguel Mosquera Pérez
Correo:     miguel.mosquera.perez@udc.es
Grupo:      4.2

*)

open Diccionario;;
open Instruccion;;
open Libreria;;


let rec calc d =
        print_string("\n\n");
        print_string(">>");
        try
            let instr = Parser.s Scanner.token (Lexing.from_string (read_line ())) in
            calc (ejecutar_instruccion d instr)
        with
            Scanner.Error_lexico -> print_endline("Error lexico"); calc d
            | Parsing.Parse_error -> print_endline("Error sintactico"); calc d
            | Comando_no_implementado nombre -> print_endline("Comando " ^ nombre ^ " no implemetado");calc d
            | Fin_de_ejecucion -> print_endline("...Adios !!!")
            | Funcion_no_implementada nombre -> print_endline("Funcion " ^ nombre ^ " no implementada");calc d
            | Variable_no_asignada nombre -> print_endline("Variable " ^ nombre ^ " no asignada");calc d;;

print_endline("Calculadora de punto flotante con variables...");calc diccionario_vacio;;