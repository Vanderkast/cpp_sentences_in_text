//  main.cpp
//
// В файле хранится код на яп c++. Найти и вывести синтаксически правильные операции присваивания строковой константы. Ключевые слова записать в отдельный файл.

#include <iostream>
#include <string>
#include <vector>

#include "lib/Cursor.h"
#include "lib/Sentence.h"
#include "lib/SentenceFiller.h"

using namespace std;

#define SENTENCE_PATH "/Users/admin/Documents/GitHub/cfao/cpp_find_assignmet_operations/cpp_find_assignmet_operations/res/sentence.txt"
#define TEXT_PATH "/Users/admin/Documents/GitHub/cfao/cpp_find_assignmet_operations/cpp_find_assignmet_operations/res/text1.txt"

string inputString(string);
Sentence* fillSentence(string);

int main(int argc, const char * argv[]) {
    //Sentence* sentence = fillSentence(inputString("Enter file name with keywords: "));
    //Cursor* cursor = new FileCursor(inputString("Enter text file name: "));
    Sentence* sentence = fillSentence(SENTENCE_PATH);
    Cursor* cursor = new FileCursor(TEXT_PATH);
    SentenceFounder* founder = new SentenceFounder(sentence, cursor);
    
    vector<string> result = founder->proceed();
    cout << "\n\n";
    for(int i = 0; i < result.size(); i++)
        cout << result[i] << endl;
    
    delete sentence;
    delete cursor;
    delete founder;
    return 0;
}

string inputString(string message){
    string input;
    cout << message;
    cin >> input;
    return input;
}

Sentence* fillSentence(string fileName){
    SentenceFiller* filler = new SentenceFiller(fileName);
    Sentence* sentence = new Sentence();
    filler->fill(sentence);
    delete filler;
    return sentence;
}
