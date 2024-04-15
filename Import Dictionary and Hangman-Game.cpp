// Paulo Jose Zapata Vaca 

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
#include <stdlib.h>
using namespace std;

const int MAX_WORDS = 1000;
int word_count = 0;
string words[MAX_WORDS];
string definitions[MAX_WORDS];
string pos[MAX_WORDS];

void readWords(string filename){
    ifstream fin(filename);
    if (fin.fail()) { 
        cerr << "File cannot be opened for reading." << endl; 
        exit(1); 
    }
    string word, posi, junk, def;
    while(fin >>  word >> posi >> junk){
        getline(fin,def);
        def = def.substr(1);
        words[word_count]= word;
        pos[word_count]=posi;
        definitions[word_count]= def;
        
        cout<< words[word_count] << pos[word_count] << definitions[word_count] << endl;
        word_count+=1;
    }
}
int main(){
    readWords("text.txt");
    return 0;
}

int getIndex(string word){
	for (int i=0;i<word_count;i++){
		if(words[i]==word){
            return i;
		}
	}
    return -1;
}

string getDefinition(string word){
    if(getIndex(word)==-1){
        return "NOT_FOUND";
    }
	return definitions[getIndex(word)];
}
string getPOS(string word){
    if (getIndex(word)==-1){
        return "NOT_FOUND";
    }
	return pos[getIndex(word)];
}

int countPrefix(string prefix){
	int number=0;
    for (int i=0;i<word_count;i++){
        string sub=words[i].substr(0,prefix.length());
        if(words[i].length()>sub.length() && sub==prefix){
            number++;
        }
    }
    return number;
}

bool addWord(string new_word, string new_definition, string new_pos){
    if(getIndex(new_word)!=-1){
        return false;
    }
    if(word_count==MAX_WORDS){
        return  false;
    }
    words[word_count]=new_word;
    definitions[word_count]=new_definition;
    pos[word_count]=new_pos;

    word_count+=1;

    return true;
}

bool editWord(string word, string new_definition, string new_pos){
    if(getIndex(word)==-1){
        return false;
    }
    int rword= getIndex(word);
    definitions[rword]=new_definition;
    pos[rword]=new_pos;

    return true;
}

bool removeWord(string word){
    if(getIndex(word)==-1){
        return false;
    }
    int mvword= getIndex(word);
    words[mvword]=words[word_count-1];
    definitions[mvword]=definitions[word_count-1];
    pos[mvword]=pos[word_count-1];

    words[word_count-1] = "";
    definitions[word_count-1]= "";
    pos[word_count-1]= "";

    word_count-=1;
    return true;
}


string getRandomWord() {
    srand((unsigned) time(NULL));
    int index = rand() % word_count;
    return words[index];
}

string maskWord(string word){
    string strs= "";
    for(int i=0; i< word.length(); i++){
        strs+= "_";
    }
    return strs;
}

int getTries(int difficulty){
    if (difficulty==0){
        return 9;
    }
    else if(difficulty==1){
        return 7;
    }
    else if(difficulty==2){
        return 5;
    }
    return difficulty;
}

void printAttempts(int tries, int difficulty){
    for(int i=0; i < tries ;i++){
        cout<<"O";
    }
    int used= getTries(difficulty)-tries;
    for(int i=0; i < used; i++){
        cout<<"X";
    }
}
bool revealLetter(string word, char letter, string& current){
	bool Fletter = false;
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == letter) {
            current[i] = letter;
            Fletter = true;
        }
    }
    return Fletter;
}

void gameLoop() {
    int difficulty, tries;
    string word, current;
    char letter;
    while (true) {
        cout << "Welcome to Hangman!" << endl;
        cout <<  "0. easy\n1. normal\n2. hard\n3. exit\nChoose a difficulty: ";
        cin >> difficulty;
        while (difficulty < 0 || difficulty > 3) {
            cout <<  "Enough horseplay >_< !\n0. easy\n1. normal\n2. hard\n3. exit\nChoose a difficulty: ";
            cin >> difficulty;
        }
        if (difficulty == 3) {
            cout << "If you're hangry, go grab a bite! See what I did there?" << endl;
            break;
        }
        word = getRandomWord();
        current = maskWord(word);
        tries = getTries(difficulty);
        while (tries != 0) {
            cout << "Life: ";
            printAttempts(tries, difficulty);
            cout << endl << "Word: "<< current << endl;
            cout << "Enter a letter: ";
            cin >> letter;
            
            if (!revealLetter(word, letter, current)) {
                tries--;
            }
            if (current == word) {
                break;
            }
            if (tries == 2) {
                cout << "The part of speech of the word is "<< getPOS(word) << endl;
            }
            if (tries == 1) {
                cout << "Definition of the word: " << getDefinition(word) << endl;
            }
        }
        if (tries == 0) {
            cout << "The word is \"" << word << "\". Better luck next time! You're getting the ..ahem.. hang of it." << endl;
        }
        else {
            cout << "Congrats!!!" << endl;
        }
    }
}


