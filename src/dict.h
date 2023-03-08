/**
 * @file dict.h
 * @author Zheng Mickael
 * @brief Fichier avec les prototypes des fonctions lié au dictionnaire
 * @date 2022-12-18
 */
#ifndef _DICT_
#define _DICT_

#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;
/**
 * @brief Renvoie le nombre de mot dans un fichier
 * 
 * @param [in] fI : Le flux vers le fichier
 * @return unsigned int : Le nombre de mot
 */
unsigned int getNumberWord(ifstream& fI);

/**
 * @brief Ajoute une lettre à l'alphabet si necessaire
 * 
 * @param [in, out] alphabet : L'alphabet
 * @param [in] letter : La lettre à potentiellement ajouter
 * @param [in, out] index : L'indice de la dernière lettre ajouté
 * @param [in, out] maxLenAlpha : La longueur maximal de l'alphabet
 */
void addLetter(char*& alphabet, char letter, unsigned int& index, unsigned int& maxLenAlpha);

/**
 * @brief Initialise le dictionnaire
 * 
 * @param [out] dict : Le dictionnaire à initialiser
 * @param [in] nbWord : Le nombre de mot
 */
void initDict(char** dict, unsigned int nbWord);

/**
 * @brief Remplie le dictionnaire, et crée l'alphabet des lettres possible
 * 
 * @param [in] fI : Le flux vers le fichier
 * @param [out] dict : Le dictionnaire qu'on cherche à remplire
 * @param [in] nbWord : Le nombre de mot dans le fichier
 * @param [in] alphabet : L'alphabet qu'on complete en même temps que le dictionnaire
 * @param [in] maxLenAlpha : La longueur maximal de l'alphabet (modifiable s'il dans le dictionnaire
 * il y a plus 26 de symboles)
 */
void createDict(ifstream& fI, char** dict, unsigned int nbWord, char*& alphabet, unsigned int& maxLenAlpha);

/**
 * @brief Verifie si un mot est dans le dictionnaire
 * 
 * @param [in] word : Le mot
 * @param [in] dict : Le dictionnaire
 * @param [in] nbWord : Le nombre de mot dans le dictionnaire
 * @return true Si le mot est dans le dictionnaire
 * @return false Si le mot n'est pas dans le dictionnaire
 */
bool inDict(const char* word, char** dict, unsigned int nbWord);

/**
 * @brief Renvoie la première occurence d'un mot commencant par une suite de lettre(word)
 * 
 * @param [in] word : Le mot
 * @param [in] dict : Le dictionnaire
 * @param [in] iWord : l'indice du mot reçu
 * @return int L'indice de la première occurence de word
 * @see On utilise cette fonction seulement après l'appel de la fonction nCharInDict,
 */
int findFirstIndex(const char* word, const char** dict, int iWord);

/**
 * @brief Si type = 0 alors la fonction renvoie l'indice du premier 
 * mot dans le dictionnaire avec les mêmes premieres lettres, dans le cas ou il
 * n'y a pas de mot avec les mêmes premieres lettre, la fonciton renvoie -1
 *        Si type != 0 alors renvoie l'indice d'un mot qui commence par les
 * memes lettres que word
 * 
 * @param [in] word : Le mot
 * @param [in] dict : Le dictionnaire
 * @param [in] nbWord : Le nombre de mot dans le dictionnaire
 * @param [in] type 0 pour obtenir le premier indice, > 0 pour obtenir un peu 
 * @return int 
 */
int nCharInDict(const char* word, char** dict, unsigned int nbWord, unsigned int type);

#endif