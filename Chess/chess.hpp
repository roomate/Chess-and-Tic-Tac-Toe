#ifndef CHESS_HPP
#define CHESS_HPP

#include <iostream>
#include <cmath>
#include <vector>
#include <list>
#include <cstring>

using namespace std;

enum PieceColor {
	Blanc, Noir
};

enum PieceType {
	pion, tour, fou, cavalier, dame, roi
};

class Type_Piece{
public:
    PieceType Nom_piece;
    vector<vector<int>> Dep_rel;
    int valeur;
    ~Type_Piece(){
        Dep_rel.clear();
    }

    Type_Piece& operator=(const Type_Piece P) {
        Nom_piece = P.Nom_piece;
        Dep_rel = P.Dep_rel;
        valeur = P.valeur;
        return *this;
    }
};

class Pion: public Type_Piece {
public:
	Pion() {
		Nom_piece = pion;
		valeur = 100;
		vector<vector<int>> Tableau{ { 0, 1, -1, 0 },
                                     { 1, 1, 1, 2 },
                                     { 1, 1, 1, 1 } };
		Dep_rel= Tableau;
	}
};
class Tour: public Type_Piece {
public:
	Tour() {
		Nom_piece = tour;

		vector<vector<int>> Tableau{ { 0, 1, 0, -1 },
                                     { 1, 0, -1, 0 },
                                     { 0, 0, 0, 0 } };

		Dep_rel= Tableau;
        valeur = 500;
	}


};
class Fou: public Type_Piece {
public:
	Fou() {
		Nom_piece = fou;
        vector<vector<int>> Tab{ { 1, 1, -1, -1 },
                                 { 1, -1, 1, -1 },
                                 { 0, 0, 0, 0 } };
		Dep_rel= Tab;
		valeur = 300;
	}


};
class Cavalier: public Type_Piece {
public:
	Cavalier() {

		Nom_piece = cavalier;


		vector<vector<int>> Tableau{{ 1, 1, -1, -1, 2, 2, -2, -2 },
                                    { -2, 2, 2, -2, 1, -1, 1, -1 },
                                    {1, 1, 1, 1, 1, 1, 1, 1}     };

		Dep_rel= Tableau;
		valeur = 300;
	}



};
class Dame: public Type_Piece {
public:
	Dame() {
		Nom_piece = dame;

		vector<vector<int>> Tableau{{ 0, 1, 0, -1, 1, 1, -1, -1 },
                                    { 1, 0, -1, 0, 1, -1, 1, -1},
                                    { 0, 0, 0, 0, 0, 0, 0, 0 } };

        Dep_rel= Tableau;
		valeur = 900;
	}


};
class Roi: public Type_Piece {
public:
	Roi() {
		Nom_piece = roi;

		vector<vector<int>> Tableau{{ 0, 1, 0, -1, 1, 1, -1, -1 },
                                    { 1, 0, -1, 0, 1, -1, 1, -1},
                                    { 1, 1, 1, 1, 1, 1, 1, 1} };
        Dep_rel=Tableau;
        valeur = 0;
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
    Position(){};
    virtual ~Position() {};
    virtual void mise_a_jour_position(const bool text) = 0;
    virtual void print_position() const = 0;
    virtual bool gagne() const = 0;
    virtual void position_possible() = 0;
    virtual Position* get_soeur() = 0;
    virtual Position* get_fille() = 0;
    virtual void free() = 0; //Deleter of the board
};


class Piece{
public:
//============================================================
//=======================Attributes===========================
//============================================================
    Type_Piece P;
    PieceColor Couleur;
    // Essential to test checkmate
    int x;
    int y;
    bool a_bouge = false;
//============================================================
//=======================Constructor==========================
//============================================================

