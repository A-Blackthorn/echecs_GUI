#ifndef JOUEUR_H
#define JOUEUR_H
#include <iostream>
#include <string>

using namespace std;

struct position{
    int x, y;
};

struct piece{
    int id;
    string desc;
    position pos;
    bool active;
};

class joueur
{
    public:
        joueur();
        virtual ~joueur();
        void init_pieces();
        string idToDesc(int id);
        string idToPath(int id);
        void set_piece_id(int index, int x);
        void set_piece_desc(int index, string x);
        void set_piece_pos(int index, int x, int y);
        void set_piece_active(int index, bool x);
        int get_piece_id(int index);
        string get_piece_desc(int index);
        position get_piece_pos(int index);
        bool get_piece_active(int index);
        void set_playerID(int x);
        int get_playerID();
    private:
        piece P[16];
        int playerID;
};

#endif // JOUEUR_H
