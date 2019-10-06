#include <fstream>
#include <string>

#ifndef Cursor_h
#define Cursor_h

class Cursor {
public:
    static const char END = '\0';
    
    virtual char current() { return END; }
    
    virtual void forward() {}
};

class FileCursor : public Cursor {
private:
    std::ifstream file;
    char cur;

public:
    FileCursor(std::string);
    ~FileCursor();

    char current();
    
    void forward();
};

#endif
