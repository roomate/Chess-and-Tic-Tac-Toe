#include "chess.hpp"
#include <cmath>
#include <string>
#include <sstream>

string alphat = "ABCDEFGH";

//Copy constructor
coup_echec::coup_echec(const coup_echec &c){

    this->init = c.init;
    this->fin = c.fin;
    this->p_rooc = c.p_rooc;
    this->g_rooc = c.g_rooc;
    this->prom_f = c.prom_f;
    this->prom_d = c.prom_d;
    this->prom_c = c.prom_c;
    this->prom_t = c.prom_t;
    this->echec = c.echec;
    this->echec_mat = c.echec_mat;
}


//Constructor of a chess move when taking an opponent piece.
coup_echec::coup_echec(int i_init, int j_init, int i_final, int j_final){

    //Update the position of the piece
    p_rooc = false;
    g_rooc = false;
    prom_f = false;
    prom_d = false;
    prom_c = false;
    prom_t = false;

    init = {j_init, i_init};
    fin = {j_final, i_final};
}

//Constructor for a roocs move.
coup_echec::coup_echec(char const* nom_coup, PieceColor couleur){
    couleur_c = couleur;
    p_rooc = false;
    g_rooc = false;
    prom_f = false;
    prom_d = false;
    prom_c = false;
    prom_t = false;
    if (strcmp(nom_coup,"p_rooc")==0){p_rooc = true;}
    if (strcmp(nom_coup,"g_rooc")==0){g_rooc = true;}
}

//Constructor for promotions
coup_echec::coup_echec(char const* nom_coup, int i_init, int j_init, int i_final, int j_final){

    p_rooc = false;
    g_rooc = false;
    prom_f = (strcmp(nom_coup,"prom_f")==0);
    prom_d = (strcmp(nom_coup,"prom_d")==0);
    prom_c = (strcmp(nom_coup,"prom_c")==0);
    prom_t = (strcmp(nom_coup,"prom_t")==0);
    init = {j_init, i_init};
    fin = {j_final, i_final};
}

void call_for_position(string* pos_init, string* pos_final)
{
    cout<<"Position de la piece a jouer ?"<<endl;
    cin >> *pos_init;

    cout<<"Position finale de la piece ?"<<endl;
    cin >> *pos_final;
}

void convert(const string pos_init, const string pos_fin, int& i_init, int& j_init, int& i_final, int& j_final)
{
    //Translate the letter of a move into an int between 0 and 7 included

    j_init = pos_init[0] - 65;
    j_final = pos_fin[0] - 65;

    //Translate the figure of a move into an int between 0 and 7 included
    i_init = pos_init[1] - 49;
    i_final = pos_fin[1] - 49;
}

bool is_valid(const int i1, const int j1, const int i2, const int j2, const echiquier* chessboard, const bool text)
{
    type_piece tP = chessboard->plateau[i1*8 + j1]->P;
    switch(tP.Nom_piece)
    {
        case(Pion): {return is_valid_pion(i1, j1, i2, j2, chessboard, text);}
        case(Tour): {return is_valid_tour(i1, j1, i2, j2, text);}
        case(Fou): {return is_valid_fou(i1, j1, i2, j2, text);}
        case(Dame): {return is_valid_dame(i1, j1, i2, j2, text);}
        case(Cavalier): {return is_valid_cavalier(i1, j1, i2, j2, text);}
        case(Roi): {return is_valid_roi(i1, j1, i2, j2, chessboard, text);}
    }
    cout<<"Erreur, le type de la piece n'est pas conforme"<<endl;
    return false;
}

