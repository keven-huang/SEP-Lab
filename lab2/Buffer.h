#pragma once

#include <string>

using std::string;

class Buffer {
private:
    int currentLineNum;
    // TODO: add a List here for storing the input lines
    struct node{
        string data;
        node *next;
    };
    node *head; 

public:
    int CurrentLen;
    Buffer();
    ~Buffer();

    void writeToFile(const string &filename) const;

    const string &moveToLine(int idx) ;

    void showLines(int from, int to);

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);

};
