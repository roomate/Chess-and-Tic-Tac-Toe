#ifndef CLASS_POSITION_HPP
#define CLASS_POSITION_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <list>

using namespace std;

class grille
{
public:
//============================================================
//=======================Attributes===========================
//============================================================
    int *T = nullptr;
//============================================================
//=======================Constructors==========================
//============================================================
    grille(const grille &g);
    grille();
//============================================================
//=======================Methods==============================
//============================================================
    void affichage() const;
    bool a_gagne(int joueur) const;
    bool grille_pleine() const;
    int &operator[](int i);
    grille &operator=(const grille &g);
    ~grille()
    {
        if (T != nullptr)
            delete[] T;
    }
};

class Position
{
public:
//============================================================
//=======================Attributes===========================
//============================================================
    int joueur;

//============================================================
//=======================Constructor==========================
//============================================================

    Position(int J) : joueur(J) {}

//============================================================
//=======================Methods==============================
//============================================================

    virtual double valeur_position() const = 0;
    virtual ~Position() {};
    virtual void mise_a_jour_position(const bool text) = 0;
    virtual void print_position() const = 0;
    virtual bool gagne() const = 0;
    virtual void position_possible() = 0;
    virtual Position* get_soeur() const = 0;
    virtual Position* get_fille() const = 0;
};

class Position_Morpion : public Position
{
public:
//============================================================
//=======================Attributes===========================
//============================================================

    grille* G = nullptr;
    list<vector<int>> coup;
    Position_Morpion *fille = nullptr;
    Position_Morpion *soeur = nullptr;


//============================================================
//=======================Constructor==========================
//============================================================
    //Copy constructor, normally not used.
    Position_Morpion(const Position_Morpion& Pos) : Position(Pos.joueur)
    {
        G = new grille(*Pos.G);
        coup = Pos.coup;
    }

    Position_Morpion(const int J) : Position(J) {init(); }
    Position_Morpion(const int J, const list<vector<int>> cp) : Position(J) {coup = cp;}
    void init() {G = new grille();}

    Position_Morpion& operator=(const Position_Morpion& Pos);

//============================================================
//=========================Methods============================
//============================================================

    int possession(int i, int j) const { return G->T[i * 3 + j]; }

    void position_possible();
    bool gagne() const;
    double valeur_position() const;

    ~Position_Morpion()
    {
        coup.clear();
        //Do NOT free the grid, its memory allocation is unique in the algorithm.
//        if (this->fille != nullptr)
//        {
//                delete this->fille;
//            this->fille = nullptr;
//        }
//        if (this->soeur != nullptr)
//        {
//            delete this->soeur;
//            this->soeur = nullptr;
//        }
    }
    Position_Morpion* libere_soeur(); //Supposed to return a nullptr
    void print_position() const { G->affichage(); }
    bool pleine() const {return G->grille_pleine(); }
    bool is_valid_move(int i) const;
    void mise_a_jour_position(const bool text);
    void coup_humain();
    void affiche_fille();

    Position* get_soeur() const {return soeur;}
    Position* get_fille() const {return fille;}
};


int minimax(Position &P, int alpha, int beta, int depth);

#endif // CLASS_POSITION_HPP
