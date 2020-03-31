/* 
 * File:   player.h
 * Author: David guijosa
 *
 * Created on November 23, 2018, 2:24 PM
 */

#ifndef ABSPLAYER_H
#define ABSPLAYER_H

class AbsPlyr{
    public:
        virtual bool isalive(char)const = 0; //created to know if the 
                                             //player is alive
};

#endif /* PLAYER_H */