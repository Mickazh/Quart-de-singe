/**
 * @file game.cpp
 * @author Zheng Mickael
 * @brief Fichier avec les fonctions necassaires pour jouer
 * @date 2022-12-18
 */


#include "game.h"

void initGame(game& g, const char* players, char** dict){
    unsigned int nbPlayers = strlen(players);
    initialiser(g.players, 2, 2);
    for (unsigned int i = 0; i < nbPlayers; ++i){
        initPlayer(g, players[i], i);
    }
    g.turn = 0;
    g.nbPlayers = nbPlayers;
    g.dict = dict;
}


void initPlayer(game& g, char type, unsigned int pos){
    player p;
    p.type = type;
    p.nbQuart = 0;
    p.pos = pos;
    ecrire(g.players, pos, p);
}

char getTypeAtm(const game& g){
    return lire(g.players, g.turn%g.nbPlayers)->type;
}

char getType(const game& g, int i){
    if (i < 0){
        return lire(g.players, g.nbPlayers-1)->type;
    }
    return lire(g.players, i)->type;
}

void affichePlayer(const game& g, int i){
    if (i < 0){
        cout << lire(g.players, g.nbPlayers-1)->pos + 1 << lire(g.players, g.nbPlayers-1)->type;
        return;
    }
    cout << lire(g.players, i)->pos + 1 << lire(g.players, i)->type; 
}

void affichePlayerAtm(const game& g){
    affichePlayer(g, g.turn%g.nbPlayers);
}

void addQuart(game& g, int i){
    if (i < 0){
        ++lire(g.players, g.nbPlayers-1)->nbQuart;
        gameState(g);
        return;
    }
    ++lire(g.players, i)->nbQuart;
    gameState(g);
}

void gameState(const game& g){
    for (int i = 0; i < g.nbPlayers; ++i){
        cout << i+1 << lire(g.players, i)->type << " : " << (float)lire(g.players, i)->nbQuart/4;
        if (i != g.nbPlayers-1)
            cout << "; ";
    }
    cout << endl;
}

int getIndexMax(const int* tab, unsigned int len){
    unsigned int iMax = 0;
    for (unsigned int i = 1; i < len; ++i){
        if (tab[iMax] < tab[i])
            iMax = i;
    }
    return iMax;
}

char bestChar(const char* word, char** dict, unsigned int nbWord, char* alphabet, const game& g){
    if (strcmp(word, "") == 0){
        return alphabet[(rand())%strlen(alphabet)];
    }
    int j = nCharInDict(word, dict, nbWord, 0);
    if (j == -1 || strlen(word) > MAX_CHAR-1){
        return '?';
    }
    char testWord[MAX_CHAR+1];
    unsigned int nbLettre = strlen(alphabet), len = strlen(word);
    int* score = new int[nbLettre];
    int lastWord = -1;
    for (unsigned int i = 0; i < nbLettre; ++i){
        strcpy(testWord, word);
        score[i] = INT_MAX;  //valeur arbitraire
        testWord[len] = alphabet[i];
        testWord[len+1] = '\0';
        if (inDict(testWord, dict, nbWord) && strlen(testWord) > 2){
            score[i] = -1;
            continue;
        }
        int firstIndex = nCharInDict(testWord, dict, nbWord, 0); //ne reprente pas toujours le premiere indice, le nom peut porter à confusion
        if (firstIndex == -1){
            score[i] = -1;
            continue;
        }
        unsigned int compIndex = firstIndex; // utile
        while (strncmp(testWord, dict[firstIndex], len+1) == 0 && firstIndex < nbWord){
            if (strncmp(dict[compIndex], dict[firstIndex], strlen(dict[compIndex])) == 0)
                if (strlen(dict[firstIndex]) > strlen(dict[compIndex])){
                    ++firstIndex;
                    continue;
                }
            else {
                compIndex = firstIndex;
            }

            if ((strlen(dict[firstIndex])-len-1)%g.nbPlayers == 0 && strlen(dict[firstIndex]) > 2){
                --score[i];
            }

            ++firstIndex;
            if (firstIndex == nbWord){
                break;
            }
        }
    }
    unsigned int bestIndex = getIndexMax(score, nbLettre); 
    if (score[bestIndex] == -1){
        delete [] score;
        return '?';
    }
    delete [] score;
    return alphabet[bestIndex];
}

void askWord(game& g, char*& word, unsigned int nbWord, unsigned int& i, unsigned int& maxLen){
    char ask[MAX_CHAR];
    int indexAdd; //l'indice du joueur qui doit prendre un quart de singe
    affichePlayer(g, (g.turn-1)%g.nbPlayers);
    cout << ", saisir le mot > ";
    if (getType(g, (g.turn-1)%g.nbPlayers) == 'H'){ // type du joueur précédent
        cin.width(MAX_CHAR);
        cin >> ask;
        cin.ignore(INT_MAX, '\n');
    }
    else{
        int index = nCharInDict(word, g.dict, nbWord, 1);
        if (index == -1){ // Impossible normalement/ pour ne pas faire planter le programme s'il y a une erreur
            strcpy(ask, "ILYAUNPROBLEME");
        }
        else 
            strcpy(ask, g.dict[nCharInDict(word, g.dict, nbWord, 1)]);
    }
        
    for (int j = 0; j < strlen(ask); ++j){
        ask[j] = toupper(ask[j]);
    }
    cout << "le mot " << ask;
    if (strncmp(word, ask, strlen(word))){
        --g.turn;
        cout << " ne commence pas par les lettres attendues, le joueur ";
        affichePlayer(g, g.turn%g.nbPlayers);
        cout << " prend un quart de singe" << endl;
        addQuart(g, g.turn%g.nbPlayers);
        resetWord(word, i, maxLen);
        return;
    }
    if (inDict(ask, g.dict, nbWord)){
        indexAdd = g.turn%g.nbPlayers;
        cout << " existe, le joueur ";
        affichePlayer(g, g.turn%g.nbPlayers);
    }
    else{
        --g.turn;
        indexAdd = g.turn%g.nbPlayers;
        cout << " n'existe pas, le joueur ";
        affichePlayer(g, g.turn%g.nbPlayers);
    }
    cout << " prend un quart de singe" << endl;
    addQuart(g, indexAdd);
    resetWord(word, i, maxLen);
    return;    
}

void addChar(char*& word, char letter, unsigned int& i, unsigned int& maxLen){
    if (i+1 == maxLen){
        maxLen = (i+1)*2; //on double la taille, valeur arbitraire
        char* newWord = new char[maxLen]; 
        strcpy(newWord, word);
        delete [] word;
        word = newWord;
    }
    word[i] = letter;
    word[i+1] = '\0';
    ++i;
}

void resetWord(char*& word, unsigned int& i, unsigned int& maxLen){
    char* newWord = new char[MAX_CHAR];
    delete [] word;
    word = newWord;
    maxLen = MAX_CHAR;
    word[0] = '\0';
    i = 0;
}

void abandon(game& g, char*& word, unsigned int& i, unsigned int& maxLen){
    cout << "le joueur ";
    affichePlayer(g, g.turn%g.nbPlayers);
    cout << " abandonne la manche et prend un quart de singe" << endl;
    addQuart(g, g.turn%g.nbPlayers);
    resetWord(word, i, maxLen);
    return;
}

bool finPartie(const game& g){
    for(int i = 0; i < g.nbPlayers; ++i){
        if (lire(g.players, i)->nbQuart == 4)
            return true;
    }
    return false;
}