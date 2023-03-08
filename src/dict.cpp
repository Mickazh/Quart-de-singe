/**
 * @file dict.cpp
 * @author Zheng Mickael
 * @brief Fichier avec les fonctions necassaires pour jouer
 * @date 2022-12-18
 */

#include "dict.h"

enum{MAX_CHAR = 26};

unsigned int getNumberWord(ifstream& fI){
    char buffer[MAX_CHAR];
    unsigned int nbWord = 0;
    fI >> setw(MAX_CHAR) >> buffer;
    while (fI){
        ++nbWord;
        fI >> setw(MAX_CHAR) >> buffer;
    }
    return nbWord;
}

void initDict(char** dict, unsigned int nbWord){
    for (int i = 0; i < nbWord; ++i){
        dict[i] = new char[MAX_CHAR];
    }
}

void addLetter(char*& alphabet, char letter, unsigned int& index, unsigned int& maxLenAlpha){
    if (index+1 == maxLenAlpha){
        maxLenAlpha = index+1; //on agrandi l'alphabet d'une lettre si cherche à rajouter plus que le nombre de lettre max (26 normalement)
        char* newAlpha = new char[maxLenAlpha];
        strcpy(newAlpha, alphabet);
        delete [] alphabet;
        alphabet = newAlpha;
    }
    if (alphabet[index] != letter){
        alphabet[++index] = letter;
        alphabet[index+1] = '\0';
    }
}

void createDict(ifstream& fI, char** dict, unsigned int nbWord, char*& alphabet, unsigned int& maxLenAlpha){
    initDict(dict, nbWord);
    char buffer[MAX_CHAR];
    unsigned int i = 0, j = 0;
    fI >> setw(MAX_CHAR) >> buffer;
    alphabet[0] = buffer[0];
    while (fI){
        strcpy(dict[i], buffer);
        addLetter(alphabet, buffer[0], j, maxLenAlpha);
        fI >> setw(MAX_CHAR) >> buffer;
        ++i;
    }
}

bool inDict(const char* word, char** dict, unsigned int nbWord){
    int deb = 0, fin = nbWord-1, mid; // int et non pas unsigned int car si word est A fin = 0-1
    while (deb <= fin){
        mid = (deb+fin)/2;
        if (strcmp(word, dict[mid]) == 0)
            return true;
        if (strcmp(word, dict[mid]) > 0)
            deb = mid + 1;
        else
            fin = mid - 1;
    }
    return false;
}

int findFirstIndex(const char* word, char** dict, int iWord){
    while (strncmp(word, dict[iWord], strlen(word)) == 0){
        --iWord;
        if (iWord < 0)
            return 0;
    }
    return iWord+1;
}

int nCharInDict(const char* word, char** dict, unsigned int nbWord, unsigned int type){
    if (strlen(word) == 0){
        unsigned int randomIndex = rand()%nbWord;
        while (strlen(dict[randomIndex]) < 3){
            randomIndex = rand()%nbWord;
        }
        return randomIndex;
    }
    int deb = 0, fin = nbWord-1, mid; // int et non pas unsigned int car si word est A fin = 0-1
    unsigned int len = strlen(word);
    while (deb <= fin){
        mid = (deb+fin)/2;
        if (strncmp(word, dict[mid], strlen(word)) == 0){
            if (type == 0)
                return findFirstIndex(word, dict, mid);
            return mid;
        }
        if (strncmp(word, dict[mid], strlen(word)) > 0)
            deb = mid + 1;
        else
            fin = mid - 1;
    }
    return -1;
}