    //Constructeur de la classe
    Piece(Piece& p){
        x = p.x;
        y = p.y;
        Couleur = p.Couleur;
        P = p.P;
        a_bouge = p.a_bouge;
    }
    Piece(){}
    //Basic constructor
    Piece(PieceType nom_piece, PieceColor couleur, int a, int b, bool bouge){
        x = b;
        y = a;
        a_bouge = bouge;
        Couleur = couleur;
        if (nom_piece == roi){
            Roi piece;
            P = piece;
        }
        if (nom_piece == pion){
            Pion piece;
            P = piece;
        }
        if (nom_piece == tour){
            Tour piece;
            P = piece;
        }
        if (nom_piece == dame){
            Dame piece;
            P = piece;
        }
        if (nom_piece == fou){
            Fou piece;
            P = piece;
        }
        if (nom_piece == cavalier){
            Cavalier piece;
            P = piece;
        }
    }

    //Basic constructor
    Piece(const PieceType nom_piece, const PieceColor couleur, const int a, const int b){
        x = b;
        y = a;
        Couleur = couleur;
        if (nom_piece == roi){
            Roi Piece;
            P = Piece;
        }
        if (nom_piece == pion){
            Pion Piece;
            P = Piece;
        }
        if (nom_piece == tour){
            Tour Piece;
            P = Piece;
        }
        if (nom_piece == dame){
            Dame Piece;
            P = Piece;
        }
        if (nom_piece == fou){
            Fou Piece;
            P = Piece;
        }
        if (nom_piece == cavalier){
            Cavalier Piece;
            P = Piece;
        }
    }


//============================================================
//=========================Methods============================
//============================================================
    ~Piece(){}//deleter

    Piece& operator=(Piece& Pi) {this->P = Pi.P; this->Couleur = Pi.Couleur; this->x = Pi.x; this->y = Pi.y; this->a_bouge = Pi.a_bouge; return *this;}


    const char* string_type(){ //Permet de récuperer une chaine de caractère correspondant au Type de piece
        switch(P.Nom_piece){
            case dame : return("D");
            case roi : return("R");
            case pion : return("P");
            case cavalier : return("C");
            case fou : return("F");
            case tour : return("T");
        }
        return ("erreur string_type");
    }
};


class Echiquier{
public:
//============================================================
//=======================Attributes===========================
//============================================================
    //piece plateau[64];
    vector<Piece*> plateau;
    list<Piece*> aliveB; //List all the user's piece alive
    list<Piece*> aliveN; //List all the opponent's piece alive
    Piece* roi_B = nullptr; //State where the king of Player 1 is, useful for checkmate
    Piece* roi_N = nullptr; //State where the king of Player 2 is

//============================================================
//=======================Constructor==========================
//============================================================
    Echiquier(){
        plateau.resize(64,nullptr); //Initialize all pointers to NULL
    }

    Echiquier(const Echiquier &p){ //Copy constructor
        plateau.resize(64,NULL);
        for (int i = 0; i<=63; i++){
            if (p.plateau[i] != nullptr){
                plateau[i] = new Piece(p.plateau[i]->P.Nom_piece, p.plateau[i]->Couleur, p.plateau[i]->y, p.plateau[i]->x, p.plateau[i]->a_bouge);
                switch(p.plateau[i]->Couleur){
                    case(Blanc): aliveB.push_front(plateau[i]); break;
                    case(Noir): aliveN.push_front(plateau[i]);
                }
                if (p.plateau[i]->P.Nom_piece == roi)
                {
                    if (p.plateau[i]->Couleur == Blanc) roi_B = plateau[i];
                    else if (p.plateau[i]->Couleur == Noir) roi_N = plateau[i];
                }
            }
        }
    }
//============================================================
//=========================Methods============================
//============================================================

    //Overload of operator =
    Echiquier& operator=(const Echiquier &p){
        if (plateau.size() != 0) plateau.clear();
        plateau = p.plateau;
        aliveB = p.aliveB;
        aliveN = p.aliveN;
        roi_B = p.roi_B;
        roi_N = p.roi_N;
        return *this;
    }

