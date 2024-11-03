#include <iostream>
#include "class_position.hpp"

using namespace std;

struct GameState {
    bool victoire_joueur = false;
    bool victoire_ordi = false;
    bool nul = false;
};

int main()
{
    Position_Morpion P(1); //Default constructor
    GameState GS;
    int minimaxi;
    int maxi;

    while (!GS.victoire_joueur && !GS.victoire_ordi && !GS.nul)
    {
        P.print_position();
        cout<<"C'est au tour du Player "<<P.joueur<<" de jouer"<<endl;
        if (P.joueur == 1)
        {
            P.coup_humain();
            P.mise_a_jour_position(0);
            GS.victoire_joueur = P.gagne();
            if (P.pleine()) GS.nul = true;
            P.joueur = 2;
        }
        else if (P.joueur == 2)
        {
            P.position_possible(); //Allocate memory to get all the 'fille' possible positions
            Position_Morpion* best_fille;
            Position_Morpion* fille = P.fille;
            if (fille == nullptr) GS.nul = true;
            else
            {
                minimaxi = minimax(*fille, 0, 0, 7);
                maxi = minimaxi;
                best_fille = fille;
                fille = P.fille->soeur;
                while (fille != nullptr)
                {
                    minimaxi = minimax(*fille, 0, 0, 7);
                    if (minimaxi < maxi)
                    {
                        best_fille = fille;
                        maxi = minimaxi;
                    }
                    fille = fille->soeur;
                }
            }
            best_fille->mise_a_jour_position(0);
            P.fille = P.fille->libere_soeur();//Free all the sisters allocated at the beginning of the instruction block, and set the pointer to nullptr
            P = *best_fille;
            GS.victoire_ordi = P.gagne();
            P.joueur = 1;
        }
    }
    if (GS.victoire_joueur && !GS.victoire_ordi)
    {
        cout<<"Vous avez gagne"<<endl;
    }
    if (GS.victoire_ordi && !GS.victoire_joueur)
    {
        cout<<"L'ordinateur a gagne"<<endl;
    }
    if (GS.nul && !GS.victoire_ordi && !GS.victoire_joueur)
    {
        cout<<"Le match est nul"<<endl;
    }
    delete P.G; //Delete the memory allocated for the grid
    return 0;
}

