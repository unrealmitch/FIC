(*

Practica:	5
Asignatura:	Paradigmas de Programacion
Fecha:		11/2014
Autor:		Miguel Mosquera Pérez
Correo:		miguel.mosquera.perez@udc.es
Grupo:		4.2

*)

type 'a fb_tree

val string_of_tree : ('a -> string) -> 'a fb_tree -> string

exception Branches

val single: 'a -> 'a fb_tree

val comp: 'a -> 'a fb_tree * 'a fb_tree -> 'a fb_tree

val root: 'a fb_tree -> 'a

val branches: 'a fb_tree -> 'a fb_tree * 'a fb_tree