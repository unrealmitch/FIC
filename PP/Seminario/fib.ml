open Num;;
let n1 = num_of_int 1 
and n0 = num_of_int 0;;

let fib n =
	if n < 0 then raise(Failure "fib")
	else 
		let rec fib_aux n a b = match n with
			  0 -> a
			| _ -> fib_aux (n - 1) (a +/ b) a
		in fib_aux n n0 n1;;	


(*let fib n =
	if n < 0 then raise(Failure "fib")
	else 
		let rec fib_aux i a b = 
                        if  i = n then b
			else fib_aux (n+1) (a +/ b) a
		in fib_aux 0 n1 n0;;	
*)
(*
let main() =
	let arg = Sys.argv.(1) in
		print_endline (string_of_num (fib (int_of_string arg)))
;;
*)


(* 

	let fib n =
		if n < 0 then raise(Failure "fib")
		else
			let rec fib_aux i a b =
				i = n-1
				a,b = 10
				c,d = 01
				if i = 0 then x
				else if i mod 2 = 0 then aux x y*y z/2
					else aux x*y y z-1
			in aux 1 a b

	int i=1,j=0,k=0,h=1,t;
	while ( n > 0 )
	{
		if ((n % 2) != 0)
		{
			t = j * h;
			j = (i * h) + (j * k) + t;
			i = (i * k) + t;
		}
		t = h * h;
		h = (2 * k * h) + t;
		k = (k * k) + t;
		n = n / 2;
	}
	return j;

*)
let crono f x =
	let t = Sys.time() in
	let _ = f x in
		print_float(Sys.time() -. t);
		print_newline()
;;

let main() =
	let arg = Sys.argv.(1) in
		print_string(string_of_num( fib (int_of_string arg)))
;;


main();;
