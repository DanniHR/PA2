#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>

using namespace std;

struct WordHolder{
        int length;
        char* word;
};

class AllWords{
    public:
        AllWords() {};
        void addWord(char* wrd) {
            words[size].word = wrd;
        }
        const char* operator[](int idx) {
            return words[idx].word;
        }
    private:
        int capacity = 2;
        int size = 0;
        WordHolder *words = new WordHolder[capacity];
};

int main() {
    ifstream fin;
    fin.open("words.txt", ios::in);

    WordHolder *words;
    words = new WordHolder[100];
    int numwrds = 0;
    do {
        words[numwrds].word = new char[128];
        fin >> words[numwrds].word;
        words[numwrds].length = strlen(words[numwrds].word);
        numwrds++;
    } while (!fin.eof());

    srand(time(NULL));

    for (int i = 0; i < numwrds; i++) {
        const int len = words[i].length;
        char shuffled[128];
        strcpy(shuffled, words[i].word);
        for (int j = 0; j < len; j++) {
            int place1 = rand() % len;
            int place2 = rand() % len;
            char temp = shuffled[place1];
            shuffled[place1] = shuffled[place2];
            shuffled[place2] = temp;
        }
        cout << words[i].word << ": " << shuffled << endl;
    }

    delete[] words;
    return 0;
}