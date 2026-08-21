/**
 @file
 @brief Программа для решения квадратных и линейных уравнений.
 @details Включает считывание коэффициентов с клавиатуры, очистку буфера ввода,
 вычисление дискриминанта и обработку всех частных случаев (включая равенство нулю).
*/

/**
 @brief Константа для сравнения чисел с плавающей точкой с нулем.
*/
#define EPS 1e-9

/**
 @brief Отлов ошибок пользователя.
 @param [in] condition Проверяемое условие.
 @param [in] message Сообщение об ошибке.
*/
#define verify_it(condition, message) \
    if(!(condition)){\
        printf(message);\
        abort();\
    }\

/**
 @brief Перечисление статусов и количество корней уравнения.
*/
typedef enum {
    ZERO = 0,    ///< Уравнение не имеет решений.
    ONE = 1,     ///< Уравнение имеет 1 решение.
    TWO = 2,     ///< Уравнение имеет 2 решения.
    INF = 200,   ///< Уравнение имеет бесконечное кол-во корней.
    ERROR = 404, ///< Деление на 0.
} roots;

/**
 @brief Главная функция-диспетчер для решения квадратного уравнения
 @param [in] a Коэффициент при x^2.
 @param [in] b Коэффициент при x.
 @param [in] c Свободный член.
 @param [out] x1 Указатель для записи первого корня.
 @param [out] x2 Указатель для записи второго корня.
 @return Статус решения из перечисления #roots.

 Пример того, как использовать функцию
 @code
    int main() {
        double a = 0.0, b = 0.0, c = 0.0;
        double x1 = 0, x2 = 0;
        roots nRoot = solve_quadratic_equations (a, b, c, &x1, &x2);
    }
 @endcode
*/
roots solve_quadratic_equations (const double a, const double b, const double c, double* x1, double* x2);

/**
 @brief Функция для решения уравнений линейного вида.
 @param [in] b Коэффициент при x.
 @param [in] c Свободный член.
 @param [out] x1 Указатель для записи первого корня.
 @return Статус решения из перечисления #roots (INF, ERROR, ONE).
*/
roots solve_linear (const double b, const double c, double* x1);

/**
 @brief Функция для решения уравнений квадратного вида.
 @param [in] a Коэффициент при x^2.
 @param [in] b Коэффициент при x.
 @param [in] c Свободный член.
 @param [out] x1 Указатель для записи первого корня.
 @param [out] x2 Указатель для записи второго корня.
 @return Статус решения из перечисления #roots (ZERO, ONE, TWO).
*/
roots solve_square (const double a, const double b, const double c, double* x1, double* x2);

/**
 @brief Проверяет равно ли число 0 с учетом погрешности EPS
 @param [in] val Проверяемое значение.
 @return true если число близко к 0, иначе false.
*/
bool is_zero (const double val);

/**
 @brief Подсчитывает дискриминант квадратного уравнения.
 @param [in] a Коэффициент при x^2.
 @param [in] b Коэффициент при x.
 @param [in] c Свободный член.
 @return дискриминант данного уравнения.
*/
double find_discriminant (const double a, const double b, const double c);

/**
 @brief Выводит результат работы программы, с учетом кол-ва корней.
 @param [in] x1 Первый корень уравнения.
 @param [in] x2 Второй корень уравнения.
 @param [in] nRoot Кол-во корней.
*/
void print_root (const double x1, const double x2, const roots nRoot);

/**
 @brief Очищает поле ввода если пользователь ввел мусор.
*/
void clear_the_buffer ();

/**
 @brief Ввод коэффициентов уравнения.
 @param [in] a Указатель на коэффициент при x^2.
 @param [in] b Указатель на коэффициент при x.
 @param [in] c Указатель на свободный член.
 @param [out] scanCount кол-во правильно считанных переменных.
*/
void scanСoefficient (double* a, double* b, double* c, int* scanCount);
