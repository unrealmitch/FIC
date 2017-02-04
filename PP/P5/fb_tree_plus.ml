(*

Practica:   5
Asignatura: Paradigmas de Programacion
Fecha:      11/2014
Autor:      Miguel Mosquera Pérez
Correo:     miguel.mosquera.perez@udc.es
Grupo:      4.2

*)

(* Cargamos "fb_tree.cmo" *)
open Fb_tree;;

(* identifica árboles-hoja *)
let is_single t = 
	try let _ = branches t in false 
	with Branches -> true ;;

(* rama izquierda *)
let l_branch t = fst (branches t);;

(* rama derecha *)
let r_branch t = snd (branches t);;

(* número de nodos *)
let rec size t =
  if is_single t then 1
  else 1 + size(l_branch t) + size(r_branch t);;

(* altura *)
let rec height t =
  if is_single t then 1
  else 1 + max (height (l_branch t)) (height (r_branch t));;

(* preorder *)
let rec preorder t =
  if is_single t then [root t]
  else  root t::preorder(l_branch t)@preorder(r_branch t);;

(* postoder *)
let rec postorder t =
  if is_single t then [root t]
  else postorder(l_branch t)@postorder(r_branch t)@[root t];;

(* inorder *)
let rec inorder t =
  if is_single t then [root t]
  else inorder(l_branch t)@[root t]@ inorder(r_branch t);;

(* Lista de hojas *)
let rec leafs t =
  if is_single t then [root t]
  else leafs(l_branch t) @ leafs(r_branch t);;

(* Imagen Especular (arbol visto en espejo) *)
let rec mirror t =
	if is_single t then single(root t)
	else comp (root t)(mirror(r_branch t),mirror(l_branch t));;

(* Aplica f a todos los nodos *)
let rec treemap func t =
	if is_single t then single(func(root t)) 
	else comp(func(root t))((treemap func(l_branch t)),(treemap func(r_branch t)));;

(* Arbol perfecto = todas sus hojas son del mismo lvl (ultimo nivel completo) *)
let is_perfect t =
	if is_single t then true
  else let altura = height t and numHojas = List.length (leafs t) in
    2.0 ** float_of_int (altura - 1) = float_of_int numHojas;;

(*Un árbol es completo si todo nivel, excepto quizás el último, está lleno
y todos los nodos del último nivel están lo más a la izquierda posible *)

let rec is_complet t = 
	if is_single t then true
	else
		height(l_branch t)-height(r_branch t)=0
		||height(l_branch t)-height(r_branch t)=1
		&& is_complet(l_branch t)
		&& is_complet(r_branch t);;