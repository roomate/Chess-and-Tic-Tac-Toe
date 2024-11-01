#include "chess.hpp"
#include <cmath>
#include <string>
#include <sstream>
//====================================

const int alpha = 1;
const int beta = 1;

const int MAX = 1000000;
const int MIN = -1000000;
const string Normal("N");
const string Special("SPECIAL");
const vector<string> list_move = {Normal,Special};
const string alphat = "ABCDEFGH";
string p_rock = "p_rooc";
string g_rock = "g_rooc";
string prom_t = "prom_t";
string prom_d = "prom_d";
string prom_c = "prom_c";
string prom_f = "prom_f";
string Nul = "nul";

vector<string> special_moves = {p_rock, g_rock, prom_t, prom_d, prom_c, prom_f, Nul};



///====================================
///==== Methods of Position_Echec =====
///====================================

//Update  the chessboard for a specific: v
void Position_Echec::mise_a_jour_coup(const Coup_Echec& move_chess, const bool text)
{

    PieceColor C = this->couleur_joueur;
    if (move_chess.g_rock)
    {
        if (text) cout<<"Grand rooc"<<endl;
        Piece* temp;
        if (C == Blanc)
        {
            echiquier_ref->plateau[7]->x = 3; echiquier_ref->plateau[3]->x = 7;
            echiquier_ref->plateau[7]->a_bouge = true; echiquier_ref->plateau[3]->a_bouge = true;
            //Swap
            temp = echiquier_ref->plateau[7]; //Take the white left tower
            echiquier_ref->plateau[7] = echiquier_ref->plateau[3];
            echiquier_ref->plateau[3] = temp;
            return;
        }
        else if (C == Noir)
        {
            echiquier_ref->plateau[63]->x = 3; echiquier_ref->plateau[59]->x = 7;
            echiquier_ref->plateau[63]->a_bouge = true; echiquier_ref->plateau[59]->a_bouge = true;
            //Swap
            temp = echiquier_ref->plateau[63]; //Take the black left tower
            echiquier_ref->plateau[63] = echiquier_ref->plateau[59];
            echiquier_ref->plateau[59] = temp;
            return;
        }
    }
    if (move_chess.p_rock)
    {
        if (text) cout<<"Petit rooc"<<endl;
        Piece* temp;
        if (C == Blanc)
        {
            echiquier_ref->plateau[0]->x = 3; echiquier_ref->plateau[3]->x = 0;
            echiquier_ref->plateau[0]->a_bouge = true; echiquier_ref->plateau[3]->a_bouge = true;
            //Swap
            temp = echiquier_ref->plateau[0]; //Take the white right tower
            echiquier_ref->plateau[0] = echiquier_ref->plateau[3];
            echiquier_ref->plateau[3] = temp;
            return;
        }
        else if (C == Noir)
        {
            echiquier_ref->plateau[56]->x = 3; echiquier_ref->plateau[59]->x = 0;
            echiquier_ref->plateau[56]->a_bouge = true; echiquier_ref->plateau[59]->a_bouge = true;
            //Swap
            temp = echiquier_ref->plateau[56]; //Take the black right tower
            echiquier_ref->plateau[56] = echiquier_ref->plateau[59];
            echiquier_ref->plateau[59] = temp;
            return;
        }
    }
    Piece* Pprise = echiquier_ref->plateau[move_chess.fin[1]*8 + move_chess.fin[0]];
    Piece* Pjoue = echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]];
    if (move_chess.prom_c)
    {
        if (text) cout<<"Promotion d'un pion en cavalier"<<endl;

//      If a piece lies at this position
        if (Pprise!=nullptr){
            elimine_piece(*this, Pprise, Pjoue, text);
        }
        Piece* promoted = echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]];

        echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]] = nullptr; //Set it to 0
        Piece* tmp = new Piece(cavalier, C, move_chess.fin[1], move_chess.fin[0], 1);
        tmp->a_bouge = true;
        echiquier_ref->plateau[move_chess.fin[1]*8 + move_chess.fin[0]] = tmp;

        switch(C) {
        case(Blanc) : echiquier_ref->aliveB.push_front(tmp); echiquier_ref->aliveB.remove(promoted);
        case(Noir) : echiquier_ref->aliveN.push_front(tmp); echiquier_ref->aliveN.remove(promoted);
        }
        delete promoted; //Delete the memory allocated for this piece

        return;
    }
    if (move_chess.prom_d)
    {
        if (text) cout<<"Promotion d'un pion en dame"<<endl;

        //If a piece lies at this position
        if (Pprise!=nullptr){
            elimine_piece(*this, Pprise, Pjoue, text);
        }

        Piece* promoted = echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]];

        echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]] = nullptr;
        Piece* tmp = new Piece(dame, C, move_chess.fin[1], move_chess.fin[0], 1);
        tmp->a_bouge = true;
        echiquier_ref->plateau[move_chess.fin[1]*8 + move_chess.fin[0]] = tmp;

        switch(C) {
        case(Blanc) : echiquier_ref->aliveB.push_front(tmp); echiquier_ref->aliveB.remove(promoted);
        case(Noir) : echiquier_ref->aliveN.push_front(tmp); echiquier_ref->aliveN.remove(promoted);
        }

        delete promoted; //Delete the memory allocated for this piece
        return;
    }
    if (move_chess.prom_t)
    {
        if (text) cout<<"Promotion d'un pion en tour"<<endl;
        //If a piece lies at this position
        if (Pprise!=nullptr){
            elimine_piece(*this, Pprise, Pjoue, text);
        }
        Piece* promoted = echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]];

        echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]] = nullptr;
        Piece* tmp = new Piece(tour, C, move_chess.fin[1], move_chess.fin[0], 1);
        tmp->a_bouge = true;
        echiquier_ref->plateau[move_chess.fin[1]*8 + move_chess.fin[0]] = tmp;

        switch(C) {
        case(Blanc) : echiquier_ref->aliveB.push_front(tmp); echiquier_ref->aliveB.remove(promoted);
        case(Noir) : echiquier_ref->aliveN.push_front(tmp); echiquier_ref->aliveN.remove(promoted);
        }

        delete promoted; //Delete the memory allocated for this piece
        return;
    }
    if (move_chess.prom_f)
    {
        if (text) cout<<"Promotion d'un pion en fou"<<endl;
        //If a piece lies at this position
        if (Pprise!=nullptr){
            elimine_piece(*this, Pprise, Pjoue, text);
        }
        Piece* promoted = echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]];

        echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]] = nullptr; //Set it as nullptr
        Piece* tmp = new Piece(fou, C, move_chess.fin[1], move_chess.fin[0], 1);
        tmp->a_bouge = true;
        echiquier_ref->plateau[move_chess.fin[1]*8 + move_chess.fin[0]] = tmp;

        switch(C) {
        case(Blanc) : echiquier_ref->aliveB.push_front(tmp); echiquier_ref->aliveB.remove(promoted);
        case(Noir) : echiquier_ref->aliveN.push_front(tmp); echiquier_ref->aliveN.remove(promoted);
        }

        delete promoted; //Delete the memory allocated for this piece

        return;
    }
