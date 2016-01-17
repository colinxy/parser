// main.cpp


#include <iostream>
#include <string>
#include "arith_eval.h"

using namespace std;


int main(int argc, char *argv[]) {
    if (argc == 2) {
        string expr(argv[1]);
        expr = '(' + expr + ')';

        try {
            cout << eval_expr(expr) << endl;
        } catch (int error_status) {
        }

        return 0;
    }

    while (true) {
        cout << ">>> ";

        string expr;
        getline(cin, expr);
        if (expr == "" || expr == "q") break;

        expr = '(' + expr + ')';
        // cout << expr << endl;

        try {
            cout << eval_expr(expr) << endl;
        } catch(int error_status) {
        }
    }

    return 0;
}
