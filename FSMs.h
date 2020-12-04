#pragma once
#include "FSM.h"

using namespace std;

vector<FSM> initFSM() {
    vector<FSM> fsms;

    FSM NUMBER;
    NUMBER.setType("literal");
    NUMBER.newFinalState("int");
    NUMBER.newFinalState("float");
    NUMBER.newFinalState("floatE+");
    NUMBER.newFinalState("floatE-");
    for (char c = '0'; c <= '9'; c++) {
        NUMBER.newState("start", c, "int");
        NUMBER.newState("int", c, "int");
        NUMBER.newState("intToFloat", c, "float");
        NUMBER.newState("float", c, "float");
        NUMBER.newState("floatE+", c, "floatE+");
        NUMBER.newState("floatE-", c, "floatE-");
        NUMBER.newState("numToE", c, "floatE+");
        NUMBER.newState("eToMinus", c, "floatE-");
    }
    NUMBER.newState("int", '.', "intToFloat");
    NUMBER.newState("int", 'e', "numToE");
    NUMBER.newState("numToE", '+', "floatE+");
    NUMBER.newState("numToE", '-', "eToMinus");
    NUMBER.newState("intToFloat", 'e', "numToE");
    NUMBER.newState("float", 'e', "numToE");
    fsms.push_back(NUMBER);

    FSM IDEN;
    IDEN.setType("iden");
    IDEN.newFinalState("iden");
    for (char c = 'a'; c <= 'z'; c++) {
        IDEN.newState("iden", c, "iden");
        IDEN.newState("start", c, "iden");
    }
    for (char c = '0'; c <= '9'; c++) {
        IDEN.newState("iden", c, "iden");
    }
    IDEN.newState("iden", '_', "iden");
    IDEN.newState("start", '_', "iden");
    fsms.push_back(IDEN);

    FSM OPERATOR;
    OPERATOR.setType("operator");
    set<string> operators = {
                            "=",
                            ">",
                            "<",
                            "&&",
                            "&",
                            "!",
                            "-",
                            "+",
                            "<=",
                            ">=",
                            "==",
                            "!=",
                            "+=",
                            "-=",
                            "*=",
                            "/=",
                            "*",
                            "/" };
    set<char> singleOperators = {
                            '=',
                            '>',
                            '<',
                            '&',
                            '!',
                            '-',
                            '+',
                            '*',
                            '/' };
    for (string op : operators) {
        OPERATOR.newFinalState(op);
    }
    for (char op : singleOperators) {
        OPERATOR.newState("start", op, string(1, op));
    }
    OPERATOR.newState("<", '=', "<=");
    OPERATOR.newState(">", '=', ">=");
    OPERATOR.newState("=", '=', "==");
    OPERATOR.newState("&", '&', "&&");
    OPERATOR.newState("*", '=', "*=");
    OPERATOR.newState("+", '=', "+=");
    OPERATOR.newState("-", '=', "-=");
    OPERATOR.newState("/", '=', "/=");
    OPERATOR.newState("!", '=', "!=");
    OPERATOR.newFinalState("{");
    OPERATOR.newFinalState("}");
    OPERATOR.newState("start", '{', "{");
    OPERATOR.newState("start", '}', "}");
    OPERATOR.newFinalState("(");
    OPERATOR.newFinalState(")");
    OPERATOR.newState("start", '(', "(");
    OPERATOR.newState("start", ')', ")");
    fsms.push_back(OPERATOR);

    FSM SEMICOLON;
    SEMICOLON.setType("semicolon");
    SEMICOLON.newFinalState(";");
    SEMICOLON.newState("start", ';', ";");
    fsms.push_back(SEMICOLON);

    return fsms;
}

set<string> initKeywords() {
    set<string> types;
    types.insert("while");
    types.insert("if");
    types.insert("break");
    types.insert("false");
    types.insert("true");
    types.insert("int");
    types.insert("boolean");
    types.insert("double");
    return types;
}