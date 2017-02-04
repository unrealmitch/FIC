open Num;;

let n1 = num_of_int 1;;
let n0 = num_of_int 0;;

let fib n =
	if n < 0 then raise(Failure "fib")
	else 
		let rec fib_aux n x y = match n with
			  0 -> x
			| _ -> fib_aux (n - 1) (x +/ y) x
		in fib_aux n n0 n1;;

(*************************)
(* |||||SEMINARIO 2 |||||*)
(*************************)

let fib n =
		if n > 3 then
			let rec aux (count, first, middle, last)=
				if count <= m then aux (count+1, middle, last, first +/ middle */ last)		(*la suma con num_of_int es O(n)*)
				else last
			in aux (4, num_of_int 1, num,_of_int 2, num_of_int 3)
	else num_of_int m;;


(*

(fib3 = suma por matrices)  	(fibn1)   (1 1 1)   (fibn-1) 								(1 1 1)			)	(2)
let fib3 n = 					(fibn2) = (1 0 0) x	(fibn-2)	=> (con pow matrices) => 	(1 0 0) ^ n-2 	) * (1)
								(fibn3)   (0 1 0)	(fibn-3)								(0 1 0)			)	(0)
*)

let pow n = function		(*O(n)*)
	 0 -> 1
	 | 1 -> n
	 | m -> n * pow n (n-1)


(* 

  [	n^m = (n^2) ^ (m/2) = (n*n) m/2 si m es par	]
  [	n^m = (n*n)^(m-1) si m es impart			]  O(log n) 

*)
let pow n = function		(*O(n)*)
	 0 -> 1
	 | 1 -> n
	 | m -> if m mod 2 = 0 then pow (n*n) (m/2)
	 		else n*pow n (n-1)

let mult_matrix (	a11,a12,a13,
					a21,a22,a23,
					a31,a32,a33,	)
				(	b11,b12,b13,
					b21,b22,b23
					b31,b32,b33		) =

				(	a11*/b11 +/ a12*b21 +/ a13*/b31 ,
					a11*/b12 +/ a12*b22 +/ a13*/b32 ,
					a11*/b13 +/ a12*b23 +/ a13*/b33 ,

					a21*/b11 +/ a22*b21 +/ a23*/b31 ,
					a21*/b12 +/ a22*b22 +/ a23*/b32 ,
					a21*/b13 +/ a22*b23 +/ a23*/b33 ,

					a31*/b11 +/ a32*b21 +/ a33*/b31 ,
					a31*/b12 +/ a32*b22 +/ a33*/b32 ,
					a31*/b13 +/ a32*b23 +/ a33*/b33 	);;

let rec pow mult n id = function
	0 -> id
	| 1 -> n
	| m -> 	if m mod 2= 0 then pow muld id  (mult n n) (m/2)
			else mult n (pow mult id n (n-1) ) ;; (* else mult n (pow n (m-1)) *)

let rec pow_int = pow ( * ) 1;;
let rec pow_int n m = pow ( * ) 1 n m;;

let uno = num_of_int 1;;
let zero = num_of_int 0;;
let id = (	uno,zero,zereo)
			zereo,uno,zero
			zero,zero,uno);;

let pow_matrix mult_matrix id_matrix;

let fibo n =
		if <= n then num_of_int n 
		else let (x,y,_,_,_,_,_,_,_)=
			pow_matrix(	uno,uno,uno,
						uno,zero,zero,
						zero,uno,zero ) (n-2)
		in x */ (num_of_int 2) +/ y ;;


(*************************)
(* |||||SEMINARIO 2 |||||*)
(*************************)


let main = match Array.length Sys.argv with
    nargs when nargs = 1 -> raise(Invalid_argument "Falta argumento: [fibo x]")
  | n -> try
            print_endline (string_of_num (fib (int_of_string  Sys.argv.(1))))
         with
          | Failure "int_of_string" -> raise(Invalid_argument "fibo [x] -> x debe ser un numero entero ")
;;

main;;