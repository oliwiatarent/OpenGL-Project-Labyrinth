#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Punkt {
public:
    int x, y, k;

    Punkt(int x, int y): x(x), y(y), k(0) {}
    Punkt(int x, int y, int k): x(x), y(y), k(k) {}

    void przesun() {
        switch (k) {
            case 0: y--; break;
            case 1: x++; break;
            case 2: y++; break;
            case 3: x--; break;
        }
    }
};

class Labirynt {
public:
    int wysokosc, szerokosc;
    bool ***sciana;
    bool **odwiedzony;
    vector<Punkt> aktualnie;

    Labirynt(int wysokosc, int szerokosc) {
        this->wysokosc = wysokosc;
        this->szerokosc = szerokosc;

        sciana = new bool**[szerokosc];
        for (int x = 0; x < szerokosc; x++) {
            sciana[x] = new bool*[wysokosc];
            for (int y = 0; y < wysokosc; y++) {
                sciana[x][y] = new bool[4];
                for (int k = 0; k < 4; k++)
                    sciana[x][y][k] = true;
            }
        }

        odwiedzony = new bool*[szerokosc];
        for (int x = 0; x < szerokosc; x++) {
            odwiedzony[x] = new bool[wysokosc];
            for (int y = 0; y < wysokosc; y++)
                odwiedzony[x][y] = false;
        }

        odwiedzony[0][0] = true;

        while (szukaj())
            aktualizujSciany(aktualnie[rand() % aktualnie.size()]);
    }

    ~Labirynt() {
        for (int x = 0; x < szerokosc; x++) {
            for (int y = 0; y < wysokosc; y++)
                delete[] sciana[x][y];
            delete[] sciana[x];
            delete[] odwiedzony[x];
        }
        delete[] sciana;
        delete[] odwiedzony;
    }

    bool wZakresie(int x, int y) {
        return x >= 0 && x < szerokosc && y >= 0 && y < wysokosc;
    }

    bool szukaj(int max = 2) {
        if (max >= 4)
            return false;

        int xp = rand() % szerokosc;
        int yp = rand() % wysokosc;
        int x = xp, y = yp;

        do {
            if (!odwiedzony[x][y]) {
                if (x > 0 && odwiedzony[x - 1][y])
                    dodajSciane(Punkt(x - 1, y, 1), max);
                if (y > 0 && odwiedzony[x][y - 1])
                    dodajSciane(Punkt(x, y - 1, 2), max);
                if (x < szerokosc - 1 && odwiedzony[x + 1][y])
                    dodajSciane(Punkt(x + 1, y, 3), max);
                if (y < wysokosc - 1 && odwiedzony[x][y + 1])
                    dodajSciane(Punkt(x, y + 1, 0), max);

                if (!aktualnie.empty())
                    return true;
            }

            x++;
            if (x == szerokosc) {
                x = 0;
                y++;
                if (y == wysokosc)
                    y = 0;
            }

        } while (x != xp || y != yp);

        return szukaj(max + 1);
    }

    void dodajSciane(Punkt p, int max) {
        int ile = 0;
        for (int i = 0; i < 4; i++) {
            if (!sciana[p.x][p.y][i])
                ile++;
        }
        if (ile < max)
            dodajSciane(p);
    }

    void dodajSciane(Punkt p) {
        if (p.x > 0 && !odwiedzony[p.x - 1][p.y])
            aktualnie.push_back(Punkt(p.x, p.y, 3));
        if (p.x + 1 < szerokosc && !odwiedzony[p.x + 1][p.y])
            aktualnie.push_back(Punkt(p.x, p.y, 1));
        if (p.y > 0 && !odwiedzony[p.x][p.y - 1])
            aktualnie.push_back(Punkt(p.x, p.y, 0));
        if (p.y + 1 < wysokosc && !odwiedzony[p.x][p.y + 1])
            aktualnie.push_back(Punkt(p.x, p.y, 2));
    }

    void aktualizujSciany(Punkt p) {
        aktualnie.clear();

        int x1 = p.x;
        int y1 = p.y;
        int k = p.k;

        p.przesun();

        if (!wZakresie(p.x, p.y)) return;

        sciana[x1][y1][k] = false;
        sciana[p.x][p.y][(k + 2) % 4] = false;
        odwiedzony[p.x][p.y] = true;
        dodajSciane(p);
    }

    void wypisz() {
        for (int y = 0; y < wysokosc; y++) {
            for (int x = 0; x < szerokosc; x++) {
                cout << "+";
                cout << (sciana[x][y][0] ? "---" : "   ");
            }
            cout << "+" << endl;

            for (int x = 0; x < szerokosc; x++) {
                cout << (sciana[x][y][3] ? "|" : " ");
                cout << "   ";
            }
            cout << "|" << endl;
        }

        for (int x = 0; x < szerokosc; x++)
            cout << "+---";
        cout << "+" << endl;
    }
};

int main() {
    srand(time(NULL));

    Labirynt labirynt(10, 30);
    labirynt.wypisz();

    return 0;
}
