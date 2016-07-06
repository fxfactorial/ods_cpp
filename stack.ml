
class ['a] stack size = object(self)

  val array_a : 'a option array = Array.init size (fun _ -> None)
  val mutable n = size

  method size = n

  method resize = ()
  method add i x =
    if n + 1 > Array.length array_a then self#resize;
    for j = n downto i + 1 do
      array_a.(j) <- array_a.(j - 1)
    done;
    array_a.(i - 1) <- x;
    n <- n + 1

  method remove i =
    let x = array_a.(i) in
    for j = i to Array.length array_a - 1 do
      array_a.(j) <- array_a.(j + 1)
    done;
    n <- n - 1;
    if Array.length array_a >= 3 * n then self#resize;
    x

  method push item = self#add n (Some item)

  method pop : 'a = match self#remove (n - 1) with None -> assert false | Some x -> x

end

let () =
  let s = new stack 10 in
  s#push 'a';
  print_char s#pop;
  print_newline ()