    ~Echiquier(){ //Chess deleter
//        for (int i = 0; i<=63; i++){
//            if (plateau[i] != nullptr){delete[] plateau[i];} //Call the piece deleter
//        }
//        plateau.clear();
        aliveB.clear();
        aliveN.clear();
        if (roi_B != nullptr) delete roi_B;
        if (roi_N != nullptr) delete roi_N;
    }
    void affichage() const;
};

class Coup_Echec{
public:
//============================================================
//=======================Attributes===========================
//============================================================
    int joueur;
    PieceColor couleur_c;
    //Coordinates of initial and final position
    vector<int> init;
    vector<int> fin;

    //Special moves
    bool p_rock = false;
    bool g_rock = false;
    bool prom_f = false;
    bool prom_d = false;
    bool prom_c = false;
    bool prom_t = false;

    bool echec = false; //Check if there is a check
    bool echec_mat = false; //Check if there is a checkmate

//============================================================
//=======================Constructor==========================
//============================================================

    ~Coup_Echec() {}

    //Null constructor
    Coup_Echec(){}

    //Copy constructor
    Coup_Echec(const Coup_Echec &c);

    //Constructor of a chess move when taking an opponent piece; no need of color.
    Coup_Echec(const int y, const int x, const int mv_y, const int mx_x, const PieceColor C, const int j);

    //Constructor for a roocs move.
    Coup_Echec(const char* nom_coup,const PieceColor couleur, const int j);

    //Constructor of a move promoting a piece and taking another.
    Coup_Echec(const char* nom_coup, const int y, const int x, const int mv_y, const int mv_x, const PieceColor C, const int j);

//============================================================
//=======================Methods==============================
//============================================================

    void affichage_standard(const Echiquier* E) const; //Displays the chess
};

class Position_Echec: public Position {
public:
//============================================================
//=======================Attributes===========================
//============================================================
    PieceColor couleur_joueur; //Color of the player having to play
    list<Coup_Echec> Liste_coup; //List of move from the beginning of the game
    Echiquier* echiquier_ref; //Current state of the chessboard

    Position_Echec* fille = nullptr;
    Position_Echec* soeur = nullptr;

//============================================================
//=======================Constructor==========================
//============================================================

    //Basic constructor
    Position_Echec(const Echiquier& E, const PieceColor C, const list<Coup_Echec> L){
        echiquier_ref = new Echiquier(E); //Call the copy constructor of the class echiquier, make a deep copy
        couleur_joueur = C;
        Liste_coup = L;
    }

    //Basic constructor
    Position_Echec(const list<Coup_Echec> L){
        Liste_coup = L;
    }

    //Basic constructor
    Position_Echec(const Echiquier& E, const PieceColor C): couleur_joueur(C){
        echiquier_ref = new Echiquier(E); //Call the copy constructor of the class echiquier
    }

    //Basic constructor
    Position_Echec(const PieceColor couleur) : couleur_joueur(couleur){
    }

    //Copy constructor
    Position_Echec(const Position_Echec& Pos): couleur_joueur(Pos.couleur_joueur)
    {
        Liste_coup = Pos.Liste_coup;
        echiquier_ref = new Echiquier(*Pos.echiquier_ref); //We could also do new echiquier(*pos)
        joueur = Pos.joueur;
    }
    Position_Echec(){}

    Position_Echec& operator=(const Position_Echec& Pos){
        echiquier_ref = Pos.echiquier_ref;
        Liste_coup = Pos.Liste_coup;
        couleur_joueur = Pos.couleur_joueur;
        fille = Pos.fille;
        soeur = Pos.soeur;
        return *this;
    }

//============================================================
//=========================Methods============================
//============================================================

    //Destructor
    ~Position_Echec()
    {
        Liste_coup.clear();
    }

    void position_possible(); //List all the possible consecutive move given a chessboard.


    bool gagne()const {return true;} //correspond au test d'echec et mat

