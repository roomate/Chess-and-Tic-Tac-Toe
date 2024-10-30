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
	Pion, Tour, Fou, Cavalier, Dame, Roi
};

class type_piece{
public:
    PieceType Nom_piece;
    vector<vector<int>> Dep_rel;
    int valeur;
    ~type_piece(){
        Dep_rel.clear();
    }
};

class pion: public type_piece {
public:
	pion() {
		this->Nom_piece = Pion;
		this->valeur = 100;
		vector<vector<int>> Tableau{ { 0, 1, 1, 0 },
                                     { 1, 1, -1, 2 },
                                     { 1, 1, 1, 1 } };
		this->Dep_rel= Tableau;
	}
};
class tour: public type_piece {
public:
	tour() {
		this->Nom_piece = Tour;

		vector<vector<int>> Tableau{ { 0, 1, 0, -1 },
                                     { 1, 0, -1, 0 },
                                     { 0, 0, 0, 0 } };

		this->Dep_rel= Tableau;
		this->valeur = 500;
	}


};
class fou: public type_piece {
public:
	fou() {
		this->Nom_piece = Fou;
        vector<vector<int>> Tab{ { 1, 1, -1, -1 },
                                 { 1, -1, 1, -1 },
                                 { 0, 0, 0, 0 } };
		this->Dep_rel= Tab;
		this->valeur = 300;
	}


};
class cavalier: public type_piece {
public:
	cavalier() {
		this->Nom_piece = Cavalier;


		vector<vector<int>> Tableau{{ 1, 1, -1, -1, 2, 2, -2, -2 },
                                    { -2, 2, 2, -2, 1, -1, 1, -1 },
                                    {1, 1, 1, 1, 1, 1, 1, 1}     };



		this->Dep_rel= Tableau;
		this->valeur = 300;
	}



};
class dame: public type_piece {
public:
	dame() {
		this->Nom_piece = Dame;

		vector<vector<int>> Tableau{{ 0, 1, 0, -1, 1, 1, -1, -1 },
                                    { 1, 0, -1, 0, 1, -1, 1, -1},
                                    { 0, 0, 0, 0, 0, 0, 0, 0 } };



		this->Dep_rel= Tableau;
		this->valeur = 900;
	}


};
class roi: public type_piece {
public:
	roi() {
		this->Nom_piece = Roi;

		vector<vector<int>> Tableau{{ 0, 1, 0, -1, 1, 1, -1, -1 },
                                    { 1, 0, -1, 0, 1, -1, 1, -1},
                                    { 1, 1, 1, 1, 1, 1, 1, 1} };
        Dep_rel=Tableau;
        this->valeur = 0;
	}




};

class Position
{
public:
    int joueur;
    Position(int J) : joueur(J) {}
    virtual double valeur_position() =0;
    Position* fille = nullptr;
    Position* soeur = nullptr;
    Position(){};
    virtual ~Position(){};
    virtual Position* position_possible() = 0;
    virtual void print_position() const = 0;
    virtual bool gagne() const = 0;
};

class piece{
public:
//============================================================
//=======================Attributes===========================
//============================================================
    type_piece P;
    PieceColor Couleur;
    // Essential to test checkmate
    int x;
    int y;
    bool a_bouge = false;
//============================================================
//=======================Constructor==========================
//============================================================

    //Constructeur de la classe
    piece(piece& p){
        x = p.x;
        y = p.y;
        Couleur = p.Couleur;
        P = p.P;
        a_bouge = p.a_bouge;
    }
    piece(){}

//============================================================
//=========================Methods============================
//============================================================
    ~piece(){}//deleter

    piece& operator=(piece& Pi) {this->P = Pi.P; this->Couleur = Pi.Couleur; this->x = Pi.x; this->y = Pi.y; this->a_bouge = Pi.a_bouge; return *this;}

    //Basic constructor
    piece(PieceType nom_piece, PieceColor couleur, int a, int b, bool bouge){
        x = b;
        y = a;
        a_bouge = bouge;
        Couleur = couleur;
        if (nom_piece == Roi){
            roi piece;
            P = piece;
        }
        if (nom_piece == Pion){
            pion piece;
            P = piece;
        }
        if (nom_piece == Tour){
            tour piece;
            P = piece;
        }
        if (nom_piece == Dame){
            dame piece;
            P = piece;
        }
        if (nom_piece == Fou){
            fou piece;
            P = piece;
        }
        if (nom_piece == Cavalier){
            cavalier piece;
            P = piece;
        }
    }

