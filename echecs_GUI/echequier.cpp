#include "echequier.h"
#include "ui_echequier.h"
#include "QString"
#include <QMessageBox>
#include <string>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <QModelIndex>
#include <QImage>
#include <QLabel>

int playerID = 0;
int pieceID = 0;
int nbtour = 1;

echequier::echequier(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::echequier)
{
    ui->setupUi(this);
    this->setWindowTitle("ECHECS");
    echequier::init_cell_colors();
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 2 ; j++){
            echequier::init_cell_state(i, j, true);
        }
        for (int j = 2; j < 6 ; j++){
            echequier::init_cell_state(i, j, false);
        }
        for (int j = 6; j < 8 ; j++){
            echequier::init_cell_state(i, j, true);
        }
    }
        A.set_playerID(1);
        B.set_playerID(2);
        init_pos_pieces(A);
        init_pos_pieces(B);
        display();
        S = 0;
        ui->lcdNumber->setPalette(Qt::black);
        //ui->tableWidget->setFrameStyle(3);
}

echequier::~echequier()
{
    delete ui;
}

void echequier::init_cell_colors(){
    QColor x, y;
    for(int i = 0; i < 8; i++){
        if(i%2==1){
            x=Qt::gray;
            y=Qt::white;
        }else{
            x=Qt::white;
            y=Qt::gray;
        }
        for(int j = 0; j < 8; j++){
            ui->tableWidget->setItem(i, j, new QTableWidgetItem);
            ui->tableWidget->item(i, j)->setTextAlignment(4);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsSelectable);
            if((j%2)==1){
                ui->tableWidget->item(i, j)->setBackgroundColor(x);
                ui->tableWidget->item(i, j)->setTextColor(y);
            }else{
                ui->tableWidget->item(i, j)->setBackgroundColor(y);
                ui->tableWidget->item(i, j)->setTextColor(x);
            }
        }
    }
}

int echequier::get_player_cell(int x, int y){
    //returns an int that indicates which player owns the piece occupying the cell
    //return value meanings:
    //--1 means player A
    //--2 means player B
    if(echequier::C[x][y].plein){
        position p, p2;
        for(int i = 0; i < 16; i++){
            p = echequier::A.get_piece_pos(i);
            p2 = echequier::B.get_piece_pos(i);
            if(p.x==x && p.y==y) return 1;
            if(p2.x==x && p2.y==y) return 2;
        }
    }
    return 0;
}

int echequier::get_piece_cell(int playerID, int x, int y){
    if(playerID==1){
        //search in pieces of player A
        position p;
        for(int i = 0; i < 16; i++){
            p = A.get_piece_pos(i);
            if(p.x==x && p.y==y){
                return A.get_piece_id(i);
            }
        }
    }
    else if(playerID==2){
        //search in pieces of player B
        position p;
        for(int i = 0; i < 16; i++){
            p = B.get_piece_pos(i);
            if(p.x==x && p.y==y){
                return B.get_piece_id(i);
            }
        }
    }
    return 0;
}

