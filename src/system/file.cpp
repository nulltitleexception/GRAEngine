#include "file.h"

#include "log.h"

namespace GRAE {
File::File(std::string path) : myPath(path) {}

std::vector<std::string> File::getLines() {
    std::ifstream in;
    in.open(myPath);
    std::vector<std::string> lines;
    std::string line;
    if (in.good()) {
        while (std::getline(in, line)) {
            lines.push_back(line);
        }
    } else {
        log->err << "File could not be read: " << myPath;
    }
    in.close();
    return lines;
}

std::string File::getContents() {
    std::ifstream in;
    in.open(myPath);
    std::ostringstream contents;
    if (in.good()) {
        contents << in.rdbuf();
    } else {
        log->err << "File could not be read: " << myPath;
    }
    in.close();
    return contents.str();
}

char *File::getBytes() {
    std::ifstream in(myPath, std::ios::binary | std::ios::ate);
    long length = in.tellg();
    in.seekg(0, in.beg);
    char *contents = new char[length];
    in.read(contents, length);
    return contents;
}

void File::createOrOverwrite(const char *contents, long size) {
    std::ofstream out(myPath, std::ios::out | std::ios::binary);
    out.write(contents, size);
}

void File::createOrOverwrite(std::string contents) {
    std::ofstream out(myPath, std::ios::out);
    out << contents;
}

void File::append(const char *contents, long size) {
    std::ofstream out(myPath, std::ios::out | std::ios::binary | std::ios::app);
    out.write(contents, size);
}

void File::append(std::string contents) {
    std::ofstream out(myPath, std::ios::out | std::ios::app);
    out << contents;
}

bool File::getExists() {
    std::ifstream in(myPath);
    return in.good();
}
}