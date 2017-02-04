(*

Practica:   6
Asignatura: Paradigmas de Programacion
Fecha:      12/2014
Autor:      Miguel Mosquera Pérez
Correo:     miguel.mosquera.perez@udc.es
Grupo:      4.2

*)

exception Funcion_no_implementada of string;;

let rec assoc name = function
    [] -> raise(Funcion_no_implementada name)
  | (a,b)::t -> if compare a name = 0 then b else assoc name t


let round f = floor (f +. 0.5);;

let lista_funciones =  [
        ("abs",(abs_float," valor absoluto"));
        ("sqrt",(sqrt,"raíz cuadrada"));
        ("log",(log,"logaritmo natural"));
        ("exp",(exp,"exponencial"));
		("round",(round,"redondeo"))
        ];;

let funcion name = fst (assoc name lista_funciones);;

let descripcion name = snd (assoc name lista_funciones);;

let mostrar_libreria () = List.iter (function (name,(f,des)) -> print_endline(name ^ " : " ^ des)) lista_funciones;;