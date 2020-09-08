//
// Created by dan on 2020-09-07.
//

#include "CSVWriter.h"

CSVWriter::CSVWriter(const char *filename)
        : outFile(filename) {
    this->filename = filename;

    if (!outFile) {
        throw "could not open file";
    }
}

CSVWriter::~CSVWriter() = default;

void CSVWriter::Write(const std::vector<float>& records) {
    for (auto record : records) {
        outFile << record << '\n';
    }
    outFile.close();
    std::printf("wrote %d records to %s\n", records.size(), filename);
}
