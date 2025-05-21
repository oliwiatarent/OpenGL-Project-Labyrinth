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

void Labyrinth::generateCoordinates(int labyrinthNumber, float wallLength, float wallHeight, float wallWidth, unsigned short liczba_pochodni){
        ofstream sciany, podlogi, rampy, dachy, pochodnie;
        sciany.open("input/labyrinth_" + to_string(labyrinthNumber) + ".txt");
        podlogi.open("input/floors_" + to_string(labyrinthNumber) + ".txt");
        rampy.open("input/rampy_" + to_string(labyrinthNumber) + ".txt");
        pochodnie.open("input/pochodnie_"+to_string(labyrinthNumber)+".txt");

        float floorThickness = 2.0f;
        int stairsRoomLength = 4, stairsRoomWidth = 2;
        
        int i;
        
        // Wygenerowanie klatki schodowej dla wejścia
        // Generowanie ścian bocznych
        for (i = 0; i < stairsRoomLength; i++) {
            sciany << i * wallWidth * -1 << " " << labyrinthNumber * wallHeight << " " << 0 << " " << 
                wallLength << " " << wallHeight << " " << wallWidth << " " << 1 << endl;

            sciany << i * wallWidth * -1 << " " << labyrinthNumber * wallHeight << " " << 2 * wallWidth << " " << 
                wallLength << " " << wallHeight << " " << wallWidth << " " << 1 << endl;
        }
        // Generowanie ścian tylnich
        for (int j = 0; j < 2; j++) {
            sciany << -(stairsRoomLength * wallWidth) << " " << labyrinthNumber * wallHeight << " " << j * wallWidth << " " << 
                wallLength << " " << wallHeight << " " << wallWidth << " " << 0 << endl;
        }
        
        // Generowanie podłogi
        if (labyrinthNumber == 0)
            // Generowanie podłogi w wejściu na parterze
            podlogi << -(wallWidth * stairsRoomLength) << " " << labyrinthNumber * wallHeight - floorThickness << " " << 0 << " " 
                << stairsRoomLength * wallWidth << " " << floorThickness << " " << stairsRoomWidth * wallWidth << endl;

        if (labyrinthNumber % 2 != 0 && (labyrinthNumber + 1) != numberOfFloors) {
            // Generowanie filaru przy rampie
            podlogi << -(wallWidth * stairsRoomLength) << " " << labyrinthNumber * wallHeight  << " " << wallWidth << " " 
                << wallWidth << " " << wallHeight << " " << wallWidth << endl;

            // Generowanie podłogi piętro wyżej w klatce schodowej
            podlogi << -(wallWidth * stairsRoomLength) << " " << (labyrinthNumber + 1) * wallHeight - floorThickness << " " << 0 << " " 
                << wallWidth * stairsRoomLength << " " << floorThickness << " " << wallWidth << endl;

            podlogi << -(wallWidth) << " " << (labyrinthNumber + 1) * wallHeight - floorThickness << " " << wallWidth << " "
                << wallWidth << " " << floorThickness << " " << wallWidth << endl;

            // Generowanie podłogi w klatce schodowej jeśli generujemy rampę
            podlogi << -(wallWidth * stairsRoomLength) << " " << labyrinthNumber * wallHeight - floorThickness  << " " << 0 << " " 
                << stairsRoomLength * wallWidth << " " << floorThickness << " " << stairsRoomWidth * wallWidth << endl;

            // Generowanie rampy
            rampy << -(wallWidth * (stairsRoomWidth + 1)) << " " << labyrinthNumber * wallHeight << " " << wallWidth << " " 
                << wallWidth << " " << wallWidth * 2 << " " << wallHeight << " " << 0 << endl;
        }

        // Generowanie podłogi dla końca labiryntu
        if (labyrinthNumber % 2 != 0 && (labyrinthNumber + 1) == numberOfFloors) {
            podlogi << -(wallWidth * i) << " " << labyrinthNumber * wallHeight << " " << 0 << " " 
                << i * wallWidth << " " << floorThickness << " " << i * wallWidth << endl;
        }


        // Generowanie dachu
        if ((labyrinthNumber + 1) == numberOfFloors) {
            podlogi << -(wallWidth * stairsRoomLength) << " " << (labyrinthNumber + 1) * wallHeight - floorThickness << " " << 0 << " " 
                << stairsRoomLength * wallWidth << " " << floorThickness << " " << stairsRoomWidth * wallWidth << endl;
        }


        // Wygenerowanie klatki schodowej dla wyjścia
        // Generowanie ścian bocznych
        for (i = 0; i < stairsRoomLength; i++) {
            sciany << (szerokosc + 1 + i) * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight << " " << (wysokosc) * wallWidth << " "
                << wallLength << " " << wallHeight << " " << (wallWidth + wallLength) << " " << 1 << endl;
                
            sciany << (szerokosc + 1 + i) * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight << " " << (wysokosc - 2) * wallWidth << " "
                << wallLength << " " << wallHeight << " " << (wallWidth + wallLength) << " " << 1 << endl;
        }
        // Generowanie ścian tylnich
        for (int j = 0; j < stairsRoomWidth; j++) {
            sciany << (szerokosc + stairsRoomLength) * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight << " " << (wysokosc + j - stairsRoomWidth) * wallWidth 
                << " " << wallLength << " " << wallHeight << " " << (wallWidth + wallLength) << " " << 0 << endl;
        }

        // Generowanie podłogi
        if (labyrinthNumber % 2 == 0 && (labyrinthNumber + 1) != numberOfFloors) {
            // Generowanie filaru przy rampie
            podlogi << (szerokosc + (stairsRoomLength - 1)) * (wallWidth + wallLength) + wallLength << " " << labyrinthNumber * wallHeight << " " << ((wysokosc - stairsRoomWidth) * wallWidth) + wallLength
            << " " << wallWidth << " " << wallHeight << " " << wallWidth << endl;

            // Generowanie podłogi piętro wyżej w klatce schodowej
            podlogi << szerokosc * (wallWidth + wallLength) << " " << (labyrinthNumber + 1) * wallHeight - floorThickness << " " << ((wysokosc - 1) * wallWidth) + wallLength
                << " " << (wallWidth + wallLength) * stairsRoomLength << " " << floorThickness << " " << wallWidth << endl;  
                
            podlogi << szerokosc * (wallWidth + wallLength) << " " << (labyrinthNumber + 1) * wallHeight - floorThickness << " " << ((wysokosc - 2) * wallWidth) + wallLength
                << " " << wallWidth + wallLength << " " << floorThickness << " " << wallWidth << endl;  
                    
            // Generowanie podłogi w klatce schodowej jeśli generujemy rampę
            podlogi << szerokosc * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight - floorThickness << " " << (wysokosc - stairsRoomWidth) * wallWidth 
                << " " << stairsRoomLength * (wallWidth + wallLength) << " " << floorThickness << " " << stairsRoomWidth * wallWidth << endl;

            // Generowanie rampy
            rampy << (szerokosc + 3) * (wallLength + wallWidth) + wallLength << " " << labyrinthNumber * wallHeight << " " << (((wysokosc + 1) - stairsRoomWidth) * wallWidth) + wallLength
                << " " << wallWidth << " " << wallWidth * 2 << " " << wallHeight << " " << 1 << endl;
        }

        // Generowanie podłogi dla końca labiryntu
        if (labyrinthNumber % 2 == 0 && (labyrinthNumber + 1) == numberOfFloors) {
            podlogi << szerokosc * (wallLength + wallWidth) << " " << labyrinthNumber * wallHeight - floorThickness << " " << (wysokosc - stairsRoomWidth) * wallWidth 
                << " " << stairsRoomLength * (wallWidth + wallLength) << " " << floorThickness << " " << stairsRoomWidth * wallWidth << endl;
        }

        // Generowanie dachu
        if ((labyrinthNumber + 1) == numberOfFloors) {
            podlogi << szerokosc * (wallLength + wallWidth) << " " << (labyrinthNumber + 1) * wallHeight - floorThickness << " " << (wysokosc - stairsRoomWidth) * wallWidth 
                << " " << stairsRoomLength * (wallWidth + wallLength) << " " << floorThickness << " " << stairsRoomWidth * wallWidth << endl;
        }

        // Generowanie podłóg i dachu w labiryncie
        
        int k = 1;
        bool dec_numberOfFloors = false;
        while(true){
            for (int y = 0; y < wysokosc; y++) {
                for (int x = szerokosc - 1; x >= 0; x--) {
                    
                    // Generowanie kolumn, w celu wyeliminowania niedokładnych narożników labiryntu
                    if (x == szerokosc - 1){ // Wygeneruj kolumny w skrajnie dolnej ścianie
                        sciany << wallLength << " " << labyrinthNumber * (wallHeight+ floorThickness) - floorThickness << " " 
                            << y * (wallWidth) << " " << wallLength << " " << floorThickness << " " << wallLength << " " << 1 << endl;
                    }
                    sciany << k * (wallWidth) + wallLength << " " << labyrinthNumber * (wallHeight+ floorThickness) - floorThickness  << " " << y * (wallWidth) << " " << 
                            wallLength << " " << floorThickness << " " << wallLength << " " << 1 << endl;
                    
                    // Ściany pioniowe z punktu widzenia obserwatora

                        sciany << k * (wallWidth) << " " << labyrinthNumber * (wallHeight+ floorThickness) - floorThickness  << " " << y * wallWidth << " " << 
                            wallLength << " " << floorThickness << " " << wallWidth - wallLength << " " << 1 << endl;
                    
                    
                    // Ściany poziome

                        // Nie generuj ściany: wyjście z labiryntu 
                        sciany << k * (wallWidth) << " " << labyrinthNumber * (wallHeight+ floorThickness) - floorThickness  << " " << y * wallWidth + wallLength << " " << 
                            wallLength << " " << floorThickness << " " << wallWidth - wallLength << " " << 0 << endl;
                    
                    
                    // Skrajnie prawa ściana labirytnu
                    if (y == wysokosc - 1 && sciana[x][y][2]) {
                        sciany << k * (wallWidth) << " " << labyrinthNumber * (wallHeight+ floorThickness) - floorThickness  << " " << (y + 1) * wallWidth << " "
                            << wallLength << " " << floorThickness << " " << (wallWidth - wallLength) << " " << 1 << endl;
                        //KOLUMNY w celu poprawnego cieniowania
                        sciany << k * (wallWidth) + wallLength << " " << labyrinthNumber * (wallHeight+ floorThickness) - floorThickness << " " << (y + 1) * wallWidth << " "
                            << wallLength << " " << floorThickness << " " << (wallLength) << " " << 1 << endl; 
                    }
                    
                    // Skrajnie dolna
                    if (x == szerokosc - 1 && sciana[x][y][1]) {
                        sciany << (k * (wallLength + wallWidth)) - wallLength - wallWidth<< " "  << labyrinthNumber * (wallHeight+ floorThickness) - floorThickness  << " "  << y * wallWidth + wallLength
                            << " " << wallLength << " " << floorThickness << " " << wallWidth - wallLength << " " << 0 << endl;
                    }
                    // podłoga między ścianami
                    sciany << k * (wallWidth) << " " << labyrinthNumber * (wallHeight+ floorThickness) - floorThickness  << " " << y * (wallWidth) + wallLength << " " << 
                            wallWidth - wallLength << " " << floorThickness << " " << wallWidth - wallLength << " " << 1 << endl;
                    k++;
                }
                k = 1;
            }

            if((labyrinthNumber + 1) == numberOfFloors){
                labyrinthNumber++;
                dec_numberOfFloors = true;
            }
            else break;
        }
        if(dec_numberOfFloors) labyrinthNumber--;
        
        // Generowanie ścian labiryntu
        k = 1;
        for (int y = 0; y < wysokosc; y++) {
            for (int x = szerokosc - 1; x >= 0; x--) {
                
                // Generowanie kolumn, w celu wyeliminowania niedokładnych narożników labiryntu
                if (x == szerokosc - 1){ // Wygeneruj kolumny w skrajnie dolnej ścianie
                    sciany << wallLength << " " << labyrinthNumber * wallHeight +floorThickness*labyrinthNumber << " " << y * (wallWidth) << " " << wallLength << " " << wallHeight << " " << wallLength << " " << 1 << endl;
                }
                sciany << k * (wallWidth) + wallLength << " " << labyrinthNumber * wallHeight+floorThickness*labyrinthNumber  << " " << y * (wallWidth) << " " << 
                        wallLength << " " << wallHeight << " " << wallLength << " " << 1 << endl;
                
                // Ściany pioniowe z punktu widzenia obserwatora
                if (sciana[x][y][0]) {
                    sciany << k * (wallWidth) << " " << labyrinthNumber * wallHeight+floorThickness*labyrinthNumber  << " " << y * wallWidth << " " << 
                        wallLength << " " << wallHeight << " " << wallWidth - wallLength << " " << 1 << endl;
                }
                
                // Ściany poziome
                if (sciana[x][y][3]) {
                    if (x != 0 || (x == 0 && y != wysokosc - 1)) // Nie generuj ściany: wyjście z labiryntu 
                        sciany << k * (wallWidth) << " " << labyrinthNumber * wallHeight+floorThickness*labyrinthNumber  << " " << y * wallWidth + wallLength << " " << 
                        wallLength << " " << wallHeight << " " << wallWidth - wallLength << " " << 0 << endl;
                }
                
                // Skrajnie prawa ściana labirytnu
                if (y == wysokosc - 1 && sciana[x][y][2]) {
                    sciany << k * (wallWidth) << " " << labyrinthNumber * wallHeight+floorThickness*labyrinthNumber  << " " << (y + 1) * wallWidth << " "
                        << wallLength << " " << wallHeight << " " << (wallWidth - wallLength) << " " << 1 << endl;
                    //KOLUMNY w celu poprawnego cieniowania
                    sciany << k * (wallWidth) + wallLength << " " << labyrinthNumber * wallHeight +floorThickness*labyrinthNumber << " " << (y + 1) * wallWidth << " "
                        << wallLength << " " << wallHeight << " " << (wallLength) << " " << 1 << endl; 
                }
                
                // Skrajnie dolna
                if (x == szerokosc - 1 && sciana[x][y][1]) {
                    if (y != 0) // Nie generuj ściany: wejście do labiryntu 
                        sciany << (k * (wallLength + wallWidth)) - wallLength - wallWidth<< " "  << labyrinthNumber * wallHeight+floorThickness*labyrinthNumber  << " "  << y * wallWidth + wallLength
                            << " " << wallLength << " " << wallHeight << " " << wallWidth - wallLength << " " << 0 << endl;
                }
                k++;
            }

            k = 1;
        }

        float torch_radius = 1.0;
        unsigned int liczba_prob = 100000;
        for(unsigned short nr_pochodni=0, proba=0;nr_pochodni<liczba_pochodni/2;){
            unsigned short x = rand() % (szerokosc-1), y = rand() % (wysokosc-1);

            if(sciana[x][y][1] && !sciana[x][y][2] && !sciana[x+1][y+1][0] && sciana[x+1][y+1][3]){
                nr_pochodni++;
                pochodnie<< (szerokosc-x-1)*(wallWidth)+wallLength/2 - torch_radius <<" "<< (labyrinthNumber+1) * wallHeight - wallHeight/3 <<" "<< (y+1)*(wallWidth)+wallLength/2 << endl;
                pochodnie<< (szerokosc-x-1)*(wallWidth)+wallLength/2 + torch_radius <<" "<< (labyrinthNumber+1) * wallHeight - wallHeight/3 <<" "<< (y+1)*(wallWidth)+wallLength/2 << endl;
                printf("f1 %hd %hd\n", x, y);
            }
            else if(!sciana[x][y][1] && sciana[x][y][2] && sciana[x+1][y+1][0] && !sciana[x+1][y+1][3]){
                nr_pochodni++;
                pochodnie<< (szerokosc-x-1)*(wallWidth) +wallLength/2<<" "<< (labyrinthNumber+1) * wallHeight+ - wallHeight/3 <<" "<< (y+1)*(wallWidth)+wallLength/2 - torch_radius << endl;
                pochodnie<< (szerokosc-x-1)*(wallWidth) +wallLength/2 <<" "<< (labyrinthNumber+1) * wallHeight+ - wallHeight/3 <<" "<< (y+1)*(wallWidth)+wallLength/2 + torch_radius << endl;
                printf("f2 %hd %hd\n", x, y);
            }
        }
        
        sciany.close();
        podlogi.close();
        rampy.close();
        pochodnie.close();
}


