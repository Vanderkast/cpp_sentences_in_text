#include <stdio.h>
#include <string>

#include "../lib/Word.h"

Word* WordFactory::get(std::string input){
    if(input.empty())
        throw "Empty input does not allowed";
    if(input[0] == '%'){
        if(input[1] == 'v'){
            return new VarNameWord();
        }
        if(input[1] == 's')
            return new StringInputWord();
    }
    return new ConstWord(input);
}

VarNameWord::VarNameWord() {
    this->state = IN_PROCESS;
}

bool isWordBreaker(char symbol){
    return symbol == ' ' || symbol == '\t' || symbol == '\n';
}

void VarNameWord::addSymbol(char symbol){
    bool wordBreaker = isWordBreaker(symbol);
    if(wordBreaker){
        if(this->word.empty())
            this->state = ERROR;
        else
            this->state = DONE;
    }
    else
        this->word += symbol;
}

StringInputWord::StringInputWord(){
    this->state = IN_PROCESS;
}

void StringInputWord::addSymbol(char symbol){
    if(this->word.empty()){
        if(symbol != '"')
            this->state = ERROR;
    } else {
        if(symbol == '"')
            this->state = DONE;
    }
    this->word += symbol;
}

ConstWord::ConstWord(std::string word){
    this->word = word;
    this->pos = 0;
    this->state = IN_PROCESS;
}

void handleEndOfConstWord(int& pos, long wordLength, WordState& state){
    if(wordLength - 1 == pos)
        state = DONE;
    else ++pos;
}

void ConstWord::addSymbol(char symbol){
    if(word[pos] == '_' && isWordBreaker(symbol)){
        word[pos] = ' ';
        handleEndOfConstWord(pos, word.length(), state);
        return;
    }
    if(word[pos] == symbol)
        handleEndOfConstWord(pos, word.length(), state);
    else
        this->state = ERROR;
}

