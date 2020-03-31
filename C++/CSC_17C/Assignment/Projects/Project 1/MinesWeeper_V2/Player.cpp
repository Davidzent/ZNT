/* 
 * File:   player.h
 * Author: David guijosa
 *
 * Created on November 23, 2018, 2:24 PM
 */

#include "Player.h"

Player::Player(){
    points=0;   //at the beginning set player points to 0
}
bool Player::isalive(char cord)const{
    static bool live=true;
    if(cord=='X')live=false;      //returns if the player can still play
    return live;
} 
float Player::gtpoint()const{
    return points;          //get the points of the player
}
void Player::operator ++(){
    points++;               
}
void Player::operator +=(int val){
    points+=val;
}