vector <position> echequier::list_possible_moves(int id, joueur P){
    int x, y, r;
    x=P.get_piece_pos(id-1).x;
    y=P.get_piece_pos(id-1).y;
    vector <position> pos;
    position res, res2, RES[8];
    bool way = true, way2 = true;
    switch(id){
    case 1:
        for(int i = x-1; i<x+2; i++){
            for (int j = y-1; j<y+2; j++){
                if(i<0 || i>7 || j<0 || j>7 || ((i==x) && (j==y))){}
                else{
                    res.y=j;
                    res.x=i;
                    if(get_player_cell(i, j)!=P.get_playerID())  pos.push_back(res);
                }
            }
        }
        break;
    case 2:
        res.x=x;;
        res2.y=y;
        r = y;
        while(r < 8){
            if(r!=y && way){
                res.y=r;
                if(get_player_cell(res.x, res.y)!=P.get_playerID() && get_player_cell(res.x, res.y)!=0){
                    pos.push_back(res);
                    way = false;
                }
                else if(get_player_cell(res.x, res.y)!=P.get_playerID())   pos.push_back(res);
                else way = false;
            }
            r++;
        }
        way = true;
        r = y;
        while(r > -1){
            if(r!=y && way){
                res.y=r;
                if(get_player_cell(res.x, res.y)!=P.get_playerID() && get_player_cell(res.x, res.y)!=0){
                    pos.push_back(res);
                    way = false;
                }
                else if(get_player_cell(res.x, res.y)!=P.get_playerID())   pos.push_back(res);
                else way = false;
            }
            r--;
        }
        way = true;
        r = x;
        while(r < 8){
            if(r!=x && way){
                res2.x=r;
                if(get_player_cell(res2.x, res2.y)!=P.get_playerID() && get_player_cell(res2.x, res2.y)!=0){
                    pos.push_back(res2);
                    way = false;
                }
                else if(get_player_cell(res2.x, res2.y)!=P.get_playerID())   pos.push_back(res2);
                else way = false;
            }
            r++;
        }
        way = true;
        r = x;
        while(r > -1){
            if(r!=x && way){
                res2.x=r;
                if(get_player_cell(res2.x, res2.y)!=P.get_playerID() && get_player_cell(res2.x, res2.y)!=0){
                    pos.push_back(res2);
                    way = false;
                }
                else if(get_player_cell(res2.x, res2.y)!=P.get_playerID())   pos.push_back(res2);
                else way = false;
            }
            r--;
        }
        way = true;
        way2 = true;
        for(int i = 1; i < 7; i++){
            res.x=x-i;
            res.y=y-i;
            res2.x=x+i;
            res2.y=y+i;
            if(!(res.x<0 || res.y<0) && way){
                if(get_player_cell(res.x, res.y)!=P.get_playerID() && get_player_cell(res.x, res.y)!=0){
                    pos.push_back(res);
                    way = false;
                }
                else if(get_player_cell(res.x, res.y)!=P.get_playerID()) pos.push_back(res);
                else way = !way;
            }
            if(!(res2.y>7 || res2.x>7) && way2){
                if(get_player_cell(res2.x, res2.y)!=P.get_playerID() && get_player_cell(res2.x, res2.y)!=0){
                    pos.push_back(res2);
                    way2 = false;
                }
                else if(get_player_cell(res2.x, res2.y)!=P.get_playerID())   pos.push_back(res2);
                else way2 = !way2;
            }
        }
        way = true;
        way2 = true;
        for(int i = 1; i < 7; i++){
            res.x=x-i;
            res.y=y+i;
            res2.x=x+i;
            res2.y=y-i;
            if(!(res.x<0 || res.y>7) && way){
                if(get_player_cell(res.x, res.y)!=P.get_playerID() && get_player_cell(res.x, res.y)!=0){
                    pos.push_back(res);
                    way = false;
                }
                else if(get_player_cell(res.x, res.y)!=P.get_playerID()) pos.push_back(res);
                else way = ! way;
            }
            if(!(res2.y<0 || res2.x>7) && way2){
                if(get_player_cell(res2.x, res2.y)!=P.get_playerID() && get_player_cell(res2.x, res2.y)!=0){
                    pos.push_back(res2);
                    way2 = false;
                }
                else if(get_player_cell(res2.x, res2.y)!=P.get_playerID())   pos.push_back(res2);
                else way2 = ! way2;
            }
        }
        break;
    case 3:
    case 4:
        for(int i = 1; i < 7; i++){
            res.x=x-i;
            res.y=y-i;
            res2.x=x+i;
            res2.y=y+i;
            if(!(res.x<0 || res.y<0) && way){
                if(get_player_cell(res.x, res.y)!=P.get_playerID() && get_player_cell(res.x, res.y)!=0){
                    pos.push_back(res);
                    way = false;
                }
                else if(get_player_cell(res.x, res.y)!=P.get_playerID()) pos.push_back(res);
                else way = !way;
            }
            if(!(res2.y>7 || res2.x>7) && way2){
                if(get_player_cell(res2.x, res2.y)!=P.get_playerID() && get_player_cell(res2.x, res2.y)!=0){
                    pos.push_back(res2);
                    way2 = false;
                }
                else if(get_player_cell(res2.x, res2.y)!=P.get_playerID())   pos.push_back(res2);
                else way2 = !way2;
            }
        }
        way = true;
        way2 = true;
        for(int i = 1; i < 7; i++){
            res.x=x-i;
            res.y=y+i;
            res2.x=x+i;
            res2.y=y-i;
            if(!(res.x<0 || res.y>7) && way){
                if(get_player_cell(res.x, res.y)!=P.get_playerID() && get_player_cell(res.x, res.y)!=0){
                    pos.push_back(res);
                    way = false;
                }
                else if(get_player_cell(res.x, res.y)!=P.get_playerID()) pos.push_back(res);
                else way = ! way;
            }
            if(!(res2.y<0 || res2.x>7) && way2){
                if(get_player_cell(res2.x, res2.y)!=P.get_playerID() && get_player_cell(res2.x, res2.y)!=0){
                    pos.push_back(res2);
                    way2 = false;
                }
                else if(get_player_cell(res2.x, res2.y)!=P.get_playerID())   pos.push_back(res2);
                else way2 = ! way2;
            }
        }
        break;
    case 5:
    case 6:
        RES[0].x=x-2;
        RES[0].y=y-1;

        RES[1].x=x-1;
        RES[1].y=y-2;

        RES[2].x=x-2;
        RES[2].y=y+1;

        RES[3].x=x-1;
        RES[3].y=y+2;

        RES[4].x=x+2;
        RES[4].y=y+1;

        RES[5].x=x+1;
        RES[5].y=y+2;

        RES[6].x=x+2;
        RES[6].y=y-1;

        RES[7].x=x+1;
        RES[7].y=y-2;

        for(int i = 0; i < 8; i++){
            if(RES[i].x<0 || RES[i].x>7 || RES[i].y<0 || RES[i].y>7){}
            else{
                if(get_player_cell(RES[i].x, RES[i].y)!=P.get_playerID())   pos.push_back(RES[i]);
            }
        }
        break;
    case 7:
    case 8:
        res.x=x;
        res2.y=y;
        r = y;
        while(r < 8){
            if(r!=y && way){
                res.y=r;
                if(get_player_cell(res.x, res.y)!=P.get_playerID() && get_player_cell(res.x, res.y)!=0){
                    pos.push_back(res);
                    way = false;
                }
                else if(get_player_cell(res.x, res.y)!=P.get_playerID())   pos.push_back(res);
                else way = false;
            }
            r++;
        }
        way = true;
        r = y;
        while(r > -1){
            if(r!=y && way){
                res.y=r;
                if(get_player_cell(res.x, res.y)!=P.get_playerID() && get_player_cell(res.x, res.y)!=0){
                    pos.push_back(res);
                    way = false;
                }
                else if(get_player_cell(res.x, res.y)!=P.get_playerID())   pos.push_back(res);
                else way = false;
            }
            r--;
        }
        way = true;
        r = x;
        while(r < 8){
            if(r!=x && way){
                res2.x=r;
                if(get_player_cell(res2.x, res2.y)!=P.get_playerID() && get_player_cell(res2.x, res2.y)!=0){
                    pos.push_back(res2);
                    way = false;
                }
                else if(get_player_cell(res2.x, res2.y)!=P.get_playerID())   pos.push_back(res2);
                else way = false;
            }
            r++;
        }
        way = true;
        r = x;
        while(r > -1){
            if(r!=x && way){
                res2.x=r;
                if(get_player_cell(res2.x, res2.y)!=P.get_playerID() && get_player_cell(res2.x, res2.y)!=0){
                    pos.push_back(res2);
                    way = false;
                }
                else if(get_player_cell(res2.x, res2.y)!=P.get_playerID())   pos.push_back(res2);
                else way = false;
            }
            r--;
        }
        break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        res.x=x;
        if(P.get_playerID()==1){
            if(y+1<7 && !echequier::C[x][y+1].plein){
                res.y=y+1;
                pos.push_back(res);
            }
            if(y==1 && !C[x][y+2].plein){
                res.y=y+2;
                pos.push_back(res);
            }
            if(x < 7 && y < 7 && C[x+1][y+1].plein && get_player_cell(x+1, y+1)!=P.get_playerID()){
                res.x=x+1;
                res.y=y+1;
                pos.push_back(res);
            }
            if(x > 1 && y < 7 && C[x-1][y+1].plein && get_player_cell(x-1, y+1)!=P.get_playerID()){
                res.x=x-1;
                res.y=y+1;
                pos.push_back(res);
            }
        }else if(P.get_playerID()==2){
            if(y-1>0 && !echequier::C[x][y-1].plein){
                res.y=y-1;
                pos.push_back(res);
            }
            if(y==6 && !C[x][y-2].plein){
                res.y=y-2;
                pos.push_back(res);
            }
            if(x < 7 && y > 1 && C[x+1][y-1].plein && get_player_cell(x+1, y-1)!=P.get_playerID()){
                res.x=x+1;
                res.y=y-1;
                pos.push_back(res);
            }
            if(x > 1 && y > 1 && C[x-1][y-1].plein && get_player_cell(x-1, y-1)!=P.get_playerID()){
                res.x=x-1;
                res.y=y-1;
                pos.push_back(res);
            }
        }
        break;
    }
    if(pos.size()==0){
        position a;
        a.x = -1;
        a.y = -1;
        pos.push_back(a);
    }
    return pos;
}

