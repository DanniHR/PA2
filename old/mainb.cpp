#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>

using namespace std;

struct WordHolder{
        int length;
        char* word;
        char* shuffled;
        WordHolder() {
            word = new char[128];
            shuffled = new char[128];
        }
        friend ostream& operator<<(ostream& out, const WordHolder& word){
            out << "W:" << word.word << " S:" << word.shuffled << " L:" << word.length << endl;
            return out;
        }
        void shuffle() {
            strcpy(shuffled, word);
            for (int j = 0; j < length; j++) {
                int place1 = rand() % length;
                int place2 = rand() % length;
                char temp = shuffled[place1];
                shuffled[place1] = shuffled[place2];
                shuffled[place2] = temp;
        }
        }

};

class AllWords{
    public:
        AllWords() {
            capacity = 2;
            size = 0;
            words = new WordHolder[capacity];
        }

        void addWord(const WordHolder& wrd) {
            if (size == capacity) {resize();}
            words[size] = wrd;
            size++;
        }

        int getSize() {
            return size;
        }

        WordHolder getWord(int idx) {
            return words[idx];
        }

        friend ostream& operator<<(ostream& out, const AllWords& words){
            for(int i = 0; i < words.size; i++){
                out << words.words[i];
            }
            return out;
        }

        WordHolder operator[](int idx) {
            return words[idx];
        }

        virtual ~AllWords(){
            delete[] words;
        }

    private:
        int capacity;
        int size;
        WordHolder *words;

        void resize() {
            for (int i = 0; i < size; i++) {
            }
            WordHolder *tmp_arr = new WordHolder[capacity * 2];
            for(int i = 0; i < size; i++){
                tmp_arr[i] = words[i];            }
            delete[] words;
            words = tmp_arr;
            capacity *= 2;
        }
};

int main() {
    ifstream fin;
    fin.open("words.txt", ios::in);
    AllWords words;

    do {
        WordHolder word;
        fin >> word.word;
        word.length = strlen(word.word);
        words.addWord(word);
    } while (!fin.eof());

    srand(time(NULL));

    for(int i = 0; i < words.getSize(); i++) {
        words[i].shuffle();
    }
    cout << words;
    return 0;
}