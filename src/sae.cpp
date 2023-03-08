/**
 * @file sae.cpp
 * @author Zheng Mickael
 * @brief Fichier principal
 * @date 2022-12-18
 */

using namespace std;
#include <time.h>
#include "game.h"


void verifArg(unsigned int nbArg, char *argv[]){
    if(nbArg != 2){
        cerr << "Un probleme avec le nombre de paramètres" << endl;
        exit(0);
    }
    for (int i = 0; i < strlen(argv[1]); ++i){
        if (argv[1][i] != 'H' && argv[1][i] != 'R'){
            cerr << "Un le paramètre des joueurs" << endl;
            exit(0);
        }
    }
}

int main(int argc, char *argv[]){
    verifArg(argc, argv);
    srand(time(NULL));
    ifstream file;
    file.open("ods4.txt", ios::in);
    if (file.fail()){
        cerr << "Impossible d'ouvrir le dictionnaire, verrifiez que le dictionnaire s'appel bien ods4.txt" << endl;
        exit(1);
    }
    
    unsigned int nbWord = getNumberWord(file);
    file.clear();
    file.seekg(0);
    char** dict = new char* [nbWord];
    unsigned int maxLenAlpha = MAX_CHAR;
    char* alphabet = new char[maxLenAlpha];
    createDict(file, dict, nbWord, alphabet, maxLenAlpha);
    file.close();

    unsigned int nbPlayer = strlen(argv[1]);
    unsigned int maxLen = MAX_CHAR;
    char* word = new char[maxLen];
    word[0] = '\0';
    char ask[MAX_CHAR] = "";
    char c;
    unsigned int i = 0;
    game g;
    initGame(g, argv[1], dict);

    while (!finPartie(g)){
        affichePlayerAtm(g);
        cout << ", (" << word << ") > ";
        if (getTypeAtm(g) == 'H'){
            cin >> c;
            cin.ignore(INT_MAX, '\n');
            c = toupper(c);
        }
        else{
            c = bestChar(word, dict, nbWord, alphabet, g);
            cout << c << endl;
        }
        if (c == '?'){
            askWord(g, word, nbWord, i, maxLen);
            continue;
        }
        if (c == '!'){
            abandon(g, word, i, maxLen);
            continue;
        }
        addChar(word, c, i, maxLen);
        if (inDict(word, dict, nbWord) && strlen(word) > 2){
            cout << "le mot " << word << " existe, le joueur ";
            affichePlayerAtm(g);
            cout << " prend un quart de singe" << endl;
            addQuart(g, g.turn%nbPlayer);
            resetWord(word, i, maxLen);
            continue;
        }
        ++g.turn;
    }
    delete [] word;
    cout << "La partie est finie" << endl;
    return 0;
}