void echequier::init_pos_pieces(joueur &player)
{
    switch (player.get_playerID()){
    case 1:
        player.set_piece_pos(0, 3, 0);
        player.set_piece_pos(1, 4, 0);
        player.set_piece_pos(2, 2, 0);
        player.set_piece_pos(3, 5, 0);
        player.set_piece_pos(4, 1, 0);
        player.set_piece_pos(5, 6, 0);
        player.set_piece_pos(6, 0, 0);
        player.set_piece_pos(7, 7, 0);
        for (int i = 0; i<8 ;i++ )
        {
            player.set_piece_pos(i+8, i, 1);
        }
        break;
    case 2:
        player.set_piece_pos(0, 3, 7);
        player.set_piece_pos(1, 4, 7);
        player.set_piece_pos(2, 2, 7);
        player.set_piece_pos(3, 5, 7);
        player.set_piece_pos(4, 1, 7);
        player.set_piece_pos(5, 6, 7);
        player.set_piece_pos(6, 0, 7);
        player.set_piece_pos(7, 7, 7);
        for (int i = 0; i<8 ;i++ )
        {
            player.set_piece_pos(i+8, i, 6);
        }
        break;
    }
}

void echequier::display(){
    position p;
    for(int i = 0; i < 16; i++){
        //QString name = QString::fromStdString(A.idToDesc(i+1));
        p = A.get_piece_pos(i);
        //ui->tableWidget->item(p.y, p.x)->setText(name);
        if(p.x!=-1 && p.y!=-1){
            ui->tableWidget->item(p.y, p.x)->setToolTip(QString::fromStdString(A.idToDesc(i+1)));
            QPixmap pix(QString::fromStdString(A.idToPath(i+1)));
            QPixmap resPix = pix.scaled(30,30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            QLabel *lblTest = new QLabel;
            lblTest->setPixmap(resPix);
            lblTest->setAlignment(Qt::AlignCenter);
            ui->tableWidget->setCellWidget(p.y, p.x, lblTest);
            //delete lblTest;
        }

        //QString name2 = QString::fromStdString(B.idToDesc(i+1));
        p = B.get_piece_pos(i);
        //ui->tableWidget->item(p.y, p.x)->setText(name2);
        if(p.x!=-1 && p.y!=-1){
            ui->tableWidget->item(p.y, p.x)->setToolTip(QString::fromStdString(B.idToDesc(i+1)));
            QPixmap pix2(QString::fromStdString(B.idToPath(i+1)));
            QPixmap resPix2 = pix2.scaled(30,30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            QLabel *lblTest2 = new QLabel;
            lblTest2->setPixmap(resPix2);
            lblTest2->setAlignment(Qt::AlignCenter);
            ui->tableWidget->setCellWidget(p.y, p.x, lblTest2);
            //delete lblTest;
        }
    }
    QLabel *emptylabel = new QLabel;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(C[j][i].plein==false) ui->tableWidget->setCellWidget(i, j, emptylabel);
        }
    }
    ui->lcdNumber->display(nbtour);
}