    //Basic constructor
    piece(const PieceType nom_piece, const PieceColor couleur, const int a, const int b){
        x = b;
        y = a;
        Couleur = couleur;
        if (nom_piece == Roi){
            roi piece;
            P = piece;
        }
        if (nom_piece == Pion){
            pion piece;
            P = piece;
        }
        if (nom_piece == Tour){
            tour piece;
            P = piece;
        }
        if (nom_piece == Dame){
            dame piece;
            P = piece;
        }
        if (nom_piece == Fou){
            fou piece;
            P = piece;
        }
        if (nom_piece == Cavalier){
            cavalier piece;
            P = piece;
        }
    }


    const char* string_type(){ //Permet de récuperer une chaine de caractère correspondant au Type de piece
        switch(P.Nom_piece){
            case Dame : return("D");
            case Roi : return("R");
            case Pion : return("P");
            case Cavalier : return("C");
            case Fou : return("F");
            case Tour : return("T");
        }
        return ("erreur string_type");
    }
};


class echiquier{
public:
//============================================================
//=======================Attributes===========================
//============================================================
    //piece plateau[64];
    vector<piece*> plateau;
    list<piece*> aliveB; //List all the user's piece alive
    list<piece*> aliveN; //List all the opponent's piece alive
    piece* roi_B = nullptr; //State where the king of Player 1 is, useful for checkmate
    piece* roi_N = nullptr; //State where the king of Player 2 is

//============================================================
//=======================Constructor==========================
//============================================================
    echiquier(){
        plateau.resize(64,nullptr); //Initialize all pointers to NULL
    }

    echiquier(const echiquier &p){ //Copy constructor
        plateau.resize(64,NULL);
        for (int i = 0; i<=63; i++){
            if (p.plateau[i] != nullptr){
                plateau[i] = new piece(p.plateau[i]->P.Nom_piece, p.plateau[i]->Couleur,p.plateau[i]->y,p.plateau[i]->x, p.plateau[i]->a_bouge);
                if (p.plateau[i]->P.Nom_piece != Roi){
                    switch(p.plateau[i]->Couleur){
                        case(Blanc): aliveB.push_front(plateau[i]);break;
                        case(Noir): aliveN.push_front(plateau[i]);
                    }
                } else if (p.plateau[i]->Couleur == Blanc) roi_B = plateau[i];
                else if (p.plateau[i]->Couleur == Noir) roi_N = plateau[i];
            }
        }
    }

//============================================================
//=========================Methods============================
//============================================================

    //Overload of operator =
    echiquier& operator=(const echiquier &p){
        for (int i = 0; i<=63; i++){
            delete this->plateau[i];
            if (p.plateau[i] != nullptr){
                piece* p_temp = new piece(p.plateau[i]->P.Nom_piece, p.plateau[i]->Couleur,p.plateau[i]->y,p.plateau[i]->x, p.plateau[i]->a_bouge);
                this->plateau[i] = p_temp;
            }else if (p.plateau[i]==nullptr){
                this->plateau[i] = nullptr;
            }
        }
        *(this->roi_B) = *p.roi_B;
        *(this->roi_N) = *p.roi_N;
        list<piece*>::const_iterator it;
        for (it = p.aliveB.begin(); it != p.aliveB.end(); ++it)
        {piece* tmp = new piece; *tmp = **it; aliveB.push_front(tmp);}
        for (it = p.aliveN.begin(); it != p.aliveN.end(); ++it)
        {piece* tmp = new piece; *tmp = **it; aliveN.push_front(tmp);}
        return *this;
    }

