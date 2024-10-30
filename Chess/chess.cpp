#include "chess.hpp"
#include <cmath>
#include <string>
#include <sstream>
//====================================

const int alpha = 1;
const int beta = 1;

const int MAX = 100000;
const int MIN = -100000;
const string Normal("N");
const string Special("SPECIAL");
const vector<string> list_move = {Normal,Special};
const string alphat = "ABCDEFGH";
string p_rooc = "p_rooc";
string g_rooc = "g_rooc";
string prom_t = "prom_t";
string prom_d = "prom_d";
string prom_c = "prom_c";
string prom_f = "prom_f";
string Nul = "nul";

vector<string> special_moves = {p_rooc, g_rooc, prom_t, prom_d, prom_c, prom_f, Nul};



//====================================
//==== Methods of Position_Echec =====
//====================================

//Update  the chessboard for a specific: v
void Position_Echec::mise_a_jour_coup(const coup_echec& move_chess, const bool text)
{

    PieceColor C = this->couleur_joueur;
    if (move_chess.g_rooc)
    {
        if (text) cout<<"Grand rooc"<<endl;
        piece* temp;
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
    if (move_chess.p_rooc)
    {
        if (text) cout<<"Petit rooc"<<endl;
        piece* temp;
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
    piece* Pprise = echiquier_ref->plateau[move_chess.fin[1]*8 + move_chess.fin[0]];
    piece* Pjoue = echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]];
    if (move_chess.prom_c)
    {
        if (text) cout<<"Promotion d'un pion en cavalier"<<endl;

//      If a piece lies at this position
        if (Pprise!=nullptr){
            elimine_piece(*this, Pprise, Pjoue, text);
        }
        piece* promoted = echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]];

        echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]] = nullptr; //Set it to 0
        piece* tmp = new piece(Cavalier, C, move_chess.fin[1], move_chess.fin[0], 1);
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

        piece* promoted = echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]];

        echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]] = nullptr;
        piece* tmp = new piece(Dame, C, move_chess.fin[1], move_chess.fin[0], 1);
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
        piece* promoted = echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]];

        echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]] = nullptr;
        piece* tmp = new piece(Tour, C, move_chess.fin[1], move_chess.fin[0], 1);
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
        piece* promoted = echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]];

        echiquier_ref->plateau[move_chess.init[1]*8 + move_chess.init[0]] = nullptr; //Set it as nullptr
        piece* tmp = new piece(Fou, C, move_chess.fin[1], move_chess.fin[0], 1);
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
    for (list<coup_echec>::iterator it = Liste_coup.begin(); it != Liste_coup.end(); ++it){this->mise_a_jour_coup(*it, text);}
    Liste_coup.clear();
}


double Position_Echec::valeur_position(){

//    int cont_blanc = 0;
//    int cont_noir = 0;
//    int val_blanc = 0;
//    int val_noir = 0;
//    int val;
//    this->mise_a_jour_position();
//    if (this->test_echec_mat()==true) //Si le joueur 1 ou 2 est mis en echec et mat
//    {
//            if (this->joueur == 1)
//            {
//                return MIN; //Si le joueur est mis en echec et mat, l'ordinateur gagne
//            }
//            if (this->joueur == 2)
//            {
//                return MAX; //Si l'ordinateur est mis en echec et mat, le joueur gagne
//            }
//
////    } else if (this->test_match_nul()==true)
////    {
////        return 0;
//    } else
//    {
//        for(int i = 0; i<64;i++)
//        {
//            if (this->echiquier_ref->plateau[i] != NULL)
//            {
//                if (this->echiquier_ref->plateau[i]->Couleur == Blanc)
//                {
//                    cont_blanc = cont_blanc +1;
//                    val_blanc = val_blanc + this->echiquier_ref->plateau[i]->P.valeur;
//                } else if (this->echiquier_ref->plateau[i]->Couleur == Noir)
//                {
//                    cont_noir = cont_noir +1;
//                    val_noir = val_noir + this->echiquier_ref->plateau[i]->P.valeur;
//                }
//            }
//        }
//	    if ((this->couleur_joueur == Blanc && this->joueur == 1) || (this->couleur_joueur == Noir && this->joueur == 2))
//        {
//            val = alpha*(val_blanc - val_noir) + beta*(cont_blanc - cont_noir);
//        }
//        else if((this->couleur_joueur == Blanc && this->joueur == 2) || (this->couleur_joueur == Noir && this->joueur ==1))
//        {
//                    val = -(alpha *(val_blanc - val_noir) + beta*(cont_blanc - cont_noir));
//        }
//    }
    return 0;
}

