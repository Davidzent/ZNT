/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: rcc
 *
 * Created on November 21, 2018, 3:02 PM
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