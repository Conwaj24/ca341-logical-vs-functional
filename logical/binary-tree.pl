childOf(6, 10).
childOf(18, 10).
childOf(5, 10).

leftOf(C, P) :-
	childOf(C, P),
	C < P.

rightOf(C, P) :-
	childOf(C, P),
	C > P.

binaryTree(nil) :- !.
binaryTree(T) :- %inverse-predicate ensures T is integer
	not(integer(T)), !,
	false.
binaryTree(T) :- %inverse-predicate ensures T has no more than 2 children
	findall(C, childOf(C, T), Children),
	length(Children, X),
	X > 2, !,
	false.
binaryTree(T) :-
	not(leftOf(_, T)),
	not(rightOf(_, T)).
binaryTree(T) :-
	not(rightOf(_, T)),
	leftOf(L, T), !,
	binaryTree(L).
binaryTree(T) :-
	not(leftOf(_, T)),
	rightOf(R, T), !,
	binaryTree(R).
binaryTree(T) :-
	rightOf(R, T),
	leftOf(L, T), !,
	binaryTree(R),
	binaryTree(L).

insert(X, T, R) :-
	X < T,
	leftOf(C, T), !,
	insert(X, C, R1),
	leftOf(R1, R),
	binaryTree(R).
insert(X, T, R) :-
	X > T,
	rightOf(C, T), !,
	insert(X, C, R1),
	rightOf(R1, R),
	binaryTree(R).
insert(X, T, R) :-
	X < T,
	leftOf(X, R),
	binaryTree(R).
insert(X, T, R) :-
	X > T,
	rightOf(X, R),
	binaryTree(R).

search(X, X) :- !.
search(X, T) :-
	childOf(X, T).
search(X, T) :-
	childOf(C, T),
	search(X, C).

preorder(T, (T, L, R)) :-
	(
		leftOf(T, Left),
		preorder(Left, L)
	) ;
		L is nil,
	(
		rightOf(T, Right),
		preorder(Right, R)
	) ;
		R is nil.
postorder(T, (L, R, T)) :-
	(
		leftOf(T, Left),
		postorder(Left, L)
	) ;
		L is nil,
	(
		rightOf(T, Right),
		postorder(Right, R)
	) ;
		R is nil.
inorder(T, (L, T, R)) :-
	(
		leftOf(T, Left),
		inorder(Left, L)
	) ;
		L is nil,
	(
		rightOf(T, Right),
		inorder(Right, R)
	) ;
		R is nil.
