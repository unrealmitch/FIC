(*

Practica:	  5
Asignatura:	Paradigmas de Programacion
Fecha:		  11/2014
Autor:		  Miguel Mosquera Pérez
Correo:     miguel.mosquera.perez@udc.es
Grupo:		  4.2

*)

type 'a fb_tree =
    Leaf of 'a
  | Node of 'a * 'a fb_tree * 'a fb_tree
;;

let rec string_of_tree f = function
    Leaf a ->
      "(" ^ (f a) ^ ")"
  | Node (a, t1, t2) ->
    "(" ^ (f a) ^ " " ^ (string_of_tree f t1) 
    ^ " " ^ (string_of_tree f t2) ^ ")";;

exception Branches;;

let single tree = Leaf(tree);;
let comp tree (ar1,ar2) = Node(tree,ar1, ar2) ;;

let root = function
    Leaf(r) -> r 
  | Node(r,_,_) -> r;;

let branches = function
  Leaf(a) -> raise Branches
  | Node(r,i,d) -> (i, d);;