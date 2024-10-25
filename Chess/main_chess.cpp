#include <string>
#include "chess.hpp"
#include <cmath>
#include <iostream>
using namespace std;


int main(){

    echiquier echiquier_d = echiquier_depart();
    Position_Echec pos(echiquier_d);
    int minimaxi;
    int mini;
    int depth = 4;
    bool victoire_joueur = false; //Il joue les blancs
    bool victoire_ordi = false; //Il joue les noirs
    bool nul = false;
    string C;
    cout<<"Voulez-vous jouez les Blancs ou les Noirs ?"<<endl;
    cin>>C;
    while (C != "Blanc" && C != "Noir")
    {
        cout<<"Ca ne correspond à aucune couleur"<<endl;
        cin>>C;
    }
    if (C == "Blanc")
    {
        pos.joueur = 1;
    }
    else if (C == "Noir")
    {
        pos.joueur = 2;
    }
    pos.couleur_joueur = Blanc;
    Position_Echec& posi = pos;
    while (victoire_joueur == false && victoire_ordi == false && nul == false)
    {
        cout<<"===================================="<<endl;
        posi.echiquier_ref.affichage();
        if (posi.test_echec()==true){
            if(posi.couleur_joueur == Blanc){
                cout<<"Le joueur Noir est en position d'echec"<<endl;
            }
            else
            {
                cout<<"Le joueur Blanc est en position d'echec"<<endl;
            }
        }
        if (posi.joueur == 1) //C'est à notre tour de jouer
        {
            posi.coup_humain();
            posi.mise_a_jour_position();
            posi.joueur = 2;
        }
        else if (posi.joueur == 2) //C'est au tour de l'ordinateur de jouer
        {
            posi.fille = nullptr; //On s'assure que ces filles soient bien des pointeurs nulles
            posi.position_possible();
            if (posi.fille != nullptr)
            {
                Position* Fille = posi.fille->soeur;
                minimaxi = min(minimax(*posi.fille, 0,0 ,depth),-minimax(*posi.fille, 0,0 ,depth));
                cout<<minimaxi<<endl;
                mini = minimaxi;
                posi = dynamic_cast<Position_Echec&>(*posi.fille);
                cout<<"=====Premiere fille ======"<<endl;
                posi.mise_a_jour_position();
                posi.echiquier_ref.affichage();
                cout<<"=========================="<<endl;
                while (Fille != nullptr)
                {
                    minimaxi = minimax(*Fille, 0, 0,depth);
                    if (minimaxi < mini)
                    {
                        posi = dynamic_cast<Position_Echec&>(*Fille);
                        mini = minimaxi;
                    }
                    Fille = Fille->soeur;
                }
                posi.mise_a_jour_position();
                posi.joueur = 1;
            }
        }
        bool test_echecmat = posi.test_echec_mat();
        if (test_echecmat)
        {
            if(posi.couleur_joueur==Blanc){
                cout<<"C'est un mat : Le joueur blanc a gagne !"<<endl;
                victoire_joueur = true;
            }
            if(posi.couleur_joueur==Noir){
                cout<<"C'est un mat : Le joueur noir a gagne !"<<endl;
                victoire_ordi = true;
            }
        }
    }
    if (posi.test_match_nul()==true){
        cout<<"C'est un match nul !"<<endl;
        nul = true;
    }
    if (victoire_joueur == true && victoire_ordi == false)
    {
        cout<<"Vous avez gagne"<<endl;
    }
    if (victoire_ordi == true && victoire_joueur == false)
    {
        cout<<"L'ordinateur a gagne"<<endl;
    }
    if (nul == true && victoire_ordi == false && victoire_joueur == false)
    {
        cout<<"Le match est nul"<<endl;
    }
    return 0;
}


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






