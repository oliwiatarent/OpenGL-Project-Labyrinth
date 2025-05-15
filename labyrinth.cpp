#include "labyrinth.h"

Punkt::Punkt(int x, int y): x(x), y(y), k(0) {}
Punkt::Punkt(int x, int y, int k): x(x), y(y), k(k) {}

void Punkt::move() {
    switch (k) {
        case 0: y--; break;
        case 1: x++; break;
        case 2: y++; break;
        case 3: x--; break;
    }
}

Labyrinth::Labyrinth(int wysokosc, int szerokosc) {
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

        while (search())
            updateWalls(aktualnie[rand() % aktualnie.size()]);
    }

Labyrinth::~Labyrinth() {
    for (int x = 0; x < szerokosc; x++) {
        for (int y = 0; y < wysokosc; y++)
            delete[] sciana[x][y];
        delete[] sciana[x];
        delete[] odwiedzony[x];
    }
    delete[] sciana;
    delete[] odwiedzony;
}

bool Labyrinth::inRange(int x, int y) {
    return x >= 0 && x < szerokosc && y >= 0 && y < wysokosc;
}

bool Labyrinth::search(int max) {
    if (max >= 4)
        return false;

    int xp = rand() % szerokosc;
    int yp = rand() % wysokosc;
    int x = xp, y = yp;

    do {
        if (!odwiedzony[x][y]) {
            if (x > 0 && odwiedzony[x - 1][y])
                addWall(Punkt(x - 1, y, 1), max);
            if (y > 0 && odwiedzony[x][y - 1])
                addWall(Punkt(x, y - 1, 2), max);
            if (x < szerokosc - 1 && odwiedzony[x + 1][y])
                addWall(Punkt(x + 1, y, 3), max);
            if (y < wysokosc - 1 && odwiedzony[x][y + 1])
                addWall(Punkt(x, y + 1, 0), max);

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

    return search(max + 1);
}

void Labyrinth::addWall(Punkt p, int max) {
    int ile = 0;
    for (int i = 0; i < 4; i++) {
        if (!sciana[p.x][p.y][i])
            ile++;
    }
    if (ile < max)
        addWall(p);
}

void Labyrinth::addWall(Punkt p) {
    if (p.x > 0 && !odwiedzony[p.x - 1][p.y])
        aktualnie.push_back(Punkt(p.x, p.y, 3));
    if (p.x + 1 < szerokosc && !odwiedzony[p.x + 1][p.y])
        aktualnie.push_back(Punkt(p.x, p.y, 1));
    if (p.y > 0 && !odwiedzony[p.x][p.y - 1])
        aktualnie.push_back(Punkt(p.x, p.y, 0));
    if (p.y + 1 < wysokosc && !odwiedzony[p.x][p.y + 1])
        aktualnie.push_back(Punkt(p.x, p.y, 2));
}

void Labyrinth::updateWalls(Punkt p) {
    aktualnie.clear();

    int x1 = p.x;
    int y1 = p.y;
    int k = p.k;

    p.move();

    if (!inRange(p.x, p.y)) return;

    sciana[x1][y1][k] = false;
    sciana[p.x][p.y][(k + 2) % 4] = false;
    odwiedzony[p.x][p.y] = true;
    addWall(p);
}

void Labyrinth::print() {
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

void Labyrinth::generateCoordinates(int labyrinthNumber, float wallLength, float wallHeight, float wallWidth) {
        ofstream data;
        data.open("input/labyrinth_" + to_string(labyrinthNumber) + ".txt");

        float wallGap = wallWidth;  // Odstęp między ścianami
        
        int i;
        // Wygenerowanie klatki schodowej dla wejścia
        for (i = 0; i < 2; i++) {
            data << i * wallWidth * -1 << " " << labyrinthNumber * wallHeight << " " << 0 << " " << 
                wallLength << " " << wallHeight << " " << wallWidth << " " << 1 << endl;

            data << i * wallWidth * -1 << " " << labyrinthNumber * wallHeight << " " << 2 * wallWidth << " " << 
                wallLength << " " << wallHeight << " " << wallWidth << " " << 1 << endl;
        }
        for (int j = 0; j < 2; j++) {
            data << 0 - i * wallWidth << " " << labyrinthNumber * wallHeight << " " << j * wallWidth << " " << 
                wallLength << " " << wallHeight << " " << wallWidth << " " << 0 << endl;
        }

        // Wygenerowanie klatki schodowej dla wyjścia
        for (i = 0; i < 2; i++) {
            if (i == 0)
                data << (i * wallWidth) + ((wysokosc + 1) * (wallWidth + wallLength)) << " " << labyrinthNumber * wallHeight << " " 
                    << szerokosc * wallWidth << " " << wallLength << " " << wallHeight << " " << wallWidth + 1 << " " << 1 << endl;
            else 
                data << ((i * wallWidth) + ((wysokosc + 1) * (wallWidth + wallLength))) + wallLength << " " << labyrinthNumber * wallHeight << " " 
                    << szerokosc * wallWidth << " " << wallLength << " " << wallHeight << " " << wallWidth + 1 << " " << 1 << endl;

            data << (i * wallWidth) + ((wysokosc + 1) * (wallWidth + wallLength)) << " " << labyrinthNumber * wallHeight << " " 
                << (szerokosc - 2) * wallWidth << " " << wallLength << " " << wallHeight << " " << wallWidth << " " << 1 << endl;
        }
        for (int j = 0; j < 2; j++) {
            data << ((i - 1) * wallWidth) + ((wysokosc + 1) * (wallWidth + wallLength)) << " " << labyrinthNumber * wallHeight << " " 
                << (szerokosc - (j + 1)) * wallWidth << " " << wallLength << " " << wallHeight << " " << wallWidth << " " << 0 << endl;
        }

        int k = 1;

        for (int y = 0; y < wysokosc; y++) {
            for (int x = szerokosc - 1; x >= 0; x--) {

                // Ściany pioniowe z punktu widzenia obserwatora
                if (sciana[x][y][0]) {
                    data << k * (wallLength + wallGap) << " " << labyrinthNumber * wallHeight << " " << y * wallWidth << " " << 
                        wallLength << " " << wallHeight << " " << (wallWidth + wallLength) << " " << 1 << endl;
                }

                // Ściany poziome
                if (sciana[x][y][3]) {
                    if (x != 0 || (x == 0 && y != wysokosc - 1)) // Nie generuj ściany: wyjście z labiryntu 
                        data << k * (wallLength + wallGap) << " " << labyrinthNumber * wallHeight << " " << y * wallWidth << " " << 
                        wallLength << " " << wallHeight << " " << wallWidth << " " << 0 << endl;
                }

                // Skrajnie prawa ściana labirytnu
                if (y == wysokosc - 1 && sciana[x][y][2]) {
                    data << k * (wallLength + wallGap) << " " << labyrinthNumber * wallHeight << " " << (y + 1) * wallWidth << " "
                        << wallLength << " " << wallHeight << " " << (wallWidth + wallLength) << " " << 1 << endl;
                }

                // Skrajnie dolna
                if (x == szerokosc - 1 && sciana[x][y][1]) {
                    if (y != 0) // Nie generuj ściany: wejście do labiryntu 
                        data << (k * (wallLength + wallGap)) - wallLength - wallGap << " "  << labyrinthNumber * wallHeight << " " 
                        << y * wallWidth << " " << wallLength << " " << wallHeight << " " << wallWidth << " " << 0 << endl;
                }

                k++;
            }

            k = 1;
        }

        data.close();
}


