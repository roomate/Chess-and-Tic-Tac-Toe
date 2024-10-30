#include <string>
#include "chess.hpp"
#include <cmath>
#include <list>
#include <iostream>
using namespace std;



int main(){
    echiquier echiquier_d;
    PieceColor Color_Player;
    int minimaxi;
    int mini;
    int depth = 4;
    bool victoire_joueur = false; //Plays the whites
    bool victoire_ordi = false; //Plays the blacks
    bool* nul = new bool; *nul = false;

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

    Position* pos_poss = posi.position_possible();
    while (victoire_joueur == false && victoire_ordi == false && *nul == false)
    {
        posi.print_position();
        if (posi.joueur == 1) //It is the user turn
        {
            bool retry = posi.coup_humain(nul); //Make a move, Test inside if the proposed move is valid
            while(retry) {posi.print_position(); retry = posi.coup_humain(nul);}
            posi.mise_a_jour_position(1); //Update

            //test a potential checkmate
            is_check = posi.test_echec(posi.couleur_joueur); //Tell if the king's opponent is check or not
            if (is_check) {cout<<"Echec"<<endl; victoire_joueur = posi.test_echec_mat(posi.couleur_joueur);} //Tell if the king's opponent is checkmate or not
            if (posi.test_match_nul()) *nul = true;
            posi.joueur = 2;
            posi.couleur_joueur = (posi.couleur_joueur == Blanc) ? Noir : Blanc; //Change the colour of the next position

        }
        else
        {
            bool retry = posi.coup_humain(nul); //Make a move
            while(retry) {posi.print_position(); retry = posi.coup_humain(nul);}
            posi.mise_a_jour_position(1); //Update

            //test a potential checkmate
            is_check = posi.test_echec(posi.couleur_joueur); //Tell if the king's opponent is check or not
            is_check = posi.test_echec(posi.couleur_joueur); //Tell if the king's opponent is check or not
            if (is_check) {victoire_joueur = posi.test_echec_mat(posi.couleur_joueur);}
            if (posi.test_match_nul()) *nul = true; //Test if the party can keep going on

            //Update chessboard player
            posi.joueur = 1;
            posi.couleur_joueur = (posi.couleur_joueur == Blanc) ? Noir : Blanc; //Change the colour of the next position

        }
    }
//        else if (posi.joueur == 2) //Computer turn
//        {
//            posi.fille = nullptr; //On s'assure que ces filles soient bien des pointeurs nulles
//            posi.position_possible(); //Fill the positions fille and its soeurs
//            if (posi.fille != nullptr)
//            {
//                Position* Fille = posi.fille->soeur;
//                minimaxi = min(minimax(*posi.fille, 0,0 ,depth),-minimax(*posi.fille, 0,0 ,depth));
//                cout<<minimaxi<<endl;
//                mini = minimaxi;
//                posi = dynamic_cast<Position_Echec&>(*posi.fille);
//                cout<<"=====Premiere fille ======"<<endl;
//                posi.mise_a_jour_position();
//                posi.echiquier_ref.affichage();
//                cout<<"=========================="<<endl;
//                while (Fille != nullptr)
//                {
//                    minimaxi = minimax(*Fille, 0, 0,depth);
//                    if (minimaxi < mini)
//                    {
//                        posi = dynamic_cast<Position_Echec&>(*Fille);
//                        mini = minimaxi;
//                    }
//                    Fille = Fille->soeur;
//                }
//                posi.mise_a_jour_position();
//            }
//            posi.joueur = 1;
//        }
//        bool test_echecmat = posi.test_echec_mat();
//        if (test_echecmat)
//        {
//            if(posi.couleur_joueur==Blanc){
//                cout<<"C'est un mat : Le joueur blanc a gagne !"<<endl;
//                victoire_joueur = true;
//            }
//            if(posi.couleur_joueur==Noir){
//                cout<<"C'est un mat : Le joueur noir a gagne !"<<endl;
//                victoire_ordi = true;
//            }
//        }
//    }
    if (*nul==true){
        cout<<"C'est un match nul !"<<endl;
    }
    if (victoire_joueur == true && victoire_ordi == false)
    {
        cout<<"Vous avez gagne"<<endl;
    }
    if (victoire_ordi == true && victoire_joueur == false)
    {
        cout<<"L'ordinateur a gagne"<<endl;
    }
    while (pos_poss != nullptr) {pos_poss->print_position(); pos_poss = pos_poss->soeur;}
    return 0;
}

//To test position_possible()
//int main(){
//    echiquier echiquier_d;
//    PieceColor Color_Player;
//    echiquier_test_echec_mat(echiquier_d);
//    Position_Echec posi(echiquier_d, Color_Player);
//    cout<<"Original chessboard is:"<<endl;
//    posi.print_position();
//    posi.couleur_joueur = Noir;
//    Position* pos_poss = posi.position_possible();
//    while (pos_poss != nullptr) {pos_poss->print_position(); pos_poss = pos_poss->soeur;}
//    return 0;
//}


//To test check
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
//     echiquier_test_echec(echiquier_d);
//
////   Initialize the position, always start with white.
//    Position_Echec posi(&echiquier_d, Color);
//    posi.joueur = (Color == Blanc) ? 1 : 2; //To anticipate the first swap
//    posi.print_position();
//    cout<<posi.test_echec(Noir)<<endl;
//    return 0;
//}

//To test checkmate
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
//    Position_Echec posi(&echiquier_d, Color);
//    posi.joueur = (Color == Blanc) ? 1 : 2; //To anticipate the first swap
//    posi.print_position();
//    cout<<posi.test_echec_mat(Noir)<<endl;
//    return 0;
//}



//int main() //Main test pour voir si le pion mange un cavalier quand il a l'occasion
//{
//    int mini;
//    int minimaxi;
//    echiquier echiquier_d = echiquier_test_pion();
//    echiquier_d.affichage();
//    Position_Echec E(echiquier_d);
//    E.couleur_joueur = Blanc;
//    E.joueur = 2;
//    affichage_fille(E);
////    E.position_possible();
////    Position_Echec& Fille = dynamic_cast<Position_Echec&>(*E.fille->soeur);
////    cout<<"==============================="<<endl;
////    Fille.mise_a_jour_position();
////    Fille.echiquier_ref.affichage();
////    cout<<minimax(E,0,0,1)<<endl;
////    cout<<minimax(Fille,0,0,1)<<endl;
////    if (E.fille != nullptr)
////    {
////        Position* Filles = Fille.soeur;
////        minimaxi = minimax(Fille, 0,0 ,1);
////        mini = minimaxi;
////        E = dynamic_cast<Position_Echec&>(Fille);
////        E.echiquier_ref.affichage();
////        while (Filles != nullptr)
////        {
////            minimaxi = minimax(Fille, 0, 0,1);
////            if (minimaxi < mini)
////            {
////                E = dynamic_cast<Position_Echec&>(*Filles);
////                mini = minimaxi;
////            }
////            cout<<mini<<endl;
////            Filles = Filles->soeur;
////        }
////        E.mise_a_jour_position();
////        E.joueur = 1;
////    }
////    E.echiquier_ref.affichage();
////    return 0;
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






