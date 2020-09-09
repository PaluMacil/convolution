// Dan Wolf
// Document.h

#include <fstream>
#include <vector>
#include <map>

#ifndef CONVOLUTION_DOCUMENT_H
#define CONVOLUTION_DOCUMENT_H

class Document {
private:
    char * filename;
    std::ifstream inFile;
    std::vector<std::string> words;
public:
    explicit Document(char * filename);
    ~Document();

    // Parses a document and saves cleaned words
    void Parse();

    // analyzes windows of given size and returns a vector of scores
    std::vector<float> Analyze(int windowSize);
};


#endif //CONVOLUTION_DOCUMENT_H
