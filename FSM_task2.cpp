#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include "init.h"

using namespace std;

void printOutput(ofstream& output, string type, string str, set<string>& keywords) {
    str.pop_back();
    if (type == "iden") {
        type = keywords.count(str) ? "keyword" : type;
    }
    output << "< " << type << ", " << '"' << str << '"' << " >" << endl;
}

void lexer(vector<FSM>& fsms) {
    ifstream input("input.txt");
    ofstream output("output.txt");
    streampos prevSymbPos = 0;
    char ch;

    string lexem = "";
    set<string> keywords = initKeywords();
    
    bool allDone;
    bool canMove;
    bool haveAnswer;

    vector<bool> isNotDone;

    for (int i = 0; i < fsms.size(); i++) {
        isNotDone.push_back(true);
    }

    for (input.get(ch); !input.eof(); input.get(ch)) {
        lexem += ch;
        allDone = true;
        haveAnswer = false;
        for (int i = 0; i < fsms.size(); i++) {
            if (isNotDone[i]) {
                canMove = fsms[i].nextState(ch);
                allDone = allDone && !canMove;
                if (!canMove) {
                    isNotDone[i] = false;
                }
            }
        }
        if (allDone) {
            for (int i = 0; i < fsms.size(); i++) {
                if (fsms[i].isFinal()) {
                    printOutput(output, fsms[i].getType(), lexem, keywords);
                    haveAnswer = true;
                    break;
                }
            }
            for (int i = 0; i < fsms.size(); i++) {
                isNotDone[i] = true;
                fsms[i].reset();
            }
            lexem = "";
            if (haveAnswer) {
                input.seekg(prevSymbPos);
            }
        }
        prevSymbPos = input.tellg();
    }

    input.close();
    output.close();
}

int main()
{
    vector<FSM> FSMs = initFSMs();
    lexer(FSMs);
}