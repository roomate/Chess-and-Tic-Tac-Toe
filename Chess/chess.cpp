
#include "chess.hpp"
#include <cmath>
#include <string>
#include <sstream>
//====================================

const int alpha = 1;
const int beta = 1;

const int MAX = 100000;
const int MIN = -100000;

//====================================

void echiquier::affichage(){

    string alphat("ABCDEFGH");
    for (int i = 7; i>=0; i--){
        cout<<i+1<<"   ";
        for (int j=0; j<8; j++){
            if (plateau[i*8+j] != nullptr){
                cout<<plateau[i*8+j]->string_type()<<(plateau[i*8+j]->Couleur==Blanc?"b":"n")<<"  ";
            }else{
                cout<<"    ";
            }
        }
        cout<<endl;
    }
    cout<<"    ";
    for (int i = 0; i < 8; i++)
    {
        cout<<alphat[i]<<"   ";
    }
    cout<<endl;
}


//======================================
//    "Affichage du coup"
//======================================

void coup_echec::affichage_standard(){
    cout<<"(";
    const char* alphat = "ABCDEFGH";
    if (p_rooc == true){
        cout<<"o-o";
    }
    else if (g_rooc == true){
        cout<<"o-o-o";
    }
    else if (prom_d == true){
        cout<<"Dame"<<alphat[i2]<<j2+1;
    }
    else if (prom_c == true){
        cout<<"Cavalier"<<alphat[i2]<<j2+1;
    }
    else if (prom_f == true){
        cout<<"Fou"<<alphat[i2]<<j2+1;
    }
    else if (prom_t == true){
        cout<<"Tour"<<alphat[i2]<<j2+1;
    }
    else {
        if (PJ->P.Nom_piece == Roi){
            cout<<"Roi";
        }
        if (PJ->P.Nom_piece == Dame){
            cout<<"Dame";
        }
        if (PJ->P.Nom_piece == Fou){
            cout<<"Fou";
        }
        if (PJ->P.Nom_piece == Cavalier){
            cout<<"Cavalier";
        }
        if (PJ->P.Nom_piece == Tour){
            cout<<"Tour";
        }
        if (PJ->P.Nom_piece == Pion){
            cout<<"Pion";
        }
        if (PJ->Couleur == Blanc){
            cout<<" Blanc";
        }
        if (PJ->Couleur == Noir){
            cout<<" Noir";
        }
        cout<<" "<<alphat[j1]<<i1+1;
        cout<<"-";
        cout<<alphat[j2]<<i2+1;

    }
    if (echec == true){
        cout<<"+";
    }
    if (echec_mat == true){
        cout<<"++";
    }
    cout<<")"<<endl;
}

//======================================
//    "Construction de l'echiquier"
//======================================

echiquier construction_echiquier(Position_Echec& P){
    echiquier echiquier_final = P.echiquier_ref; //Il faut un constructeur par copie ?
    list<coup_echec>::iterator it;
    for (it=P.Liste_coup.begin();it!=P.Liste_coup.end();it++){
        if (it->p_rooc== true){
            if (it->couleur_c == Blanc){
                if (echiquier_final.plateau[4] != nullptr && echiquier_final.plateau[7] != nullptr)
                {
                    echiquier_final.plateau[6] = echiquier_final.plateau[4];
                    echiquier_final.plateau[6]->x = 0;
                    echiquier_final.plateau[6]->y = 6;
                    echiquier_final.plateau[6]->a_bouger = true;
                    echiquier_final.plateau[4] = nullptr;
                    echiquier_final.plateau[5] = echiquier_final.plateau[7];
                    echiquier_final.plateau[5]->a_bouger = true;
                    echiquier_final.plateau[5]->x = 0;
                    echiquier_final.plateau[5]->y = 5;
                    echiquier_final.plateau[7] = nullptr;
                }
            }
            if (it->couleur_c == Noir){
                if (echiquier_final.plateau[60] != nullptr && echiquier_final.plateau[63] != nullptr){
                    echiquier_final.plateau[61] = echiquier_final.plateau[63];
                    echiquier_final.plateau[61]->a_bouger = true;
                    echiquier_final.plateau[61]->x = 7;
                    echiquier_final.plateau[61]->y = 5;
                    echiquier_final.plateau[63] = nullptr;
                    echiquier_final.plateau[62] = echiquier_final.plateau[60];
                    echiquier_final.plateau[62]->a_bouger = true;
                    echiquier_final.plateau[62]->x = 7;
                    echiquier_final.plateau[62]->y = 6;
                    echiquier_final.plateau[60] = nullptr;
                }
            }
        }
        else if (it->g_rooc == true){
            if (it->couleur_c == Blanc){
                if (echiquier_final.plateau[4] != nullptr && echiquier_final.plateau[0] != nullptr)
                {
                    echiquier_final.plateau[2] = echiquier_final.plateau[4]; //On déplace le roi
                    echiquier_final.plateau[2]->x = 0;
                    echiquier_final.plateau[2]->y = 2;
                    echiquier_final.plateau[2]->a_bouger = true;
                    echiquier_final.plateau[4] = nullptr;
                    echiquier_final.plateau[3] = echiquier_final.plateau[0];
                    echiquier_final.plateau[3]->a_bouger = true;
                    echiquier_final.plateau[3]->x = 0;
                    echiquier_final.plateau[3]->y = 3;
                    echiquier_final.plateau[0] = nullptr;
                }
            }
            if (it->couleur_c == Noir){
                if (echiquier_final.plateau[56] != nullptr && echiquier_final.plateau[60] != nullptr)
                {
                    echiquier_final.plateau[59] = echiquier_final.plateau[56];
                    echiquier_final.plateau[59]->a_bouger = true;
                    echiquier_final.plateau[59]->x = 7;
                    echiquier_final.plateau[59]->y = 3;
                    echiquier_final.plateau[56] = nullptr;
                    echiquier_final.plateau[58] = echiquier_final.plateau[60];
                    echiquier_final.plateau[58]->a_bouger = true;
                    echiquier_final.plateau[58]->x = 7;
                    echiquier_final.plateau[58]->y = 2;
                    echiquier_final.plateau[60] = nullptr;
                }
            }

        }
        else if (it->prom_f == true){
            if (echiquier_final.plateau[it->i1*8+it->j1] != nullptr)
            {
                piece* promotion = echiquier_final.plateau[it->i1*8+it->j1];
                fou type_prom;
                promotion->a_bouger=true;
                promotion->P = type_prom;
                promotion->x = it->i2;
                promotion->y = it->j2;
                echiquier_final.plateau[it->i2*8+it->j2] = promotion;
                echiquier_final.plateau[it->i1*8+it->j1] = nullptr;
            }

        }
        else if (it->prom_d == true){
            if (echiquier_final.plateau[it->i1*8+it->j1] != nullptr){
                piece* promotion = echiquier_final.plateau[it->i1*8+it->j1];
                dame type_prom;
                promotion->a_bouger=true;
                promotion->P = type_prom;
                promotion->x = it->i2;
                promotion->y = it->j2;
                echiquier_final.plateau[it->i2*8+it->j2] = promotion;
                echiquier_final.plateau[it->i1*8+it->j1] = nullptr;
            }

        }
        else if (it->prom_t == true){
            if (echiquier_final.plateau[it->i1*8+it->j1] != nullptr)
            {
                piece* promotion = echiquier_final.plateau[it->i1*8+it->j1];
                tour type_prom;
                promotion->a_bouger=true;
                promotion->P = type_prom;
                promotion->x = it->i2;
                promotion->y = it->j2;
                echiquier_final.plateau[it->i2*8+it->j2] = promotion;
                echiquier_final.plateau[it->i1*8+it->j1] = nullptr;
            }

        }
        else if (it->prom_c == true){
            if (echiquier_final.plateau[it->i1*8+it->j1] != nullptr){
                piece* promotion = echiquier_final.plateau[it->i1*8+it->j1];
                cavalier type_prom;
                promotion->a_bouger=true;
                promotion->P = type_prom;
                promotion->x = it->i2;
                promotion->y = it->j2;
                echiquier_final.plateau[it->i2*8+it->j2] = promotion;
                echiquier_final.plateau[it->i1*8+it->j1] = nullptr;
            }

        }
        else if (echiquier_final.plateau[it->i1*8+it->j1] != nullptr)
        {
            echiquier_final.plateau[it->i2*8+it->j2] = nullptr;
            piece* temp = echiquier_final.plateau[it->i1*8+it->j1];
            temp->x = it->i2;
            temp->y = it->j2;
            temp->a_bouger=true;
            echiquier_final.plateau[it->i2*8+it->j2] = temp;
            //cout<<"&"<<temp<<endl;
            //cout<<"&&"<<echiquier_final.plateau[it->i1*8+it->j1]<<endl;
            echiquier_final.plateau[it->i1*8+it->j1] = nullptr;
        }
    }
    return(echiquier_final);
}


//====================================
//     "Affichage fille "
//==================================

