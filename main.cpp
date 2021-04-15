#include "brainfry.hpp"

using namespace std;

int main() {
    string code;
    getline(cin, code, '\0');
    BrainFry brainfry;

    brainfry.parse(code, cin, cout);
    return 0;
}
