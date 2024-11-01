#include "chess.hpp"
#include <cmath>
#include <string>
#include <sstream>

string alphat = "ABCDEFGH";

//Copy constructor
Coup_Echec::Coup_Echec(const Coup_Echec &c){

    this->init = c.init;
    this->fin = c.fin;
    this->p_rock = c.p_rock;
    this->g_rock = c.g_rock;
    this->prom_f = c.prom_f;
    this->prom_d = c.prom_d;
    this->prom_c = c.prom_c;
    this->prom_t = c.prom_t;
    this->echec = c.echec;
    this->echec_mat = c.echec_mat;
}


//Constructor of a chess move when taking an opponent piece.
Coup_Echec::Coup_Echec(int y, int x, int mv_y, int mv_x){

    //Update the position of the piece
    p_rock = false;
    g_rock = false;
    prom_f = false;
    prom_d = false;
    prom_c = false;
    prom_t = false;

    init = {x, y};
    fin = {mv_x, mv_y};
}

//Constructor for a roocs move.
Coup_Echec::Coup_Echec(const char* nom_coup, PieceColor couleur){
    couleur_c = couleur;
    p_rock = false;
    g_rock = false;
    prom_f = false;
    prom_d = false;
    prom_c = false;
    prom_t = false;
    if (strcmp(nom_coup,"p_rooc")==0){p_rock = true;}
    if (strcmp(nom_coup,"g_rooc")==0){g_rock = true;}

}

//Constructor for promotions
Coup_Echec::Coup_Echec(const char* nom_coup, int y, int x, int mv_y, int mv_x){

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

bool is_valid(const int y, const int x, const int mv_y, const int mv_x, const Echiquier* chessboard, const bool text)
{
    Type_Piece tP = chessboard->plateau[y*8 + x]->P;
    switch(tP.Nom_piece)
    {
        case(pion): {return is_valid_pion(y, x, mv_y, mv_x, chessboard, text);}
        case(tour): {return is_valid_tour(y, x, mv_y, mv_x, text);}
        case(fou): {return is_valid_fou(y, x, mv_y, mv_x, text);}
        case(dame): {return is_valid_dame(y, x, mv_y, mv_x, text);}
        case(cavalier): {return is_valid_cavalier(y, x, mv_y, mv_x, text);}
        case(roi): {return is_valid_roi(y, x, mv_y, mv_x, chessboard, text);}
    }
    if (text) cout<<"Erreur, le type de la piece n'est pas conforme"<<endl;
    return false;
}

bool is_valid_pion(const int y, const int x, const int mv_y, const int mv_x, const Echiquier* chessboard, const bool text)
{
    Piece* pj = chessboard->plateau[y*8 + x];
    Piece* piece_prise = chessboard->plateau[mv_y*8 + mv_x];
    PieceColor C = pj->Couleur;
    int m = (C == Blanc) ? 1 : -1;
    if ((mv_y == y + m) && (x == mv_x) && piece_prise == nullptr) {return true;}
    if (piece_prise != nullptr)
    {
        if (mv_y == y + m && mv_x == x + m) {return true;}
        else if (mv_y == y + m && mv_x == x - m) {return true;}
    }
    if (!pj->a_bouge && mv_y == y + 2*m && x == mv_x && piece_prise == nullptr && chessboard->plateau[(y + m)*8 + x] == nullptr) {return true;}
    if (text) cout<<"Le deplacement du pion n'est pas conforme."<<endl;
    return false;
}

bool is_valid_fou(const int i1, const int j1, const int i2, const int j2, const bool text)
{
    if (i1 == i2) {cout<<"Le deplacement du fou n'est pas conforme."<<endl; return false;}
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

bool is_valid_roi(const int i1, const int j1, const int i2, const int j2, const Echiquier* chessboard, const bool text)
{
    Piece* pj = chessboard->plateau[i1*8 + j1];
    if (i2 == i1 && j2 == j1) {return false;}
    if (abs(i2 - i1) <= 1 && abs(j2 - j1) <= 1) {pj->a_bouge = true; return true;}
    if (text) cout<<"Le mouvement de roi n'est pas conforme."<<endl;
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
        if (Cprise == Blanc){
            cout<<" Blanc";
            pos.echiquier_ref->aliveB.remove(Pprise);
        }
        if (Cprise == Noir){
            pos.echiquier_ref->aliveN.remove(Pprise);
            cout<<" Noir";
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
    delete Pprise; //Free the previously allocated memory
}


