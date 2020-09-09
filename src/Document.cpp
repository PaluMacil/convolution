// Dan Wolf
// Document.cpp

#include <set>
#include <cctype>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "Document.h"

Document::Document(char *filename)
        : inFile(filename, std::ifstream::binary) {
    this->filename = filename;

    if (!inFile) {
        throw "could not open file";
    }
}

Document::~Document() {

}

void Document::Parse() {
    // stores whether currently in a word
    bool inWord = false;
    std::ostringstream currentWord;
    char currentChar;
    // iterate through chars
    while (!inFile.eof()) {
        inFile.get(currentChar);
        // if this char is a letter, you're in a word
        if (std::isalpha(currentChar)) {
            inWord = true;
            // send lowercase of the current letter to the current word stream
            currentChar = std::tolower(currentChar);
            currentWord << currentChar;
        } else if (inWord) {
            // you're no longer in a word since this wasn't a letter, so change state
            inWord = false;
            // add the current word to words and clear the stream for reuse
            words.push_back(currentWord.str());
            currentWord.str("");
            currentWord.clear();
        }
    }
    // if file ended while building a word, add it to words
    if (inWord) {
        words.push_back(currentWord.str());
    }

    std::printf("parsed %zu words from %s\n", words.size(), filename);
}

std::vector<float> Document::Analyze(int windowSize) {
    std::vector<float> scores;
    int maxWindow = words.size() - windowSize + 1;
    // uniqueWords is a set of each string in the examined window
    // it is cleared after score is calculated
    std::set<std::string> uniqueWords;
    // for every window being examined
    for (int win = 0; win < maxWindow; win++) {
        // for every word in window, go from start index of window to end of window
        for (int i = win; i < win + windowSize; i++) {
            uniqueWords.insert(words[i]);
        }
        // calculate and save score
        scores.push_back(float(uniqueWords.size())/float(windowSize));
        // reset the word set for the next window
        uniqueWords.clear();
    }
    std::set<std::string> globalUniqueWords(words.begin(), words.end());
    auto total = float(globalUniqueWords.size()) / words.size();
    auto average = std::accumulate(scores.begin(), scores.end(), 0.0) / scores.size();
    auto min = *std::min_element(scores.begin(), scores.end());
    auto max = *std::max_element(scores.begin(), scores.end());
    std::printf("complexity summary:\ntotal: %.4f\taverage: %.4f\tmin: %.4f\tmax: %.4f\n",
                total, average, min, max);

    return scores;
}

