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
        ofstream sciany, podlogi, rampy, dachy;
        sciany.open("input/labyrinth_" + to_string(labyrinthNumber) + ".txt");
        podlogi.open("input/floors_" + to_string(labyrinthNumber) + ".txt");
        rampy.open("input/rampy_" + to_string(labyrinthNumber) + ".txt");

        
        int i;
        // Wygenerowanie klatki schodowej dla wejścia
        // Generowanie ścian bocznych
        for (i = 0; i < 2; i++) {
            sciany << i * wallWidth * -1 << " " << labyrinthNumber * wallHeight << " " << 0 << " " << 
                wallLength << " " << wallHeight << " " << wallWidth << " " << 1 << endl;

            sciany << i * wallWidth * -1 << " " << labyrinthNumber * wallHeight << " " << 2 * wallWidth << " " << 
                wallLength << " " << wallHeight << " " << wallWidth << " " << 1 << endl;
        }
        // Generowanie ścian tylnich
        for (int j = 0; j < 2; j++) {
            sciany << 0 - i * wallWidth << " " << labyrinthNumber * wallHeight << " " << j * wallWidth << " " << 
                wallLength << " " << wallHeight << " " << wallWidth << " " << 0 << endl;
        }

        // Generowanie podłogi
        if (labyrinthNumber == 0)
            // Generowanie podłogi w wejściu na parterze
            podlogi << -(wallWidth * i) << " " << labyrinthNumber * wallHeight << " " << 0 << " " 
                << i * wallWidth << " " << 0.1 << " " << i * wallWidth << endl;

        if (labyrinthNumber % 2 != 0 && (labyrinthNumber + 1) != numberOfFloors) {
            // Generowanie filaru przy rampie
            podlogi << -(wallWidth * i) << " " << labyrinthNumber * wallHeight + 0.1 << " " << 0 << " " 
                << wallWidth << " " << wallHeight << " " << (wallWidth / 2) + wallLength << endl;

            // Generowanie podłogi piętro wyżej w klatce schodowej
            podlogi << -(wallWidth * (i - 1)) << " " << (labyrinthNumber + 1) * wallHeight << " " << 0 << " " 
                << wallWidth << " " << 0.1 << " " << i * wallWidth + wallLength << endl;

            // Generowanie podłogi w klatce schodowej jeśli generujemy rampę
            podlogi << -(wallWidth * i) << " " << labyrinthNumber * wallHeight << " " << 0 << " " 
                << i * wallWidth << " " << 0.1 << " " << i * wallWidth << endl;

            // Generowanie rampy
            rampy << -(wallWidth * (i - 1)) << " " << labyrinthNumber * wallHeight + 0.1 << " " << (wallWidth / 2) + wallLength << " " 
                << wallWidth << " " << wallWidth << " " << wallHeight << endl;
        }

        // Generowanie podłogi dla końca labiryntu
        if (labyrinthNumber % 2 != 0 && (labyrinthNumber + 1) == numberOfFloors) {
            podlogi << -(wallWidth * i) << " " << labyrinthNumber * wallHeight << " " << 0 << " " 
                << i * wallWidth << " " << 0.1 << " " << i * wallWidth << endl;
        }


        // Generowanie dachu
        if ((labyrinthNumber + 1) == numberOfFloors) {
            podlogi << -(wallWidth * i) << " " << (labyrinthNumber + 1) * wallHeight << " " << 0 << " " 
                << i * wallWidth << " " << 0.1 << " " << i * wallWidth << endl;
        }


        // Wygenerowanie klatki schodowej dla wyjścia
        // Generowanie ścian bocznych
        for (i = 0; i < 2; i++) {
            sciany << (szerokosc + 1 + i) * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight << " " << (wysokosc) * wallWidth << " "
                << wallLength << " " << wallHeight << " " << (wallWidth + wallLength) << " " << 1 << endl;
                
            sciany << (szerokosc + 1 + i) * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight << " " << (wysokosc - 2) * wallWidth << " "
                << wallLength << " " << wallHeight << " " << (wallWidth + wallLength) << " " << 1 << endl;
        }
        // Generowanie ścian tylnich
        for (int j = 0; j < 2; j++) {
            sciany << (szerokosc + i) * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight << " " << (wysokosc + j - i) * wallWidth 
                << " " << wallLength << " " << wallHeight << " " << (wallWidth + wallLength) << " " << 0 << endl;
        }

        // Generowanie podłogi
        if (labyrinthNumber % 2 == 0 && (labyrinthNumber + 1) != numberOfFloors) {
            // Generowanie filaru przy rampie
            podlogi << (szerokosc + (i - 1)) * (wallWidth + wallLength) + wallLength << " " << labyrinthNumber * wallHeight + 0.1 << " " << ((wysokosc - i) * wallWidth)
            << " " << wallWidth << " " << wallHeight << " " << (wallWidth / 2) + wallLength << endl;

            // Generowanie podłogi piętro wyżej w klatce schodowej
            podlogi << szerokosc * (wallWidth + wallLength) << " " << (labyrinthNumber + 1) * wallHeight << " " << ((wysokosc - i) * wallWidth)
                << " " << wallWidth + wallLength * 2 << " " << 0.1 << " " << i * wallWidth + wallLength << endl;
            
            // Generowanie podłogi w klatce schodowej jeśli generujemy rampę
            podlogi << szerokosc * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight << " " << (wysokosc - i) * wallWidth 
                << " " << i * wallWidth + wallLength * i << " " << 0.1 << " " << i * wallWidth << endl;

            // Generowanie rampy
            rampy << (szerokosc + i) * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight + 0.1 << " " << ((wysokosc - i) * wallWidth) + (wallWidth / 2) + wallLength
                << " " << wallWidth << " " << wallWidth << " " << wallHeight << endl;
        }

        // Generowanie podłogi dla końca labiryntu
        if (labyrinthNumber % 2 == 0 && (labyrinthNumber + 1) == numberOfFloors) {
            podlogi << szerokosc * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight << " " << (wysokosc - i) * wallWidth 
                << " " << i * wallWidth + wallLength * i << " " << 0.1 << " " << i * wallWidth << endl;
        }

        // Generowanie dachu
        if ((labyrinthNumber + 1) == numberOfFloors) {
            podlogi << szerokosc * (wallLength + wallWidth) << " " << (labyrinthNumber + 1) * wallHeight << " " << (wysokosc - i) * wallWidth 
                << " " << i * wallWidth + wallLength * i << " " << 0.1 << " " << i * wallWidth << endl;
        }



        // Generowanie podłóg w labiryncie
        podlogi << 0 << " " << labyrinthNumber * wallHeight << " " << 0 << " " 
            << szerokosc * (wallWidth + wallLength) << " " << 0.1 << " " << wysokosc * wallWidth << endl;

        
        // Generowanie dachu w labiryncie
        if ((labyrinthNumber + 1) == numberOfFloors) {
            podlogi << 0 << " " << (labyrinthNumber + 1) * wallHeight << " " << 0 << " " 
                << szerokosc * (wallWidth + wallLength) << " " << 0.1 << " " << wysokosc * wallWidth << endl;
        }



        // Generowanie ścian labiryntu
        int k = 1;

        for (int y = 0; y < wysokosc; y++) {
            for (int x = szerokosc - 1; x >= 0; x--) {
                
                // Generowanie kolumn, w celu wyeliminowania niedokładnych narożników labiryntu
                if (x == szerokosc - 1) // Wygeneruj kolumny w skrajnie dolnej ścianie
                    sciany << wallLength << " " << labyrinthNumber * wallHeight << " " << y * (wallWidth) << " " << 
                        wallLength << " " << wallHeight << " " << wallLength << " " << 1 << endl;
                sciany << k * (wallLength + wallWidth) + wallLength << " " << labyrinthNumber * wallHeight << " " << y * (wallWidth) << " " << 
                        wallLength << " " << wallHeight << " " << wallLength << " " << 1 << endl;

                // Ściany pioniowe z punktu widzenia obserwatora
                if (sciana[x][y][0]) {
                    sciany << k * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight << " " << y * wallWidth << " " << 
                        wallLength << " " << wallHeight << " " << wallWidth << " " << 1 << endl;
                }

                // Ściany poziome
                if (sciana[x][y][3]) {
                    if (x != 0 || (x == 0 && y != wysokosc - 1)) // Nie generuj ściany: wyjście z labiryntu 
                        sciany << k * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight << " " << y * wallWidth << " " << 
                        wallLength << " " << wallHeight << " " << wallWidth << " " << 0 << endl;
                }

                // Skrajnie prawa ściana labirytnu
                if (y == wysokosc - 1 && sciana[x][y][2]) {
                    sciany << k * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight << " " << (y + 1) * wallWidth << " "
                        << wallLength << " " << wallHeight << " " << (wallWidth + wallLength) << " " << 1 << endl;
                }

                // Skrajnie dolna
                if (x == szerokosc - 1 && sciana[x][y][1]) {
                    if (y != 0) // Nie generuj ściany: wejście do labiryntu 
                        sciany << (k * (wallLength + wallWidth)) - wallLength - wallWidth << " "  << labyrinthNumber * wallHeight << " " 
                            << y * wallWidth << " " << wallLength << " " << wallHeight << " " << wallWidth << " " << 0 << endl;
                }

                k++;
            }

            k = 1;
        }

        sciany.close();
        podlogi.close();
        rampy.close();
}


