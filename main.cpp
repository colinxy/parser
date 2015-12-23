// main.cpp


#include <iostream>
#include <string>
#include "arith_eval.h"


int main() {
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
