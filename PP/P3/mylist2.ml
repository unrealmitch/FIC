(*
Practica: 	3
Autor:		Miguel Mosquera Pérez
Fecha:		28/10/2014
Org:		UDC- Paradigmas de programación

Páginas de interes:

List doc: http://caml.inria.fr/pub/docs/manual-ocaml/libref/List.html
*)


(*
Redefina las funciones hd, tl, length, nth y append, del módulo List, sin utilizar ese módulo ni la
función ( @ ) del módulo Pervasives.
*)

(*Devuelve la cabezerá [primer elemento] de una lista*)
let hd = function
	[] -> failwith "hd"
	| h::t -> h;;

(*Devuelve la cola de una lista [todo menos el primer elemento*)
let tl = function
	[] -> failwith "tl"
	| h::t -> t;;

(*Devuelve la longitud de la lista*)
let length l=
	let rec lengthx len = function
		[] -> len
		| h::t -> lengthx (len + 1) t
	in lengthx 0 l;;

(*Devuelve el n elemento de una lista*)
let nth l n =
	if n < 0 then 
		invalid_arg "List.nth" 
	else
		let rec aux l n =
			match l with
			| [] -> failwith "nth"
			| h::t -> if n = 0 then h
					else aux t (n-1)
		in aux l n;;

(*Concatena dos listas*)
let rec append l1 l2 =
	match l1 with
	[] -> l2
	| h::t -> h:: append t l2;;

(*
Redefina las funciones rev, rev_append, concat, flatten, map, map2, fold_left y fold_right, del
módulo List, sin utilizar ese módulo.
*)

(*Devuelve la rista al reves*)
let rev l = 
	let rec revx lin lout = 
		match lin with
			| [] -> lout
			| h::t -> revx t (h::lout)
	in revx l [];;

(*Devuelve la concatenación de l1 al reves y l2*)
let rec rev_append l1 l2 = 
	match l1 with
		| [] -> l2
		| h::t -> rev_append t (h::l2);;

(*Concatena una lista de listas['a list list -> 'a list]*)
let rec concat = function
	[] -> []
	| h::t -> append h (concat t);;

(*Igual que concat*)
let flatten l = concat l;;

(*Aplica una funcion a todos los elementos de una lista y devuelve otra con los resultado*)
let rec map f = function 
	[] -> [] 
	| h::t -> (f h):: map f t;;

(*Aplica una funcion a todos los elemenos de dos listas [de la forma: F an bn], y devuelve los resultado en una nueva lsita*)
let rec map2 f l1 l2 = 
	match (l1, l2) with
		([],[]) -> []
		| (h1::t1 , h2::t2) -> let r = f h1 h2 in r :: map2 f t1 t2
		| ( _, _) -> raise(Invalid_argument "map2");;

(*Aplica una funcion de la fomra f a [b1; ...; bn], la salida será: f (... (f (f a b1) b2) ...) bn *)
let rec fold_left f n = function
	[] -> n
  | h::t -> let r = f n h in fold_left f r t;;

(*Aplica una funcion de la fomra f [a1; ...; an] b, la salida será: f a1 (f a2 (... (f an b) ...)) *)
let rec fold_right f l n =
	match l with
	[] -> n
	| h::t -> f h (fold_right f t n);;

(*
Redefina las funciones find, for_all, exists, mem, filter, find_all, partition, split y combine del
módulo List, sin utilizar ese módulo.
*)

(*Devuelve el primer resultado que satisfaca p [una funcion que devuelve un bool] *)
let rec find p = function
	[] -> raise Not_found
	| h::t -> if p h = true then h
				else find p t;;

let rec for_all p l = match l with
	[] -> true
	| h::t -> (p h) && for_all p t;;

(*Comprueba que algún resultado de la lista cumple p*)
let rec exists p = function
	[] -> false
	| h::t -> p h || exists p t;;

(*Devuelve true si algún elemento de la lista es igual a 'a'*)
let rec mem n = function
	[]-> false
	| h::t-> h = n || mem n t;;

(*Devuelve una lista con los elementos de l que cumplen p, y aparecen en el mismo orden*)
let filter p =
	let rec aux box = function
		[] -> rev box
		| h::t -> if p h then aux (h::box) t
				  else aux box t
	in aux [];;

(*Igual que filter*)
let find_all p =
	let rec aux box = function
		[] -> rev box
		| h::t -> if p h then aux (h::box) t
				  else aux box t
	in aux [];;

(*Devuelve un par de listas, una con los elementos que cumplen p, y la otra con los que no lo cumplen*)
let partition p =
	let rec aux box1 box2 = function
		[] -> ((rev box1) , (rev box2))
		| h::t -> 	if p h then aux (h::box1) box2 t
					else aux box1 (h::box2) t
	in aux [] [];;

(*Transforma una lista de pares en un par de listas*)
(*let split l =
	let rec aux box1 box2 = function
		[] -> (rev box1, rev box2)
		| (h1,h2)::t -> aux (h1::box1) (h2::box2) t
	in aux [] [] l;;*)

let rec split = function
    [] -> ([], [])
  | (h1,h2)::t -> let (l1, l2) = split t in (h1::l1, h2::l2)

(*Transforma un par de listas en una lista de pares*)
let combine l1 l2 =
	let rec aux box l1 l2 = match l1, l2 with
	([], []) -> rev box
	| (h1::t1, h2::t2) -> aux ((h1, h2)::box) t1 t2
	| (_, _) -> raise(Invalid_argument "combine")
in aux [] l1 l2;;

(*'a -> 'a list -> 'a list, que “elimine la primera aparición, si la hay, de
un valor en una lista”; de forma que, por ejemplo remove 3 [2; 6; 3; 4; 3] sea la lista [2; 6; 4; 3] y
remove 3 [1; 2; 4] sea la lista [1; 2; 4].*)
let remove a = 
	let rec aux box a = function
		[] -> rev box
		| h::t -> 	if h = a then rev_append box t
					else aux (h::box) a t
	in aux [] a;;

(*'a -> 'a list -> 'a list, que “elimine todas las apariciones de un valor
en una lista”; de forma que remove_all 3 [2; 6; 3; 4; 3] sea la lista [2; 6; 4].*)
let remove_all a l=
	let rec aux box a l= match l with
		[] -> rev box
		| h::t -> 	if a=h then aux box a t
					else aux (h::box) a t
	in aux [] a l;;

(*a list -> 'a list -> 'a list, de forma que ldif l1 l2 elimine de l1 todas las
apariciones de todos aquellos valores que aparezcan en l2. Así, por ejemplo, ldif [1;2;3;2;4]
[2;3;3;5] debería ser la lista [1;4].*)
let rec ldif l1 l2 = match (l1, l2) with
    (l1, []) -> l1
  | ([], l2) -> []
  | (l1, h2::t2) -> ldif (remove_all h2 l1) t2
;;

(*lprod: 'a list -> 'b list -> ('a * 'b) list, de forma que lprod l1 l2 calcule el
“producto cartesiano” de l1 y l2. Así, por ejemplo, lprod [1;3;1;2] ['a';'b'] debería ser la lista
[(1,'a'); (1,'b'); (3,'a'); (3,'b'); (1,'a'); (1,'b'); (2,'a'); (2,'b')].*)
let rec aux_lprod h1 l2= match l2 with
	[] -> []
	| h::t->(h1,h)::(aux_lprod h1 t);;

let rec lprod l1 l2 = match l1 with
	[] -> []
	| h::t -> append (aux_lprod h l2) (lprod t l2);;

(*'a list -> 'a list * 'a list, de forma que divide l devuelva un par de listas
(l1,l2), donde l1 contiene los elementos de l que ocupan posición impar y l2 los que ocupan
posición par. En ambos casos, los elementos de l1 y l2 deben mantener el mismo orden relativo que
tienen en la lista original l. Así, por ejemplo, divide ['a';'e';'i';'o';'u'] debería ser el par (['a';'i';'u'],
['e';'o']).*)
let rec divide l= 
	let rec aux box1 box2 = function
		[]-> (rev box1, rev box2)
		| h::[] -> aux (h::box1) box2 []
		| h1::h2::t -> aux (h1::box1) (h2::box2) t
	in aux [] [] l;;