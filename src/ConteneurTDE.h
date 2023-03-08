#ifndef _CONTENEUR_TDE_
#define _CONTENEUR_TDE_

/**
 * @file ConteneurTDE.h
 * Projet sem04-tp-Cpp1-3
 * @author l'�quipe p�dagogique 
 * @version 2 26/11/11
 * @brief Composant d'un conteneur d'items de capacit� extensible
 * Structures de donn�es et algorithmes - DUT1 Paris 5
 */
#include <iostream>
#include <cassert>
using namespace std;
#include "Item.h"

/** @brief Conteneur d'items allou�s en m�moire dynamique
 *  de capacit� extensible suivant un pas d'extension
 */ 
struct ConteneurTDE {
    unsigned int capacite; 	   // capacit� du conteneur (>0)
	unsigned int pasExtension; // pas d'extension du conteneur (>0)
	Item* tab;				   // conteneur allou� en m�moire dynamique
};

/**
 * @brief Initialise un conteneur d'items
 * Allocation en m�moire dynamique du conteneur d'items
 * de capacit� (capa) extensible par pas d'extension (p)
 * @see detruire, pour sa d�sallocation en fin d'utilisation 
 * @param[out] c : le conteneur d'items
 * @param [in] capa : capacit� du conteneur
 * @param [in] p : pas d'extension de capacit�
 * @pre capa>0 et p>0
 */
void initialiser(ConteneurTDE& c, unsigned int capa, unsigned int p);

/**
 * @brief D�salloue un conteneur d'items en m�moire dynamique
 * @see initialiser, le conteneur d'items a d�j� �t� allou� 
 * @param[in,out] c : le conteneur d'items
 */
void detruire(ConteneurTDE& c); 

/**
 * @brief Lecture d'un item d'un conteneur d'items
 * @param[in] c : le conteneur d'items
 * @param[in] i : la position de l'item dans le conteneur
 * @return l'item � la position i
 * @pre i < c.capacite   
 */
 Item* lire(const ConteneurTDE& c, unsigned int i);

/**
 * @brief Ecrire un item dans un conteneur d'items
 * @param[in,out] c : le conteneur d'items
 * @param[in] i : la position o� ajouter/modifier l'item
 * @param[in] it : l'item � �crire 
 */
void ecrire(ConteneurTDE& c, unsigned int i, const Item& it);

#endif /*_CONTENEUR_TDE_*/
