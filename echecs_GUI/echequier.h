#ifndef ECHEQUIER_H
#define ECHEQUIER_H

#include <QMainWindow>
#include "joueur.h"
#include <vector>

namespace Ui {
class echequier;
}

class echequier : public QMainWindow
{
    Q_OBJECT

public:
    explicit echequier(QWidget *parent = 0);
    ~echequier();
    void init_cell_colors();
    struct cell{
        int x, y;
        bool plein;
    };
    joueur A, B;
    void init_pos_pieces(joueur &player);
    void init_cell_state(int x, int y, bool state);
    void move_piece(int id, joueur P);
    int get_player_cell(int x, int y);
    int get_piece_cell(int playerID, int x, int y);
    vector <position> list_possible_moves(int id, joueur P);
    void display();
    void display_possible_moves(vector <position> pos);
    void movement(int state, int row, int col, int playerID, int pieceID, vector <position> &P);
    cell C[8][8];
    int S;
    vector <position> P;
private slots:
    void on_tableWidget_clicked(const QModelIndex &index);

private:
    Ui::echequier *ui;
};

#endif // ECHEQUIER_H
