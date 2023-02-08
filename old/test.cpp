#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include "allwords.h"

using namespace std;

int main() {
    srand(time(NULL));
    ifstream fin;
    fin.open("words.txt", ios::in);
    AllWords words;

    do {
        WordHolder word;
        fin >> word;
        words.addWord(word);
    } while (!fin.eof());


    for (int i = 0; i < words.getSize(); i++) {
        int j = 0;
        cout << words[i];
        do {
            words[i].unshuffle();
            j++;
        } while (strcmp(words[i].word, words[i].shuffled) != 0);
        cout << words[i] << j << endl;
    }

    return 0;
}