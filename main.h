/**
 @file
 @brief Программа для решения квадратных и линейных уравнений.
*/

/**
 @brief Отлов ошибок пользователя.
 @param [in] condition Проверяемое условие.
 @param [in] message Сообщение об ошибке.
*/
#ifdef NDEBUG
#define verify_it(condition, message) ((void)0)
#else
#define verify_it(condition, message) \
        if (!(condition)){\
        printf(MAKE_YELLOW("%s: %d")" %s\n", __FILE__, __LINE__, message);\
        abort();\
        }
#endif



