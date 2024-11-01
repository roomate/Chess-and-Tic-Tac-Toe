#include <string>
#include "chess.hpp"
#include <cmath>
#include <list>
#include <iostream>
using namespace std;

struct GameState{
    bool match_nul = false;
    bool victoire_ordi = false;
    bool victoire_joueur = false;
};


void play_PvC(){
//    Echiquier echiquier_d;
//    PieceColor Color_Player;
//
//    int minimaxi;
//    int mini;
//    int depth = 4;
//
//    GameState GS;
//
//    bool is_check = false;
//
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
//
//    //If it is white
//    Color_Player = (C == "Blanc") ? Blanc : Noir;
//
//    //Initialize the chessboard, accordingly to the color
//    echiquier_depart(echiquier_d);
//
//    //Initialize the position, always start with white.
//    Position_Echec posi(echiquier_d, Color_Player);
//    posi.joueur = (Color_Player == Blanc) ? 1 : 2; //To anticipate the first swap
//
//    while (!GS.victoire_joueur && !GS.victoire_ordi && !GS.match_nul)
//    {
//        posi.print_position();
//        if (posi.joueur == 1) //It is the user turn
//        {
//            bool retry = posi.coup_humain(&GS.match_nul); //Make a move, Test inside if the proposed move is valid
//            while(retry) {posi.print_position(); retry = posi.coup_humain(&GS.match_nul);}
//            posi.mise_a_jour_position(1); //Update
//
//            //test a potential checkmate
//            is_check = posi.echec(posi.couleur_joueur); //Tell if the king's opponent is check or not
//            if (is_check) {cout<<"Echec"<<endl; GS.victoire_joueur = posi.echec_mat(posi.couleur_joueur);} //Tell if the king's opponent is checkmate or not
//            if (posi.test_match_nul()) GS.match_nul = true;
//            posi.joueur = 2;
//            posi.couleur_joueur = (posi.couleur_joueur == Blanc) ? Noir : Blanc; //Change the colour of the next position
//        }
//        else if (posi.joueur == 2) //Computer turn
//        {
//            posi.fille = nullptr; //Set this pointer to 0.
//            posi.position_possible(); //Get all the possibles subsequent position
//            if (posi.fille != nullptr)
//            {
//                Position* tmp;
//                Position* Fille = posi.fille;
//                minimaxi = min( minimax(*Fille, 0, 0 , depth), - minimax( *Fille, 0, 0, depth) );
//                mini = minimaxi;
//                while (Fille != nullptr)
//                {
//                    minimaxi = minimax(*Fille, 0, 0, depth);
//                    if (minimaxi < mini) //If we find a better minimum
//                    {
//                        //Update the min and best position.
//                        tmp = Fille;
//                        mini = minimaxi;
//                    }
//                    Fille = Fille->soeur;
//                }
//                tmp->mise_a_jour_position(0);
//            }
//            tmp->print_position();
//            posi.joueur = 1;
//        }
//        bool test_echecmat = posi.echec_mat();
//        if (test_echecmat)
//        {
//            switch(posi.couleur_joueur)
//            case(Blanc):
//                cout<<"C'est un mat : Le joueur blanc a gagne !"<<endl;
//                victoire_joueur = true;
//
//            case(Noir):
//                cout<<"C'est un mat : Le joueur noir a gagne !"<<endl;
//                victoire_ordi = true;
//        }
//    }
////    if (GS.match_nul){
////        cout<<"C'est un match nul !"<<endl;
////    }
////    if (GS.victoire_joueur && !GS.victoire_ordi)
////    {
////        cout<<"Vous avez gagne"<<endl;
////    }
////    if (GS.victoire_ordi && !GS.victoire_joueur)
////    {
////        cout<<"L'ordinateur a gagne"<<endl;
////    }
}


void play_PvP(){
    Echiquier echiquier_d;
    PieceColor Color_Player;

    GameState GS;

    bool is_check = false;

    //Idee de renverser le plateau si on choisit noir?
    string C;
    cout<<"Voulez-vous jouez 'Blanc' ou 'Noir' ?"<<endl;
    cin>>C;
    C = "Blanc";
    while (C != "Blanc" && C != "Noir")
    {
        cout<<"Choisissez entre 'Blanc' et 'Noir' svp."<<endl;
        cin>>C;
    }

    //If it is white
    Color_Player = (C == "Blanc") ? Blanc : Noir;

    //Initialize the chessboard, accordingly to the color
    echiquier_depart(echiquier_d);

    //Initialize the position, always start with white.
    Position_Echec posi(echiquier_d, Color_Player);
    posi.joueur = (Color_Player == Blanc) ? 1 : 2; //To anticipate the first swap

    while (!GS.victoire_joueur && !GS.victoire_ordi && !GS.match_nul)
    {
        posi.print_position();
        if (posi.joueur == 1) //It is the user turn
        {
            bool retry = posi.coup_humain(&GS.match_nul); //Make a move, Test inside if the proposed move is valid
            while(retry) {posi.print_position(); retry = posi.coup_humain(&GS.match_nul);}
            posi.mise_a_jour_position(1); //Update

            //test a potential checkmate
            is_check = posi.echec(posi.couleur_joueur); //Tell if the king's opponent is check or not
            if (is_check) {cout<<"Echec"<<endl; GS.victoire_joueur = posi.echec_mat(posi.couleur_joueur);} //Tell if the king's opponent is checkmate or not
            if (posi.match_nul()) GS.match_nul = true;
            posi.joueur = 2;
            posi.couleur_joueur = (posi.couleur_joueur == Blanc) ? Noir : Blanc; //Change the colour of the next position

        }
        else
        {
            bool retry = posi.coup_humain(&GS.match_nul); //Make a move
            while(retry) {posi.print_position(); retry = posi.coup_humain(&GS.match_nul);}
            posi.mise_a_jour_position(1); //Update

            //test a potential checkmate
            is_check = posi.echec(posi.couleur_joueur); //Tell if the king's opponent is check or not
            is_check = posi.echec(posi.couleur_joueur); //Tell if the king's opponent is check or not
            if (is_check) {GS.victoire_joueur = posi.echec_mat(posi.couleur_joueur);}
            if (posi.match_nul()) GS.match_nul = true; //Test if the party can keep going on

            //Update chessboard player
            posi.joueur = 1;
            posi.couleur_joueur = (posi.couleur_joueur == Blanc) ? Noir : Blanc; //Change the colour of the next position

        }
    }
    if (GS.match_nul){
        cout<<"C'est un match nul !"<<endl;
    }
    if (GS.victoire_joueur && !GS.victoire_ordi)
    {
        cout<<"Vous avez gagne"<<endl;
    }
    if (GS.victoire_ordi && !GS.victoire_joueur)
    {
        cout<<"L'ordinateur a gagne"<<endl;
    }
//    while (pos_poss != nullptr) {pos_poss->print_position(); pos_poss = pos_poss->soeur;}
}

