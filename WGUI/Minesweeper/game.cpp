#include "game.hpp"
#include "painter.hpp"
#include <iostream>
using namespace std;


Game::Game(){
    temp.crtmap();
}
void Game::draw(){
    temp.draw();
}
void Game::mark(int y, int x){
    temp.mark(y,x);
}
void Game::open(int y, int x){
    temp.open(y,x);
    //temp.prntmap();
}

