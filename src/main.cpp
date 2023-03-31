#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <thread>
#include <chrono>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;
using namespace sf;

random_device r;
uniform_int_distribution<int> width(0,39);
uniform_int_distribution<int> height(0,19);
mt19937 gen(time(0));

struct pos {
    int x;
    int y;
};

struct square {
    int type;
    int px;
    int py;
};

bool operator == (const square &p1, const square &p2) {
    if((p1.px == p2.px) && (p1.py==p2.py) && (p1.type == p2.type)){
        return true;
    } else {
        return false;
    }
}

//0 - X  |  1 - O  |  2 - Δ  |  3 - []  |

pos startpos = {0,0};
pos endpos = {1,17};

pos gridSize = {40,18};
int size = 50;


int arr[18][40] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

float weights[18][40];
int winWidth = 2000; int winHeight = 900;
RenderWindow window(VideoMode(winWidth,winHeight),"Path finder");

void findPoints() {
    for (int y=0; y<gridSize.y; y++) {
        for (int x=0; x<gridSize.x; x++) {
            if (arr[y][x] == 2) {
                endpos = {x,y};
            } else if (arr[y][x] == 3) {
                startpos = {x,y};
            }
        }
    }
}

void initWeights(){
    for (int r=0; r<gridSize.y; r++){
        for (int x=0; x<gridSize.x; x++){
            //Nearest = bigger
            weights[r][x] = abs(r-endpos.y)+abs(x-endpos.x);
            weights[r][x] = static_cast<float>(round(1/(weights[r][x]+0.01)*100));
        }
    }
}

void displayWeights() {
    cout << "WEIGHTS:\n";
    for (int y=0; y<18; y++) {
        for (int x=0; x<40; x++){
            cout << weights[y][x] << "|";
        }
        cout << "\n";
    }
    cout << "--------------------------------------------------------------------\n";
}


vector<square> findAdjacent(square spos) {
    vector<square> r;
    square potential;
    if ((spos.px >= endpos.x-1 && spos.px <= endpos.x + 1) && (spos.py >= endpos.y-1 && spos.py <= endpos.y-1)) {
        r.push_back(square({2, endpos.x, endpos.y}));
        return r;
    }

    if (arr[spos.py][spos.px+1] != 1 && spos.px+1 < gridSize.x) {
        potential = {0,spos.px+1,spos.py};
        r.push_back(potential);
    } if (arr[spos.py][spos.px-1] != 1 && spos.px-1 >= 0) {
        potential = {0,spos.px-1,spos.py};
        r.push_back(potential);
    } if (arr[spos.py+1][spos.px] != 1 && spos.py+1 < gridSize.y) {
        potential = {0,spos.px,spos.py+1};
        r.push_back(potential);
    } if (arr[spos.py-1][spos.px] != 1 && spos.py -1 >= 0) {
        potential = {0,spos.px,spos.py-1};
        r.push_back(potential);
    }

    return r;
}

int sumWeights(vector<square> sqs) {
    int final = 0;
    for (auto s: sqs){
        final += weights[s.py][s.px] ;
    }

    return final;
}

class Player {
    public:
        square sq;
        square prev;
        vector<square> path;
        RectangleShape mesh;
        int genr = 0;

        Player() {
            mesh.setSize(Vector2f(size,size));
            mesh.setFillColor(Color::Red);
            prev = {0,0,0};
            sq = {-1, startpos.x,startpos.y};
        }

    int update() {
        vector<square> adj = findAdjacent(sq);
        if (adj.at(0).type == 2){
            return 1;
        } 

        int change = sumWeights(adj);
        vector<square> options;
        int bias = 0;

        for (auto s: adj) {
            bias = 0;
            if (find(path.begin(),path.end(), s) != path.end()) {
                bias = weights[s.py][s.px]-1;
            }
            for (int x=0; x<weights[s.py][s.px]-bias; x++) {
                options.push_back(s);
            }
        }

        uniform_int_distribution<int> n(0,options.size()-1);
        square s = options.at(n(gen));

        path.push_back(s);
        sq.px = s.px;
        sq.py = s.py;
        mesh.setPosition(sq.px*size, sq.py*size);
        window.draw(mesh);

        genr++;
        return 0;
    }
};


void renderGrid(){
    int target;
    pos p;
    int size = winWidth/gridSize.x;

    for (int x=0; x<gridSize.x; x++){
        for (int y=0; y<gridSize.y; y++) {
            target = arr[y][x];
            p = {x*size,y*size};
            
            RectangleShape m = RectangleShape(Vector2f(size,size));
            m.setPosition(p.x,p.y);
            switch (target) {
                case 0: 
                    if (weights[y][x]>=200 && weights[y][x]<=500){
                        m.setFillColor(Color::Blue);
                    } else if (weights[y][x] > 500 && weights[y][x] <= 15000) {
                        m.setFillColor(Color::Cyan);
                    } else if (weights[y][x] > 15000) {
                        m.setFillColor(Color::Magenta);
                    } else {
                        m.setFillColor(Color(weights[y][x]*10,200,0));
                    }
                    break;
                 case 1: 
                    m.setFillColor(Color::Black);break;
                 case 2: 
                    m.setFillColor(Color(225,0,200));break;
                 case 3: 
                    m.setFillColor(Color(225,0,200));break;   
            }

            window.draw(m);
        }
    }
}




void build() {
    window.setFramerateLimit(30);
    Event e;

    while (window.isOpen()) {
        window.clear(Color::Green);
        while (window.pollEvent(e)){
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        window.display();
    }
}

void populate(vector<Player>& players, int num) {
    for (int x=0; x<num; x++) {
        players.push_back(Player());
    }
}


int main(){
    findPoints();

    window.setFramerateLimit(60);
    initWeights();
    int maxIteration = 500;
    int minIteration = 300;
    int numPlayers = 500;

    vector<Player> players;
    populate(players, numPlayers);

    while (window.isOpen()){
        window.clear(Color(100,12,252));
        renderGrid();

        for (auto p = players.begin(); p!= players.end(); ++p){

            if (p->update() == 1) {
                for (square sq: p->path){
                    weights[sq.py][sq.px] += 20;
                }
            
                players.clear();
                if (maxIteration > minIteration){
                    maxIteration--;
                }
                populate(players, numPlayers);
                break;
            }
        }
        //this_thread::sleep_for(chrono::milliseconds(100));

        Event e;
        while (window.pollEvent(e)){
            if (e.type == Event::Closed){
                window.close();
                exit(0);
            }
        } 

        window.display(); 
    }

    return 0;
}
