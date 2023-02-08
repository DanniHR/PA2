#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "allwords.h"
#define DEBUG false

using namespace std;

WordHolder::WordHolder() {
    word = new char[128];
    shuffled = new char[128];
}

ostream& operator<<(ostream& out, const WordHolder& word){
    if (DEBUG) {
        out << "W:" << word.word << " S:" << word.shuffled << endl;
    } else {
        out << "\n\t";
        for (int i = 0; i < word.length-1; i++) {
            out << word.shuffled[i] << "-";
        }
        out << word.shuffled[word.length-1] << endl << "\t";
        for (int i = 0; i < word.length-1; i++) {
            if (word.word[i] == word.shuffled[i]) {
                out << word.shuffled[i] << "-";
            } else {
                out << "X" << "-";
            }
        }
        if (word.word[word.length-1] == word.shuffled[word.length-1]) {
            out << word.shuffled[word.length-1] << endl;;
        } else {
            out << "X" << endl;
        }
        
    }
    return out;
}
ifstream& operator>>(ifstream& in, WordHolder& obj){
    in >> obj.word;
    obj.length = strlen(obj.word);
    obj.shuffle();
    return in;
}

void WordHolder::shuffle() {
    strcpy(shuffled, word);
    do {
        for (int j = 0; j < length; j++) {
            int place1 = rand() % length;
            int place2 = rand() % length;
            char temp = shuffled[place1];
            shuffled[place1] = shuffled[place2];
            shuffled[place2] = temp;
        }
    } while(strcmp(word, shuffled) == 0);
    bool flag = true;
    for (int i = 0; i < length; i++) {
        if (word[i] == shuffled[i]) {
            flag = false;
            break;
        }
    }
    if (flag) {unshuffle();}
}

void WordHolder::unshuffle() {
    int new_shuffle;
    while (true) {
        new_shuffle = rand() % length;
        if ((word[new_shuffle] != shuffled[new_shuffle]) || (strcmp(word, shuffled) == 0)) {
            break;
        }
    }
    char correct = word[new_shuffle];
    for (int j = 0; j < length; j++) {
        if (correct == shuffled[j]) {
            shuffled[j] = shuffled[new_shuffle];
            shuffled[new_shuffle] = correct;
            break;
        }
    }
}

AllWords::AllWords() {
    capacity = 2;
    size = 0;
    words = new WordHolder[capacity];
}

void AllWords::addWord(const WordHolder& wrd) {
    if (size == capacity) {resize();}
    words[size] = wrd;
    size++;
}

int AllWords::getSize() {
    return size;
}

WordHolder AllWords::getWord(int idx) {
    return words[idx];
}

ostream& operator<<(ostream& out, const AllWords& words){
    for(int i = 0; i < words.size; i++){
        out << words.words[i];
    }
    return out;
}

WordHolder AllWords::operator[](int idx) {
    return words[idx];
}

void WordHolder::add_to_score_table(std::__1::ifstream& score_table, std::__1::ofstream& output,const char* name, int& correct){
    
    char* top_list = new char[128]; 
    while(!score_table.eof()){
        score_table >> top_list;
   
   
        output << correct << "," << name;
        if(!isalpha(top_list[0])){output << ";"<< top_list;}
     }
    output.close();
    score_table.close();
}
void WordHolder::get_top_score(std::__1::ifstream& score_table, const char* name, int& correct)
{
    

    int higest_value;
    char* top_list = new char[128]; 
    while(!score_table.eof()){
        score_table >> top_list;
        higest_value = get_higest(top_list);
       
        
        
        
     
        int tmp = 0;
        int rounds = 0;
        

        
     
            for(; rounds <= 5 ;rounds++, higest_value = higest_value-1){
                tmp = 0; 
            
                for(; tmp <= strlen((const char*)(top_list)) ;){

                    
                    for(int i = tmp;  tmp <= strlen((const char*)(top_list)) && (int)((top_list)[i]-48) == higest_value; i++ )
                    {
                        for(int i = tmp;  tmp <= strlen((const char*)(top_list)); i++ ){ 
                            // if the word ends
                            if(top_list[i] == ';'){ cout << endl; break;  }
                            // Here it print the num
                            if(isdigit(top_list[i]) == true && isdigit(top_list[i+1]) == false ){cout  << "Score: ";}
                            if(top_list[i] != ',' && top_list[i] != ';'){cout << top_list[i];}
                            if(isdigit(top_list[i]) == true && isdigit(top_list[i+1]) == false ){cout  << " Player: ";}
                            tmp = i;
                            }
                    }
                tmp = tmp+1;
            }
        }
        

    } 
    

score_table.close();
}

int  WordHolder::get_higest(const char* top_list){
    
    int max_value = 0; 
 
    int new_bool= 1;

    
      
        
        for(int i =0; i <= strlen((const char*)(top_list)); i++){
            // if the max has two numbers
            if(isdigit(top_list[i]) == true && isdigit(top_list[i+1]) == false && new_bool == 1){
                // Check if there is two number in top list
                if(isdigit(top_list[i]) == true && isdigit(top_list[i-1]) == true){
                    if((int)((top_list)[i-1]-48)*10+((top_list)[i]-48) > max_value)
                        {max_value = (int)((top_list)[i-1]-48)*10+((top_list)[i]-48); new_bool = 0;}
                    }
                // Check if there is one number in top list
                else if(isdigit(top_list[i]) == true && isdigit(top_list[i-1]) == false){
                    if((int)((top_list)[i]-48) > max_value)
                    {max_value = (int)((top_list)[i]-48);}
                }   
            }
            // if the max has two numbers
            else if(isdigit(top_list[i]) == true && isdigit(top_list[i+1]) == false && new_bool == 0){
                if(isdigit(top_list[i]) == true && isdigit(top_list[i-1]) == true){
                    if((int)((top_list)[i-1]-48)*10+((top_list)[i]-48) > max_value)
                        {max_value = (int)((top_list)[i-1]-48)*10+((top_list)[i]-48);}
                    }
                else if(isdigit(top_list[i]) == true && isdigit(top_list[i-1]) == false){}   
            }
        }
      
  
return max_value;
}
   


AllWords::~AllWords(){
    delete[] words;
}

void AllWords::resize() {
    for (int i = 0; i < size; i++) {
    }
    WordHolder *tmp_arr = new WordHolder[capacity * 2];
    for(int i = 0; i < size; i++){
        tmp_arr[i] = words[i];            }
    delete[] words;
    words = tmp_arr;
    capacity *= 2;
}