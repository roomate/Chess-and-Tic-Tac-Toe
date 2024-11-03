#include "chess.hpp"
#include <cmath>
#include <string>
#include <sstream>

string alphat = "ABCDEFGH";
const int MAX = 100000000;
const int MIN = -100000000;

//Copy constructor
Coup_Echec::Coup_Echec(const Coup_Echec &c){

    init = c.init;
    fin = c.fin;
    p_rock = c.p_rock;
    g_rock = c.g_rock;
    prom_f = c.prom_f;
    prom_d = c.prom_d;
    prom_c = c.prom_c;
    prom_t = c.prom_t;
    echec = c.echec;
    echec_mat = c.echec_mat;
    couleur_c = c.couleur_c;
    joueur = c.joueur;
}

//Constructor of a chess move when taking an opponent piece.
Coup_Echec::Coup_Echec(const int y, const int x, const int mv_y, const int mv_x, const PieceColor C, const int j){

    //Update the position of the piece
    p_rock = false;
    g_rock = false;
    prom_f = false;
    prom_d = false;
    prom_c = false;
    prom_t = false;
    couleur_c = C;
    joueur = j;
    init = {x, y};
    fin = {mv_x, mv_y};
}

//Constructor for a roocs move.
Coup_Echec::Coup_Echec(const char* nom_coup, const PieceColor couleur, const int j){
    couleur_c = couleur;
    p_rock = false;
    g_rock = false;
    prom_f = false;
    prom_d = false;
    prom_c = false;
    prom_t = false;
    joueur = j;
    if (strcmp(nom_coup,"p_rooc")==0){p_rock = true;}
    if (strcmp(nom_coup,"g_rooc")==0){g_rock = true;}

}

//Constructor for promotions
Coup_Echec::Coup_Echec(const char* nom_coup, const int y, const int x, const int mv_y, const int mv_x, const PieceColor C, const int j){

    joueur = j;
    couleur_c = C;
    p_rock = false;
    g_rock = false;
    prom_f = (strcmp(nom_coup,"prom_f")==0);
    prom_d = (strcmp(nom_coup,"prom_d")==0);
    prom_c = (strcmp(nom_coup,"prom_c")==0);
    prom_t = (strcmp(nom_coup,"prom_t")==0);
    init = {x, y};
    fin = {mv_x, mv_y};

}

void call_for_position(string* pos_init, string* pos_final)
{
    cout<<"Position de la piece a jouer ?"<<endl;
    cin >> *pos_init;

    cout<<"Position finale de la piece ?"<<endl;
    cin >> *pos_final;
}

void convert(const string pos_init, const string pos_fin, int& y, int& x, int& mv_y, int& mv_x)
{
    //Translate the letter of a move into an int between 0 and 7 included

    x = pos_init[0] - 65;
    mv_x = pos_fin[0] - 65;

    //Translate the figure of a move into an int between 0 and 7 included
    y = pos_init[1] - 49;
    mv_y = pos_fin[1] - 49;
}

bool is_valid_roi(const int i1, const int j1, const int i2, const int j2, const bool text)
{
    if (i2 == i1 && j2 == j1) {return false;}
    if (abs(i2 - i1) <= 1 && abs(j2 - j1) <= 1) {return true;}
    if (text) cout<<"Le mouvement de roi n'est pas conforme."<<endl;
    return false;
}

bool is_valid_fou(const int i1, const int j1, const int i2, const int j2, const bool text)
{
    if (i1 == i2) {if (text) cout<<"Le deplacement du fou n'est pas conforme."<<endl; return false;}
    if (abs(i1 - i2) == abs(j1 - j2)) {return true;}
    if (text) cout<<"Le deplacement du fou n'est pas conforme."<<endl;
    return false;
}

bool is_valid_tour(const int i1, const int j1, const int i2, const int j2, const bool text)
{
    if ((i1 == i2 && j1 != j2) || (j1 == j2 && i1 != i2)) {return true;}
    if (text) cout<<"Le deplacement de la tour n'est pas conforme."<<endl;
    return false;
}

bool is_valid_cavalier(const int i1, const int j1, const int i2, const int j2, const bool text)
{
    if (abs(j2 - j1) == 1 && abs(i2 - i1) == 2) {return true;}
    if (abs(i2 - i1) == 2 && abs(j2 - j1) == 1) {return true;}
    if (text) cout<<"Le deplacement du cavalier n'est pas conforme."<<endl;
    return false;
}

bool is_valid_dame(const int i1, const int j1, const int i2, const int j2, const bool text)
{
    if (abs(i1 - i2) == abs(j1 - j2) && i1 != i2) {return true;}
    if ((i1 == i2 && j1 != j2) || (j1 == j2 && i1 != i2)) {return true;}
    if (text) cout<<"Le deplacement de la dame n'est pas conforme."<<endl;
    return false;
}

