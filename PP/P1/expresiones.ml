(*
Practica: 	1
Autor:		Miguel Mosquera Pérez
Org:		UDC- Paradigmas de programación
*)


(*
Redefina las funciones hd, tl, length, nth y append, del módulo List, sin utilizar ese módulo ni la
función ( @ ) del módulo Pervasives.
*)

();;
(*unit = ()*)

2+5*3;;
(*int = 17*)

1.0;;
(*float = 1.0*)

(* 1.0 * 2;; *)
(*error: wait a int and found float*)
(*Correct: "1.0 *. 2.;;" or "1 * 2;;"*)

(* 2 - 2.0;; *)
(*error: wait a int and found a float*)
(*Correct: "2 - 2;;" or "2.0 -. 2.0" *)

(*3.0 + 2.0;;*)
(*error: wait a int and found a float*)
(*Correct: "3+2;;" or "3.0 +. 2.0;;" *)

5 / 3;;
(*int = 1*)

5 mod 3;;
(*MAL: float = 1.66...*)
(*int = 2*)

3.0 *. 2.0 ** 3.0;;
(*float = 24*)

3.0 = float_of_int 3;;
(*bool = true*)

(* sqrt 4;; *)
(*MAL float = 2*)
(*Error: wait a float and found a int*)
(*Correct sqrt 4.;;*)

int_of_float 2.1 + int_of_float (-2.9);;
(*int = 0*)

truncate 2.1 + truncate (-2.9);;
(*int = 0*)

floor 2.1 +. floor (-2.9);;
(*float = -1.*)	

(*ceil 2.1 +. ceil -2.9;; *)
(*Syntaxsis error: ceil -2.9*)
(*Correct: ceil 2.1 +. ceil (-2.9);;*)
(*float = 1.*)	

(*Info about last op: http://caml.inria.fr/pub/docs/manual-ocaml-4.00/libref/Pervasives.html*)

'B';;
(*char = B*)

int_of_char 'A';;
(*int = 65*)

char_of_int 66;;
(*char = B*)

Char.code 'B';;
(*int = 66*)

Char.chr 67;;
(*char = C*)

'\067';;
(*char = C*)

Char.chr (Char.code 'a' - Char.code 'A' + Char.code 'Ñ');;
(*Error syntaxsis*)
(*Correct: "Char.chr (Char.code 'a' - Char.code 'A' + Char.code 'Ñ')" *)
(*Para que funcione correctamente la Ñ, cambiar configuracion de caracteres a occidental*)

(*char = '\241' //ñ minuscula*) 

Char.uppercase 'ñ';;
(*char = '\209' //Ñ mayuscula*)

Char.lowercase 'O';;
(*char = o*)

"this is a string";;
(*string = "this is a string"*)

String.length "longitud";;
(*int = 8*)

(* "1999" + "1";; *)
(*Error: wait a int and found a string*)
(*Correct: next command*)

"1999" ^ "1";;
(*string = 1991*)

int_of_string "1999" + 1;;
(*int = 2000*)

"\064\065";;
(*string = @A*)

string_of_int 010;;
(*string = "10"*)

not true;;
(*bool = false*)

true && false;;
(*bool = flase*)

true || false;;
(*bool = true*)

true or false;;
(*bool = true*)

(* true and false;; *)
(*Syntaxsis error: and es una palabra reservada*)

(1 < 2) = false;;
(*bool = false*)

"1" < "2";;
(*bool = true*)

2 < 12;;
(*bool = true*)

"2" < "12";;
(*bool = false*)

"uno" < "dos";;
(*bool = false*)

2,5;;
(* int * int = (2,5) *)

"hola", "adios";;
(* string * string = ("hola","adios") *)

0, 0.0;;
(* int * float = (0 , 0.0) *)

fst ('a',0);;
(* char = 'a'  [First element]*)

snd (false, true);;
(* bool = true  [Second element]*)

(1,2,3);;
(* int * int * int = (1,2,3) *)

(1,2),3;;
(* (int * int) * int = ((1,2)*3) *)

fst ((1,2),3);;
(* int * int = (1,2)*)

(),abs;;
(* unit * (int -> int) = [], <fun> *)

if 3 = 4 then 0 else 4;;
(* int = 3 *)

if 3 = 4 then "0" else "4";;
(* string = "4" *)

(* if 3 = 4 then 0 else "4";; *)
(* Error: wait a int bout found a string*)
(* Correct: "if 3 = 4 then 0 else 4;;" or "if 3 = 4 then "0" else "4";;" *)

(if 3 < 5 then 8 else 10) + 4;;
(*int = 12*)

let pi = 3.14;;
(* pi : float = 3.14 *)

sin (pi /. 2.);;
(* float = 0.999... *)

let x = 1;;
(* x : int = 1 *)

let y = 2;;
(* y : int = 2 *)

x - y;;
(* int = -1 *)

let x = y in x - y;;
(* x : int = 0 *)

x - y;;
(* int = -1 *)

(* z;; *)
(*Error: z not defined *)

let z = x + y;;
(* z : int = 3 *)

z;;
(* z: int = 3 *)

let x = 5;;
(* x: int = 5 *)

z;;
(* z: int = 3 *)


let y = 5 in x + y;;
(* int =  10 *)

x + y;;
(* int = 7 *)

let p = 2,5;;
(* p : int * int = (2,5) *)

snd p, fst p;;
(* int * int = (5,2) *)

p;;
(* p : int * int = (2,5) *)

let p = 0,1 in snd p, fst p;;
(* int * int = (1,0) *)

p;;
(* p : int * int = (2,5) *)

let x,y = p;;
(* x : int = 2 | y : int = 5 *)

let z = x + y;;
(* z : int = 7 *)

let x,y = p,x;;
(* x : int * int = (2,5) | y : int = 2 *)

let x = let x,y = 2,3 in x * x + y;;
(* x : int = 7 *)

x + y;;
(* int = 9 *)

z;;
(* int = 7 *)

let x = x + y in let y = x * y in x + y + z;;
(*  x=9 ; y = 18; 9+18+7 *)
(* int = 34 *)

x + y + z;;
(* int = 16 *)

int_of_float;;
(* float -> int = <fun> *)

float_of_int;;
(* int -> float = <fun> *)

int_of_char;;
(* char -> int = <fun> *)

char_of_int;;
(* int -> char = <fun> *)

abs;;
(* int -> int = <fun> *)

sqrt;;
(* float -> float = <fun> *)

truncate;;
(* float -> int = <fun> *)

ceil;;
(* float -> float = <fun> *)

floor;;
(* float -> float = <fun> *)

Char.code;;
(* char -> int = <fun> *)

String.length;;
(* string -> int = <fun> *)

fst;;
(* 'a * 'b -> 'b = <fun> *)

snd;;
(* 'a * 'b -> 'a = <fun> *)

function x -> 2 * x;;
(* int -> int = <fun> *)

(function x -> 2 * x) (2 + 1);;
(* Exec funcion with x = 3 *)
(* int = 6 *)

function (x,y) -> x;;
(*MAL: int*int -> int = <fun> *)
(* 'a * 'b -> 'a = <fun> *)

let f = function x -> 2 * x;;
(* f : int -> int = <fun> *)

f (2+1);;
(* int = 6 *)

f 2 + 1;;
(* int = 5 *)