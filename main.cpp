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

    cout << "Welcome to word jumble!!" << endl;
    char *input = new(char[128]);
    int points = 10;
    int correct = 0;
    WordHolder shuffled_word = words.getWord(rand() % words.getSize());
    do {
        cout << "Jumbled word: " << shuffled_word  << endl;
        cout << "Your guess(lower case)\n\t(h) for hint\n\t(q) for quit: ";
        cin >> input;

        if (strcmp(input, "h") == 0) {
            shuffled_word.unshuffle();
            points--;
        }

        if (strcmp(shuffled_word.shuffled, shuffled_word.word) == 0) {
            cout << "OOPS!! Too many hints, the word was: " << shuffled_word.word << endl << endl;
            shuffled_word = words.getWord(rand() % words.getSize());
        }
        
        if (strcmp(input, shuffled_word.word) == 0) {
            cout << "Congrats!!" << endl << endl;
            correct++;
            shuffled_word = words.getWord(rand() % words.getSize());
        }

        if (points == 0) {
            cout << "Game Over!!" << endl << "You guessed " << correct << " words" << endl;
            break;
        }
        
        if(strcmp(input, "q") == 0){
            fin.close();
            char name[128];
            cout << "Add name: ";
            cin >> name;
            
            ofstream fout; fout.open("highscore_table.txt", ios::in );
            ifstream fin_2; fin_2.open("highscore_table.txt", ios::out );
            cout << "Press 't' to get the highscore table: ";
            char* input_value = new (char[0]);
            cin >> input_value;
    
            WordHolder list;
            // Here we type cast it to const char to create an object
            list.add_to_score_table(fin_2, fout, (const char*)(name),(int&)(correct)); 
            fout.close();  
            fin_2.close();
            ifstream fin_3; fin_3.open("highscore_table.txt", ios::in );
            if(input_value[0] == 't'){list.get_top_score(fin_3, (const char*)(name),(int&)(correct));}
            fin_3.close();         
        }
        
    } while(strcmp(input, "q") != 0);
   
    return 0;
}