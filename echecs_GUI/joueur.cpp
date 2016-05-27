#include "joueur.h"
#include <iostream>

/*
+---+----------------+---------------+
|   |    nom         |       id      |
+---+----------------+---------------+
| 0 |    Roi         |       1       |
| 1 |    Reine       |       2       |
| 2 |    Fou1        |       3       |
| 3 |    Fou2        |       4       |
| 4 |    Cavalier1   |       5       |
| 5 |    Cavalier2   |       6       |
| 6 |    Tour1       |       7       |
| 7 |    Tour2       |       8       |
| 8 |    Pion1       |       9       |
| 9 |    Pion2       |       10      |
| 10|    Pion3       |       11      |
| 11|    Pion4       |       12      |
| 12|    Pion5       |       13      |
| 13|    Pion6       |       14      |
| 14|    Pion7       |       15      |
| 15|    Pion8       |       16      |
+---+----------------+---------------+
*/

string joueur::idToDesc(int id){
    switch (id){
    case 1:
        return "Roi";
        break;
    case 2:
        return "Reine";
        break;
    case 3:
        return "Fou 1";
        break;
    case 4:
        return "Fou 2";
        break;
    case 5:
        return "Cavalier 1";
        break;
    case 6:
        return "Cavalier 2";
        break;
    case 7:
        return "Tour 1";
        break;
    case 8:
        return "Tour 2";
        break;
    case 9:
        return "Pion 1";
        break;
    case 10:
        return "Pion 2";
        break;
    case 11:
        return "Pion 3";
        break;
    case 12:
        return "Pion 4";
        break;
    case 13:
        return "Pion 5";
        break;
    case 14:
        return "Pion 6";
        break;
    case 15:
        return "Pion 7";
        break;
    case 16:
        return "Pion 8";
        break;
    default:
        return "";
        break;
    }
}

string joueur::idToPath(int id){
    switch(playerID){
    case 1:
        switch (id){
        case 1:
            return "D:/ESISA/C++/echecs_GUI/pieces/king_black.svg";
            break;
        case 2:
            return "D:/ESISA/C++/echecs_GUI/pieces/queen_black.svg";
            break;
        case 3:
        case 4:
            return "D:/ESISA/C++/echecs_GUI/pieces/bishop_black.svg";
            break;
        case 5:
        case 6:
            return "D:/ESISA/C++/echecs_GUI/pieces/knight_black.svg";
            break;
        case 7:
        case 8:
            return "D:/ESISA/C++/echecs_GUI/pieces/rook_black.svg";
            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            return "D:/ESISA/C++/echecs_GUI/pieces/pawn_black.svg";
            break;
        default:
            return "";
            break;
        }
        break;
    case 2:
        switch (id){
        case 1:
            return "D:/ESISA/C++/echecs_GUI/pieces/king_white.svg";
            break;
        case 2:
            return "D:/ESISA/C++/echecs_GUI/pieces/queen_white.svg";
            break;
        case 3:
        case 4:
            return "D:/ESISA/C++/echecs_GUI/pieces/bishop_white.svg";
            break;
        case 5:
        case 6:
            return "D:/ESISA/C++/echecs_GUI/pieces/knight_white.svg";
            break;
        case 7:
        case 8:
            return "D:/ESISA/C++/echecs_GUI/pieces/rook_white.svg";
            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            return "D:/ESISA/C++/echecs_GUI/pieces/pawn_white.svg";
            break;
        default:
            return "";
            break;
        }
        break;
    default:
        return "";
        break;
    }
}

joueur::joueur(){
    joueur::init_pieces();
}
joueur::~joueur(){};

void joueur::set_piece_id(int index, int x){P[index].id = x;}
void joueur::set_piece_desc(int index, string x){P[index].desc = x;}
void joueur::set_piece_pos(int index, int x, int y){
    P[index].pos.x = x;
    P[index].pos.y = y;
}
void joueur::set_piece_active(int index, bool x){
    P[index].active = x;
}

int joueur::get_piece_id(int index){return P[index].id;}
string joueur::get_piece_desc(int index){return P[index].desc;}
position joueur::get_piece_pos(int index){return P[index].pos;}
bool joueur::get_piece_active(int index){return P[index].active;}

void joueur::init_pieces(){
    for (int i = 0; i < 16 ; i++)
    {
        joueur::set_piece_id(i, i+1);
    }
    for(int i = 0; i < 16; i++){
        joueur::set_piece_desc(i, idToDesc(joueur::get_piece_id(i)));
        joueur::set_piece_active(i, true);
    };
}
void joueur::set_playerID(int x){joueur::playerID=x;}
int joueur::get_playerID(){return joueur::playerID;}
