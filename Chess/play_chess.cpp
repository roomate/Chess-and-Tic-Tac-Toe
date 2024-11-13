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
    Echiquier echiquier_d;
    PieceColor Color_Player;

    int minimaxi;
    int mini;
    int depth = 4;

    GameState GS;

    bool is_check = false;

    string C;
    cout<<"Voulez-vous jouez 'Blanc' ou 'Noir' ?"<<endl;
//    cin>>C;
    C  = "Blanc";
    while (C != "Blanc" && C != "Noir")
    {
        cout<<"Choisissez entre 'Blanc' et 'Noir' svp."<<endl;
        cin>>C;
    }

    Color_Player = (C == "Blanc") ? Blanc : Noir;

//    Initialize the chessboard, accordingly to the color
    echiquier_depart(echiquier_d);

//    Initialize the position, always start with White.
    Position_Echec posi(echiquier_d, Blanc);
    posi.joueur = (Color_Player == Blanc) ? 1 : 2; //White always starts

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
        }
        else if (posi.joueur == 2) //Computer turn
        {
            Position_Echec* tmp;
            posi.fille = nullptr; //Set this pointer to 0.
            posi.position_possible(); //Get all the possibles subsequent position
            tmp = posi.fille;
            tmp=posi.fille;
            if (posi.fille != nullptr)
            {
                Position_Echec* Fille = posi.fille;
                minimaxi = minimax(*Fille, 0, 0, depth);
                mini = minimaxi;
                Fille = Fille->soeur;
                while (Fille != nullptr)
                {
                    minimaxi = minimax(*Fille, 0, 0, depth);
                    if (minimaxi < mini) //If we find a better minimum
                    {
//                      Update the min and best position.
                        tmp = Fille;
                        mini = minimaxi;
                    }
                    Fille = Fille->soeur;
                }
            }
            tmp->mise_a_jour_position(1);
            //Free all the daughters, except the one selected
            Position_Echec* tmp2 = posi.fille;
            Position_Echec* tmp3;
            while (tmp2 != nullptr){
                if (tmp2 != tmp) {tmp3 = tmp2->soeur; delete tmp2; tmp2 = tmp3;}
                else tmp3 = tmp2->soeur; tmp2 = tmp3;
            }
            posi = *tmp;

            //test a potential checkmate
            is_check = posi.echec(posi.couleur_joueur); //Tell if the king's opponent is check or not
            cout<<is_check<<endl;
            if (is_check) {cout<<"Echec"<<endl; GS.victoire_ordi = posi.echec_mat(posi.couleur_joueur);} //Tell if the king's opponent is checkmate or not
            if (posi.match_nul()) GS.match_nul = true;

            posi.joueur = 1;
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
    posi.free();
}


void play_PvP(){
    Echiquier echiquier_d;
    PieceColor Color_Player;

    GameState GS;

    bool is_check = false;

    string C;
    cout<<"Voulez-vous jouez 'Blanc' ou 'Noir' ?"<<endl;
    cin>>C;
    while (C != "Blanc" && C != "Noir")
    {
        cout<<"Choisissez entre 'Blanc' et 'Noir' svp."<<endl;
        cin>>C;
    }

    Color_Player = (C == "Blanc") ? Blanc : Noir;

    //Initialize the chessboard, accordingly to the color
    echiquier_depart(echiquier_d);

    //Initialize the position, always start with white.
    Position_Echec posi(echiquier_d, Color_Player);
    posi.joueur = (Color_Player == Blanc) ? 1 : 2;
    while (!GS.victoire_joueur && !GS.victoire_ordi && !GS.match_nul)
    {
        posi.print_position();
        if (posi.joueur == 1) //It is the user turn
        {
            bool retry = posi.coup_humain(&GS.match_nul); //Make a move, Test inside if the proposed move is valid
            while(retry) {posi.print_position(); retry = posi.coup_humain(&GS.match_nul);}
            cout<<posi.couleur_joueur<<endl;
            posi.mise_a_jour_position(1); //Update
            cout<<posi.couleur_joueur<<endl;

            //test a potential checkmate
            is_check = posi.echec(posi.couleur_joueur); //Tell if the king's opponent is check or not
            if (is_check) {cout<<"Echec"<<endl; GS.victoire_joueur = posi.echec_mat(posi.couleur_joueur);} //Tell if the king's opponent is checkmate or not
            if (posi.match_nul()) GS.match_nul = true;
            posi.joueur = 2;
        }
        else
        {
            bool retry = posi.coup_humain(&GS.match_nul); //Make a move
            while(retry) {posi.print_position(); retry = posi.coup_humain(&GS.match_nul);}
            posi.mise_a_jour_position(1); //Update

            //test a potential checkmate
            is_check = posi.echec(posi.couleur_joueur); //Tell if the king's opponent is check or not
            if (is_check) {cout<<"Le roi est en echec"<<endl; GS.victoire_joueur = posi.echec_mat(posi.couleur_joueur);}
            if (posi.match_nul()) GS.match_nul = true; //Test if the party can keep going on
            //Update chessboard player
            posi.joueur = 1;
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
    posi.free();
}