//     If a piece lies at this position
    if (Pprise!=nullptr){
        elimine_piece(*this, Pprise, Pjoue, text);
    }
    //Change the position of the piece
    echiquier_ref->plateau[move_chess.fin[1]*8 + move_chess.fin[0]] = echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]];

    //Update the position of the piece
    echiquier_ref->plateau[move_chess.fin[1]*8 + move_chess.fin[0]]->x = move_chess.fin[0];
    echiquier_ref->plateau[move_chess.fin[1]*8 + move_chess.fin[0]]->y = move_chess.fin[1];
    echiquier_ref->plateau[move_chess.fin[1]*8 + move_chess.fin[0]]->a_bouge = true;

    echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]] = nullptr; //Points towards nullptr
}

//Given a position Position_Echec and a list List_coup, it has to update the chess accordingly: v
void Position_Echec::mise_a_jour_position(const bool text)
{
    for (list<Coup_Echec>::iterator it = Liste_coup.begin(); it != Liste_coup.end(); ++it){this->mise_a_jour_coup(*it, text);}
    Liste_coup.clear();
}


double Position_Echec::valeur_position(){
    int J = this->joueur;
    PieceColor C = this->couleur_joueur;
    bool check = this->echec(C);
    bool check_mat;
    if (check) check_mat = this->echec_mat(this->couleur_joueur);
    list<Piece*> aliveJ1;
    list<Piece*> aliveJ2;
    if ((J == 1 && C == Blanc) || (J == 2 && C == Noir)) {aliveJ1 = this->echiquier_ref->aliveB; aliveJ2 = this->echiquier_ref->aliveN;}
    else {aliveJ2 = this->echiquier_ref->aliveB; aliveJ1 = this->echiquier_ref->aliveN;}
    int Count_J1 = aliveJ1.size();
    int Count_J2 = aliveJ2.size();
    int val;
    list<Piece*>::const_iterator it;
    switch (J)
    {
        case(1): if(check_mat) return MAX;
        case(2): if(check_mat) return MIN;
    }
    val = beta*(Count_J1 - Count_J2);
    for (it = aliveJ1.begin(); it != aliveJ1.end(); ++it) {val += alpha*((*it)->P.valeur);}
    for (it = aliveJ2.begin(); it != aliveJ2.end(); ++it) {val -= alpha*((*it)->P.valeur);}
    return val;
}

///Check if the player is in check position: v
bool Position_Echec::echec(const PieceColor C) const {

    int m = 2;
    vector<vector<int>> Dep;
    Piece* roi = (C == Blanc) ? this->echiquier_ref->roi_N : this->echiquier_ref->roi_B; //Find the threatened king
    list<Piece*> alive = (C == Blanc) ? this->echiquier_ref->aliveB : this->echiquier_ref->aliveN; //Which set of piece?
    list<Piece*>::const_iterator it;
    bool is_ok;

    int mv_x; int mv_y; bool multi;
    int new_pos_x; int new_pos_y;

    int b = (C == Blanc) ? 1 : -1;

    PieceType nom;

    for (it = alive.begin(); it != alive.end(); ++it) //for every remaining piece
    {
        Dep = (*it)->P.Dep_rel;
        nom = (*it)->P.Nom_piece;

        if (nom == pion) Dep = {{1, 1}, {1, -1}, {1,1}}; //Attacks allowed

        for (int i = 0; i < Dep[0].size(); ++i) { //For every potential move

            mv_x = Dep[0][i]; mv_y = Dep[1][i]; multi = Dep[2][i];

            new_pos_x = (*it)->x + b*mv_x; new_pos_y = (*it)->y + b*mv_y;

            is_ok = is_valid_move((*it)->y, (*it)->x, new_pos_y, new_pos_x, C, 0);

            if (is_ok && new_pos_x == roi->x && new_pos_y == roi->y) {return true;}

            if (!multi && is_ok){
                m = 2;
                new_pos_x = (*it)->x + m*b*mv_x; new_pos_y = (*it)->y + m*b*mv_y;
                is_ok = is_valid_move((*it)->y, (*it)->x, new_pos_y, new_pos_x, C, 0);
                while (is_ok)
                {
                    if (new_pos_x == roi->x && new_pos_y == roi->y) return true;
                    m++;
                    new_pos_x = (*it)->x + m*b*mv_x; new_pos_y = (*it)->y + m*b*mv_y;
                    is_ok = is_valid_move((*it)->y, (*it)->x, new_pos_y, new_pos_x, C, 0);
                }
            }
        }
    }
    return false;
}