    ~echiquier(){ //Chess deleter
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

class coup_echec{
public:
//============================================================
//=======================Attributes===========================
//============================================================

    PieceColor couleur_c;
    //Coordinates
    vector<int> init;
    vector<int> fin;

    //Special moves
    bool p_rooc = false;
    bool g_rooc = false;
    bool prom_f = false;
    bool prom_d = false;
    bool prom_c = false;
    bool prom_t = false;

    bool echec = false; //Check if there is a check
    bool echec_mat = false; //Check if there is a checkmate

//============================================================
//=======================Constructor==========================
//============================================================

    ~coup_echec() {}

    //Null constructor
    coup_echec(){}

    //Copy constructor
    coup_echec(const coup_echec &c);

    //Constructor of a chess move when taking an opponent piece; no need of color.
    coup_echec(const int y_init, const int x_init, const int y_final, const int x_final);

    //Constructor for a roocs move.
    coup_echec(char const* nom_coup,const PieceColor couleur);

    //Constructor of a move promoting a piece and taking another.
    coup_echec(char const* nom_coup,const int x_init, const int y_init, const int x_final, const int y_final);

//============================================================
//=======================Methods==============================
//============================================================

    void affichage_standard(const echiquier* E) const; //Displays the chess
};

class Position_Echec: public Position {
public:
//============================================================
//=======================Attributes===========================
//============================================================
    PieceColor couleur_joueur; //Color of the player having to play
    coup_echec Dernier_coup; //Last move
    list<coup_echec> Liste_coup; //List of move from the beginning of the game
    echiquier* echiquier_ref; //Current state of the chessboard
//============================================================
//=======================Constructor==========================
//============================================================
    //Basic constructor
    Position_Echec(const echiquier& E, const PieceColor C, const list<coup_echec> L){
        echiquier_ref = new echiquier(E); //Call the copy constructor of the class echiquier
        couleur_joueur = C;
        Liste_coup = L;
    }

    //Basic constructor
    Position_Echec(const echiquier& E, const PieceColor C): couleur_joueur(C){
        echiquier_ref = new echiquier(E); //Call the copy constructor of the class echiquier
    }

    //Basic constructor
    Position_Echec(const PieceColor couleur) : couleur_joueur(couleur){
    }

    //Copy constructor
    Position_Echec(const Position_Echec& Pos)
    {
        couleur_joueur = Pos.couleur_joueur;
        Liste_coup = Pos.Liste_coup;
        echiquier_ref = new echiquier(*Pos.echiquier_ref); //We could also do new echiquier(*pos)
    }

//============================================================
//=========================Methods============================
//============================================================
    void libere_fille(Position_Echec* P)
    {
        Position_Echec* pfille = dynamic_cast<Position_Echec*>(fille);
        while (pfille != nullptr)
        {
//            Position_Echec* next = dynamic_cast<Position_Echec*>(pfille->soeur);
            if (pfille != P)
            {
                pfille->libere_fille(P);
                delete pfille;
            }
        }
    }

    Position_Echec(): couleur_joueur(Blanc){//Liste_coup = new coup_echec[10];
    }

    //Destructor
    ~Position_Echec()
    {
        if (fille != nullptr){delete fille;} //delete the daughter
        if (soeur !=nullptr){delete soeur;} //delete recursively the sisters
    }

    Position* position_possible(); //List all the possible consecutive move given a chessboard.

    double valeur_position() const {return 0;} //a def

    bool gagne()const {return true;} //correspond au test d'echec et mat

    //Test if a rooc is feasible
    bool test_p_rooc() const;
    bool test_g_rooc() const;

    //Test if a move is valid given a chessboard disposition
    bool is_valid_move(const int& i_init, const int& j_init, const int& i_final, const int& j_final, const PieceColor C,const bool text) const;
    bool all_valid(const int& i_init, const int& j_init, const int& i_final, const int& j_final, const bool text) const;
    bool valid_check(const int& i_init, const int& j_init, const int& i_final, const int& j_final) const;

    bool coup_humain(bool* nul); //Perform the move indicated by the user

    bool test_echec(const PieceColor C) const; //Test echec pour regarder si le roi adverse est en échec ou non
    bool test_match_nul() const; //Test if it is a draw
    bool test_echec_mat(const PieceColor C) const;

    void mise_a_jour_coup(const coup_echec& move_chess, const bool text);
    void mise_a_jour_position(const bool text);

    double valeur_position();
    void print_position() const {cout<<"===================================="<<endl; echiquier_ref->affichage();}
} ;


//=============================
    //Fonctions externes
//=============================

void echiquier_depart(echiquier& E);
void echiquier_test_p_rooc(echiquier& E);
void echiquier_test_g_rooc(echiquier& E);
void echiquier_test_prom(echiquier& E);
void echiquier_test_echec(echiquier& E);
void echiquier_test_echec_mat(echiquier& E);
void echiquier_piece(echiquier& E);
void echiquier_test_pion(echiquier& E);

void elimine_piece(Position_Echec& Posi, piece* Pprise, const piece* const Pjoue, const bool text);

void convert(string pos_init, string pos_fin, int& i_init, int& j_init, int& i_final, int& j_final);

void affichage_fille(Position_Echec& P);

void call_for_position(string* pos_init, string* pos_final);

// int minimax(Position &P, int alpha, int beta, int depth);

bool interieur_plateau(int i,int j);

bool find_word(string mot, vector<string> list_mot);


//Check if a move is valid according to the game's rules
bool is_valid(const int i1, const int j1, const int i2, const int j2, const echiquier* chessboard, const bool text); //Check if the move is valid
bool is_valid_pion(const int i1, const int j1, const int i2, const int j2, const echiquier* chessboard, const bool text);
bool is_valid_tour(const int i1, const int j1, const int i2, const int j2, const bool text);
bool is_valid_dame(const int i1, const int j1, const int i2, const int j2, const bool text);
bool is_valid_fou(const int i1, const int j1, const int i2, const int j2, const bool text);
bool is_valid_roi(const int i1, const int j1, const int i2, const int j2, const echiquier* chessboard, const bool text);
bool is_valid_cavalier(const int i1, const int j1, const int i2, const int j2, const bool text);

inline int abs(int a){return (a>0) ? a : -a;}

void ask_promotion();

#endif
