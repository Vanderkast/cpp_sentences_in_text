#include <string>
#include <fstream>
#include <iostream>

#include "../lib/SentenceFiller.h"

SentenceFiller::SentenceFiller(std::string file){
    this->stream.open(file);
}

SentenceFiller::~SentenceFiller(){
    if(stream.is_open())
        stream.close();
}

void SentenceFiller::fill(Sentence* sentence){
    std::vector<std::string> words;
    std::string s;
    while (std::getline(stream, s)) {
        words.push_back(s);
    }
    sentence->setWords(words);
}