    //Test if a rooc is feasible
    bool p_rooc(const bool text) const;
    bool g_rooc(const bool text) const;

    //Test if a move is valid given a chessboard disposition
    bool coup_valide(const int& y, const int& x, const int& mv_y, const int& mv_x, const PieceColor C,const bool text) const;
    bool tous_valide(const int& y, const int& x, const int& mv_y, const int& mv_x, const bool text) const;
    bool valid_check(const int y, const int x, const int mv_y, const int mv_x) const;
    bool test_chemin(const int y, const int x, const int mv_y, const int mv_x, const bool text) const;
    bool dep_valide(const int y, const int x, const int mv_y, const int mv_x, const bool text) const; //Check if the move is valid

    Position* get_soeur() {return soeur;}
    Position* get_fille() {return fille;}

    bool coup_humain(bool* nul); //Perform the move indicated by the user

    bool echec(const PieceColor C) const; //Test echec pour regarder si le roi adverse est en échec ou non
    bool match_nul() const; //Test if it is a draw
    bool echec_mat(const PieceColor C) const;

    void mise_a_jour_coup(const Coup_Echec& move_chess, const bool text);
    void mise_a_jour_position(const bool text);

    double valeur_position() const;

    string affiche_couleur(const PieceColor C) const;
    void print_position() const {cout<<"===================================="<<endl; cout<<"C'est le tour du joueur "<<this->joueur<<", sa couleur est "<<affiche_couleur(this->couleur_joueur)<<endl; echiquier_ref->affichage();}
    void affiche_attributs() const;

    void ajoute_fille(const int y, const int x, const int mv_y, const int mv_x);
    void ajoute_fille(const char* Prom, const int y, const int x, const int mv_y, const int mv_x);
    void ajoute_fille(const char* rooc);

    void free();

    Position_Echec* libere_soeur(); //Supposed to return a nullptr
};


//=============================
//   Fonctions externes
//=============================

void echiquier_depart(Echiquier& E);
void echiquier_test_p_rooc(Echiquier& E);
void echiquier_test_g_rooc(Echiquier& E);
void echiquier_test_prom(Echiquier& E);
void echiquier_test_echec(Echiquier& E);
void echiquier_test_echec_mat(Echiquier& E);
void echiquier_piece(Echiquier& E);
void echiquier_test_pion(Echiquier& E);
void echiquier_test_echec_rooc(Echiquier& E);
void echiquier_test(Echiquier& E);

void elimine_piece(Position_Echec& Posi, Piece* Pprise, const Piece* const Pjoue, const bool text);

void convert(string pos_init, string pos_fin, int& y, int& x, int& mv_y, int& mv_x);

void affichage_fille(Position_Echec& P);

void call_for_position(string* pos_init, string* pos_final);

int minimax(Position &P, int alpha, int beta, int depth);

bool interieur_plateau(int y,int x);

bool find_word(string mot, vector<string> list_mot);

//Check if a move is valid according to the game's rules
bool is_valid_pion(const int y, const int x, const int mv_y, const int mv_x, const Piece* Pjoue, const Piece* Pp, const bool text);
bool is_valid_tour(const int y, const int x, const int mv_y, const int mv_x, const bool text);
bool is_valid_dame(const int y, const int x, const int mv_y, const int mv_x, const bool text);
bool is_valid_fou(const int y, const int x, const int mv_y, const int mv_x, const bool text);
bool is_valid_roi(const int y, const int x, const int mv_y, const int mv_x, const bool text);
bool is_valid_cavalier(const int y, const int x, const int mv_y, const int mv_x, const bool text);

inline int abs(int a){return (a>0) ? a : -a;}

void play_PvP();
void play_PvC();

PieceColor inverse_color(const PieceColor C);

void echiquier_test_p_g_rooc(Echiquier& E);

string affiche_couleur(const PieceColor C);

void ask_promotion();

#endif