//Check if the player is in check position: v
bool Position_Echec::test_echec(const PieceColor C) const {
    //cout << turn << endl;
    //echiquier echiquier_final = construction_echiquier(*this); // Construire echiquier
   // (*this).mise_a_jour_position();
    int m = 2;
    vector<vector<int>> Dep;
    piece* roi = (C == Blanc) ? this->echiquier_ref->roi_N : this->echiquier_ref->roi_B; //Find the threatened king
    list<piece*> alive = (C == Blanc) ? this->echiquier_ref->aliveB : this->echiquier_ref->aliveN; //Which set of piece?
    list<piece*>::const_iterator it;
    bool is_ok;
    int siz;

    int mv_x; int mv_y; bool multi;
    int new_pos_x; int new_pos_y;

    int b = (C == Blanc) ? 1 : -1;

    PieceType nom;
    int si = alive.size();

    for (it = alive.begin(); it != alive.end(); ++it) //for every remaining piece
    {
        Dep = (*it)->P.Dep_rel;
        nom = (*it)->P.Nom_piece;
        if (nom == Pion) Dep = {{1, 1}, {1, -1}, {1,1}}; //Attacks allowed
        siz = Dep[0].size();
        for (int i = 0; i < siz; ++i) { //For every potential move
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
bool Position_Echec::test_echec_mat(const PieceColor C) const{ //NOTE: The simple check is assumed to already have been tested: v
    piece* roi = (C == Blanc) ? this->echiquier_ref->roi_N : this->echiquier_ref->roi_B;
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

//Check if a position is a draw: v
bool Position_Echec::test_match_nul() const{
    if (this->echiquier_ref->aliveB.empty() && this->echiquier_ref->aliveN.size() == 1) {return true;}
    if (this->echiquier_ref->aliveN.empty() && this->echiquier_ref->aliveB.size() == 1) {return true;}
    return false;
}

//Tells if a position is admissible for a small rooc
bool Position_Echec::test_p_rooc() const{
    PieceColor C = this->couleur_joueur;
    piece* roi;
    piece* tour;
    piece* piece1;
    piece* piece2;
    switch(C)
    {
        case(Blanc): roi = this->echiquier_ref->plateau[3]; tour = this->echiquier_ref->plateau[0]; piece1 = this->echiquier_ref->plateau[1]; piece2 = this->echiquier_ref->plateau[2]; break;
        case(Noir): roi = this->echiquier_ref->plateau[59]; tour = this->echiquier_ref->plateau[56]; piece1 = this->echiquier_ref->plateau[57]; piece2 = this->echiquier_ref->plateau[58];
    }
    if (roi == nullptr || roi->a_bouge) {cout<<"Le roi a deja bouge, petit rooc impossible."<<endl;return false;}
    if (tour == nullptr || tour->a_bouge) {cout<<"La tour a deja bouge, petit rooc impossible."<<endl;return false;}
    if (roi->P.Nom_piece != Roi) {cout<<"Le roi n'est pas a la bonne position."<<endl; return false;}
    if (tour->P.Nom_piece != Tour) {cout<<"La Tour n'est pas a la bonne position."<<endl; return false;}
    if (piece1 != nullptr || piece2 != nullptr) {cout<<"Il y a des pieces sur le chemin, petit rooc impossible."<<endl; return false;}
    return true;
}

//Tells if a position is admissible for a big rooc
bool Position_Echec::test_g_rooc() const{
    PieceColor C = this->couleur_joueur;
    piece* roi;
    piece* tour;
    piece* piece1;
    piece* piece2;
    piece* piece3;
    switch(C)
    {
        case(Blanc): roi = this->echiquier_ref->plateau[3]; tour = this->echiquier_ref->plateau[7]; piece1 = this->echiquier_ref->plateau[4]; piece2 = this->echiquier_ref->plateau[5];  piece3 = this->echiquier_ref->plateau[6]; break;
        case(Noir): roi = this->echiquier_ref->plateau[59]; tour = this->echiquier_ref->plateau[63]; piece1 = this->echiquier_ref->plateau[60]; piece2 = this->echiquier_ref->plateau[61];  piece3 = this->echiquier_ref->plateau[62];
    }
    if (roi == nullptr || roi->a_bouge) {cout<<"Le roi a deja bouge, grand rooc impossible."<<endl;return false;}
    if (tour == nullptr || tour->a_bouge) {cout<<"La tour a deja bouge, grand rooc impossible."<<endl;return false;}
    if (roi->P.Nom_piece != Roi) {cout<<"Le roi n'est pas a la bonne position."<<endl; return false;}
    if (tour->P.Nom_piece != Tour) {cout<<"La Tour n'est pas a la bonne position."<<endl; return false;}
    if (piece1 != nullptr || piece2 != nullptr || piece3 != nullptr) {cout<<"Il y a des pieces sur le chemin, grand rooc impossible."<<endl; return false;}
    return(true);
}

//Put the move chosen by user in the move list and return a new chess position.
//Return false if everything went normal. Return true if the player made a wrong move and chose special instead of normal,
//because the special move is not authorized: v
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
        coup_echec coup_joue(i_init, j_init, i_final, j_final);
        coup_joue.affichage_standard(this->echiquier_ref);
        (this->Liste_coup).push_back(coup_joue);
        list<coup_echec>::iterator it;
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
        if(reponse_S == p_rooc ){
            //Check if it is authorized
            is_authorized = this->test_p_rooc();

            if (is_authorized)
            {
                coup_echec coup_joue("p_rooc", this->couleur_joueur);
                coup_joue.affichage_standard(this->echiquier_ref); //Display the move
                this->Liste_coup.push_back(coup_joue);
            }
            else return true;
        }
        if(reponse_S == g_rooc ){
            //Check if it is authorized
            is_authorized = this->test_g_rooc();;

            if (is_authorized)
            {
                coup_echec coup_joue("g_rooc",this->couleur_joueur);
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
            if (this->echiquier_ref->plateau[8*i_init + j_init]->P.Nom_piece != Pion) {cout<<"La promotion ne s'effectue que sur les pions."<<endl; return true;}

            //Check if the promotion actually concerns a pawn.
            if (C == Blanc && i_final != 7) {cout<<"La piece doit atteindre la derniere ligne du plateau."<<endl; return true ;}
            if (C == Noir && i_final != 0) {cout<<"La piece doit atteindre la premiere ligne du plateau."<<endl;return true;}

            //Update the list of moves
            if(reponse_S == prom_c){
                coup_echec coup_joue("prom_c",i_init,j_init,i_final,j_final);
                coup_joue.affichage_standard(this->echiquier_ref);
                this->Liste_coup.push_front(coup_joue);
                return false;
            }
            if(reponse_S == prom_f){
                coup_echec coup_joue("prom_f", i_init, j_init, i_final, j_final);
                coup_joue.affichage_standard(this->echiquier_ref);
                this->Liste_coup.push_front(coup_joue);
                return false;
            }
            if(reponse_S == prom_d){
                coup_echec coup_joue("prom_d", i_init, j_init, i_final, j_final);
                coup_joue.affichage_standard(this->echiquier_ref);
                this->Liste_coup.push_front(coup_joue);
                return false;
            }
            if(reponse_S == prom_t){

                coup_echec coup_joue("prom_t", i_init, j_init, i_final, j_final);
                coup_joue.affichage_standard(this->echiquier_ref);
                this->Liste_coup.push_front(coup_joue);
                return false;
            }
            delete pi_init; delete pj_init; delete pi_final; delete pj_final;
        }
    }
    return false;
}


bool Position_Echec::valid_check(const int& i_init, const int& j_init, const int& i_final, const int& j_final) const{
    coup_echec mv_checkmate(i_init, j_init, i_final, j_final);
    Position_Echec checkmate(*this);//We make a copy because we do not want to modify the original chessboard
    checkmate.Liste_coup.push_front(mv_checkmate);
    checkmate.mise_a_jour_position(0);
    switch(this->couleur_joueur) //We need to swap colors because we want to see if the player's king is check after moving, not the opponent's,
    //which is assumed by the method test_check.
    {
        case Blanc : return checkmate.test_echec(Noir); break; //Tell if the new position is check
        case Noir : return checkmate.test_echec(Blanc);
    }
}

//v
bool Position_Echec::is_valid_move(const int& i_init, const int& j_init, const int& i_final, const int& j_final, const PieceColor C, const bool text) const
{
    bool valid_move_init = interieur_plateau(i_init,j_init);
    bool valid_move_fin = interieur_plateau(i_final,j_final);

    //Out of the board
    if ((!valid_move_init) || (!valid_move_fin)) {if (text) {cout<< "La position initiale ou finale n'est pas a l'interieur du plateau."<<endl;} return false;}

    piece* pos_init = this->echiquier_ref->plateau[8*i_init + j_init];

    //There is no piece at this position
    if (pos_init == nullptr) {if (text) {cout<<"Il n'y a pas de piece a cette position"<<endl;} return false;}

    //If this is an opponent's piece
    if (C != pos_init->Couleur) {if (text) {cout<<"Il s'agit d'une piece de l'adversaire"<<endl;} return false;}

    piece* pos_final = this->echiquier_ref->plateau[8*i_final + j_final];

    bool empty_case = (pos_final == nullptr);
    if (empty_case) return true;
    else if (pos_final->Couleur == C) {if (text) {cout<<"On ne mange pas ses allies!!"<<endl;} return false;}
    return true;
}

//Check if a move is overall valid: v
bool Position_Echec::all_valid(const int& i_init, const int& j_init, const int& i_final, const int& j_final, const bool text) const
{
    if (!is_valid_move(i_init, j_init, i_final, j_final, this->couleur_joueur ,text)) {return false;}

    else
    {
        //Check whether the move is conform or not to the rules
        bool valid_move = is_valid(i_init, j_init, i_final, j_final, this->echiquier_ref, text);
        if (!valid_move) return false;
        //Check whether the move put the player's king into a check position
        bool valid_chec = valid_check(i_init, j_init, i_final, j_final);
        if (valid_chec) {cout<<"Ce coup mene le roi en echec."<<endl; return false;}
    }
    return true;
}


//On se sert des listes alive pour deux methodes, position_possible et test_echec. Dans ces deux cas, on doit avoir une vision globale
//Du plateau et repérer le roi facilement.

Position* Position_Echec::position_possible()
{
    PieceColor C = couleur_joueur;
    list<piece*> alive = (C == Blanc) ? this->echiquier_ref->aliveB : this->echiquier_ref->aliveN;
    list<piece*>::const_iterator it;
    vector<vector<int>> Del;

    int x; int y;
    int mv_x; int mv_y; bool multi;

    int siz;
    int m;

    bool valid;

    int b = (C == Blanc) ? 1 : -1;

    Position_Echec* new_move = nullptr;
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
                new_move = new Position_Echec(*this);
                coup_echec mv_checkmate(y, x, mv_y, mv_x);
                new_move->Liste_coup.push_front(mv_checkmate);
                new_move->mise_a_jour_position(0);
                Position* tmp = this->fille;
                this->fille = new_move;
                new_move->soeur = tmp;
            }
            m = 2;
            while (!multi && valid)
            {
                mv_x = x + m*b*Del[0][i]; mv_y = y + m*b*Del[1][i];
                valid = this->all_valid(y,x,mv_y,mv_x, 0); //Check if the movement is valid
                if (valid)
                {
                    new_move = new Position_Echec(*this);
                    coup_echec mv_checkmate(y, x, mv_y, mv_x);
                    new_move->Liste_coup.push_front(mv_checkmate);
                    new_move->mise_a_jour_position(0);
                    Position* tmp = this->fille;
                    this->fille = new_move;
                    new_move->soeur = tmp;
                }
                m++;
            }
        }
    }
    return new_move;
}

