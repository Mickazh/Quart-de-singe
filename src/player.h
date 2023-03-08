/**
 * @file player.h
 * @author Zheng Mickael
 * @brief Fichier contenant la structure player
 * @date 2022-12-18
 */

#ifndef _PLAYER_
#define _PLAYER_

/**
 * @brief structure player contenant le type de joueur, le nombre de quart de singe et sa position
 * 
 */
struct player{
    char type;                  //type du joueur H pour humain et R pour robot
    unsigned int nbQuart, pos;  //nombre de quart de singe et la position du joueur
};

#endif