void affichage_fille(Position_Echec& posi)
{
    posi.fille = nullptr;
    posi.position_possible();
    if (posi.fille != nullptr)
    {
        Position_Echec* Fille = dynamic_cast<Position_Echec*>(posi.fille);
        while (Fille != nullptr)
        {
            posi = *Fille;
            posi.mise_a_jour_position();
            cout<<"================================="<<endl;
            posi.echiquier_ref.affichage();
            cout<<"================================="<<endl;
            Fille = dynamic_cast<Position_Echec*>(Fille->soeur);
        }
    }
}


Position_Echec& Position_Echec::mise_a_jour_position(){ //Met à jour l'echiquier de ref, vide la liste de coup, et determine le joueur à qui c'est au tour de jouer
    this->Dernier_coup = this->Liste_coup.back(); //Recup du dernier coup
    list<coup_echec>::iterator it;
    for (it=this->Liste_coup.begin();it!=this->Liste_coup.end();it++){
        if (this->joueur == 1){
            this->joueur = 2;
        }else{
            this->joueur =1;
        }
    }
    enum PieceColor Dernier_joueur = this->Dernier_coup.couleur_c;
    if (Dernier_joueur == Blanc){
        this->couleur_joueur = Noir;
        //cout<<"c'est maintenant au joueur noir de jouer"<<endl;
    }
    if (Dernier_joueur == Noir){
        this->couleur_joueur = Blanc;
        //cout<<"c'est maintenant au joueur blanc de jouer"<<endl;
    }
    echiquier_ref = construction_echiquier(*this); //Mise à jour de l'echiquier


    Liste_coup.clear();

    return *this;
}

double Position_Echec::valeur_position(){


    int cont_blanc = 0;
    int cont_noir = 0;
    int val_blanc = 0;
    int val_noir = 0;
    int val;
    this->mise_a_jour_position();
    if (this->test_echec_mat()==true) //Si le joueur 1 ou 2 est mis en echec et mat
    {
            if (this->joueur == 1)
            {
                return MIN; //Si le joueur est mis en echec et mat, l'ordinateur gagne
            }
            if (this->joueur == 2)
            {
                return MAX; //Si l'ordinateur est mis en echec et mat, le joueur gagne
            }

//    } else if (this->test_match_nul()==true)
//    {
//        return 0;
    } else
    {
        for(int i = 0; i<64;i++)
        {
            if (this->echiquier_ref.plateau[i] != NULL)
            {
                if (this->echiquier_ref.plateau[i]->Couleur == Blanc)
                {
                    cont_blanc = cont_blanc +1;
                    val_blanc = val_blanc + this->echiquier_ref.plateau[i]->P.valeur;
                } else if (this->echiquier_ref.plateau[i]->Couleur == Noir)
                {
                    cont_noir = cont_noir +1;
                    val_noir = val_noir + this->echiquier_ref.plateau[i]->P.valeur;
                }
            }
        }
	    if ((this->couleur_joueur == Blanc && this->joueur == 1) || (this->couleur_joueur == Noir && this->joueur == 2))
        {
            val = alpha*(val_blanc - val_noir) + beta*(cont_blanc - cont_noir);
        }
        else if((this->couleur_joueur == Blanc && this->joueur == 2) || (this->couleur_joueur == Noir && this->joueur ==1))
        {
                    val = -(alpha *(val_blanc - val_noir) + beta*(cont_blanc - cont_noir));
        }
    }
    return val;
}

bool interieur_plateau(int i,int j)
{
    if (i>= 0 && i<8 && j >=0 && j<8){
        return true;}
    return false;
}


bool Position_Echec::test_echec(){ //Permet de tester si une position est echec ou pas pour le joueur de la position
    PieceColor turn = couleur_joueur; // Recuperer la couleur du joueur
    //cout << turn << endl;
    int m; // Pour les deplacements relatifs non limités
    //echiquier echiquier_final = construction_echiquier(*this); // Construire echiquier
   // (*this).mise_a_jour_position();
    int pos_x_roi=0;
    int pos_y_roi=0;
    vector<vector<int>> Dep;
    for (int i = 0; i<64; i++){ // Récupérer la position du Roi du joueur
        if ((echiquier_ref.plateau[i]!= nullptr) && (echiquier_ref.plateau[i]->P.Nom_piece == Roi) && (echiquier_ref.plateau[i]->Couleur == turn)){ //&& (echiquier_d.plateau[i]!= nullptr)){

            pos_x_roi = (*echiquier_ref.plateau[i]).x;
            pos_y_roi = (*echiquier_ref.plateau[i]).y;
            }


    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
                if (((echiquier_ref.plateau[8*i+j])!=nullptr) &&
                    (echiquier_ref.plateau[8*i+j]->Couleur != turn)) {// Rechercher les pieces adverses sur le plateau
                        piece* Pad= echiquier_ref.plateau[8*i+j]; // Récupérer la piece adverse
                     //   cout << (*Pad).string_type() <<endl;
                        Dep= (Pad->P).Dep_rel; // Dep relatif du type de la piece
                        //cout << Dep[0][0] << endl;
                        if ((Pad->P).Nom_piece!= Pion ){    // Si c'est pas un pion pas besoin de savoir s'il a bougé ou pas
                            for(int l = 0; l<int(Dep[1].size()); l++){
                                if (int(Dep[2][l]) == 1){
                                    if ( (i + Dep[0][l]== pos_x_roi) && (j + Dep[1][l]== pos_y_roi) ){
                                        return true;
                                    }}
                                if (Dep[2][l] == 0){
                                    m=1;
                                    if ( (i + (m)*Dep[0][l]== pos_x_roi) && (j + (m)*Dep[1][l]== pos_y_roi) ){
                                            return true;
                                        }
                                    while (  (interieur_plateau(i + m*Dep[0][l],  j + m*Dep[1][l])) && (echiquier_ref.plateau[8*(i + m*Dep[0][l]) + j + m*Dep[1][l]]== nullptr) && (m<7)){
                                        if ( (i + (m+1)*Dep[0][l]== pos_x_roi) && (j + (m+1)*Dep[1][l]== pos_y_roi) ){
                                            return true;
                                        }
                                    m=m+1;
                                    }
                                }
                            }
                        }
                        else { // Sinon si c'est un pion
                            for(int l = 1 ; l<int(Dep[1].size() -1); l++){ // Toutes les possibilités du Dep relatif diag
                                if ( (i + Dep[0][l]== pos_x_roi) && (j + Dep[1][l]== pos_y_roi) && (Pad->Couleur==Blanc) ){
                                    return true;
                                }
                                else if ( (i - Dep[0][l]== pos_x_roi) && (j + Dep[1][l]== pos_y_roi) && (Pad->Couleur ==Noir) ){
                                    return true;
                                }

                            }
                        }
                   }
            }
        }
        return false;
}

bool Position_Echec::test_echec2(){ //Permet de tester si une position est echec ou pas pour le joueur de la position
    PieceColor turn;
    if (couleur_joueur == Blanc)
    {
        turn = Noir;
    }
    else
    {
        turn = Blanc;
    }
    //cout << turn << endl;
    int m; // Pour les deplacements relatifs non limités
    //echiquier echiquier_final = construction_echiquier(*this); // Construire echiquier
   // (*this).mise_a_jour_position();
    int pos_x_roi=0;
    int pos_y_roi=0;
    vector<vector<int>> Dep;
    for (int i = 0; i<64; i++){ // Récupérer la position du Roi du joueur
        if ((echiquier_ref.plateau[i]!= nullptr) && (echiquier_ref.plateau[i]->P.Nom_piece == Roi) && (echiquier_ref.plateau[i]->Couleur == turn)){ //&& (echiquier_d.plateau[i]!= nullptr)){

            pos_x_roi = (*echiquier_ref.plateau[i]).x;
            pos_y_roi = (*echiquier_ref.plateau[i]).y;
            }


    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
                if (((echiquier_ref.plateau[8*i+j])!=nullptr) &&
                    (echiquier_ref.plateau[8*i+j]->Couleur != turn)) {// Rechercher les pieces adverses sur le plateau
                        piece* Pad= echiquier_ref.plateau[8*i+j]; // Récupérer la piece adverse
                     //   cout << (*Pad).string_type() <<endl;
                        Dep= (Pad->P).Dep_rel; // Dep relatif du type de la piece
                        //cout << Dep[0][0] << endl;
                        if ((Pad->P).Nom_piece!= Pion ){    // Si c'est pas un pion pas besoin de savoir s'il a bougé ou pas
                            for(int l = 0; l<int(Dep[1].size()); l++){
                                if (int(Dep[2][l]) == 1){
                                    if ( (i + Dep[0][l]== pos_x_roi) && (j + Dep[1][l]== pos_y_roi) ){
                                        return true;
                                    }}
                                if (Dep[2][l] == 0){
                                    m=1;
                                    if ( (i + (m)*Dep[0][l]== pos_x_roi) && (j + (m)*Dep[1][l]== pos_y_roi) ){
                                            return true;
                                        }
                                    while (  (interieur_plateau(i + m*Dep[0][l],  j + m*Dep[1][l])) && (echiquier_ref.plateau[8*(i + m*Dep[0][l]) + j + m*Dep[1][l]]== nullptr) && (m<7)){
                                        if ( (i + (m+1)*Dep[0][l]== pos_x_roi) && (j + (m+1)*Dep[1][l]== pos_y_roi) ){
                                            return true;
                                        }
                                    m=m+1;
                                    }
                                }
                            }
                        }
                        else { // Sinon si c'est un pion
                            for(int l = 1 ; l<int(Dep[1].size() -1); l++){ // Toutes les possibilités du Dep relatif diag
                                if ( (i + Dep[0][l]== pos_x_roi) && (j + Dep[1][l]== pos_y_roi) && (Pad->Couleur==Blanc) ){
                                    return true;
                                }
                                else if ( (i - Dep[0][l]== pos_x_roi) && (j + Dep[1][l]== pos_y_roi) && (Pad->Couleur ==Noir) ){
                                    return true;
                                }

                            }
                        }
                   }
            }
        }
        return false;
}







