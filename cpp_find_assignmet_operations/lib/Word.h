#include <stdio.h>
#include <string>

#ifndef Word_h
#define Word_h

class Word;
class VarNameWord;
class StringInputWord;
class ConstWord;

class WordFactory {
public:
    Word* get(std::string);
};

enum WordState {
    DONE, IN_PROCESS, ERROR
};

class Word {
protected:
    WordState state;
    std::string word;
    
    Word() {}
    
public:
    virtual void create(std::string) {}
    virtual void addSymbol(char symbol) {}
    virtual WordState getState() { return this->state; }
    virtual std::string toString() { return this->word; }
    virtual bool needSpaces() { return false; }
};

class VarNameWord : public Word {
public:
    VarNameWord();
    void addSymbol(char symbol);
};

class StringInputWord : public Word {
public:
    StringInputWord();
    void addSymbol(char symbol);
};

class ConstWord : public Word {
private:
    int pos;
    
public:
    ConstWord(std::string);
    void addSymbol(char symbol);
};

#endif
