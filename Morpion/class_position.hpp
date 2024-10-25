#ifndef CLASS_POSITION_HPP
#define CLASS_POSITION_HPP

#include <iostream>
#include <cmath>
using namespace std;




class grille{
public:
    int* T;
    grille(const grille& g);
    grille();
    void affichage() const;
    bool a_gagne(int joueur) const;
    bool grille_pleine() const;
    int& operator[](int i);
    grille& operator=(const grille& g);
    ~grille() {if (T!= nullptr) delete [] T;}
};


class Position
{
public:
    int joueur;
    Position(int J) : joueur(J) {}
    virtual double valeur_position() const =0;
    Position* fille = NULL;
    Position* soeur = NULL;
    virtual ~Position(){};
    virtual Position& position_possible() = 0;
    virtual void print_position() const = 0;
    virtual bool gagne() const = 0;
};

class Position_Morpion : public Position
{
public:
    grille G;
    int possession(int i, int j) const {return G.T[i*3+j];}
    Position_Morpion(int J) : Position(J) {init();}
    void init() {grille G();}
    Position_Morpion& position_possible();
    bool gagne() const ;
    double valeur_position() const ;
    ~Position_Morpion()
    {

        if (this->fille != nullptr)
        {
            delete this->fille;
            this->fille = nullptr;
        }
        if (this->soeur != nullptr)
        {
           delete this->soeur;
           this->soeur = nullptr;
        }
    }
    void print_position() const {G.affichage();}
    bool pleine() const {return G.grille_pleine();}
};


int minimax(Position &P, int alpha, int beta, int depth);

#endif // CLASS_POSITION_HPP
