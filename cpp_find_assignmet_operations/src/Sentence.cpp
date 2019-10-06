#include <string>

#include "../lib/Sentence.h"
#include "../lib/Word.h"

Sentence::Sentence(){
    current = 0;
}

void Sentence::setWords(std::vector<std::string> words){
    for(int i = 0; i < words.size(); i++)
        this->words.push_back(words[i]);
}

Word* Sentence::next(){
     if(current >= this->words.size())
         return NULL;
     return WordFactory().get(this->words.at(this->current++));
}

void Sentence::reset(){
    this->current = 0;
}

SentenceFounder::SentenceFounder(Sentence* sentence, Cursor* cursor){
    this->sentence = sentence;
    this->cursor = cursor;
}

class ErrorInWord {};
class EndOfFile {};

std::string completeSentence(Sentence* sentence, Cursor* cursor);
std::string completeWord(Word*, Cursor*);

void skipSpaces(Cursor*);

std::vector<std::string> SentenceFounder::proceed(){
    std::vector<std::string> result;
    std::string s;
    
    try {
        while (true) {
            s = completeSentence(sentence, cursor);
            result.push_back(s);
        }
    } catch(EndOfFile _) {}
    
    return result;
}

std::string completeSentence(Sentence* sentence, Cursor* cursor){
    Word* word;
    std::string filledWord;
    std::string readSentence;
    while((word = sentence->next()) != NULL){
        try {
            filledWord = completeWord(word, cursor);
            skipSpaces(cursor);
            readSentence.append(filledWord);
        } catch (ErrorInWord _){
            sentence->reset();
        } catch (EndOfFile e){
            sentence->reset();
            delete word;
            throw e;
        }
        delete word;
    }
    sentence->reset();
    return readSentence;
}

std::string completeWord(Word* word, Cursor* cursor){
    while(cursor->current() != Cursor::END){
        word->addSymbol(cursor->current());
        cursor->forward();
        if(word->getState() == WordState::ERROR)
            throw ErrorInWord();
        if(word->getState() == WordState::DONE)
            return word->toString();
    }
    throw EndOfFile();
    return NULL;
}

void skipSpaces(Cursor* cursor) {
    char cur = cursor->current();
    while (cur == ' ' || cur == '\t' || cur == '\n') {
        cursor->forward();
        cur = cursor->current();
    }
}