//=====================================
//== Function returning a chessboard ==
//=====================================

//Initialize the chessboard
void echiquier_depart(echiquier& E){
    piece* P_0 = new piece(Tour,Blanc,0,0);
    E.plateau[0]= P_0;
    piece* P_1 = new piece(Cavalier,Blanc,0,1);
    E.plateau[1]= P_1;
    piece* P_2= new piece(Fou,Blanc,0,2);
    E.plateau[2]= P_2;
    piece* P_3= new piece(Roi,Blanc,0,3);
    E.plateau[3]= P_3;
    piece* P_4= new piece(Dame,Blanc,0,4);
    E.plateau[4]= P_4;
    piece* P_5= new piece(Fou,Blanc,0,5);
    E.plateau[5]= P_5;
    piece* P_6= new piece(Cavalier,Blanc,0,6);
    E.plateau[6]= P_6;
    piece* P_7= new piece(Tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    piece* P_56 = new piece(Tour,Noir,7,0);
    E.plateau[56]= P_56;
    piece* P_57 = new piece(Cavalier,Noir,7,1);
    E.plateau[57]= P_57;
    piece* P_58 = new piece(Fou,Noir,7,2);
    E.plateau[58]= P_58;
    piece* P_59= new piece(Roi,Noir,7,3);
    E.plateau[59]= P_59;
    piece* P_60= new piece(Dame,Noir,7,4);
    E.plateau[60]= P_60;
    piece* P_61= new piece(Fou,Noir,7,5);
    E.plateau[61]= P_61;
    piece* P_62= new piece(Cavalier,Noir,7,6);
    E.plateau[62]= P_62;
    piece* P_63= new piece(Tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Noir,6,i);
        E.plateau[6*8+i] = temp_P;
    }
    E.roi_B = P_3;
    E.roi_N = P_59;
    for (int i = 0; i < 16; ++i) {E.aliveB.push_front(E.plateau[i]); E.aliveN.push_front(E.plateau[i + 48]);}
}

