#define ZERO 0
#define ONE 1
#define TWO 2
#define INF 200
#define ERROR 404
#define EPS 1e-9

#define verify_it(condition, message) \
    if(!(condition)){\
        printf(message);\
        abort();\
    }\

int solve_quadratic_equations (const double, const double, const double, double*, double*);
int is_zero (double);
double find_disc (const double, const double, const double);
void print_root (double, double, int);
int solve_linear (const double, const double, double*);
int solve_square (const double, const double, const double, double*, double*);