bool is_valid_pion(const int i1, const int j1, const int i2, const int j2, const echiquier* chessboard, const bool text)
{
    piece* pj = chessboard->plateau[i1*8 + j1];
    piece* piece_prise = chessboard->plateau[i2*8 + j2];
    PieceColor C = pj->Couleur;
    int m = (C == Blanc) ? 1 : -1;
    if ((i2 == i1 + m) && (j1 == j2) && piece_prise == nullptr) {return true;}
    if (piece_prise != nullptr)
    {
        if (i2 == i1 + m && j2 == j1 + m) {return true;}
        else if (i2 == i1 + m && j2 == j1 - m) {return true;}
    }
    if (!pj->a_bouge && i2 == i1 + 2*m && j1 == j2 && piece_prise == nullptr && chessboard->plateau[(i1 + m)*8 + j1] == nullptr) {return true;}
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

bool is_valid_roi(const int i1, const int j1, const int i2, const int j2, const echiquier* chessboard, const bool text)
{
    piece* pj = chessboard->plateau[i1*8 + j1];
    if (i2 == i1 && j2 == j1) {return false;}
    if (abs(i2 - i1) <= 1 && abs(j2 - j1) <= 1) {pj->a_bouge = true; return true;}
    if (text) cout<<"Le mouvement de roi n'est pas conforme."<<endl;
    return false;
}

//Display the move on a non-yet updated chessboard
void coup_echec::affichage_standard(const echiquier* E) const{
    cout<<"(";
    if (p_rooc == true){
        cout<<"o-o";
    }
    else if (g_rooc == true){
        cout<<"o-o-o";
    }
    else{
        piece* PJ = E->plateau[this->init[1]*8 + this->init[0]]; //this->init is empty if a rooc is played
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
            if (PJ->P.Nom_piece == Roi){
                cout<<"Roi";
            }
            if (PJ->P.Nom_piece == Dame){
                cout<<"Dame";
            }
            if (PJ->P.Nom_piece == Fou){
                cout<<"Fou";
            }
            if (PJ->P.Nom_piece == Cavalier){
                cout<<"Cavalier";
            }
            if (PJ->P.Nom_piece == Tour){
                cout<<"Tour";
            }
            if (PJ->P.Nom_piece == Pion){
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

void elimine_piece(Position_Echec& pos, piece* Pprise, const piece* const Pjoue, const bool text)
{
    type_piece pi = Pprise->P;
    type_piece pj = Pjoue->P;

    PieceColor Cprise = Pprise->Couleur;
    PieceColor Cjoue = Pjoue->Couleur;
    if (text){
        if (pi.Nom_piece == Roi){
            cout<<"Le Roi";
        }
        if (pi.Nom_piece == Dame){
            cout<<"La Dame";
        }
        if (pi.Nom_piece == Fou){
            cout<<"Le Fou";
        }
        if (pi.Nom_piece == Cavalier){
            cout<<"Le Cavalier";
        }
        if (pi.Nom_piece == Tour){
            cout<<"La Tour";
        }
        if (pi.Nom_piece == Pion){
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

        if (pj.Nom_piece == Roi){
            cout<<"le Roi";
        }
        if (pj.Nom_piece == Dame){
            cout<<"la Dame";
        }
        if (pj.Nom_piece == Fou){
            cout<<"le Fou";
        }
        if (pj.Nom_piece == Cavalier){
            cout<<"le Cavalier";
        }
        if (pj.Nom_piece == Tour){
            cout<<"la Tour";
        }
        if (pj.Nom_piece == Pion){
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

////Overload of operator =
//coup_echec &coup_echec::operator=(const coup_echec &c){
//    if (c.PJ!=nullptr)
//    {
//        piece* p_temp = new piece(c.PJ->P.Nom_piece,c.PJ->Couleur,c.PJ->x,c.PJ->y);
//        this->PJ = p_temp;
//    }
//    if (c.Pprise != nullptr)
//    {
//        piece* pprise_temp = new piece(c.Pprise->P.Nom_piece,c.Pprise->Couleur,c.Pprise->x,c.Pprise->y);
//        this->Pprise = pprise_temp;
//    }
//    this->couleur_c = c.couleur_c;
//    this->i1 = c.i1;
//    this->i2 = c.i2;
//    this->j1 = c.j1;
//    this->j2 = c.j2;
//    this->p_rooc = c.p_rooc;
//    this->g_rooc = c.g_rooc;
//    this->prom_f = c.prom_f;
//    this->prom_d = c.prom_d;
//    this->prom_c = c.prom_c;
//    this->prom_t = c.prom_t;
//    this->echec = c.echec;
//    this->echec_mat = c.echec_mat;
//    return *this;
//
//}

////Constructor of a chess move when the coordinate of a piece changes.
//coup_echec::coup_echec(piece* piece_jouee,int x_init, int y_init, int x_final, int y_final){
//    if (piece_jouee!=nullptr){
//        piece* p_temp = new piece(piece_jouee->P.Nom_piece,piece_jouee->Couleur,piece_jouee->x,piece_jouee->y);
//        PJ = p_temp;
//    }
//    p_rooc = false;
//    g_rooc = false;
//    prom_f = false;
//    prom_d = false;
//    prom_c = false;
//    prom_t = false;
//    i1 = x_init;
//    i2 = x_final;
//    j2 = y_final;
//    j1 = y_init;
//    couleur_c = piece_jouee->Couleur;
//}

////Constructor of a move promoting a piece.
//coup_echec::coup_echec(char const* nom_coup,piece* piece_jouee,int x_init, int y_init, int x_final, int y_final){
//    if (piece_jouee!=nullptr){
//        piece* p_temp = new piece(piece_jouee->P.Nom_piece,piece_jouee->Couleur,piece_jouee->x,piece_jouee->y);
//        PJ = p_temp;
//    }
//    couleur_c = piece_jouee->Couleur;
//    p_rooc = false;
//    g_rooc = false;
//    prom_f = false;
//    prom_d = false;
//    prom_c = false;
//    prom_t = false;
//    if (strcmp(nom_coup,"prom_f")==0){prom_f = true;}
//    if (strcmp(nom_coup,"prom_d")==0){prom_d = true;}
//    if (strcmp(nom_coup,"prom_c")==0){prom_c = true;}
//    if (strcmp(nom_coup,"prom_t")==0){prom_t = true;}
//    i1 = x_init;
//    i2 = x_final;
//    j2 = y_final;
//    j1 = y_init;
//    couleur_c = piece_jouee->Couleur;
//}


