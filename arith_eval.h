// arith_eval.h


/*
 * Arithmetic Expression Parser
 *
 * Supported operation:
 *     +, -, *, /
 *
 * error status:
 *     1 : mismatched parenthesis
 *     2 : unrecognized operator
 *     3 : unexpected expression
 */

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// #define ARITH_TYPE (double (*)(double, double))

enum EXPECT {
    NUM = 0,
    OP  = 1,
};

union EXPR {
    double num;
    char   op;
};

typedef union EXPR EXPR;

const char ARITH_SUPPORTED[] {'+', '-', '*', '/'};

void   error_status1 (const string &expr, int &index);
void   error_status2 (const string &expr, int &index);
void   error_status3 (const string &expr, int &index);
void   bypass_space  (const string &expr, int &index);
bool   is_num        (const string &expr, int &index);
double infix_eval    (vector<EXPR>);
double parse_num     (const string &expr, int &index);
double parse_paren   (const string &expr, int &index);
double parse_expr    (const string &expr, int &index);
double eval_expr     (const string &expr);
