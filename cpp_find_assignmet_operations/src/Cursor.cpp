#include <string>
#include <fstream>

#include "../lib/Cursor.h"

FileCursor::FileCursor(std::string fileName){
    this->file.open(fileName, std::fstream::in);
    noskipws(this->file);
    if(!this->file.is_open())
        throw "file was not opened";
    this->forward();
}

FileCursor::~FileCursor(){
    if(this->file.is_open())
        this->file.close();
}

char FileCursor::current(){
    return this->cur;
}

void FileCursor::forward(){
    if(this->file.eof())
        this->cur = END;
    else
        this->file >> this->cur;
}
