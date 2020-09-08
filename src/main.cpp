#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "Document.h"
#include "CSVWriter.h"

int main(int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        std::printf("Got %d arguments, expected a filename and optionally a window size.\n", argc - 1);
        return 1;
    }
    int windowSize = 16;
    // special window size requested
    if (argc == 3) {
        windowSize = std::atoi(argv[2]);
    }
    try {
        auto inFilename = argv[1];
        Document doc(inFilename);
        doc.Parse();
        auto scores = doc.Analyze(windowSize);
        auto outFilename = std::string(inFilename);
        outFilename.append(".csv");
        const char *cstrFilename = outFilename.c_str();
        CSVWriter writer(cstrFilename);
        writer.Write(scores);
    }
    catch (const char* ex) {
        std::cout << ex;
        return 1;
    }

    return 0;
}
