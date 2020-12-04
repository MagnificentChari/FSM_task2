#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include "FSMs.h"

using namespace std;

void printOutput(ofstream& output, string lexem, string str, set<string> keywords) {
    str.pop_back();
    if (lexem == "iden") {
        lexem = keywords.count(str) ? "keyword" : lexem;
    }
    output << "< " << lexem << ", " << '"' << str << '"' << " >" << endl;
}

void lexer(vector<FSM> fsms) {
    ifstream input("input.txt");
    ofstream output("output.txt");
    string lexem = "";
    char ch;
    bool allDone;
    bool canMove;
    streampos prevSymbPos = 0;

    vector<bool> isNotDone;
    vector<FSM> answers;
    vector<int> rounds;
    for (FSM fsm : fsms) {
        isNotDone.push_back(true);
        rounds.push_back(0);
    }

    for (input.get(ch); !input.eof(); input.get(ch))
    {
        set<string> keywords = initKeywords();
        lexem += ch;
        allDone = true;
        for (int i = 0; i < fsms.size(); i++) {
            if (isNotDone[i]) {
                canMove = fsms[i].nextState(ch);
                allDone = allDone && !canMove;
                if (!canMove) {
                    isNotDone[i] = false;
                }
                else {
                    rounds[i] += 1;
                }
            }
        }
        if (allDone) {
            for (int i = 0; i < fsms.size(); i++) {
                if ((fsms[i].isFinal()) && (rounds[i] == lexem.size() - 1)) {
                    answers.push_back(fsms[i]);
                }
            }

            for (FSM answer : answers) {
                printOutput(output, answer.getType(), lexem, keywords);
            }

            for (int i = 0; i < fsms.size(); i++) {
                isNotDone[i] = true;
                fsms[i].reset();
                rounds[i] = 0;
            }

            lexem = "";
            if (!answers.empty()) {
                input.seekg(prevSymbPos);
            }
            answers.clear();
        }
        prevSymbPos = input.tellg();
    }

    input.close();
    output.close();
}


int main()
{
    setlocale(LC_ALL, "rus");

    vector<FSM> FSMs = initFSM();
    lexer(FSMs);
}