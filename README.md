# C++ project

This project aims to simulate a simple Morpion and Chess game. Both of this games needs two players; one first player is tue interface user (you) and the adversary is implemented by the well-known MinMax algorithm and its AlphaBeta variant. It plays an opponent playing the less risky strategy at every turn. This project is the right occasion to master advanced features of c++ such as virtual class, polymorphism and ths Standard Library. Also, given the exponential growth of the number of move in Chess, some peculiar care have to be given to the computational cost. Indeed, there is on average around 40 possible moves every turn at the beginning and mid stage of a chess game. 

The Morpion and Chess games derive from the same virtual class: **Position**, **Piece**, **type_piece** and **Coup**.

## Morpion

The implementation is easy and mostly serves of testing case than is of real interest. With a correct implementation
of the MinMax algorithm, it is impossible to win a Morpion game, as the adversary will always have a counter available.
Nonetheless, if the player plays a bad move, it can lose. Thus, a standard play ends up in a draw, hence the limited interest
of this case.

<img src="Morpion/img/1.PNG" alt="drawing" width="200"/> <img src="Morpion/img/2.PNG" alt="drawing" width="190"/> <img src="Morpion/img/3.PNG" alt="drawing" width="190"/>

<img src="Morpion/img/4.PNG" alt="drawing" width="200"/> <img src="Morpion/img/5.PNG" alt="drawing" width="190"/>

## Chess