bool Position_Echec::test_echec_mat(){ //Teste si une position est echec et mat
    if ((*this).test_echec() == false){
        return false;
    }
    else{
            PieceColor turn = PieceColor(joueur);// Recuperer la couleur du joueur
           // (*this).position_possible();
            Position_Echec* pFilles= dynamic_cast<Position_Echec*>(this->fille);
            while (pFilles != nullptr){
                pFilles->couleur_joueur = turn;
                if ((*pFilles).test_echec() == false) {
                    return false;
                }
                pFilles= dynamic_cast<Position_Echec*>(pFilles->soeur);
            }
    return true;

}}

bool Position_Echec::test_match_nul(){
    if ((*this).test_echec() == true){
        return false;
    }
    else{
            PieceColor turn = PieceColor(joueur);// Recuperer la couleur du joueur
            //(*this).position_possible();
            Position_Echec* pFilles= dynamic_cast<Position_Echec*>(this->fille);
            while (pFilles != nullptr){
                pFilles->couleur_joueur = turn;
                if ((*pFilles).test_echec() == false) {
                    return false;
                }
                pFilles= dynamic_cast<Position_Echec*>(pFilles->soeur);
            }
    return true;

}}

echiquier echiquier_depart(){
    echiquier E;
    piece* P_0 = new piece(Tour,Blanc,0,0);
    E.plateau[0]= P_0;
    piece* P_1 = new piece(Cavalier,Blanc,0,1);
    E.plateau[1]= P_1;
    piece* P_2= new piece(Fou,Blanc,0,2);
    E.plateau[2]= P_2;
    piece* P_3= new piece(Dame,Blanc,0,3);
    E.plateau[3]= P_3;
    piece* P_4= new piece(Roi,Blanc,0,4);
    E.plateau[4]= P_4;
    piece* P_5= new piece(Fou,Blanc,0,5);
    E.plateau[5]= P_5;
    piece* P_6= new piece(Cavalier,Blanc,0,6);
    E.plateau[6]= P_6;
    piece* P_7= new piece(Tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    piece* P_56 = new piece(Tour,Noir,7,0);
    E.plateau[56]= P_56;
    piece* P_57 = new piece(Cavalier,Noir,7,1);
    E.plateau[57]= P_57;
    piece* P_58 = new piece(Fou,Noir,7,2);
    E.plateau[58]= P_58;
    piece* P_59= new piece(Roi,Noir,7,3);
    E.plateau[59]= P_59;
    piece* P_60= new piece(Dame,Noir,7,4);
    E.plateau[60]= P_60;
    piece* P_61= new piece(Fou,Noir,7,5);
    E.plateau[61]= P_61;
    piece* P_62= new piece(Cavalier,Noir,7,6);
    E.plateau[62]= P_62;
    piece* P_63= new piece(Tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Noir,6,i);
        E.plateau[6*8+i] = temp_P;
    }
    return E;
}

