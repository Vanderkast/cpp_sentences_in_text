#include <string>
#include <vector>

#include "Word.h"
#include "Cursor.h"

#ifndef Sentence_h
#define Sentence_h

class Sentence {
private:
    std::vector<std::string> words;
    int current;
    
public:
    Sentence();
    
    void setWords(std::vector<std::string> words);
    
    Word* next();
    void reset();

};

class SentenceFounder {
private:
    Sentence* sentence;
    Cursor* cursor;

public:
    SentenceFounder(Sentence*, Cursor*);
    
    std::vector<std::string> proceed();
};

#endif
