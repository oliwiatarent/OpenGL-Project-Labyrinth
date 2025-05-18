#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

extern int numberOfFloors;

struct Punkt {
public:
    int x, y, k;

    Punkt(int x, int y);
    Punkt(int x, int y, int k);

    void move();
};

class Labyrinth {
private:
    int wysokosc, szerokosc;
    bool ***sciana;
    bool **odwiedzony;
    vector<Punkt> aktualnie;


public:
    Labyrinth(int wysokosc, int szerokosc);
    ~Labyrinth();

    bool inRange(int x, int y);
    bool search(int max = 2);
    void addWall(Punkt p, int max);
    void addWall(Punkt p);
    void updateWalls(Punkt p);
    void print();
    void generateCoordinates(int numberOfLabyrinths, float wallLength, float wallheight, float wallWidth);
};