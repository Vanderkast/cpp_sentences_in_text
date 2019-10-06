#include <string>
#include <fstream>

#include "Sentence.h"

class SentenceFiller {
private:
    std::ifstream stream;
    
public:
    SentenceFiller(std::string);
    ~SentenceFiller();
    
    void fill(Sentence*);
};
