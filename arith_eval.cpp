// arith_eval.cpp


#include <iostream>
#include "arith_eval.h"
using namespace std;


void error_status1(const string &expr, int &index) {
    cerr << "mismatched parenthesis at index " << index << endl;
    cerr << expr.substr(1, expr.size()-2) << endl;
    cerr << string(index-1, '~') << '^' << endl;
}

void error_status2(const string &expr, int &index) {
    cerr << "unrecognized operator at index " << index << endl;
    cerr << expr.substr(1, expr.size()-2) << endl;
    cerr << string(index-1, '~') << '^' << endl;
}

void error_status3(const string &expr, int &index) {
    cerr << "unexpected expression at index " << index << endl;
    cerr << expr.substr(1, expr.size()-2) << endl;
    cerr << string(index-1, '~') << '^' << endl;
}

inline bool arith_supported(char arith) {
    for (int i = 0; i < sizeof(ARITH_SUPPORTED); ++i)
        if (arith == ARITH_SUPPORTED[i])
            return true;

    return false;
}

inline void bypass_space(const string &expr, int &index) {
    while (index < expr.size() && isspace(expr[index]))
        ++index;
}

bool is_num(const string &expr, int &index) {
    return isdigit(expr[index]) ||
           expr[index] == '-' ||
           expr[index] == '+' ||
           expr[index] == '.';
}

// flat infix expression evaluation
double infix_eval(vector<EXPR> exprs) {
    // first level operator: *, /
    for (int i = 1; i < exprs.size(); i+=2) {
        if (exprs[i].op == '*') {
            exprs[i-1].num *= exprs[i+1].num;
            // erase the operator
            exprs.erase(exprs.begin()+i);
            // erase the latter operand
            exprs.erase(exprs.begin()+i);

            i -= 2;
        } else if (exprs[i].op == '/') {
            exprs[i-1].num /= exprs[i+1].num;
            // erase the operator
            exprs.erase(exprs.begin()+i);
            // erase the latter operand
            exprs.erase(exprs.begin()+i);

            i -= 2;
        }
    }

    double result = exprs[0].num;
    // second level operator: +, -
    for (int i = 1; i < exprs.size(); i+=2) {
        if (exprs[i].op == '+') {
            result += exprs[i+1].num;
        } else if (exprs[i].op == '-') {
            result -= exprs[i+1].num;
        }
    }

    return result;
}

double parse_num(const string &expr, int &index) {
    bypass_space(expr, index);

    int sign = 1;
    int integer = 0;
    int decimal = 0;
    int decimal_offby = 1;

    // deal with potential sign
    if (expr[index] == '-') {
        sign = -1;
        ++index;
    } else if (expr[index] == '+') {
        ++index;
    }

    char c;

    // before the . sign
    while (isdigit(c = expr[index])) {
        integer = integer * 10 + c - '0';
        ++index;
    }

    if (expr[index] != '.')
        return sign * integer;
    else // expr[index] == '.'
        ++index;

    // after the . sign
    while (isdigit(c = expr[index])) {
        decimal = decimal * 10 + c - '0';
        decimal_offby *= 10;
        ++index;
    }

    return sign * (integer + (double)decimal / decimal_offby);
}

double parse_paren(const string &expr, int &index) {
    bypass_space(expr, ++index);

    EXPECT expected = EXPECT::NUM;

    vector<EXPR> expressions;

    while (index < expr.size()) {
        if (expr[index] == ')') {
            ++index;
            return infix_eval(expressions);
        }

        if (expected == EXPECT::OP) {
            if (arith_supported(expr[index])) {
                // operator
                EXPR op = {.op = expr[index]};
                expressions.push_back(op);

                ++index;

                // number
                EXPR num = {.num = parse_expr(expr, index)};
                expressions.push_back(num);
            } else {
                // unrecognized operator
                error_status2(expr, index);
                throw 2;
            }

        } else if (expected == EXPECT::NUM) {
            EXPR num;
            num.num = parse_expr(expr, index);
            expressions.push_back(num);

            expected = EXPECT::OP;
        }

        bypass_space(expr, index);
    }

    // mismatched parenthesis
    error_status1(expr, index);
    throw 1;
}

double parse_expr(const string &expr, int &index) {
    bypass_space(expr, index);

    double value;

    if (expr[index] == '(') {
        value = parse_paren(expr, index);
    } else if (is_num(expr, index)) {
        value = parse_num(expr, index);
    } else {
        // unexpected expression
        error_status3(expr, index);
        throw 3;
    }

    return value;
}

double eval_expr(const string &expr) {
    int index = 0;

    double result = parse_expr(expr, index);
    if (index != expr.size()) {
        // mismatched parenthesis
        error_status1(expr, index);
        throw 1;
    }

    return result;
}
