// Dan Wolf
// CSVWriter.h

#include <fstream>
#include <vector>

#ifndef CONVOLUTION_CSVWRITER_H
#define CONVOLUTION_CSVWRITER_H


class CSVWriter {
private:
    const char *filename;
    std::ofstream outFile;
public:
    explicit CSVWriter(const char *filename);

    ~CSVWriter();

    void Write(const std::vector<float>& records);
};


#endif //CONVOLUTION_CSVWRITER_H
