#pragma once

using namespace std;

class FSM {
    private:
        string initialState;
        string currentState;
        string type;
        set<string> finalStates;
        map<pair<string, char>, string> setState;
    public:
        FSM() {
            initialState = "start";
            currentState = initialState;
        }

        void newFinalState(string state) {
            finalStates.insert(state);
        }

        void newState(string from, char with, string to) {
            setState[make_pair(from, with)] = to;
        }

        void setType(string t) {
            type = t;
        }

        bool nextState(char symbol) {
            if (!setState.count(make_pair(currentState, symbol))) {
                return false;
            }
            else {
                currentState = setState[make_pair(currentState, symbol)];
                return true;
            }
        }

        string getState() {
            return currentState;
        }

        string getType() {
            return type;
        }

        bool isFinal() {
            return finalStates.count(currentState);
        }

        void reset() {
            currentState = initialState;
        }
};