#pragma once

#include <stack>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class BrainFry {
    public:
        BrainFry() {
            dataTape = {0};
            dataPtr = dataTape.begin();
            MAX = numeric_limits<uint8_t>::max();
        }

        void parse(const string &codeTape, istream &inStream, ostream &outStream) {
            codePtr = codeTape.begin();
            while(codePtr != codeTape.end()) {
                switch(*codePtr) {
                    case '>': incPtr();             break;
                    case '<': decPtr();             break;
                    case '+': incVal();             break;
                    case '-': decVal();             break;
                    case ',': getVal(inStream);     break;
                    case '.': putVal(outStream);    break;
                    case '[': openBrac(codeTape);   break;
                    case ']': closeBrac();          break;
                }
                codePtr++;
            }
        }

        void reset() {
            dataTape.clear();
            dataTape = {0};
            dataPtr = dataTape.begin();

            while (not codeStack.empty())
                codeStack.pop();
        }

    private:
        vector<uint8_t> dataTape; 
        vector<uint8_t>::iterator dataPtr;
        uint8_t MAX;

        /*
         *  The type uint8_t is used since characters in C++ are inherently unsigned integers. 
         *  This reason is that each numeric value corresponds to a character
         *  in ASCII table and using uint8_t provides and easier reprsentation of data when manipulated.
         */

        string::const_iterator codePtr;
        stack<string::const_iterator> codeStack;
 
        void incPtr() {
            dataPtr++;

            if (dataPtr == dataTape.end()) {
                dataTape.push_back(0);
                dataPtr = dataTape.end() - 1;
            }
        }

        void decPtr() {
            if (dataPtr != dataTape.begin())
                dataPtr--;
        }

        void incVal() {
            *dataPtr = (*dataPtr == MAX) ? MAX : *dataPtr + 1;
        }

        void decVal() {
            *dataPtr = (*dataPtr == 0) ? 0 : *dataPtr - 1;
        }

        void getVal(istream &inStream) {
            char input;
            inStream >> input;
            *dataPtr = input;
        }

        void putVal(ostream &outStream) {
            outStream << char(*dataPtr);
        }

        void openBrac(const string &codeTape) {
            codeStack.push(codePtr);
            
            if (*dataPtr == 0) {
                auto startPtr = codePtr;
                while(++codePtr != codeTape.end()) {
                    if (*codePtr == '[')
                        codeStack.push(codePtr);
                    if (*codePtr == ']') {

                        if (codeStack.empty())
                            throw runtime_error("Found a ']' that did not have a matching '['!");
                        auto tmpPtr = codeStack.top();
                        codeStack.pop();

                        if (tmpPtr == startPtr)
                            break;
                    }
                }
            }
        }

        void closeBrac() {
            if (codeStack.empty())
                throw runtime_error("Found a ']' that did not have a matching '['!");
            if (*dataPtr != 0)
                codePtr = codeStack.top();
            else
                codeStack.pop();
        }
};
