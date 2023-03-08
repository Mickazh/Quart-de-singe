/**
 * @file game.h
 * @author Zheng Mickael
 * @brief Fichier avec les prototypes ainsi que la structure game 
 * @date 2022-12-18
 */

#ifndef _GAME_
#define _GAME_

#include <random>
#include <climits>

#include "ConteneurTDE.h"
#include "dict.h"

enum{MAX_CHAR = 26};

/**
 * @brief structure permetant de stocker les joueurs ainsi 
 * l'indice du joueur qui doit jouer 
 */
struct game{
    ConteneurTDE players;   // Le conteneur permetant de contenir tous les joueurs
    int turn;               // Le tour dans la partie, permet de savoir qui doit jouer
    int nbPlayers;          // Nombre de joueurs
    // pas unsigned int car comportement non voulu avec %
    char** dict;            // Un pointeur vers le dictionnaire de mot
};

/**
 * @brief Initialise la partie
 * 
 * @param [in, out] g : La partie
 * @param [in] nbPlayers : Le nombre de joueurs
 * @param [in] players : La chaine de caractère composé de H ou R
 * @param [in] dict : Un pointeur vers le dictionnaire utilisé pendant la partie
 */
void initGame(game& g, const char* players, char** dict);

// void initPlayer(player& p, char type, unsigned int pos);
/**
 * @brief Initialise un joueur
 * 
 * @param [in, out] g : La partie dans laquelle les joueurs se trouvent
 * @param [in] type : Le type de joueur
 * @param [in] pos : La position du joueur
 */
void initPlayer(game& g, char type, unsigned int pos);

/**
 * @brief Renvoie le type du joueur qui doit jouer
 * 
 * @param [in] g : La partie
 * @return char : R si le joueur est un robot, H si le joueur est un robot
 */
char getTypeAtm(const game& g);

/**
 * @brief Renvoie le type du joueur ayant la posisition i
 * 
 * @param [in] g : La partie
 * @param [in] i : La position
 * @return char : R si le joueur est un robot, H si le joueur est un robot
 */
char getType(const game& g, int i);

/**
 * @brief Affiche la position et le type du joueur à la position i
 * 
 * @param [in] g : La partie
 * @param [in] i : La position
 * @pre i < g.nbPlayers
 * @see si i < 0, c'est-à-dire qu'on souhaite afficher le joueur précedant au 
 * premier joueur donc affiche le joueur à la position g.nbPlayers-1
 */
void affichePlayer(const game& g, int i);

/**
 * @brief Affiche la position et le type du joueur qui doit jouer
 * 
 * @param [in] g : La partie
 */
void affichePlayerAtm(const game& g);

/**
 * @brief Ajoute un quart de singe au joueur à l'indice i, à chaque fois qu'on ajoute un quart
 * de singe à un joueur, il faut afficher l'état de la partie
 * 
 * @param [in, out] g : La partie
 * @param [in] i : L'indice du joueur qui prend un quart de singe
 */
void addQuart(game& g, int i);

/**
 * @brief Affiche l'état de la partie, c'est à dire les joueurs ainsi que leurs quart de singe
 * 
 * @param [in] g : La partie
 */
void gameState(const game& g);

/**
 * @brief Renvoie l'indice de l'élément le plus grand
 * 
 * @param [in] tab : La tableau dans lequel on cherche
 * @param [in] len : La taille du tablaeu
 * @return int L'indice du maximum
 */
int getIndexMax(const int* tab, unsigned int len);

/**
 * @brief Renvoie le "meilleur" caractère à jouer selon un mot word dans le dictionnaire
 * dict (pas besoin de dict), et selon un alphabet
 * 
 * @param [in] word : Le mot/debut de mot
 * @param [in] dict : Le dictionnaire (pas pas besoin)
 * @param [in] nbWord : Le nombre de mot
 * @param [in] alphabet : L'alphabet à selon le dictionnaire
 * @param [in] g : La partie
 * @return char '?' si le mot n'existe pas ou si le robot est forcé de jouer une lettre
 * formant un mot, plutôt que de former un mot. Sinon joue la "meilleur" lettre à jouer
 */
char bestChar(const char* word, char** dict, unsigned int nbWord, char* alphabet, const game& g);

/**
 * @brief La fonction permet de demander au joueur à la position i, à quel mot il pensait, et affiche
 * les messages attendus.
 * 
 * @param [in, out] g : La partie
 * @param [in, out] word : Le mot/debut de mot
 * @param [in] nbWord : Le nombre de mot dans le dictionnaire
 * @param [in, out] i : L'indice du joueur intérrogé
 * @param [in, out] maxLen : La taille maximal du mot
 */
void askWord(game& g, char*& word, unsigned int nbWord, unsigned int& i, unsigned int& maxLen);

/**
 * @brief Ajoute une lettre au mot, si on essaie d'ajouter une lettre au delas de limite
 * alors agrandi la taille du mot.
 * 
 * @param [in, out] word : Le mot/debut de mot
 * @param [in] letter : Une lettre à ajouter au mot
 * @param [in, out] i : L'indice de la lettre à ajouter, utile pour savoir quand la limite est atteinte
 * @param [in, out] maxLen : La taille maximal du mot
 */
void addChar(char*& word, char letter, unsigned int& i, unsigned int& maxLen);

/**
 * @brief Réinitialise le mot en le vidant et restaurant sa taille initiale (MAX_CHAR(=26)), met
 * aussi la lettre à 0
 * 
 * @param [in, out] word : Le mot à réinitialiser
 * @param [in, out] i : L'indice de la lettre
 * @param [in, out] maxLen : La taille maximal du mot
 */
void resetWord(char*& word, unsigned int& i, unsigned int& maxLen);

/**
 * @brief Affiche les messages liés à un abandon, et ajoute un quart de singe au joueur qui abandonne 
 * 
 * @param [in, out] g : La partie
 * @param [in, out] word : Le mot à vider
 * @param [in, out] i : L'indice du joueur qui abandonne
 * @param [in, out] maxLen : La taille maximal du mot
 */
void abandon(game& g, char*& word, unsigned int& i, unsigned int& maxLen);

/**
 * @brief Verifie si la partie est fini
 * 
 * @param [in] g : La partie
 * @return true si un joueur a quarte quart de singe
 * @return false si aucun joueur n'a quarte quart de singe
 */
bool finPartie(const game& g);

#endif