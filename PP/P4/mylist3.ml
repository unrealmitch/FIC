(*
Practica: 	4
Autor:		Miguel Mosquera Pérez
Fecha:		5/11/2014
Org:		UDC- Paradigmas de programación
*)

(*AUXILIARES*)

let rec append l1 l2 =
	match l1 with
	[] -> l2
	| h::t -> h:: append t l2;;
	
let rev l = 
	let rec revx lin lout = 
		match lin with
			| [] -> lout
			| h::t -> revx t (h::lout)
	in revx l [];;

let rec map f = function 
	[] -> [] 
	| h::t -> (f h):: map f t;;

let rec mem n = function
	[]-> false
	| h::t-> h = n || mem n t;;

let rec concat = function
	[] -> []
	| h::t -> append h (concat t);;

(*AUXILIARES*)

let rec fromto m n =
	if m>n then []
	else m::fromto(m+1) n;;

let fromto_t m n=
	let rec aux box m n =
		if (m>n) then rev(box)
		else aux (m::box) (m+1) n
in aux [] m n;;



(*Al estar ordenado de forma ascedente, se entra de forma recursiva en lmax por cada elemento, situación que no se da
al estar ordenado de forma descendente(lo que se consigue mediante rev*)
let rec lmax = function
	h::[] -> h
	| h::t -> if h >= lmax t then h
	| _ -> raise(Invalid_argument "lmax");;

let rec lmax_ok = function
	h::[] -> h
	|h::t -> let m = lmax_ok t in 
				if h>=m then h
            	else m
    |_ -> raise (Invalid_argument "lmax_ok");;

let rec lmax_t l = match l with
	h::[] -> h
	|h1::h2::t -> if (h2>h1) then lmax_t (h2::t)
                  else lmax_t (h1::t)
    |_-> raise(Invalid_argument "lmax_t");;





(*Transforma una lista l en una lista de listas, donde cada sublista_i es la sublista_(i-1)
menos su primer elemento, y la primera sublista (sublista_0) es la lista l de entrada mientras
la ultima sublista (sublista_n) será una lista vacia:

'a list -> 'a list list de la forma [a1,a2...an] -> [[a1,a2,...,an], [a2,...,an], ..., [an], [] ]

*)
let rec sufixes l = match l with
	[] -> [[]]
	| h::t -> l::sufixes t;;


(*Transforma una lista l en una lista de listas, donde la primera sublista será el primer
elemento de la lista l, y a la siguiente sublista se le añade el siguiente elemento de la lista l
hasta la ultima sublista que será la lista de entrada l:

'a list -> 'a list list de la forma [a1,a2,...,an] -> [[a1], [a1,a2], ..., [a1,a2,...,an] ]

*)
let rec prefixes = function
	[] -> []
	| h::t -> [h]::List.map (function l->h::l) (prefixes t);;

(*Transforma una lista l en una lista de listas resultante de la combinacion de prefixes a sufixes:

'a list -> 'a list list de la forma [a1,a2...,an] -> [[a1],[a1,a2],...,[a1,a2,...,an], [a2],[a2,a3],...,[a2,a3,...,an], ..... [an-1],[an-1,an],[an] ]

*)
let segments l = concat(List.map prefixes(sufixes l));;

let is_sufixe l1 l2 = mem l1 (sufixes l2);;
let is_prefixe l1 l2 = mem l1 (prefixes l2);;
let is_segment l1 l2 = mem l1 (segments l2);;


let rec is_sufix_t l1 l2 = match l1,l2 with
	[],_ -> true
	| _::_,[] -> false
	| _, _::t2 -> l1 = l2 || is_sufix_t l1 t2;;

let rec is_prefix_t l1 l2 = match l1,l2 with
	[],_ | _,[] -> false
	| h1::[], h2::_ -> h1 = h2
	| h1::t1, h2::t2 -> h1 = h2 && is_prefix_t t1 t2;;

let is_segment_t l1 l2 = match l1, l2 with
	[],[] -> false
	|[],_ | _,[] -> false
	|h1::t1, h2::t2 -> let rec aux a b = match a, b with
							[], [] | [], _ -> true
							|_, [] -> false
							|h1::t1, h2::t2 -> 	if h1=h2 then 
													aux t1 t2
												else     
													aux l1 t2
						in aux l1 l2;;

let rec is_sublist l1 l2 = match l1, l2 with
	[], _ -> true
	| h1::t1, h2::t2 -> if h1=h2 then is_sublist t1 t2
						else is_sublist l1 l2
	| _ -> false;;

(*'a list -> 'a list list, da todas las sublista de la lista dada*)

let rec sublists = function
	[] -> [[]]
	|h::l -> let sub = sublists l
			 in sub @ (map(fun l->h::l) sub);;

let is_sublist l1 l2 = mem l1 (sublists l2);;