void echequier::init_cell_state(int x, int y, bool state){
    echequier::C[x][y].plein = state;
}

void echequier::display_possible_moves(vector <position> pos){
    for(unsigned int i = 0; i < pos.size(); i++){
        if(pos[i].x!=-1 && pos[i].y!=-1){
            QColor x;
            x=Qt::red;
            ui->tableWidget->item(pos[i].y, pos[i].x)->setBackgroundColor(Qt::red);
        }
    }
}

void echequier::move_piece(int id, joueur P){
    vector <position> pos = list_possible_moves(id, P);
    display_possible_moves(pos);
}

void echequier::movement(int state, int row, int col, int playerID, int pieceID, vector <position> &P){
    if(state==0){
        if(playerID==1) P = list_possible_moves(pieceID, A);
        else if(playerID==2) P = list_possible_moves(pieceID, B);
        else{
            position tmppos;
            tmppos.x=-1;
            tmppos.y=-1;
            P.push_back(tmppos);
        }
        display_possible_moves(P);
        display();
        S++;
    }
    else if(state==1){
        bool found = false;
        for(unsigned int i = 0; i < P.size(); i++){
            if(row==P[i].y && col==P[i].x) found = true;
        }
        if(found){
            if(playerID==1){
                position tmp;
                tmp = A.get_piece_pos(pieceID-1);
                if(get_player_cell(col, row)==2){
                    int PC = get_piece_cell(2, col, row);
                    B.set_piece_active(PC-1, false);
                    B.set_piece_pos(PC-1, -1, -1);
                }
                A.set_piece_pos(pieceID-1, col, row);
                nbtour++;
                C[tmp.x][tmp.y].plein=false;
                C[col][row].plein=true;
            }
            else if(playerID==2){
                position tmp;
                tmp = B.get_piece_pos(pieceID-1);
                if(get_player_cell(col, row)==1){
                    int PC = get_piece_cell(1, col, row);
                    A.set_piece_active(PC-1, false);
                    A.set_piece_pos(PC-1, -1, -1);
                }
                B.set_piece_pos(pieceID-1, col, row);
                nbtour++;
                C[tmp.x][tmp.y].plein=false;
                C[col][row].plein=true;
            }
        }
        display();
        P.clear();
        S--;
    }
}

void echequier::on_tableWidget_clicked(const QModelIndex &index)
{
    if(A.get_piece_active(0) && B.get_piece_active(0)){
        int y = index.row();
        int x = index.column();
        init_cell_colors();
        if(S==0){
            playerID = get_player_cell(x, y);
            pieceID = get_piece_cell(playerID, x, y);
        }
        if((nbtour%2)+1==playerID) movement(S, y, x, playerID, pieceID, P);
        //cout << "=============================" << endl;
        //cout << "Player ID : " << playerID << endl;
        //cout << "S : " << S << endl;
        //cout << boolalpha << C[x][y].plein << endl;
        display();
    }else{
        A.get_piece_active(0) ? QMessageBox::critical(this, "GAME OVER", QString::fromStdString("Le joueur A remporte la partie!")) : QMessageBox::critical(this, "GAME OVER", QString::fromStdString("Le joueur B remporte la partie!"));
    }
}