//Check if a position is checkmate. C is the color of the player trying to checkmate the other.
bool Position_Echec::echec_mat(const PieceColor C) const{ //NOTE: The simple check is assumed to already have been tested: v
    Piece* roi = (C == Blanc) ? this->echiquier_ref->roi_N : this->echiquier_ref->roi_B;
    PieceColor AntiC = (C == Blanc) ? Noir : Blanc;
    vector<vector<int>> Del = roi->P.Dep_rel;
    int siz = Del[0].size();
    int x_mv; int y_mv;
    bool is_valid;
    for (int i = 0; i < siz; ++i)
    {
        x_mv = roi->x + Del[0][i]; y_mv = roi->y + Del[1][i];
        is_valid = is_valid_move(roi->y, roi->x, y_mv, x_mv, AntiC, 0);
        if (is_valid){
            if (!valid_check(roi->y, roi->x, y_mv, x_mv)) return false;
        }
    }
    return true;
}

///Check if a position is a draw: v
bool Position_Echec::test_match_nul() const{
    if (this->echiquier_ref->aliveB.empty() && this->echiquier_ref->aliveN.size() == 1) {return true;}
    if (this->echiquier_ref->aliveN.empty() && this->echiquier_ref->aliveB.size() == 1) {return true;}
    return false;
}

///Tells if a position is admissible for a small rooc
bool Position_Echec::p_rooc(const bool text) const{
    PieceColor C = this->couleur_joueur;
    Piece* t_roi;
    Piece* t_tour;
    Piece* piece1;
    Piece* piece2;
    switch(C)
    {
        case(Blanc): t_roi = this->echiquier_ref->plateau[3]; t_tour = this->echiquier_ref->plateau[0]; piece1 = this->echiquier_ref->plateau[1]; piece2 = this->echiquier_ref->plateau[2]; break;
        case(Noir): t_roi = this->echiquier_ref->plateau[59]; t_tour = this->echiquier_ref->plateau[56]; piece1 = this->echiquier_ref->plateau[57]; piece2 = this->echiquier_ref->plateau[58];
    }
    if (t_roi == nullptr || t_roi->a_bouge) {if (text) cout<<"Le roi a deja bouge, petit rooc impossible."<<endl;return false;}
    if (t_tour == nullptr || t_tour->a_bouge) {if (text) cout<<"La tour a deja bouge, petit rooc impossible."<<endl;return false;}
    if (t_roi->P.Nom_piece != roi) {if (text) cout<<"Le roi n'est pas a la bonne position."<<endl; return false;}
    if (t_tour->P.Nom_piece != tour) {if (text) cout<<"La Tour n'est pas a la bonne position."<<endl; return false;}
    if (piece1 != nullptr || piece2 != nullptr) {if (text) cout<<"Il y a des pieces sur le chemin, petit rooc impossible."<<endl; return false;}

    //Test if the small rock put the player's king in a check situation
    Coup_Echec Move_p_rock("p_rooc", this->couleur_joueur);
    Position_Echec pos_rock(*this);
    pos_rock.Liste_coup.push_front(Move_p_rock);
    pos_rock.mise_a_jour_position(0);
    if (pos_rock.echec(C)) {if (text){cout<<"Le rooc met le roi en position d'echec."<<endl;}; return false;}
    return true;
}

//Tells if a position is admissible for a big rooc
bool Position_Echec::g_rooc(const bool text) const{
    PieceColor C = this->couleur_joueur;
    Piece* t_roi;
    Piece* t_tour;
    Piece* piece1;
    Piece* piece2;
    Piece* piece3;
    switch(C)
    {
        case(Blanc): t_roi = this->echiquier_ref->plateau[3]; t_tour = this->echiquier_ref->plateau[7]; piece1 = this->echiquier_ref->plateau[4]; piece2 = this->echiquier_ref->plateau[5];  piece3 = this->echiquier_ref->plateau[6]; break;
        case(Noir): t_roi = this->echiquier_ref->plateau[59]; t_tour = this->echiquier_ref->plateau[63]; piece1 = this->echiquier_ref->plateau[60]; piece2 = this->echiquier_ref->plateau[61];  piece3 = this->echiquier_ref->plateau[62];
    }
    if (t_roi == nullptr || t_roi->a_bouge) {if (text) cout<<"Le roi a deja bouge, grand rooc impossible."<<endl;return false;}
    if (t_tour == nullptr || t_tour->a_bouge) {if (text) cout<<"La tour a deja bouge, grand rooc impossible."<<endl;return false;}
    if (t_roi->P.Nom_piece != roi) {if (text) cout<<"Le roi n'est pas a la bonne position."<<endl; return false;}
    if (t_tour->P.Nom_piece != tour) {if (text) cout<<"La Tour n'est pas a la bonne position."<<endl; return false;}
    if (piece1 != nullptr || piece2 != nullptr || piece3 != nullptr) {if (text) cout<<"Il y a des pieces sur le chemin, grand rooc impossible."<<endl; return false;}

    //Test if the big rock put the player's king in a check situation
    Coup_Echec Move_g_rooc("g_rooc", this->couleur_joueur);
    Position_Echec pos_rooc(*this);
    pos_rooc.Liste_coup.push_front(Move_g_rooc);
    pos_rooc.mise_a_jour_position(0);
    if (pos_rooc.echec(C)) {if (text) cout<<"Le rooc met le roi en position d'echec."<<endl; return false;}
    return true ;
}

