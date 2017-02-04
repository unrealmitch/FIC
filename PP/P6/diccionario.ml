(*

Practica:   6
Asignatura: Paradigmas de Programacion
Fecha:      12/2014
Autor:      Miguel Mosquera Pérez
Correo:     miguel.mosquera.perez@udc.es
Grupo:      4.2

*)

type diccionario = (string * float) list;;

exception Variable_no_asignada of string;;

let diccionario_vacio = [];; 
	
let rec consultar_valor d name = match d with  
  [] -> raise (Variable_no_asignada name)
  |(h::t) -> if fst h = name then snd h
            else consultar_valor t name;;

let asignar_valor d name value = 
    print_string(name ^ " = ");
    print_float(value);
    (name,value)::List.remove_assoc name d;; 

let rec mostrar_diccionario d = match d with
    [] -> ()
    |(h1,h2)::t -> print_endline(h1 ^ " : " ^ string_of_float h2);
                  mostrar_diccionario t;;
