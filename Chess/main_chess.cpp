#include <string>
#include "chess.hpp"
#include <cmath>
#include <list>
#include <iostream>

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
//    cin>>type_game;
    type_game = "PvC";
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


///To test position_possible() on three level of the tree
//int main(){
//    Echiquier echiquier_d;
//    PieceColor Color_Player = Blanc;
//    echiquier_test_prom(echiquier_d);
//    Position_Echec posi(echiquier_d, Color_Player);
//    posi.joueur = 1;
//    cout<<"Original chessboard is:"<<endl;
//    posi.print_position();
//    posi.position_possible();
//    Position_Echec* pos_poss = posi.fille;
//    while (pos_poss != nullptr) {
//        Position_Echec tmp(*pos_poss);
//        tmp.mise_a_jour_position(0);
//        list<Piece*> alive = (tmp.couleur_joueur == Blanc) ? tmp.echiquier_ref->aliveN : tmp.echiquier_ref->aliveB;
//        list<Piece*>::const_iterator it;
//        for (it = alive.begin(); it != alive.end(); it++)
//        {
//            cout<<(*it)->x<<" "<<(*it)->y<<" "<<(*it)->P.Nom_piece<<endl;
//        }
//
//        tmp.print_position();
//        delete tmp.echiquier_ref;
//        pos_poss = pos_poss->soeur;
//    }
//    cout<<"----------------------------------"<<endl;
//    pos_poss = posi.fille;
//    cout<<"Daughter chessboard is:"<<endl;
//
//    pos_poss->affiche_attributs();
//    pos_poss->position_possible();
//
//    Position_Echec* pos_poss2 = pos_poss->fille;
//    while (pos_poss2!= nullptr){
//        Position_Echec tmp(*pos_poss2);
//        tmp.mise_a_jour_position(0);
//        list<Piece*> alive = (tmp.couleur_joueur == Blanc) ? tmp.echiquier_ref->aliveN : tmp.echiquier_ref->aliveB;
//        list<Piece*>::const_iterator it;
//        for (it = alive.begin(); it != alive.end(); it++)
//        {
//            cout<<(*it)->x<<" "<<(*it)->y<<" "<<(*it)->P.Nom_piece<<endl;
//        }
//        tmp.print_position();
//        pos_poss2 = pos_poss2->soeur;
//        tmp.free();
//    }
//
//    pos_poss2 = pos_poss->fille;
//    cout<<"Daughter chessboard is:"<<endl;
//
//    pos_poss2->affiche_attributs();
//    pos_poss2->position_possible();
//
//    Position_Echec* pos_poss3 = pos_poss2->fille;
//    while (pos_poss3!= nullptr){
//        Position_Echec tmp(*pos_poss3);
//        tmp.mise_a_jour_position(0);
//        tmp.print_position();
//        pos_poss3 = pos_poss3->soeur;
//        tmp.free();
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
//     echiquier_test_echec(echiquier_d);
//
////   Initialize the position, always start with white.
//    Position_Echec posi(echiquier_d, Color);
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






