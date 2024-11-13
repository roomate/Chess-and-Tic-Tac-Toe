#include <string>
#include "chess.hpp"
#include <cmath>
#include <list>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const vector<string> game = {"PvP", "PvC"};

struct GameState{
    bool match_nul = false;
    bool victoire_ordi = false;
    bool victoire_joueur = false;
};

int main(){
    string type_game;
    cout<<"Voulez-vous jouer en 'PvP' ou en 'PvC' ?"<<endl;
    cin>>type_game;
    while (!find_word(type_game, game))
    {
        cout<<"Choisissez entre Player vs Player 'PvP' et Player vs Computer 'PvC'?"<<endl;
        cin>>type_game;
    }
    if (type_game == "PvP") play_PvP();
    else if (type_game == "PvC") play_PvC();
}

///===================================
///=============Test mains============
///===================================


/////To test position_possible() on count_ levels of the tree
//int main(){
//    Echiquier echiquier_d;
//    PieceColor Color_Player = Noir;
//    vector<int> l = {9, 6, 5, 8, 4, 3, 1, 7, 2, 0};
//    echiquier_test(echiquier_d);
//    Position_Echec posi(echiquier_d, Color_Player);
//    posi.joueur = 1;
//    cout<<"Original chessboard is:"<<endl;
//    posi.print_position();
//    posi.position_possible();
//    Position_Echec* pos_poss = posi.fille;
//    int count_ = 50;
//    int rd;
//    long long int* seed = new long long int;
//    *seed = count_;
//    while (count_ > 0 && pos_poss != nullptr){
//        Position_Echec* origin = pos_poss;
////        pos_poss->print_sisters(0);
//        pos_poss = origin;
//        srand((int) time(seed));
//        rd = rand();
//        while (rd > 0){
//            if (pos_poss->soeur == nullptr) {rd = 0;}
//            else {
//                pos_poss = pos_poss->soeur;
//                --rd;
//            }
//        }
//        cout<<"----------------------------------"<<endl;
//        cout<<"Daughter chessboard is:"<<endl;
//
//        pos_poss->position_possible();
//        pos_poss->affiche_attributs();
//        pos_poss = pos_poss->fille;
//        count_ -= 1;
//        *seed = count_;
//    }
//    return 0;
//}


///Test for valeur_position()
//int main(){
//    Echiquier echiquier_d;
//    PieceColor Color_Player = Noir;
//    echiquier_test_echec_rooc(echiquier_d);
//    Position_Echec posi(echiquier_d, Color_Player);
//    posi.joueur = 1;
//    cout<<"Original chessboard is:"<<endl;
//    posi.print_position();
//    cout<<posi.valeur_position()<<endl;
//    return 0;
//}


///To test check
//int main(){
//    Echiquier echiquier_d;
//    PieceColor Color;
//    //Idee de renverser le plateau si on choisit noir?
//    string C;
//    cout<<"Voulez-vous jouez 'Blanc' ou 'Noir' ?"<<endl;
//    C = "Blanc";
//    while (C != "Blanc" && C != "Noir")
//    {
//        cout<<"Choisissez entre 'Blanc' et 'Noir' svp."<<endl;
//        cin>>C;
//    }
//    //If it is white
//    Color = (C == "Blanc") ? Blanc : Noir;
//    //Initialize the chessboard, accordingly to the color
//     echiquier_test(echiquier_d);
//
////   Initialize the position, always start with white.
//    Position_Echec posi(echiquier_d, Color);
//    posi.joueur = 1;
//    posi.print_position();
//    cout<<posi.echec(Noir)<<endl;
//    return 0;
//}

///To test checkmate
//int main(){
//    echiquier echiquier_d;
//    PieceColor Color;
//    //Idee de renverser le plateau si on choisit noir?
//    string C;
//    cout<<"Voulez-vous jouez 'Blanc' ou 'Noir' ?"<<endl;
//    cin>>C;
//    C = "Blanc";
//    while (C != "Blanc" && C != "Noir")
//    {
//        cout<<"Choisissez entre 'Blanc' et 'Noir' svp."<<endl;
//        cin>>C;
//    }
//    //If it is white
//    Color = (C == "Blanc") ? Blanc : Noir;
//    //Initialize the chessboard, accordingly to the color
//    echiquier_test_echec_mat(echiquier_d);
//
////   Initialize the position, always start with white.
//    Position_Echec posi(echiquier_d, Color);
//    posi.joueur = (Color == Blanc) ? 1 : 2; //To anticipate the first swap
//    posi.print_position();
//    cout<<posi.test_echec_mat(Noir)<<endl;
//    return 0;
//}


//int main() //Test si le roi ne se met pas en échec dans ses positions possibles
//{
//    int mini;
//    int minimaxi;
//    echiquier echiquier_d = echiquier_piece();
//    //echiquier_d.affichage();
//    Position_Echec E(echiquier_d);
//    E.couleur_joueur = Blanc;
//    E.joueur = 2;
//    affichage_fille(E);
////    E.position_possible();
////    Position_Echec& Fille = dynamic_cast<Position_Echec&>(*E.fille);
////    Fille.mise_a_jour_position();
////    Fille.echiquier_ref.affichage();
////    cout<<Fille.test_echec()<<endl;
//}