bool is_valid_pion(const int y, const int x, const int mv_y, const int mv_x, const Piece* Pj, const Piece* Pp, const bool text)
{
    PieceColor C = Pj->Couleur;
    int m = (C == Blanc) ? 1 : -1;
    if ((mv_y == y + m) && (x == mv_x) && Pp == nullptr) {return true;}
    if (Pp != nullptr)
    {
        if (mv_y == y + m && mv_x == x + m) {return true;}
        else if (mv_y == y + m && mv_x == x - m) {return true;}
        else return false;
    }
    if (!Pj->a_bouge && mv_y == y + 2*m && x == mv_x) {return true;}
    if (text) cout<<"Le deplacement du pion n'est pas conforme."<<endl;
    return false;
}


//Display the move on a non-yet updated chessboard
void Coup_Echec::affichage_standard(const Echiquier* E) const{
    cout<<"(";
    if (p_rock == true){
        cout<<"o-o";
    }
    else if (g_rock == true){
        cout<<"o-o-o";
    }
    else{
        Piece* PJ = E->plateau[this->init[1]*8 + this->init[0]]; //this->init is empty if a rooc is played
        if (prom_d == true){
            cout<<"Dame en "<<alphat[fin[0]]<<fin[1] + 1;
        }
        else if (prom_c == true){
            cout<<"Cavalier en "<<alphat[fin[0]]<<fin[1] + 1;
        }
        else if (prom_f == true){
            cout<<"Fou en "<<alphat[fin[0]]<<fin[1] + 1;
        }
        else if (prom_t == true){
            cout<<"Tour en "<<alphat[fin[0]]<<fin[1] + 1;
        }
        else {
            if (PJ->P.Nom_piece == roi){
                cout<<"Roi";
            }
            if (PJ->P.Nom_piece == dame){
                cout<<"Dame";
            }
            if (PJ->P.Nom_piece == fou){
                cout<<"Fou";
            }
            if (PJ->P.Nom_piece == cavalier){
                cout<<"Cavalier";
            }
            if (PJ->P.Nom_piece == tour){
                cout<<"Tour";
            }
            if (PJ->P.Nom_piece == pion){
                cout<<"Pion";
            }
            if (PJ->Couleur == Blanc){
                cout<<" Blanc";
            }
            if (PJ->Couleur == Noir){
                cout<<" Noir";
            }
            cout<<" "<<alphat[init[0]]<<init[1] + 1;
            cout<<"-";
            cout<<alphat[fin[0]]<<fin[1] + 1;
        }
        if (echec){
            cout<<"+";
        }
        if (echec_mat){
            cout<<"++";
        }
    }
    cout<<")"<<endl;
}

void elimine_piece(Position_Echec& pos, Piece* Pprise, const Piece* const Pjoue, const bool text)
{
    Type_Piece pi = Pprise->P;
    Type_Piece pj = Pjoue->P;

    PieceColor Cprise = Pprise->Couleur;
    PieceColor Cjoue = Pjoue->Couleur;
    if (text){
        if (pi.Nom_piece == roi){
            cout<<"Le Roi";
        }
        if (pi.Nom_piece == dame){
            cout<<"La Dame";
        }
        if (pi.Nom_piece == fou){
            cout<<"Le Fou";
        }
        if (pi.Nom_piece == cavalier){
            cout<<"Le Cavalier";
        }
        if (pi.Nom_piece == tour){
            cout<<"La Tour";
        }
        if (pi.Nom_piece == pion){
            cout<<"Le Pion";
        }
        cout<<" en " << alphat[Pprise->x]<<Pprise->y + 1<<" est elimine par ";

        if (pj.Nom_piece == roi){
            cout<<"le Roi";
        }
        if (pj.Nom_piece == dame){
            cout<<"la Dame";
        }
        if (pj.Nom_piece == fou){
            cout<<"le Fou";
        }
        if (pj.Nom_piece == cavalier){
            cout<<"le Cavalier";
        }
        if (pj.Nom_piece == tour){
            cout<<"la Tour";
        }
        if (pj.Nom_piece == pion){
            cout<<"le Pion";
        }
        if (Cjoue == Blanc){
            cout<<" Blanc";
            pos.echiquier_ref->aliveB.remove(Pprise);
        }
        if (Cjoue == Noir){
            pos.echiquier_ref->aliveN.remove(Pprise);
            cout<<" Noir";
        }
    cout<<" en " << alphat[Pjoue->x]<<Pjoue->y + 1<<endl;
    }

    if (Cprise == Blanc){
        cout<<" Blanc";
        pos.echiquier_ref->aliveB.remove(Pprise);
    }
    if (Cprise == Noir){
        pos.echiquier_ref->aliveN.remove(Pprise);
        cout<<" Noir";
    }

    delete Pprise; //Free the previously allocated memory
}

bool interieur_plateau(int i,int j)
{
    if (i>= 0 && i<8 && j >=0 && j<8) return true;
    return false;
}

PieceColor inverse_color(const PieceColor C)
{
    switch(C)
    {
        case(Blanc): return Noir; break;
        case(Noir): return Blanc;
    }
}

string affiche_couleur(const PieceColor C)
{
    switch(C)
    {
        case(Blanc): return "Blanc"; break;
        case(Noir): return "Noir";
    }
}

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
        int val = minimax(*fille, alpha, beta, depth - 1);
        best = max(best, val);
//      Recur for her sisters
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
