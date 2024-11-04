#include "class_position.hpp"
#include <cmath>

const int MAX = 1000;
const int MIN = -1000;


//============================================
//            class grille
//============================================

grille::grille()
{
    T = new int[9];
    for (int i = 0; i<9 ; i++){T[i] = 0;}
}


grille::grille(const grille & g)
{
    if (T != nullptr) {delete T;}
    T=new int[9];
    for (int i = 0; i<9 ; i++){T[i] = g.T[i];}
}


void grille::affichage() const
{
    	for (int j=0; j<3; j++){
            for (int i=0; i<3; i++){
                if (T[i + 3*j]==0){
                    cout<<".";
                }
                if (T[i + 3*j]==1){
                    cout<<"X";
                }
                if (T[i + 3*j]==2){
                    cout<<"0";
                }
            }
            cout<<endl;
        }
    cout<<endl;
}

void Position_Morpion::coup_humain()
{
    bool is_valid;
    char x;
    cout<<"Joue ton coup"<<endl;
    cin>>x;
    is_valid = this->is_valid_move(x);

    while (!is_valid)
    {
        cout<<"coup non valide.\n";
        cin>>x;
        is_valid = this->is_valid_move(x);
    }
    vector<int> A = {joueur, x - 49};
    coup.push_front(A);
}

bool grille::a_gagne(int joueur) const
{
	for (int i = 0; i<3 ; ++i){
		if (T[0+3*i]==joueur && T[1+3*i]==joueur && T[2+3*i]==joueur){return true;}

		if (T[i]==joueur && T[i+3]==joueur && T[i+6]==joueur){return true;}
	}
	if (T[0]==joueur && T[4]==joueur && T[8]==joueur){return true;}
	if (T[2]==joueur && T[4]==joueur && T[6]==joueur){return true;}
	return false;
}

bool grille::grille_pleine() const {
	for (int i=0; i<9; i++){
		if (T[i]==0){return false;}
	}
	return true;
}

int& grille::operator[](int i)
{
    return (this)->T[i];
}

grille& grille::operator=(const grille& g)
{
    if (this->T == nullptr) {this->T = new int[9];}
    for (int i = 0; i<9; ++i)
    {
        this->T[i] = g.T[i];
    }
    return *this;
}

//==========================================
//==========class Position_Morpion==========
//==========================================

Position_Morpion* Position_Morpion::libere_soeur()
{
    Position_Morpion* current = this;
    Position_Morpion* tmp = current;
    while(current != nullptr) {
        current = current->soeur; delete tmp; tmp = current;}
    return nullptr;
}

void Position_Morpion::position_possible()
{
    Position_Morpion tmp(*this); //Copy constructor, make a deep copy
    tmp.mise_a_jour_position(0);

    if (tmp.pleine()){
        fille = nullptr;
        tmp.free();
        return;}

    for (int i = 0; i<9; ++i)
    {
        if (tmp.G->T[i] == 0)
        {
            Position_Morpion* pfille = new Position_Morpion(tmp.joueur%2 + 1, coup);
            pfille->G = G;
            vector<int> new_coup = {tmp.joueur, i};
            pfille->coup.push_back(new_coup);
            pfille->soeur = fille;
            fille = pfille;
        }
    }
    tmp.free();
}

bool Position_Morpion::gagne() const
{
    return(this->G->a_gagne(this->joueur%2+1));
}

double Position_Morpion::valeur_position() const
{
    Position_Morpion tmp(*this); //Copy constructor, make a deep copy
    tmp.mise_a_jour_position(0); //Update the grid
    if (tmp.G->a_gagne(1)){
        tmp.free();
        return MAX;
    }
    else if (tmp.G->a_gagne(2)){
        tmp.free();
        return MIN;
    }
    else{
        tmp.free();
        return 0;
    }
}

bool Position_Morpion::is_valid_move(int i) const
{
    if (i < 49 || i > 58) {return false;}
    if (this->G->T[i - 49] != 0) {return false;}
    return true;
}

void Position_Morpion::mise_a_jour_position(const bool text)
{
    list<vector<int>>::const_iterator it;
    for (it = coup.begin(); it != coup.end(); ++it)
    {
        int j = (*it)[0]; int i = (*it)[1];
        G->T[i] = j;
        joueur = j%2 + 1;
    }
    coup.clear();
}

Position_Morpion& Position_Morpion::operator=(const Position_Morpion& Pos)
{
    joueur = Pos.joueur;
    coup = Pos.coup;
    if (G != Pos.G && G != nullptr) delete G;
    G = Pos.G;
    return *this;
}

void Position_Morpion::affiche_fille()
{
    Position_Morpion* fille_p = fille;
    while (fille_p != nullptr) {fille_p->valeur_position(); cout<<fille_p->joueur<<endl; cout<<"--------------"<<endl; fille_p = fille_p->soeur;}
    cout<<endl;
}

void Position_Morpion::free()
{
    delete G;
    coup.clear();
}

//==========================================
//            Fonction Minmax
//==========================================

///MinMax algorithm

int minimax(Position &P, int alpha, int beta, int depth)
{
    int val = P.valeur_position();
    if (val == MAX) return MAX;
    else if (val == MIN) return MIN;
    if (depth == 0) {return val;}

    P.position_possible(); //Create the 'fille' and her 'soeurs' chained list.
    Position* fille = P.get_fille();

	if (fille == nullptr){return val;} //Equivalent to depth == 0 normally

    if (P.joueur == 1)
    {
        int best = MIN;
//        First child
//        pP=P.fille;
        int val = minimax(*fille, alpha, beta, depth - 1);
        best = max(best, val);
//   Recur for her sisters
        Position* pS = fille->get_soeur();
        while (pS != nullptr)
        {
            val = minimax(*(pS), alpha, beta, depth - 1);
            best = max(best, val);
            pS = pS->get_soeur();
            alpha = max(alpha, best);

    /*        // Alpha Beta Pruning
            if (beta <= alpha)
                break;              */
        }
        Position* tmp = fille;
        //Delete the memory allocated during Position_possible process.
        while (fille != nullptr) {fille = fille->get_soeur(); delete tmp; tmp = fille;}
        return best;
        }
    else if (P.joueur == 2)
    {
        int best = MAX;
//          first child
//        pP=P.fille;
        int val = minimax(*fille, alpha, beta, depth - 1);
        best = min(best, val);
        //Recur for her sisters
        Position* pS = fille->get_soeur();
        while (pS!=nullptr)
        {
            val = minimax(*(pS), alpha, beta, depth - 1);
            best = min(best, val);
            pS = pS->get_soeur();
            beta = min(alpha, best);
      /*      // Alpha Beta Pruning
            if (beta <= alpha)
                break;              */
        }
        //Delete the memory allocated during Position_possible process.
        Position* tmp = fille;
        while (fille != nullptr) {fille = fille->get_soeur(); delete tmp; tmp = fille;}
        return best;
    }
}