//Test chessboard for check function
void echiquier_test_echec(echiquier& E){

    piece* P_4= new piece(Roi,Blanc,0,4);
    E.plateau[4] = P_4;

    piece* P_59= new piece(Pion,Noir,1,5);
    E.plateau[13]= P_59;

    E.roi_B = P_4;

    E.aliveN.push_front(P_59);
    E.aliveB.push_front(P_4);
}

//Test chessboard for checkmate function
void echiquier_test_echec_mat(echiquier& E)
{
    piece* P_4= new piece(Roi,Blanc,0,7);
    E.plateau[7]= P_4;

    piece* P_59= new piece(Dame,Noir,7,7);
    E.plateau[63]= P_59;

    piece* P_9= new piece(Tour,Noir,5,6);
    E.plateau[46]= P_9;

  //  piece* PT = new piece(Tour, Noir, 6, 5);
  //  E.plateau[53]= PT;
    E.roi_B = P_4;
    E.aliveN.push_front(P_59);
    E.aliveN.push_front(P_9);
    E.aliveB.push_front(P_4);
}

void echiquier_test_p_rooc(echiquier& E){
    piece* P_0 = new piece(Tour,Blanc,0,0);
    E.plateau[0]= P_0;
    piece* P_3= new piece(Roi,Blanc,0,3);
    E.plateau[3]= P_3;
    piece* P_4= new piece(Dame,Blanc,0,4);
    E.plateau[4]= P_4;
    piece* P_5 = new piece(Cavalier,Blanc,0,5);
    E.plateau[5]= P_5;
    piece* P_6= new piece(Fou,Blanc,0,6);
    E.plateau[6]= P_6;

    piece* P_7= new piece(Tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    piece* P_56 = new piece(Tour,Noir,7,0);
    E.plateau[56]= P_56;
    piece* P_59= new piece(Roi,Noir,7,3);
    E.plateau[59]= P_59;
    piece* P_60= new piece(Dame,Noir,7,4);
    E.plateau[60]= P_60;
    piece* P_61= new piece(Fou,Noir,7,5);
    E.plateau[61]= P_61;
    piece* P_62= new piece(Cavalier,Noir,7,6);
    E.plateau[62]= P_62;
    piece* P_63= new piece(Tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Noir,6,i);
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

void echiquier_test_g_rooc(echiquier& E){
    piece* P_0 = new piece(Tour,Blanc,0,0);
    E.plateau[0]= P_0;

    piece* P_3= new piece(Roi,Blanc,0,3);
    E.plateau[3]= P_3;
    piece* P_1= new piece(Fou,Blanc,0,1);
    E.plateau[1]= P_1;
    piece* P_2 = new piece(Cavalier,Blanc,0,2);
    E.plateau[2]= P_2;
    piece* P_7= new piece(Tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    piece* P_56 = new piece(Tour,Noir,7,0);
    E.plateau[56]= P_56;
    piece* P_57 = new piece(Cavalier,Noir,7,1);
    E.plateau[57]= P_57;
    piece* P_58 = new piece(Fou,Noir,7,2);
    E.plateau[58]= P_58;
    piece* P_59= new piece(Roi,Noir,7,3);
    E.plateau[59]= P_59;
    piece* P_60= new piece(Dame,Noir,7,4);
    E.plateau[60]= P_60;
    piece* P_63= new piece(Tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Noir,6,i);
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
    E.aliveB.remove(P_3);
    E.aliveN.remove(P_59);
}

void echiquier_test_prom(echiquier& E){
//    piece* P_0 = new piece(Tour,Blanc,0,0);
//    E.plateau[0]= P_0;
//    piece* P_1 = new piece(Cavalier,Blanc,0,1);
//    E.plateau[1]= P_1;
//    piece* P_2= new piece(Fou,Blanc,0,2);
//    E.plateau[2]= P_2;
    piece* P_3= new piece(Roi,Blanc,0,3);
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

    E.plateau[6*8+2] = new piece(Pion,Blanc,6,2);

    E.plateau[56] = new piece(Roi, Noir, 7, 0);

    E.aliveB.push_front(E.plateau[50]);
    E.aliveB.push_front(P_3);

    E.aliveN.push_front(E.plateau[56]);

    E.roi_B = P_3;
    E.roi_N = E.plateau[56];

}

void echiquier_piece(echiquier& E)
{
    piece* roi = new piece(Roi,Blanc,4,4);
    piece* dame = new piece(Dame ,Noir, 4,2);
    E.plateau[36] = roi;
    E.plateau[34] = dame;
}

//Chessboard to test the pion behaviour
void echiquier_test_pion(echiquier& E){
    piece* P_0 = new piece(Tour,Blanc,0,0);
    E.plateau[0]= P_0;
    piece* P_1 = new piece(Cavalier,Blanc,0,1);
    E.plateau[1]= P_1;
    piece* P_2= new piece(Fou,Blanc,0,2);
    E.plateau[2]= P_2;
    piece* P_3= new piece(Dame,Blanc,0,3);
    E.plateau[3]= P_3;
    piece* P_4= new piece(Roi,Blanc,0,4);
    E.plateau[4]= P_4;
    piece* P_5= new piece(Fou,Blanc,0,5);
    E.plateau[5]= P_5;
    piece* P_6= new piece(Cavalier,Blanc,0,6);
    E.plateau[6]= P_6;
    piece* P_7= new piece(Tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    E.plateau[8*4 + 6] = E.plateau[8 + 6];
    E.plateau[4*8 + 6]->x = 6; E.plateau[4*8 + 6]->y = 4;
    E.plateau[4*8 + 6]->a_bouge = true;
    E.plateau[8 + 6] = nullptr;

    piece* P_56 = new piece(Tour,Noir,7,0);
    E.plateau[56]= P_56;
    piece* P_57 = new piece(Cavalier,Noir,7,1);
    E.plateau[57]= P_57;
    piece* P_58 = new piece(Fou,Noir,7,2);
    E.plateau[58]= P_58;
    piece* P_59= new piece(Roi,Noir,7,3);
    E.plateau[59]= P_59;
    piece* P_60= new piece(Dame,Noir,7,4);
    E.plateau[60]= P_60;
    piece* P_61= new piece(Fou,Noir,7,5);
    E.plateau[61]= P_61;
    piece* P_62= new piece(Cavalier,Noir,7,6);
    E.plateau[8*7+6]= P_62;
    piece* P_63= new piece(Tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Noir,6,i);
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
void echiquier::affichage() const{

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



////Display daughters positions
//void affichage_fille(Position_Echec& posi)
//{
//    posi.fille = nullptr;
//    posi.position_possible();
//    if (posi.fille != nullptr)
//    {
//        Position_Echec* Fille = dynamic_cast<Position_Echec*>(posi.fille);
//        while (Fille != nullptr)
//        {
//            posi = *Fille;
//            posi.mise_a_jour_position();
//            cout<<"================================="<<endl;
//            posi.echiquier_ref.affichage();
//            cout<<"================================="<<endl;
//            Fille = dynamic_cast<Position_Echec*>(Fille->soeur);
//        }
//    }
//}


bool interieur_plateau(int i,int j)
{
    if (i>= 0 && i<8 && j >=0 && j<8){
        return true;}
    return false;
}

// Profondeur en argument
//int minimax(Position &P, int alpha, int beta, int depth)
//{
////    Position* pP=&P;
////    cout<<"         debut           "<<endl;
////    cout<<"         ======          "<<endl;
////    P.print_position();
// //   int c = P.valeur_position();
//  //  if ( c == MIN || c == MAX)
//  //  {
//  //      return c;
// //   }
//
//    P.position_possible();
//    Position* pFilles= P.fille;
//    int a = alpha;
//    int b = beta;
////	 Terminating condition. i.e
////	 leaf node is reached
//	if ( pFilles == nullptr || depth == 0) {
////        cout<<"Valeur de la position finale "<<a<<endl;
//		return P.valeur_position();
//	}
//    if (P.joueur == 1)
//    {
//        int best = MIN;
//
////        First child
////        pP=P.fille;
//        pFilles->joueur = 2;
//        int val = minimax(*pFilles, a, b, depth-1);
//        best = max(best, val);
////          Recur for her sisters
//
//        while (pFilles->soeur!=NULL)
//        {
//            Position* pS=pFilles->soeur;
//            if (pS->gagne()) {return pS->valeur_position();}
//            int val = minimax(*(pS), a, b, depth-1);
//            best = max(best, val);
//            pFilles=pS;
//            alpha = max(alpha, best);
//
//    /*        // Alpha Beta Pruning
//            if (beta <= alpha)
//                break;              */
//        }
//        return best;
//        }
//    else
//    {
//        int best = MAX;
//
////          first child
////        pP=P.fille;
//        pFilles->joueur = 1;
//        int val = minimax(*pFilles, a, b, depth-1);
//        best = min(best, val);
//          //Recur for her sisters
//
//        while (pFilles->soeur!=NULL)
//        {   Position* pS=pFilles->soeur;
//            int val = minimax(*(pS), a, b, depth-1);
//            best = min(best, val);
//            pFilles=pS;
//            beta = min(alpha, best);
//      /*      // Alpha Beta Pruning
//            if (beta <= alpha)
//                break;              */
//        }
//        return best;
//    }
//}