echiquier echiquier_test_pion(){ //Echiquier pour voir si le pion mange un autre pion quand il le peut
    echiquier E;
    piece* P_0 = new piece(Tour,Blanc,0,0);
    E.plateau[0]= P_0;
    piece* P_1 = new piece(Cavalier,Blanc,0,1);
    E.plateau[1]= P_1;
    piece* P_2= new piece(Fou,Blanc,0,2);
    E.plateau[2]= P_2;
    piece* P_3= new piece(Dame,Blanc,0,3);
    E.plateau[3]= P_3;
    piece* P_4= new piece(Roi,Blanc,0,4);
    E.plateau[4]= P_4;
    piece* P_5= new piece(Fou,Blanc,0,5);
    E.plateau[5]= P_5;
    piece* P_6= new piece(Cavalier,Blanc,0,6);
    E.plateau[6]= P_6;
    piece* P_7= new piece(Tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    E.plateau[8*4 + 6] = E.plateau[8 + 7];
    E.plateau[8 + 7] = nullptr;
//    piece* temp_P = new piece(Pion,Blanc, 5,6);
//    E.plateau[5*8+6] = temp_P;
    piece* P_56 = new piece(Tour,Noir,7,0);
    E.plateau[56]= P_56;
    piece* P_57 = new piece(Cavalier,Noir,7,1);
    E.plateau[57]= P_57;
    piece* P_58 = new piece(Fou,Noir,7,2);
    E.plateau[58]= P_58;
    piece* P_59= new piece(Roi,Noir,7,3);
    E.plateau[59]= P_59;
    piece* P_60= new piece(Dame,Noir,7,4);
    E.plateau[60]= P_60;
    piece* P_61= new piece(Fou,Noir,7,5);
    E.plateau[61]= P_61;
    piece* P_62= new piece(Cavalier,Noir,7,6);
    E.plateau[8*7+6]= P_62;
    piece* P_63= new piece(Tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=6; i++){
        piece* temp_P= new piece(Pion,Noir,6,i);
        E.plateau[6*8+i] = temp_P;
    }
    E.plateau[5*8 + 7] = E.plateau[6*8 + 6];
    E.plateau[6*8 + 6] = nullptr;
    return E;
}



bool Position_Echec::test_p_rooc(){
    if (this->couleur_joueur== Blanc){
        if(this->echiquier_ref.plateau[7]!=nullptr && this->echiquier_ref.plateau[4]!=nullptr && this->echiquier_ref.plateau[5]==nullptr && this->echiquier_ref.plateau[6]==nullptr ){
            if(this->echiquier_ref.plateau[7]->P.Nom_piece==Tour && this->echiquier_ref.plateau[4]->P.Nom_piece==Roi){
                if(this->echiquier_ref.plateau[7]->Couleur==Blanc && this->echiquier_ref.plateau[4]->Couleur==Blanc){
                    if(this->echiquier_ref.plateau[7]->a_bouger==false && this->echiquier_ref.plateau[4]->a_bouger==false){
                        if (this->test_echec()==false){
                               return(true);
                        }
                    }
                }
            }
        }
        return(false);
    }
    if (this->couleur_joueur==Noir){
        if(this->echiquier_ref.plateau[63]!=nullptr && this->echiquier_ref.plateau[60]!=nullptr && this->echiquier_ref.plateau[61]==nullptr && this->echiquier_ref.plateau[62]==nullptr ){
            if(this->echiquier_ref.plateau[63]->P.Nom_piece==Tour && this->echiquier_ref.plateau[60]->P.Nom_piece==Roi){
                if(this->echiquier_ref.plateau[63]->Couleur==Noir && this->echiquier_ref.plateau[60]->Couleur==Noir){
                    if(this->echiquier_ref.plateau[63]->a_bouger==false && this->echiquier_ref.plateau[60]->a_bouger==false){
                        if (this->test_echec()==false){
                            return(true);
                        }
                    }
                }
            }
        }
        return(false);
    }
    return(false);

}

bool Position_Echec::test_g_rooc(){
    if (this->couleur_joueur== Blanc){
        if(this->echiquier_ref.plateau[0]!=nullptr && this->echiquier_ref.plateau[4]!=nullptr && this->echiquier_ref.plateau[1]==nullptr && this->echiquier_ref.plateau[2]==nullptr && this->echiquier_ref.plateau[3]==nullptr ){
            if(this->echiquier_ref.plateau[0]->P.Nom_piece==Tour && this->echiquier_ref.plateau[4]->P.Nom_piece==Roi){
                if(this->echiquier_ref.plateau[0]->Couleur==Blanc && this->echiquier_ref.plateau[4]->Couleur==Blanc){
                    if(this->echiquier_ref.plateau[0]->a_bouger==false && this->echiquier_ref.plateau[4]->a_bouger==false){
                        if (this->test_echec()==false){
                            return(true);
                        }
                    }
                }
            }
        }
        return(false);
    }
    if (this->couleur_joueur==Noir){
        if(this->echiquier_ref.plateau[56]!=nullptr && this->echiquier_ref.plateau[60]!=nullptr && this->echiquier_ref.plateau[57]!=nullptr && this->echiquier_ref.plateau[58]!=nullptr && this->echiquier_ref.plateau[59]!=nullptr ){
            if(this->echiquier_ref.plateau[56]->P.Nom_piece==Tour && this->echiquier_ref.plateau[60]->P.Nom_piece==Roi){
                if(this->echiquier_ref.plateau[56]->Couleur==Noir && this->echiquier_ref.plateau[60]->Couleur==Noir){
                    if(this->echiquier_ref.plateau[56]->a_bouger==false && this->echiquier_ref.plateau[60]->a_bouger==false){
                        if (this->test_echec()==false){
                            return(true);
                        }
                    }
                }
            }
        }
        return(false);
    }

    return(false);

}

echiquier echiquier_test_p_rooc(){
    echiquier E;
    piece* P_0 = new piece(Tour,Blanc,0,0);
    E.plateau[0]= P_0;
    piece* P_1 = new piece(Cavalier,Blanc,0,1);
    E.plateau[1]= P_1;
    piece* P_2= new piece(Fou,Blanc,0,2);
    E.plateau[2]= P_2;
    piece* P_3= new piece(Dame,Blanc,0,3);
    E.plateau[3]= P_3;
    piece* P_4= new piece(Roi,Blanc,0,4);
    E.plateau[4]= P_4;
    piece* P_7= new piece(Tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    piece* P_56 = new piece(Tour,Noir,7,0);
    E.plateau[56]= P_56;
    piece* P_57 = new piece(Cavalier,Noir,7,1);
    E.plateau[57]= P_57;
    piece* P_58 = new piece(Fou,Noir,7,2);
    E.plateau[58]= P_58;
    piece* P_59= new piece(Roi,Noir,7,3);
    E.plateau[59]= P_59;
    piece* P_60= new piece(Dame,Noir,7,4);
    E.plateau[60]= P_60;
    piece* P_61= new piece(Fou,Noir,7,5);
    E.plateau[61]= P_61;
    piece* P_62= new piece(Cavalier,Noir,7,6);
    E.plateau[62]= P_62;
    piece* P_63= new piece(Tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Noir,6,i);
        E.plateau[6*8+i] = temp_P;
    }
    return E;
}

echiquier echiquier_test_g_rooc(){
    echiquier E;
    piece* P_0 = new piece(Tour,Blanc,0,0);
    E.plateau[0]= P_0;

    piece* P_4= new piece(Roi,Blanc,0,4);
    E.plateau[4]= P_4;
    piece* P_5= new piece(Fou,Blanc,0,5);
    E.plateau[5]= P_5;
    piece* P_6= new piece(Cavalier,Blanc,0,6);
    E.plateau[6]= P_6;
    piece* P_7= new piece(Tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    piece* P_56 = new piece(Tour,Noir,7,0);
    E.plateau[56]= P_56;
    piece* P_57 = new piece(Cavalier,Noir,7,1);
    E.plateau[57]= P_57;
    piece* P_58 = new piece(Fou,Noir,7,2);
    E.plateau[58]= P_58;
    piece* P_59= new piece(Roi,Noir,7,3);
    E.plateau[59]= P_59;
    piece* P_60= new piece(Dame,Noir,7,4);
    E.plateau[60]= P_60;
    piece* P_61= new piece(Fou,Noir,7,5);
    E.plateau[61]= P_61;
    piece* P_62= new piece(Cavalier,Noir,7,6);
    E.plateau[62]= P_62;
    piece* P_63= new piece(Tour,Noir,7,7);
    E.plateau[63]= P_63;
    for (int i = 0; i<=7; i++){
        piece* temp_P= new piece(Pion,Noir,6,i);
        E.plateau[6*8+i] = temp_P;
    }
    return E;
}

echiquier echiquier_test_prom(){
    echiquier E;
    piece* P_0 = new piece(Tour,Blanc,0,0);
    E.plateau[0]= P_0;
    piece* P_1 = new piece(Cavalier,Blanc,0,1);
    E.plateau[1]= P_1;
    piece* P_2= new piece(Fou,Blanc,0,2);
    E.plateau[2]= P_2;
    piece* P_3= new piece(Dame,Blanc,0,3);
    E.plateau[3]= P_3;
    piece* P_4= new piece(Roi,Blanc,0,4);
    E.plateau[4]= P_4;
    piece* P_5= new piece(Fou,Blanc,0,5);
    E.plateau[5]= P_5;
    piece* P_6= new piece(Cavalier,Blanc,0,6);
    E.plateau[6]= P_6;
    piece* P_7= new piece(Tour,Blanc,0,7);
    E.plateau[7]= P_7;
    for (int i = 0; i<=6; i++){
        piece* temp_P= new piece(Pion,Blanc,1,i);
        E.plateau[8+i] = temp_P;
    }
    piece* temp_P= new piece(Pion,Blanc,6,2);
    E.plateau[6*8+2] = temp_P;
    return E;
}

echiquier echiquier_test_echec(){
    echiquier E;

    piece* P_4= new piece(Roi,Blanc,0,4);
    E.plateau[4]= P_4;

    piece* P_59= new piece(Dame,Noir,7,4);
    E.plateau[60]= P_59;

    return E;
}

echiquier echiquier_test_echec_mat()//Echiquier test pour l'echec et mat
{
    echiquier E;

    piece* P_4= new piece(Roi,Blanc,0,7);
    E.plateau[7]= P_4;

    piece* P_59= new piece(Dame,Noir,7,7);
    E.plateau[63]= P_59;
    piece* P_9= new piece(Tour,Noir,5,6);
    E.plateau[46]= P_9;

  //  piece* PT = new piece(Tour, Noir, 6, 5);
  //  E.plateau[53]= PT;
    return E;
}

echiquier echiquier_piece()
{
    echiquier E;
    piece* roi = new piece(Roi,Blanc,4,4);
    piece* dame = new piece(Dame ,Noir, 4,2);
    E.plateau[36] = roi;
    E.plateau[34] = dame;
    return E;
}

// Profondeur en argument
int minimax(Position &P, int alpha, int beta, int depth)
{
//    Position* pP=&P;
//    cout<<"         debut           "<<endl;
//    cout<<"         ======          "<<endl;
//    P.print_position();
 //   int c = P.valeur_position();
  //  if ( c == MIN || c == MAX)
  //  {
  //      return c;
 //   }

    P.position_possible();
    Position* pFilles= P.fille;
    int a = alpha;
    int b = beta;
//	 Terminating condition. i.e
//	 leaf node is reached
	if ( pFilles == nullptr || depth == 0) {
//        cout<<"Valeur de la position finale "<<a<<endl;
		return P.valeur_position();
	}
    if (P.joueur == 1)
    {
        int best = MIN;

//        First child
//        pP=P.fille;
        pFilles->joueur = 2;
        int val = minimax(*pFilles, a, b, depth-1);
        best = max(best, val);
//          Recur for her sisters

        while (pFilles->soeur!=NULL)
        {
            Position* pS=pFilles->soeur;
            if (pS->gagne()) {return pS->valeur_position();}
            int val = minimax(*(pS), a, b, depth-1);
            best = max(best, val);
            pFilles=pS;
            alpha = max(alpha, best);

    /*        // Alpha Beta Pruning
            if (beta <= alpha)
                break;              */
        }
        return best;
        }
    else
    {
        int best = MAX;

//          first child
//        pP=P.fille;
        pFilles->joueur = 1;
        int val = minimax(*pFilles, a, b, depth-1);
        best = min(best, val);
          //Recur for her sisters

        while (pFilles->soeur!=NULL)
        {   Position* pS=pFilles->soeur;
            int val = minimax(*(pS), a, b, depth-1);
            best = min(best, val);
            pFilles=pS;
            beta = min(alpha, best);
      /*      // Alpha Beta Pruning
            if (beta <= alpha)
                break;              */
        }
        return best;
    }
}


Position_Echec& Position_Echec::coup_humain(){ //Met le coup joué par le joueur humain dans la liste de coup
    string reponse;
    if (this->couleur_joueur==Blanc){
        cout<<"C'est au tour du joueur blanc de jouer"<<endl;
    }
    if (this->couleur_joueur==Noir){
        cout<<"C'est au tour du joueur noir de jouer"<<endl;
    }
    cout<<"Coup special ou normal ?"<<endl;
    cin >> reponse;
    string N("normal");
    string S("special");
    string A("A");
    string B("B");
    string C("C");
    string D("D");
    string E("E");
    string F("F");
    string G("G");
    string H("H");
    int j_init;
    int j_final;
    int i_init;
    int i_final;
    if (reponse == N){
        int n= 0;
        while (n==0){
            //Recupération des donnees utilisateur
            cout<<"Position de la piece a jouer ?"<<endl;
            string pos_int;
            cin >> pos_int;
            cout<<"Position finale de la piece ?"<<endl;
            string pos_final;
            cin >> pos_final;

            //Analyse de ces données
            char c1 = pos_int[1];
            char c2 = pos_final[1];
            string str_i_init(1,c1);
            string str_i_final(1,c2);
            pos_int.resize(1);
            pos_final.resize(1);


            stringstream ss;
                ss << str_i_init;
                ss >> i_init;
            stringstream sss;
                sss << str_i_final;
                sss >> i_final;
            i_init = i_init -1;
            i_final = i_final -1;




            if (pos_int==A){ j_init = 0 ;}
            if (pos_int==B){ j_init = 1 ;}
            if (pos_int==C){ j_init = 2 ;}
            if (pos_int==D){ j_init = 3 ;}
            if (pos_int==E){ j_init = 4 ;}
            if (pos_int==F){ j_init = 5 ;}
            if (pos_int==G){ j_init = 6 ;}
            if (pos_int==H){ j_init = 7 ;}

            if (pos_final==A){ j_final = 0 ;}
            if (pos_final==B){ j_final = 1 ;}
            if (pos_final==C){ j_final = 2 ;}
            if (pos_final==D){ j_final = 3 ;}
            if (pos_final==E){ j_final = 4 ;}
            if (pos_final==F){ j_final = 5 ;}
            if (pos_final==G){ j_final = 6 ;}
            if (pos_final==H){ j_final = 7 ;}

            if (this->echiquier_ref.plateau[i_init*8+j_init]->Couleur == this->couleur_joueur){
                n=1;
            } else {
                cout<<"Ce n'est pas une pièce de la bonne couleur !"<<endl;
            }
        }
        //Mise à jour de la liste de coup de la position

        if (this->echiquier_ref.plateau[i_final*8+j_final] != nullptr){
            cout<<"Vous mangez une piece"<<endl;
            coup_echec coup_joue(this->echiquier_ref.plateau[i_init*8+j_init],this->echiquier_ref.plateau[i_final*8+j_final],i_init,j_init,i_final,j_final);
            coup_joue.affichage_standard();
            this->Liste_coup.push_back(coup_joue);
        }else if (this->echiquier_ref.plateau[i_final*8+j_final] == nullptr){
            coup_echec coup_joue(this->echiquier_ref.plateau[i_init*8+j_init],i_init,j_init,i_final,j_final);
            coup_joue.affichage_standard();
            this->Liste_coup.push_back(coup_joue);
        }
    }
    if (reponse == S){
        cout<<"lequel ? : g_rooc , p_rooc , prom_t , prom_d , prom_c , prom_f ?"<<endl;
        string reponse2;
        cin >> reponse2;

        string p_rooc("p_rooc");
        string g_rooc("g_rooc");
        string prom_t("prom_t");
        string prom_d("prom_d");
        string prom_c("prom_c");
        string prom_f("prom_f");

        if(reponse2 == p_rooc ){
            cout<<"Vous effectuez un petit rooc"<<endl;
            coup_echec coup_joue("p_rooc",this->couleur_joueur);
            coup_joue.affichage_standard();
            this->Liste_coup.push_back(coup_joue);
        }
        if(reponse2 == g_rooc ){
            cout<<"Vous effectuez un grand rooc"<<endl;
            coup_echec coup_joue("g_rooc",this->couleur_joueur);
            coup_joue.affichage_standard();
            this->Liste_coup.push_back(coup_joue);
        }else if (reponse2 == prom_c || reponse2==prom_f || reponse2==prom_t || reponse2==prom_d){
            //Recupération des donnees utilisateur
                    int n= 0;
        while (n==0){
            //Recupération des donnees utilisateur
            cout<<"Position de la piece a jouer ?"<<endl;
            string pos_int;
            cin >> pos_int;
            cout<<"Position finale de la piece ?"<<endl;
            string pos_final;
            cin >> pos_final;

            //Analyse de ces données
            char c1 = pos_int[1];
            char c2 = pos_final[1];
            string str_i_init(1,c1);
            string str_i_final(1,c2);
            pos_int.resize(1);
            pos_final.resize(1);


            stringstream ss;
                ss << str_i_init;
                ss >> i_init;
            stringstream sss;
                sss << str_i_final;
                sss >> i_final;
            i_init = i_init -1;
            i_final = i_final -1;




            if (pos_int==A){ j_init = 0 ;}
            if (pos_int==B){ j_init = 1 ;}
            if (pos_int==C){ j_init = 2 ;}
            if (pos_int==D){ j_init = 3 ;}
            if (pos_int==E){ j_init = 4 ;}
            if (pos_int==F){ j_init = 5 ;}
            if (pos_int==G){ j_init = 6 ;}
            if (pos_int==H){ j_init = 7 ;}

            if (pos_final==A){ j_final = 0 ;}
            if (pos_final==B){ j_final = 1 ;}
            if (pos_final==C){ j_final = 2 ;}
            if (pos_final==D){ j_final = 3 ;}
            if (pos_final==E){ j_final = 4 ;}
            if (pos_final==F){ j_final = 5 ;}
            if (pos_final==G){ j_final = 6 ;}
            if (pos_final==H){ j_final = 7 ;}

            if (this->echiquier_ref.plateau[i_init*8+j_init]->Couleur == this->couleur_joueur){
                n=1;
            } else {
                cout<<"Ce n'est pas une pièce de la bonne couleur !"<<endl;
            }
        }
            if(reponse2 == prom_c){
                if (this->echiquier_ref.plateau[i_final*8+j_final] != nullptr){
                    cout<<"Vous mangez une piece"<<endl;
                    cout<<"Vous obtenez un cavalier"<<endl;
                    coup_echec coup_joue("prom_c",this->echiquier_ref.plateau[i_init*8+j_init],this->echiquier_ref.plateau[i_final*8+j_final],i_init,j_init,i_final,j_final);
                    coup_joue.affichage_standard();
                    this->Liste_coup.push_back(coup_joue);
                }else if (this->echiquier_ref.plateau[i_final*8+j_final] == nullptr){
                    cout<<"Vous obtenez un cavalier"<<endl;
                    coup_echec coup_joue("prom_c",this->echiquier_ref.plateau[i_init*8+j_init],i_init,j_init,i_final,j_final);
                    coup_joue.affichage_standard();
                    this->Liste_coup.push_back(coup_joue);
                }

            }
            if(reponse2 == prom_f){
                if (this->echiquier_ref.plateau[i_final*8+j_final] != nullptr){
                    cout<<"Vous mangez une piece"<<endl;
                    cout<<"Vous obtenez un fou"<<endl;
                    coup_echec coup_joue("prom_f",this->echiquier_ref.plateau[i_init*8+j_init],this->echiquier_ref.plateau[i_final*8+j_final],i_init,j_init,i_final,j_final);
                    coup_joue.affichage_standard();
                    this->Liste_coup.push_back(coup_joue);
                }else if (this->echiquier_ref.plateau[i_final*8+j_final] == nullptr){
                    cout<<"Vous obtenez un fou"<<endl;
                    coup_echec coup_joue("prom_f",this->echiquier_ref.plateau[i_init*8+j_init],i_init,j_init,i_final,j_final);
                    coup_joue.affichage_standard();
                    this->Liste_coup.push_back(coup_joue);
                }

            }
            if(reponse2 == prom_d){
                if (this->echiquier_ref.plateau[i_final*8+j_final] != nullptr){
                    cout<<"Vous mangez une piece"<<endl;
                    cout<<"Vous obtenez une dame"<<endl;
                    coup_echec coup_joue("prom_d",this->echiquier_ref.plateau[i_init*8+j_init],this->echiquier_ref.plateau[i_final*8+j_final],i_init,j_init,i_final,j_final);
                    coup_joue.affichage_standard();
                    this->Liste_coup.push_back(coup_joue);
                }else if (this->echiquier_ref.plateau[i_final*8+j_final] == nullptr){
                    cout<<"Vous obtenez une dame"<<endl;
                    coup_echec coup_joue("prom_d",this->echiquier_ref.plateau[i_init*8+j_init],i_init,j_init,i_final,j_final);
                    coup_joue.affichage_standard();
                    this->Liste_coup.push_back(coup_joue);
                }

            }
            if(reponse2 == prom_t){
                if (this->echiquier_ref.plateau[i_final*8+j_final] != nullptr){
                    cout<<"Vous mangez une piece"<<endl;
                    cout<<"Vous obtenez une tour"<<endl;
                    coup_echec coup_joue("prom_t",this->echiquier_ref.plateau[i_init*8+j_init],this->echiquier_ref.plateau[i_final*8+j_final],i_init,j_init,i_final,j_final);
                    coup_joue.affichage_standard();
                    this->Liste_coup.push_back(coup_joue);
                }else if (this->echiquier_ref.plateau[i_final*8+j_final] == nullptr){
                    cout<<"Vous obtenez une tour"<<endl;
                    coup_echec coup_joue("prom_t",this->echiquier_ref.plateau[i_init*8+j_init],i_init,j_init,i_final,j_final);
                    coup_joue.affichage_standard();
                    this->Liste_coup.push_back(coup_joue);
                }

            }


        }

    }
    return(*this);
}


Position_Echec& Position_Echec::position_possible()
{
    PieceColor turn = couleur_joueur;
    bool presence; //Ce booléen est fait pour les pieces pouvant se déplacer sur plusieurs cases : si sur le chemin on a un allié, on ne peut pas allé plus loin
    for (int i = 0; i < 8; ++i)
    { //On se balade dans les lignes
        for (int j = 0; j < 8; ++j)
        { //On se balade dans les colonnes
            piece* Pc= this->echiquier_ref.plateau[8*i+j]; //Piece qui se trouve dans cette emplacement
            if (Pc != nullptr && Pc->Couleur==turn)
            { //S'il y a une pièce et qu'elle correspond au joueur qui doit jouer
                vector<vector<int>> Dep = (Pc->P).Dep_rel; //On récupere sa matrice de mouvement
                if (Pc->P.Nom_piece != Pion && Pc->P.Nom_piece != Roi)//Si la piece n'est pas un pion
                 {
                     int b = (int)(Dep[0].size());
                     for(int l = 0; l<b; l++)
                    {
                        presence = false;
                        if (Pc->P.Nom_piece == Cavalier)
                        {
                            if (interieur_plateau(i + Dep[0][l],j + Dep[1][l] ))
                            {
                                piece* actuel = echiquier_ref.plateau[8*(i + Dep[0][l]) + j + Dep[1][l]];
                                if (actuel == nullptr) //Si la case est vide
                                {
                                    //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur = new Position_Echec;
                                    coup_echec C(Pc, i, j, i + Dep[0][l], j + Dep[1][l]); //Nouveau coup_echec
                                    nouvelle_soeur->couleur_joueur = turn;
                                    nouvelle_soeur->echiquier_ref = echiquier_ref; //On enregistre l'échiquier actuel pour le modifier après
                                    nouvelle_soeur->Liste_coup = Liste_coup;
                                    nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;
                                }
                                else if (actuel->Couleur != turn && actuel->P.Nom_piece!=Roi) //Une piece est sur le chemin : ce n'est ni une pièce allié, ni le roi
                                {
                                    Position_Echec* nouvelle_soeur = new Position_Echec;
                                    nouvelle_soeur->couleur_joueur = turn;
                                    coup_echec C(Pc,actuel, i, j, i + Dep[0][1], j + Dep[1][l]); //Nouveau coup_echec

                                    //On crée la nouvelle soeur et on change la couleur
                                    nouvelle_soeur->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur->Liste_coup = Liste_coup;
                                    nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;
                                }
                            }
                        }
                        else //Si la pièce peut se balader sur plusieurs cases
                        {
                            presence = false;
                            int k = 1;
                            while (interieur_plateau(i + k*Dep[0][l],j + k*Dep[1][l]) && presence == false)
                            {
                                piece* actuel = echiquier_ref.plateau[8*(i + k*Dep[0][l]) + j + k*Dep[1][l]];
                                if (actuel == nullptr) //Si la case est vide
                                {
                                    coup_echec C(Pc, i, j, i + k*Dep[0][l], j + k*Dep[1][l]); //Nouveau coup_echec

                                    //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur = new Position_Echec;
                                    nouvelle_soeur->couleur_joueur = turn;
                                    nouvelle_soeur->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur->Liste_coup = Liste_coup;
                                    nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;
                                    ++k;

                                }
                                else if (actuel->Couleur != turn && actuel->P.Nom_piece!=Roi) //Une piece est sur le chemin : ce n'est ni une pièce allié, ni le roi
                                {
                                    coup_echec C(Pc,actuel, i, j, i + k*Dep[0][1], j + k*Dep[1][l]); //Nouveau coup_echec

                                    //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur = new Position_Echec;
                                    nouvelle_soeur->couleur_joueur = turn;
                                    nouvelle_soeur->Liste_coup = Liste_coup;
                                    nouvelle_soeur->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;
                                    ++k;
                                    presence = true;
                                }
                                else if (actuel->Couleur == turn || actuel->P.Nom_piece==Roi)
                                {
                                    presence = true;
                                }
                            }
                        }
                    }
                }
                if(Pc->P.Nom_piece == Pion) //Si Pc est un pion
                {
                    if (Pc->Couleur == Blanc) // Si le pion est blanc
                    {
                        if (i <=5) //Si le pion n'est pas sur la dernière ligne
                        {
                            piece* actuel = echiquier_ref.plateau[8*(i + 1) + j];
                            if (actuel == nullptr)
                            {

                                coup_echec C(Pc, i, j, i + 1, j); //Nouveau coup_echec
                                //On crée la nouvelle soeur et on change la couleur
                                Position_Echec* nouvelle_soeur = new Position_Echec;
                                nouvelle_soeur->couleur_joueur = turn;
                                nouvelle_soeur->Liste_coup = Liste_coup;
                                nouvelle_soeur->echiquier_ref = echiquier_ref;
                                nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                //Pas de prise
                                nouvelle_soeur->soeur = this->fille;
                                this->fille = nouvelle_soeur;
                            }
                        }
                         else if (i == 6)//Juste promotion en avancant
                        {
                            piece* actuel = echiquier_ref.plateau[8*(i + 1) + j ];
                            if (actuel == nullptr)
                            {
                                //Promotion fou
                                coup_echec C("prom_f",Pc, i, j, i + 1, j); //Nouveau coup_echec
                            //On crée la nouvelle soeur et on change la couleur
                                Position_Echec* nouvelle_soeur = new Position_Echec;
                                nouvelle_soeur->couleur_joueur = turn;
                                nouvelle_soeur->Liste_coup = Liste_coup;
                                nouvelle_soeur->echiquier_ref = echiquier_ref;
                                nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                //pas de Pprise
                                nouvelle_soeur->soeur = this->fille;
                                this->fille = nouvelle_soeur;

                                //Promotion Tour
                                coup_echec D("prom_t",Pc, i, j, i + 1, j); //Nouveau coup_echec
                            //On crée la nouvelle soeur et on change la couleur
                                Position_Echec* nouvelle_soeur1 = new Position_Echec;
                                nouvelle_soeur1->couleur_joueur = turn;
                                nouvelle_soeur1->Liste_coup = Liste_coup;
                                nouvelle_soeur1->echiquier_ref = echiquier_ref;
                                nouvelle_soeur1->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                //pas de Pprise
                                nouvelle_soeur1->soeur = this->fille;
                                this->fille = nouvelle_soeur1;

                                //Promotion dame
                                coup_echec E("prom_d",Pc, i, j, i + 1, j); //Nouveau coup_echec
                            //On crée la nouvelle soeur et on change la couleur
                                Position_Echec* nouvelle_soeur2 = new Position_Echec;
                                nouvelle_soeur2->couleur_joueur = turn;
                                nouvelle_soeur2->Liste_coup = Liste_coup;
                                nouvelle_soeur2->echiquier_ref = echiquier_ref;
                                nouvelle_soeur2->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                //pas de Pprise
                                nouvelle_soeur2->soeur = this->fille;
                                this->fille = nouvelle_soeur2;

                                //Promotion cavalier
                                coup_echec F("prom_c",Pc, i, j, i + 1, j); //Nouveau coup_echec
                            //On crée la nouvelle soeur et on change la couleur
                                Position_Echec* nouvelle_soeur3 = new Position_Echec;
                                nouvelle_soeur3->couleur_joueur = turn;
                                nouvelle_soeur3->echiquier_ref = echiquier_ref;
                                nouvelle_soeur3->Liste_coup = Liste_coup;
                                nouvelle_soeur3->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                //pas de Pprise
                                nouvelle_soeur3->soeur = this->fille;
                                this->fille = nouvelle_soeur3;
                            }
                        }
                        if (i == 1) // Si le pion n'a pas encore bougé
                        {
                            piece* actuel = echiquier_ref.plateau[8*(i + 2) + j ];
                            if (actuel == nullptr)
                            {

                                coup_echec C(Pc, i, j, i + 2, j); //Nouveau coup_echec
                                //On crée la nouvelle soeur et on change la couleur
                                Position_Echec* nouvelle_soeur = new Position_Echec;
                                nouvelle_soeur->couleur_joueur = turn;
                                nouvelle_soeur->echiquier_ref = echiquier_ref;
                                nouvelle_soeur->Liste_coup = Liste_coup;
                                nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                nouvelle_soeur->soeur = this->fille;
                                this->fille = nouvelle_soeur;
                            }
                        }
                        if (i + 1 <=6 && 0<= j + 1 && j + 1 <=7) //Si le pion se trouve dans la situation où il peut manger (diagonale droite)
                        {
                            piece* actuel = this->echiquier_ref.plateau[8*(i + 1) + j + 1];
                            if (actuel != nullptr && actuel->Couleur == Noir) // Si la piece est mangeable
                            {
                                if (actuel->P.Nom_piece != Roi) //Et que c'est pas un roi
                                {
                                    coup_echec C(Pc,actuel, i, j, i + 1, j + 1); //Nouveau coup_echec
                                    //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur = new Position_Echec;
                                    nouvelle_soeur->couleur_joueur = turn;
                                    nouvelle_soeur->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur->Liste_coup = Liste_coup;
                                    nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;
                                }
                            }
                        }
                        else if( i  + 1 == 7 && j + 1 <= 7) //Promotion droite + manger
                        {
                            piece* actuel = this->echiquier_ref.plateau[j + 1];
                            if (actuel != nullptr && actuel->Couleur == Noir) // Si la piece est mangeable
                            {
                                if (actuel->P.Nom_piece != Roi) //Et que c'est pas un roi
                                {
                                    //Promotion fou
                                    coup_echec C("prom_f",Pc,actuel, i, j, i + 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur = new Position_Echec;
                                    nouvelle_soeur->couleur_joueur = turn;
                                    nouvelle_soeur->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur->Liste_coup = Liste_coup;
                                    nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;

                                    //Promotion tour
                                    coup_echec D("prom_t",Pc,actuel, i, j, i + 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur2 = new Position_Echec;
                                    nouvelle_soeur->couleur_joueur = turn;
                                    nouvelle_soeur2->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur2->Liste_coup = Liste_coup;
                                    nouvelle_soeur2->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur2->soeur = this->fille;
                                    this->fille = nouvelle_soeur2;

                                    //Promotion dame
                                    coup_echec E("prom_d",Pc,actuel, i, j, i + 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur3 = new Position_Echec;
                                    nouvelle_soeur->couleur_joueur = turn;
                                    nouvelle_soeur3->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur3->Liste_coup = Liste_coup;
                                    nouvelle_soeur3->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur3->soeur = this->fille;
                                    this->fille = nouvelle_soeur3;

                                    //Promotion cavalier
                                    coup_echec F("prom_c",Pc,actuel, i, j, i + 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur4 = new Position_Echec;
                                    nouvelle_soeur4->couleur_joueur = turn;
                                    nouvelle_soeur4->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur4->Liste_coup = Liste_coup;
                                    nouvelle_soeur4->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur4->soeur = this->fille;
                                    this->fille = nouvelle_soeur4;
                                }
                            }
                        }
                        if (i + 1<=6 && 0<= j - 1) //Si le pion se trouve dans la situation où il peut manger (diagonale gauche)
                        {
                            piece* actuel = this->echiquier_ref.plateau[8*(i + 1) + j - 1];
                            if (actuel != nullptr && actuel->Couleur == Noir) // Si la piece est mangeable
                            {
                                if (actuel->P.Nom_piece != Roi) //Et que c'est pas un roi
                                {
                                    coup_echec C(Pc,actuel, i, j, i + 1, j - 1); //Nouveau coup_echec
                                    //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur = new Position_Echec;
                                    nouvelle_soeur->couleur_joueur = turn;
                                    nouvelle_soeur->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur->Liste_coup = Liste_coup;
                                    nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;
                                }
                            }
                        }
                        else if( i + 1 == 7 && 0<= j - 1) //Promotion gauche + manger
                        {
                            piece* actuel = this->echiquier_ref.plateau[j + 1];
                            if (actuel != nullptr && actuel->Couleur == Noir) // Si la piece est mangeable
                            {
                                if (actuel->P.Nom_piece != Roi) //Et que c'est pas un roi
                                {
                                    //Promotion fou
                                    coup_echec C("prom_f",Pc,actuel, i, j, i + 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur = new Position_Echec;
                                    nouvelle_soeur->couleur_joueur = turn;
                                    nouvelle_soeur->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur->Liste_coup = Liste_coup;
                                    nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;

                                    //Promotion tour
                                    coup_echec D("prom_t",Pc,actuel, i, j, i + 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur2 = new Position_Echec;
                                    nouvelle_soeur2->couleur_joueur = turn;
                                    nouvelle_soeur2->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur2->Liste_coup = Liste_coup;
                                    nouvelle_soeur2->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur2->soeur = this->fille;
                                    this->fille = nouvelle_soeur2;

                                    //Promotion dame
                                    coup_echec E("prom_d",Pc,actuel, i, j, i + 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur3 = new Position_Echec;
                                    nouvelle_soeur3->couleur_joueur = turn;
                                    nouvelle_soeur3->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur3->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur3->soeur = this->fille;
                                    this->fille = nouvelle_soeur3;

                                    //Promotion cavalier
                                    coup_echec F("prom_c",Pc,actuel, i, j, i + 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur4 = new Position_Echec;
                                    nouvelle_soeur4->couleur_joueur = turn;
                                    nouvelle_soeur4->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur4->Liste_coup = Liste_coup;
                                    nouvelle_soeur4->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur4->soeur = this->fille;
                                    this->fille = nouvelle_soeur4;
                                }
                            }
                        }
                    }
                    else //Si le pion est Noire
                    {
                        if (i > 1)
                        {
                            piece* actuel = echiquier_ref.plateau[8*(i - 1) + j ];
                            if (actuel == nullptr)
                            {

                                coup_echec C(Pc, i, j, i -1, j); //Nouveau coup_echec
                            //On crée la nouvelle soeur et on change la couleur
                                Position_Echec* nouvelle_soeur = new Position_Echec;
                                nouvelle_soeur->couleur_joueur = turn;
                                nouvelle_soeur->echiquier_ref = echiquier_ref;
                                nouvelle_soeur->Liste_coup = Liste_coup;
                                nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                //pas de Pprise
                                nouvelle_soeur->soeur = this->fille;
                                this->fille = nouvelle_soeur;

                            }
                        }
                        else //Promotion, on se trouve à i = 1, impossible d'avoir un pion à i = 0 normalement
                        {
                            piece* actuel = echiquier_ref.plateau[8*(i - 1) + j ];
                            if (actuel == nullptr)
                            {
                                //Promotion fou
                                coup_echec C("prom_f",Pc, i, j, i - 1, j); //Nouveau coup_echec
                            //On crée la nouvelle soeur et on change la couleur
                                Position_Echec* nouvelle_soeur = new Position_Echec;
                                nouvelle_soeur->couleur_joueur = turn;
                                nouvelle_soeur->echiquier_ref = echiquier_ref;
                                nouvelle_soeur->Liste_coup = Liste_coup;
                                nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                //pas de Pprise
                                nouvelle_soeur->soeur = this->fille;
                                this->fille = nouvelle_soeur;

                                //Promotion Tour
                                coup_echec D("prom_t",Pc, i, j, i - 1, j); //Nouveau coup_echec
                            //On crée la nouvelle soeur et on change la couleur
                                Position_Echec* nouvelle_soeur1 = new Position_Echec;
                                nouvelle_soeur1->couleur_joueur = turn;
                                nouvelle_soeur1->echiquier_ref = echiquier_ref;
                                nouvelle_soeur1->Liste_coup = Liste_coup;
                                nouvelle_soeur1->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                //pas de Pprise
                                nouvelle_soeur1->soeur = this->fille;
                                this->fille = nouvelle_soeur1;


                                //Promotion dame
                                coup_echec E("prom_d",Pc, i, j, i - 1, j); //Nouveau coup_echec
                            //On crée la nouvelle soeur et on change la couleur
                                Position_Echec* nouvelle_soeur2 = new Position_Echec;
                                if (turn == Blanc)
                                nouvelle_soeur2->couleur_joueur = turn;
                                nouvelle_soeur2->Liste_coup = Liste_coup;
                                nouvelle_soeur2->echiquier_ref = echiquier_ref;
                                nouvelle_soeur2->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                //pas de Pprise
                                nouvelle_soeur2->soeur = this->fille;
                                this->fille = nouvelle_soeur2;

                                //Promotion cavalier
                                coup_echec F("prom_c",Pc, i, j, i - 1, j); //Nouveau coup_echec
                            //On crée la nouvelle soeur et on change la couleur
                                Position_Echec* nouvelle_soeur3 = new Position_Echec;
                                nouvelle_soeur3->couleur_joueur = turn;
                                nouvelle_soeur3->Liste_coup = Liste_coup;
                                nouvelle_soeur3->echiquier_ref = echiquier_ref;
                                nouvelle_soeur3->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                //pas de Pprise
                                nouvelle_soeur3->soeur = this->fille;
                                this->fille = nouvelle_soeur3;

                            }
                        }
                        if (i == 6) //Le pion Noir n'a pas encore bougé
                        {
                            piece*  actuel= echiquier_ref.plateau[8*(i - 2) + j ];
                            if (actuel == nullptr)
                            {

                                coup_echec C(Pc, i, j, i - 2, j); //Nouveau coup_echec
                                //On crée la nouvelle soeur et on change la couleur
                                Position_Echec* nouvelle_soeur = new Position_Echec;
                                nouvelle_soeur->couleur_joueur = turn;
                                nouvelle_soeur->echiquier_ref = echiquier_ref;
                                nouvelle_soeur->Liste_coup = Liste_coup;
                                nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                nouvelle_soeur->soeur = this->fille;
                                this->fille = nouvelle_soeur;
                            }
                        }
                        if (1<= i - 1  && i - 1 <=7 && j + 1 <=7) //Si le pion se trouve dans la situation où il peut manger (diagonale droite)
                        {
                            piece* actuel = this->echiquier_ref.plateau[8*(i - 1) + j + 1];
                            if (actuel != nullptr && actuel->Couleur == Blanc) // Si la piece est mangeable
                            {
                                if (actuel->P.Nom_piece != Roi) //Et que c'est pas un roi
                                {
                                    coup_echec C(Pc,actuel, i, j, i - 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur = new Position_Echec;
                                    nouvelle_soeur->couleur_joueur = turn;
                                    nouvelle_soeur->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur->Liste_coup = Liste_coup;
                                    nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;
                                }
                            }
                        }
                        else if (i == 1 && j + 1 <=7) //Le pion noir peut manger et faire promotion en même temps en diagonale droite
                        {
                            piece* actuel = this->echiquier_ref.plateau[j + 1];
                            if (actuel != nullptr && actuel->Couleur == Blanc) // Si la piece est mangeable
                            {
                                if (actuel->P.Nom_piece != Roi) //Et que c'est pas un roi
                                {
                                    //Promotion fou
                                    coup_echec C("prom_f",Pc,actuel, i, j, i - 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur = new Position_Echec;
                                    nouvelle_soeur->couleur_joueur = turn;
                                    nouvelle_soeur->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur->Liste_coup = Liste_coup;
                                    nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;

                                    //Promotion tour
                                    coup_echec D("prom_t",Pc,actuel, i, j, i - 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur2 = new Position_Echec;
                                    nouvelle_soeur2->couleur_joueur = turn;
                                    nouvelle_soeur2->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur2->Liste_coup = Liste_coup;
                                    nouvelle_soeur2->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur2->soeur = this->fille;
                                    this->fille = nouvelle_soeur2;

                                    //Promotion dame
                                    coup_echec E("prom_d",Pc,actuel, i, j, i - 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur3 = new Position_Echec;
                                    nouvelle_soeur3->couleur_joueur = turn;
                                    nouvelle_soeur3->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur3->Liste_coup = Liste_coup;
                                    nouvelle_soeur3->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur3->soeur = this->fille;
                                    this->fille = nouvelle_soeur3;

                                    //Promotion cavalier
                                    coup_echec F("prom_c",Pc,actuel, i, j, i - 1, j + 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur4 = new Position_Echec;
                                    nouvelle_soeur4->couleur_joueur = turn;
                                    nouvelle_soeur4->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur4->Liste_coup = Liste_coup;
                                    nouvelle_soeur4->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur4->soeur = this->fille;
                                    this->fille = nouvelle_soeur4;
                                }
                            }
                        }

                        if (1<= i - 1 && i - 1 <=7 && 0<= j - 1) //Si le pion se trouve dans la situation où il peut manger (diagonale gauche)
                        {
                            piece* actuel = this->echiquier_ref.plateau[8*(i - 1) + j - 1];
                            if (actuel != nullptr && actuel->Couleur == Blanc) // Si la piece est mangeable
                            {
                                if (actuel->P.Nom_piece != Roi) //Et que c'est pas un roi
                                {
                                    coup_echec C(Pc, actuel, i, j, i - 1, j - 1); //Nouveau coup_echec
                                    //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur = new Position_Echec;
                                    nouvelle_soeur->couleur_joueur = turn;
                                    nouvelle_soeur->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur->Liste_coup = Liste_coup;
                                    nouvelle_soeur->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;
                                }
                            }
                        }
                        else if ( i == 1 && j - 1 >= 0) //Promotion plus manger d'un coup en diagonale gauche
                        {
                            piece* actuel = this->echiquier_ref.plateau[j - 1];
                            if (actuel != nullptr && actuel->Couleur == Blanc) // Si la piece est mangeable
                            {
                                if (actuel->P.Nom_piece != Roi) //Et que c'est pas un roi
                                {
                                    //Promotion fou
                                    coup_echec C("prom_f",Pc,actuel, i, j, i - 1, j - 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur1 = new Position_Echec;
                                    nouvelle_soeur1->couleur_joueur = turn;
                                    nouvelle_soeur1->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur1->Liste_coup = Liste_coup;
                                    nouvelle_soeur1->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur1->soeur = this->fille;
                                    this->fille = nouvelle_soeur1;

                                    //Promotion tour
                                    coup_echec D("prom_t",Pc,actuel, i, j, i - 1, j - 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur2 = new Position_Echec;
                                    nouvelle_soeur2->couleur_joueur = turn;
                                    nouvelle_soeur2->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur2->Liste_coup = Liste_coup;
                                    nouvelle_soeur2->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur2->soeur = this->fille;
                                    this->fille = nouvelle_soeur2;

                                    //Promotion dame
                                    coup_echec E("prom_d",Pc,actuel, i, j, i - 1, j - 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur3 = new Position_Echec;
                                    nouvelle_soeur3->couleur_joueur = turn;
                                    nouvelle_soeur3->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur3->Liste_coup = Liste_coup;
                                    nouvelle_soeur3->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur3->soeur = this->fille;
                                    this->fille = nouvelle_soeur3;

                                    //Promotion cavalier
                                    coup_echec F("prom_c",Pc,actuel, i, j, i - 1, j - 1); //Nouveau coup_echec
                                     //On crée la nouvelle soeur et on change la couleur
                                    Position_Echec* nouvelle_soeur4 = new Position_Echec;
                                    nouvelle_soeur4->couleur_joueur = turn;
                                    nouvelle_soeur4->echiquier_ref = echiquier_ref;
                                    nouvelle_soeur4->Liste_coup = Liste_coup;
                                    nouvelle_soeur4->Liste_coup.push_back(C); //Grace au coup echec qu'on a enregistré
                                    nouvelle_soeur4->soeur = this->fille;
                                    this->fille = nouvelle_soeur4;
                                }
                            }
                        }
                    }
                }
                else if (Pc->P.Nom_piece == Roi) //Si on bouge le roi
                {
                    for (int l = 0; l<8; l++) //Grace à sa matrice de mouvement
                    {
                        if (0<= i + Dep[0][l] && i + Dep[0][l]  < 8 && 0<= j + Dep[1][l] && j + Dep[1][l]<8)
                        {

                            piece* actuel = echiquier_ref.plateau[8*(i + Dep[0][l]) +  j + Dep[1][l]];
                            if (actuel == nullptr)
                            {
                                coup_echec C(Pc, i, j, i + Dep[0][l], j + Dep[1][l]);
                                Position_Echec* nouvelle_soeur = new Position_Echec;
                                nouvelle_soeur->couleur_joueur = turn;
                                nouvelle_soeur->echiquier_ref = echiquier_ref;
                                nouvelle_soeur->Liste_coup = Liste_coup;
                                nouvelle_soeur->Liste_coup.push_back(C);
                                Position_Echec* T = nouvelle_soeur;
                                T->mise_a_jour_position();
                                if (!T->test_echec2())
                                {
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;
                                }
                            }
                            else if (actuel != nullptr && actuel->Couleur != Pc->Couleur) //Si le roi mange un truc sans se mettre en echec
                            {
                                coup_echec C(Pc,actuel, i, j, i + Dep[0][l], j + Dep[1][l]);
                                Position_Echec* nouvelle_soeur = new Position_Echec;
                                nouvelle_soeur->couleur_joueur = turn;
                                nouvelle_soeur->Liste_coup = Liste_coup;
                                nouvelle_soeur->echiquier_ref = echiquier_ref;
                                nouvelle_soeur->Liste_coup.push_back(C);
                                Position_Echec* T = nouvelle_soeur;
                                T->mise_a_jour_position();
                                if (!T->test_echec2())
                                {
                                    nouvelle_soeur->soeur = this->fille;
                                    this->fille = nouvelle_soeur;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (this->test_g_rooc()) //Test du grand rooc
    {
        Position_Echec* nouvelle_soeur = new Position_Echec;
        nouvelle_soeur->couleur_joueur = turn;
        coup_echec C("g_rooc", turn);
        nouvelle_soeur->echiquier_ref = echiquier_ref;
        nouvelle_soeur->soeur = this->fille;
        this->fille = nouvelle_soeur;
        nouvelle_soeur->Liste_coup = Liste_coup;
        nouvelle_soeur->Liste_coup.push_back(C);
    }
    else if (this->test_p_rooc()) //Test du petit rooc
    {
        Position_Echec* nouvelle_soeur = new Position_Echec;
        nouvelle_soeur->couleur_joueur = turn;
        coup_echec C("p_rooc", turn);
        nouvelle_soeur->echiquier_ref = echiquier_ref;
        nouvelle_soeur->Liste_coup = Liste_coup;
        nouvelle_soeur->soeur = this->fille;
        this->fille = nouvelle_soeur;
        nouvelle_soeur->Liste_coup.push_back(C);
    }
    return *this;
}
