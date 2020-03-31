/* 
 * File:   player.h
 * Author: David guijosa
 *
 * Created on November 23, 2018, 2:24 PM
 */

#include "Player.h"

Player::Player(){
    points=0;
}
bool Player::isalive(char cord)const{
    if(cord=='X')return false;
    return true;
} 
float Player::gtpoint()const{
    return points;
}
void Player::operator ++(){
    points++;
}
void Player::operator +=(int val){
    points+=val;
}