///Put the move chosen by user in the move list and return a new chess position.
///Return false if everything went normal. Return true if the player made a wrong move and chose special instead of normal,
///because the special move is not authorized: v
bool Position_Echec::coup_humain(bool* nul){
    string reponse;
    PieceColor C = this->couleur_joueur;
    if (C==Blanc){
        cout<<"C'est au tour des blancs de jouer"<<endl;
    }
    if (C==Noir){
        cout<<"C'est au tour des noirs de jouer"<<endl;
    }

    cout<<"Coup special ou normal ?"<<endl;
    cin >> reponse;

    bool is_in = find_word(reponse, list_move);
    while(!is_in) {cout<<"Erreur. Choisissez un coup normal avec 'N' ou 'special' avec 'SPECIAL'."<<endl; cin >> reponse; is_in = find_word(reponse, list_move);}

    string pos_init; //Store the coordinates of initial position
    string pos_final; //Store the coordinates of final position

    bool valid = false; //Tell whether a move is valid or not

    if (reponse == Normal){

        int* pi_init = new int; int* pj_init = new int;
        int* pi_final = new int; int* pj_final = new int;

        int& i_init = *pi_init; int& j_init = *pj_init;
        int& i_final = *pi_final; int& j_final = *pj_final;

        //While the move is not valid
        while (!valid)
        {
            //Asking what to do
            call_for_position(&pos_init, &pos_final);
            convert(pos_init, pos_final, i_init, j_init, i_final, j_final);
            valid = (this->all_valid)(i_init, j_init, i_final, j_final, 1);
            if (!valid) {this->print_position();}
        }

        //Update the list of moves
        Coup_Echec coup_joue(i_init, j_init, i_final, j_final);
        coup_joue.affichage_standard(this->echiquier_ref);
        (this->Liste_coup).push_back(coup_joue);
        list<Coup_Echec>::iterator it;
        delete pi_init; delete pj_init; delete pi_final; delete pj_final;
    }
    if (reponse == Special){
        cout<<"lequel ? : g_rooc , p_rooc , prom_t , prom_d , prom_c , prom_f, nul, stop"<<endl;
        string reponse_S;

        bool is_authorized; //Boolean to check the special move is actually possible according the the game's rules

        cin >> reponse_S;

        //If typed wrong
        is_in = find_word(reponse_S, special_moves);
        while(!is_in)
        {
            cout << "Le coup special entre n'existe pas, reessayez."<< endl;
            cin >> reponse_S;
            is_in = find_word(reponse_S, special_moves);
        }

        //Update the list of moves
        if(reponse_S == p_rock ){
            //Check if it is authorized
            is_authorized = this->p_rooc(1);

            if (is_authorized)
            {
                Coup_Echec coup_joue("p_rooc", this->couleur_joueur);
                coup_joue.affichage_standard(this->echiquier_ref); //Display the move
                this->Liste_coup.push_back(coup_joue);
            }
            else return true;
        }
        if(reponse_S == g_rock ){
            //Check if it is authorized
            is_authorized = this->g_rooc(1);;

            if (is_authorized)
            {
                Coup_Echec coup_joue("g_rooc",this->couleur_joueur);
                coup_joue.affichage_standard(this->echiquier_ref); //Display the move
                this->Liste_coup.push_back(coup_joue);
            }
            else return true;
        }
        else if (reponse_S == Nul){
            switch(C)
            {
                case Blanc : cout<<"Les blancs abandonnent"<<endl; break;
                case Noir : cout<<"Les noirs abandonnent"<<endl;
            }
            *nul = true;
            return false;
        }
        else if (reponse_S == prom_c || reponse_S == prom_f || reponse_S == prom_t || reponse_S == prom_d){
            int* pi_init = new int; int* pj_init = new int;
            int* pi_final = new int; int* pj_final = new int;

            int& i_init = *pi_init; int& j_init = *pj_init;
            int& i_final = *pi_final; int& j_final = *pj_final;

            while(!valid)
            {
                //Ask for the initial and final position
                call_for_position(&pos_init, &pos_final);
                convert(pos_init, pos_final, i_init, j_init, i_final, j_final);
                valid = (this->all_valid)(i_init, j_init, i_final, j_final, 1);
                if (!valid) this->print_position();
            }

            //Check if it is actually on the second or before-last row.
            if (this->echiquier_ref->plateau[8*i_init + j_init]->P.Nom_piece != pion) {cout<<"La promotion ne s'effectue que sur les pions."<<endl; return true;}

            //Check if the promotion actually concerns a pawn.
            if (C == Blanc && i_final != 7) {cout<<"La piece doit atteindre la derniere ligne du plateau."<<endl; return true ;}
            if (C == Noir && i_final != 0) {cout<<"La piece doit atteindre la premiere ligne du plateau."<<endl;return true;}

            //Update the list of moves
            if(reponse_S == prom_c){
                Coup_Echec coup_joue("prom_c",i_init,j_init,i_final,j_final);
                coup_joue.affichage_standard(this->echiquier_ref);
                this->Liste_coup.push_front(coup_joue);
                return false;
            }
            if(reponse_S == prom_f){
                Coup_Echec coup_joue("prom_f", i_init, j_init, i_final, j_final);
                coup_joue.affichage_standard(this->echiquier_ref);
                this->Liste_coup.push_front(coup_joue);
                return false;
            }
            if(reponse_S == prom_d){
                Coup_Echec coup_joue("prom_d", i_init, j_init, i_final, j_final);
                coup_joue.affichage_standard(this->echiquier_ref);
                this->Liste_coup.push_front(coup_joue);
                return false;
            }
            if(reponse_S == prom_t){

                Coup_Echec coup_joue("prom_t", i_init, j_init, i_final, j_final);
                coup_joue.affichage_standard(this->echiquier_ref);
                this->Liste_coup.push_front(coup_joue);
                return false;
            }
            delete pi_init; delete pj_init; delete pi_final; delete pj_final;
        }
    }
    return false;
}


bool Position_Echec::valid_check(const int& y, const int& x, const int& mv_y, const int& mv_x) const{
    Coup_Echec mv_checkmate(y, x, mv_y, mv_x);
    Position_Echec checkmate(*this);//We make a copy because we do not want to modify the original chessboard
    checkmate.Liste_coup.push_front(mv_checkmate);
    checkmate.mise_a_jour_position(0);
    switch(this->couleur_joueur) //We need to swap colors because we want to see if the player's king is check after moving, not the opponent's,
    //which is assumed by the method test_check.
    {
        case Blanc : return checkmate.echec(Noir); break; //Tell if the new position is check
        case Noir : return checkmate.echec(Blanc);
    }
}

