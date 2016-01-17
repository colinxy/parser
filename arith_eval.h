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

#include <string>
#include <vector>
#include <cctype>

// #define ARITH_TYPE (double (*)(double, double))

enum TOKEN {
    NUM = 0,
    OP  = 1,
};

union EXPR {
    double num;
    char   op;
};

typedef union EXPR EXPR;

const char ARITH_SUPPORTED[] {'+', '-', '*', '/'};

  // error analysis
void   error_status1 (const std::string &expr, int &index);
void   error_status2 (const std::string &expr, int &index);
void   error_status3 (const std::string &expr, int &index);

  // untility functions
inline bool arith_supported(char arith) {
    for (int i = 0; i < sizeof(ARITH_SUPPORTED); ++i)
        if (arith == ARITH_SUPPORTED[i])
            return true;

    return false;
}

inline void bypass_space(const std::string &expr, int &index) {
    while (index < expr.size() && isspace(expr[index]))
        ++index;
}

inline bool is_num(const std::string &expr, int &index) {
    return isdigit(expr[index]) ||
           expr[index] == '-'   ||
           expr[index] == '+'   ||
           expr[index] == '.';
}

  // parser
double infix_eval    (std::vector<EXPR>);
double parse_num     (const std::string &expr, int &index);
double parse_paren   (const std::string &expr, int &index);
double parse_expr    (const std::string &expr, int &index);
double eval_expr     (const std::string &expr);
