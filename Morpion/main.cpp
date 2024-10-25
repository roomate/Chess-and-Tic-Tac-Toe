#include <iostream>
#include "class_position.hpp"

using namespace std;

int main()
{
    Position_Morpion Q(1); //Default constructor
    Position_Morpion& P = Q; //Copy constructor
    bool victoire_joueur = false; //Player 1
    bool victoire_ordi = false; //Player 2
    char x;
    int minimaxi;
    int maxi;
    int n = 0;
    bool nul = false;
    P.print_position();
    while (victoire_joueur == false && victoire_ordi == false && nul == false)
    {
        cout<<" C'est au tour du Player "<<P.joueur<<" de jouer"<<endl;
        if (P.joueur == 1)
        {
            cout<<"Joue ton coup"<<endl;
            cin>>x;
            while (x > 58 || x < 49)
            {
                cout<<"coup non valide.\n";
                cin>>x;
            }
            printf("%d\n", x - 48);
            while (P.G.T[(x - 48) - 1] != 0)
            {
                cout<<"Refaire le coup, zone deja prise.\n";
                cin>>x;
            }
            P.G.T[(x - 48) - 1] = 1;
            victoire_joueur = P.gagne();
            P.joueur = 2;
            if (P.pleine()) {nul = true;}
        }
        else
        {
            P.fille = nullptr;
            P.position_possible();

            if (P.fille == nullptr)
            {nul = true;}
            else
            {
                Position *fille = P.fille->soeur;
                minimaxi = minimax(*P.fille,0,0,9);
                maxi = minimaxi;
                P = dynamic_cast<Position_Morpion&> (*P.fille);
                while (fille != nullptr)
                {
                    minimaxi = minimax(*fille,0,0,9);
                    if (minimaxi<maxi)
                    {
                        P = dynamic_cast<Position_Morpion &> (*fille);
                        maxi = minimaxi;
                    }
                    fille = fille->soeur;
                }
            }
        }
        victoire_ordi = P.gagne();
        ++n;
        P.print_position();
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