///Check 5 things:
///     -The piece remains inside the chessboard
///     -There is actually a piece at this position (when the human plays)
///     -One does not pick an opponent's piece
///     -The piece is not moved towards an ally's position
///     -There is no piece in its path
bool Position_Echec::is_valid_move(const int& y, const int& x, const int& mv_y, const int& mv_x, const PieceColor C, const bool text) const
{
    bool valid_move_init = interieur_plateau(y,x);
    bool valid_move_fin = interieur_plateau(mv_y,mv_x);

    //Out of the board
    if ((!valid_move_init) || (!valid_move_fin)) {if (text) {cout<< "La position initiale ou finale n'est pas a l'interieur du plateau."<<endl;} return false;}

    Piece* pos_init = this->echiquier_ref->plateau[8*y + x];

    //There is no piece at this position
    if (pos_init == nullptr) {if (text) {cout<<"Il n'y a pas de piece a cette position"<<endl;} return false;}

    //If this is an opponent's piece
    if (C != pos_init->Couleur) {if (text) {cout<<"Il s'agit d'une piece de l'adversaire"<<endl;} return false;}

    Piece* pos_final = this->echiquier_ref->plateau[8*mv_y + mv_x];

    if (pos_final != nullptr && pos_final->Couleur == C) {if (text) {cout<<"On ne mange pas ses allies!!"<<endl;} return false;}
    int te = pos_init->P.Dep_rel[2][0];
    if (!pos_init->P.Dep_rel[2][0])
    {
        int diff_y;
        int diff_x;
        if (mv_y - y > 0) diff_y = 1; else if (mv_y - y == 0) diff_y = 0; else diff_y = -1;
        if (mv_x - x > 0) diff_x = 1; else if (mv_x - x == 0) diff_x = 0; else diff_x = -1;
        int counter = 1;
        while (x + diff_x*counter != mv_x || y + diff_y*counter != mv_y) {
            if ((this->echiquier_ref->plateau)[8*(y + diff_y*counter) + x + diff_x*counter] != nullptr) {if (text) cout<<"Il y a une autre piece sur le chemin."<<endl; return false;}
            ++counter;
        }
    }
    return true;
}

//Check if a move is overall valid: v
bool Position_Echec::all_valid(const int& y, const int& x, const int& mv_y, const int& mv_x, const bool text) const
{
    if (!is_valid_move(y, x, mv_y, mv_x, this->couleur_joueur ,text)) {return false;}

    else
    {
        //Check whether the move is conform or not to the rules
        bool valid_move = is_valid(y, x, mv_y, mv_x, this->echiquier_ref, text);
        if (!valid_move) return false;
        //Check whether the move put the player's king into a check position
        bool valid_chec = valid_check(y, x, mv_y, mv_x);
        if (valid_chec) {cout<<"Ce coup mene le roi en echec."<<endl; return false;}
    }
    return true;
}


//On se sert des listes alive pour deux methodes, position_possible et test_echec. Dans ces deux cas, on doit avoir une vision globale
//Du plateau et repérer le roi facilement.

Position* Position_Echec::position_possible()
{
    PieceColor C = couleur_joueur;
    list<Piece*> alive = (C == Blanc) ? this->echiquier_ref->aliveB : this->echiquier_ref->aliveN;
    list<Piece*>::const_iterator it;
    vector<vector<int>> Del;

    int b = (C == Blanc) ? 1 : -1;

    int prom = (C == Blanc) ? 7 : 0;

    int x; int y;

    int mv_x; int mv_y; bool multi;

    int siz; int m;

    bool valid;

    bool rooc_authorized;

    PieceType name;
    for (it = alive.begin(); it != alive.end(); it++)
    {
        x = (*it)->x; y = (*it)->y;
        Del = (*it)->P.Dep_rel;
        siz = Del[0].size();
        for (int i = 0; i < siz; ++i)
        {
            name = (*it)->P.Nom_piece;
            mv_x = x + b*Del[0][i]; mv_y = y + b*Del[1][i];
            multi = Del[2][i];
            valid = this->all_valid(y, x, mv_y, mv_x, 0); //Check if the movement is valid
            if (valid)
            {
                this->ajoute_fille(y, x, mv_y, mv_x);
            }
            m = 2;
            while (!multi && valid)
            {
                mv_x = x + m*b*Del[0][i]; mv_y = y + m*b*Del[1][i];
                valid = this->all_valid(y, x, mv_y, mv_x, 0); //Check if the movement is valid
                if (valid)
                {
                    this->ajoute_fille(y, x, mv_y, mv_x);
                }
                m++;
            }
            if (name == pion && mv_y == prom && valid)
            {
                this->ajoute_fille("prom_c", y, x, mv_y, mv_x);
                this->ajoute_fille("prom_d", y, x, mv_y, mv_x);
                this->ajoute_fille("prom_t", y, x, mv_y, mv_x);
                this->ajoute_fille("prom_f", y, x, mv_y, mv_x);
            }
        }
    }
    rooc_authorized = this->g_rooc(0);
    if (rooc_authorized) ajoute_fille("g_rooc");
    rooc_authorized = this->p_rooc(0);
    if (rooc_authorized) ajoute_fille("p_rooc");
    return this->fille;
}

//Il pourrait être intéressant de ne faire la mise-a-jour qu'une

void Position_Echec::ajoute_fille(const int y, const int x, const int mv_y, const int mv_x)
{
    Position_Echec* new_move;
    new_move = new Position_Echec(*this); //Call to copy constructor
    new_move->couleur_joueur = (couleur_joueur == Blanc) ? Noir : Blanc;
    new_move->joueur = (joueur == 1) ? 2 : 1;
    Coup_Echec mv_checkmate(y, x, mv_y, mv_x);
    new_move->Liste_coup.push_front(mv_checkmate);
    new_move->mise_a_jour_position(0);
    Position* tmp = this->fille;
    this->fille = new_move;
    new_move->soeur = tmp;
}

void Position_Echec::ajoute_fille(const char* Prom, const int y, const int x, const int mv_y, const int mv_x)
{
    Position_Echec* new_move = nullptr;
    new_move = new Position_Echec(*this);
    new_move->couleur_joueur = (couleur_joueur == Blanc) ? Noir : Blanc;
    Coup_Echec mv_checkmate(Prom, y, x, mv_y, mv_x);
    new_move->Liste_coup.push_front(mv_checkmate);
    new_move->mise_a_jour_position(0);
    Position* tmp = this->fille;
    this->fille = new_move;
    new_move->soeur = tmp;
}

void Position_Echec::ajoute_fille(const char* rooc)
{
    Position_Echec* new_move = nullptr;
    new_move = new Position_Echec(*this);
    new_move->couleur_joueur = (couleur_joueur == Blanc) ? Noir : Blanc;
    Coup_Echec mv_checkmate(rooc,this->couleur_joueur);
    new_move->Liste_coup.push_front(mv_checkmate);
    new_move->mise_a_jour_position(0);
    Position* tmp = this->fille;
    this->fille = new_move;
    new_move->soeur = tmp;
}

///=====================================
///== chessboard Constructors ==========
///=====================================

///Initialize the chessboard
void echiquier_depart(Echiquier& E){
    Piece* P_0 = new Piece(tour,Blanc,0,0);
    E.plateau[0]= P_0;
    Piece* P_1 = new Piece(cavalier,Blanc,0,1);
    E.plateau[1]= P_1;
    Piece* P_2= new Piece(fou,Blanc,0,2);
    E.plateau[2]= P_2;
    Piece* P_3= new Piece(roi,Blanc,0,3);
    E.plateau[3]= P_3;
    Piece* P_4= new Piece(dame,Blanc,0,4);
    E.plateau[4]= P_4;
    Piece* P_5= new Piece(fou,Blanc,0,5);
    E.plateau[5]= P_5;
    Piece* P_6= new Piece(cavalier,Blanc,0,6);
    E.plateau[6]= P_6;
    Piece* P_7= new Piece(tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        Piece* temp_P= new Piece(pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    Piece* P_56 = new Piece(tour,Noir,7,0);
    E.plateau[56]= P_56;
    Piece* P_57 = new Piece(cavalier,Noir,7,1);
    E.plateau[57]= P_57;
    Piece* P_58 = new Piece(fou,Noir,7,2);
    E.plateau[58]= P_58;
    Piece* P_59= new Piece(roi,Noir,7,3);
    E.plateau[59]= P_59;
    Piece* P_60= new Piece(dame,Noir,7,4);
    E.plateau[60]= P_60;
    Piece* P_61= new Piece(fou,Noir,7,5);
    E.plateau[61]= P_61;
    Piece* P_62= new Piece(cavalier,Noir,7,6);
    E.plateau[62]= P_62;
    Piece* P_63= new Piece(tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=7; i++){
        Piece* temp_P= new Piece(pion,Noir,6,i);
        E.plateau[6*8+i] = temp_P;
    }
    E.roi_B = P_3;
    E.roi_N = P_59;
    for (int i = 0; i < 16; ++i) {E.aliveB.push_front(E.plateau[i]); E.aliveN.push_front(E.plateau[i + 48]);}
}

///Test chessboard for check function
void echiquier_test_echec(Echiquier& E){

    Piece* P_4= new Piece(roi,Blanc,0,4);
    E.plateau[4] = P_4;

    Piece* P_59= new Piece(pion,Noir,1,5);
    E.plateau[13]= P_59;

    E.roi_B = P_4;

    E.aliveN.push_front(P_59);
    E.aliveB.push_front(P_4);
}

///Test chessboard for checkmate function
void echiquier_test_echec_mat(Echiquier& E)
{
    Piece* P_4= new Piece(roi,Blanc,0,7);
    E.plateau[7]= P_4;

    Piece* P_59= new Piece(dame,Noir,7,7);
    E.plateau[63]= P_59;

    Piece* P_9= new Piece(tour,Noir,5,6);
    E.plateau[46]= P_9;

  //  piece* PT = new piece(Tour, Noir, 6, 5);
  //  E.plateau[53]= PT;
    E.roi_B = P_4;
    E.aliveN.push_front(P_59);
    E.aliveN.push_front(P_9);
    E.aliveB.push_front(P_4);
}

///Test chessboard for small rooc
void echiquier_test_p_rooc(Echiquier& E){
    Piece* P_0 = new Piece(tour,Blanc,0,0);
    E.plateau[0]= P_0;
    Piece* P_3= new Piece(roi,Blanc,0,3);
    E.plateau[3]= P_3;
    Piece* P_4= new Piece(dame,Blanc,0,4);
    E.plateau[4]= P_4;
    Piece* P_5 = new Piece(cavalier,Blanc,0,5);
    E.plateau[5]= P_5;
    Piece* P_6= new Piece(fou,Blanc,0,6);
    E.plateau[6]= P_6;

    Piece* P_7= new Piece(tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        Piece* temp_P= new Piece(pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    Piece* P_56 = new Piece(tour,Noir,7,0);
    E.plateau[56]= P_56;
    Piece* P_59= new Piece(roi,Noir,7,3);
    E.plateau[59]= P_59;
    Piece* P_60= new Piece(dame,Noir,7,4);
    E.plateau[60]= P_60;
    Piece* P_61= new Piece(fou,Noir,7,5);
    E.plateau[61]= P_61;
    Piece* P_62= new Piece(cavalier,Noir,7,6);
    E.plateau[62]= P_62;
    Piece* P_63= new Piece(tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=7; i++){
        Piece* temp_P= new Piece(pion,Noir,6,i);
        E.plateau[6*8+i] = temp_P;
    }

    E.roi_B = P_3;
    E.roi_N = P_59;

    for (int i = 0; i < 64; ++i)
    {
        if (E.plateau[i] != nullptr)
        {
            switch(E.plateau[i]->Couleur)
            {
                case(Blanc): E.aliveB.push_front(E.plateau[i]); break;
                case(Noir) : E.aliveN.push_front(E.plateau[i]);
            }
        }
    }
}

///Test chessboard for big rooc
void echiquier_test_g_rooc(Echiquier& E){
    Piece* P_0 = new Piece(tour,Blanc,0,0);
    E.plateau[0]= P_0;

    Piece* P_3= new Piece(roi,Blanc,0,3);
    E.plateau[3]= P_3;
    Piece* P_1= new Piece(fou,Blanc,0,1);
    E.plateau[1]= P_1;
    Piece* P_2 = new Piece(cavalier,Blanc,0,2);
    E.plateau[2]= P_2;
    Piece* P_7= new Piece(tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        Piece* temp_P= new Piece(pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    Piece* P_56 = new Piece(tour,Noir,7,0);
    E.plateau[56]= P_56;
    Piece* P_57 = new Piece(cavalier,Noir,7,1);
    E.plateau[57]= P_57;
    Piece* P_58 = new Piece(fou,Noir,7,2);
    E.plateau[58]= P_58;
    Piece* P_59= new Piece(roi,Noir,7,3);
    E.plateau[59]= P_59;
    Piece* P_60= new Piece(dame,Noir,7,4);
    E.plateau[60]= P_60;
    Piece* P_61 = new Piece(fou,Noir,7,5);
    E.plateau[61]= P_61;
    Piece* P_62 = new Piece(cavalier,Noir,7,6);
    E.plateau[62]= P_62;

    Piece* P_63= new Piece(tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=7; i++){
        Piece* temp_P= new Piece(pion,Noir,6,i);
        E.plateau[6*8+i] = temp_P;
    }
    E.roi_B = P_3;
    E.roi_N = P_59;

    for (int i = 0; i < 64; ++i)
    {
        if (E.plateau[i] != nullptr)
        {
            switch(E.plateau[i]->Couleur)
            {
                case(Blanc): E.aliveB.push_front(E.plateau[i]); break;
                case(Noir) : E.aliveN.push_front(E.plateau[i]);
            }
        }
    }
}

///Test chessboard for small and big rooc
void echiquier_test_p_g_rooc(Echiquier& E){
    Piece* P_0 = new Piece(tour,Blanc,0,0);
    E.plateau[0]= P_0;

    Piece* P_3= new Piece(roi,Blanc,0,3);
    E.plateau[3]= P_3;

    Piece* P_7= new Piece(tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        Piece* temp_P= new Piece(pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    Piece* P_56 = new Piece(tour,Noir,7,0);
    E.plateau[56]= P_56;
    Piece* P_57 = new Piece(cavalier,Noir,7,1);
    E.plateau[57]= P_57;
    Piece* P_58 = new Piece(fou,Noir,7,2);
    E.plateau[58]= P_58;
    Piece* P_59= new Piece(roi,Noir,7,3);
    E.plateau[59]= P_59;
    Piece* P_60= new Piece(dame,Noir,7,4);
    E.plateau[60]= P_60;
    Piece* P_63= new Piece(tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=7; i++){
        Piece* temp_P= new Piece(pion,Noir,6,i);
        E.plateau[6*8+i] = temp_P;
    }
    E.roi_B = P_3;
    E.roi_N = P_59;

    for (int i = 0; i < 64; ++i)
    {
        if (E.plateau[i] != nullptr)
        {
            switch(E.plateau[i]->Couleur)
            {
                case(Blanc): E.aliveB.push_front(E.plateau[i]); break;
                case(Noir) : E.aliveN.push_front(E.plateau[i]);
            }
        }
    }
}

///Test chessboard for promotion
void echiquier_test_prom(Echiquier& E){
//    piece* P_0 = new piece(Tour,Blanc,0,0);
//    E.plateau[0]= P_0;
//    piece* P_1 = new piece(Cavalier,Blanc,0,1);
//    E.plateau[1]= P_1;
//    piece* P_2= new piece(Fou,Blanc,0,2);
//    E.plateau[2]= P_2;
    Piece* P_3= new Piece(roi,Blanc,0,3);
    E.plateau[3]= P_3;
//    piece* P_4= new piece(Dame,Blanc,0,4);
//    E.plateau[4]= P_4;
//    piece* P_5= new piece(Fou,Blanc,0,5);
//    E.plateau[5]= P_5;
//    piece* P_6= new piece(Cavalier,Blanc,0,6);
//    E.plateau[6]= P_6;
//    piece* P_7= new piece(Tour,Blanc,0,7);
//    E.plateau[7]= P_7;
//    for (int i = 0; i<=6; i++){
//        piece* temp_P= new piece(Pion,Blanc,1,i);
//        E.plateau[8+i] = temp_P;
//

    E.plateau[6*8+2] = new Piece(pion,Blanc,6,2);

    E.plateau[56] = new Piece(roi, Noir, 7, 0);

    E.aliveB.push_front(E.plateau[50]);
    E.aliveB.push_front(P_3);

    E.aliveN.push_front(E.plateau[56]);

    E.roi_B = P_3;
    E.roi_N = E.plateau[56];

}

///Test chessboard for check after a rooc move
void echiquier_test_echec_rooc(Echiquier& E){

    Piece* P_0 = new Piece(tour,Blanc,0,0);
    E.plateau[0] = P_0;

    Piece* P_3 = new Piece(roi,Blanc,0,3);
    E.plateau[3] = P_3;

    Piece* P_9= new Piece(fou,Noir,1,1);
    E.plateau[9]= P_9;

    E.roi_B = P_3;

    E.aliveN.push_front(P_9);
    E.aliveB.push_front(P_0);
    E.aliveB.push_front(P_3);
}


void echiquier_piece(Echiquier& E)
{
    Piece* t_roi = new Piece(roi, Blanc, 4, 4);
    Piece* t_dame = new Piece(dame, Noir, 4, 2);
    E.plateau[36] = t_roi;
    E.plateau[34] = t_dame;
}

//Chessboard to test the pion behaviour
void echiquier_test_pion(Echiquier& E){
    Piece* P_0 = new Piece(tour,Blanc,0,0);
    E.plateau[0]= P_0;
    Piece* P_1 = new Piece(cavalier,Blanc,0,1);
    E.plateau[1]= P_1;
    Piece* P_2= new Piece(fou,Blanc,0,2);
    E.plateau[2]= P_2;
    Piece* P_3= new Piece(dame,Blanc,0,3);
    E.plateau[3]= P_3;
    Piece* P_4= new Piece(roi,Blanc,0,4);
    E.plateau[4]= P_4;
    Piece* P_5= new Piece(fou,Blanc,0,5);
    E.plateau[5]= P_5;
    Piece* P_6= new Piece(cavalier,Blanc,0,6);
    E.plateau[6]= P_6;
    Piece* P_7= new Piece(tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        Piece* temp_P= new Piece(pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    E.plateau[8*4 + 6] = E.plateau[8 + 6];
    E.plateau[4*8 + 6]->x = 6; E.plateau[4*8 + 6]->y = 4;
    E.plateau[4*8 + 6]->a_bouge = true;
    E.plateau[8 + 6] = nullptr;

    Piece* P_56 = new Piece(tour,Noir,7,0);
    E.plateau[56]= P_56;
    Piece* P_57 = new Piece(cavalier,Noir,7,1);
    E.plateau[57]= P_57;
    Piece* P_58 = new Piece(fou,Noir,7,2);
    E.plateau[58]= P_58;
    Piece* P_59= new Piece(roi,Noir,7,3);
    E.plateau[59]= P_59;
    Piece* P_60= new Piece(dame,Noir,7,4);
    E.plateau[60]= P_60;
    Piece* P_61= new Piece(fou,Noir,7,5);
    E.plateau[61]= P_61;
    Piece* P_62= new Piece(cavalier,Noir,7,6);
    E.plateau[8*7+6]= P_62;
    Piece* P_63= new Piece(tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=7; i++){
        Piece* temp_P= new Piece(pion,Noir,6,i);
        E.plateau[6*8+i] = temp_P;
    }
    E.plateau[5*8 + 7] = E.plateau[6*8 + 7];
    E.plateau[5*8 + 7]->x = 7; E.plateau[5*8 + 7]->y = 5;
    E.plateau[5*8 + 7]->a_bouge = true;
    E.plateau[6*8 + 7] = nullptr;

    E.roi_B = P_4;
    E.roi_N = P_59;
    for (int i = 0; i < 64; ++i)
    {
        if (E.plateau[i] != nullptr)
        {
            switch(E.plateau[i]->Couleur)
            {
                case(Blanc): E.aliveB.push_front(E.plateau[i]); break;
                case(Noir) : E.aliveN.push_front(E.plateau[i]);
            }
        }
    }
}

//============================================
// =========== Global  Functions  ============
//============================================

bool find_word(string mot, vector<string> liste_mot)
{
    bool is_in = false;
    for (vector<string>::iterator it = liste_mot.begin(); it != liste_mot.end(); ++it) {if (*it == mot) {is_in = true;}}
    return is_in;
}

//Display the board
void Echiquier::affichage() const{

    for (int i = 7; i>=0; i--){
        cout<<i+1<<"   "; //Write the left column numbers
        for (int j=0; j<8; j++){
            if (plateau[i*8+j] != nullptr){
                cout<<plateau[i*8+j]->string_type()<<( (plateau[i*8+j]->Couleur==Blanc) ? "b":"n")<<"  ";
            }else{
                cout<<"    ";
            }
        }
        cout<<endl;
    }
    cout<<"    ";
    //Write the bottom line letters
    for (int i = 0; i < 8; i++)
    {
        cout<<alphat[i]<<"   ";
    }
    cout<<endl;
}


bool interieur_plateau(int i,int j)
{
    if (i>= 0 && i<8 && j >=0 && j<8) return true;
    return false;
}

///MinMax algorithm
int minimax(Position &P, int alpha, int beta, int depth = 4)
{
    int c = P.valeur_position();
    if (c == 1000 || c == -1000)
    {
//        cout<<"La valeur de la position finale est "<<c<<endl;
        return c;
    }
    P.position_possible();
    Position* pFilles= P.fille;
    int a = alpha;
    int b = beta;
//	 Terminating condition. i.e
//	 leaf node is reached
	if ( pFilles == nullptr) {
//        cout<<"Valeur de la position finale "<<a<<endl;
		return P.valeur_position();
	}
    if (P.joueur == 1)
    {
        int best = MIN;

        int val = minimax(*pFilles, a, b, depth-1);
        best = max(best, val);

//      Recur for her sisters
        while (pFilles->soeur!=NULL)
        {
            Position* pS=pFilles->soeur;
            if (pS->gagne()) {return pS->valeur_position();}
            int val = minimax(*(pS), a, b, depth-1);
            best = max(best, val);
            pFilles=pS;
            alpha = max(alpha, best);

    /*        // Alpha Beta Pruning
            if (beta <= alpha)
                break;              */
        }
        return best;
        }
    else
    {
        int best = MAX;

//          first child
//        pP=P.fille;
        int val = minimax(*pFilles, a, b, depth-1);
        best = min(best, val);
          //Recur for her sisters

        while (pFilles->soeur!=NULL)
        {   Position* pS=pFilles->soeur;
            int val = minimax(*(pS), a, b, depth-1);
            best = min(best, val);
            pFilles=pS;
            beta = min(alpha, best);
      /*      // Alpha Beta Pruning
            if (beta <= alpha)
                break;              */
        }
        return best;
    }
}

