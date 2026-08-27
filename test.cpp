#include <stdio.h>
#include <assert.h>


int main() {
    char buf[23];
    int num = 42, r = 230;

    int len = snprintf(buf, sizeof(buf), "%d", num);
    printf("%s\n", buf);
    snprintf(buf, sizeof(buf), "%d", r);
    printf("%s\n", buf);
    printf("%d\n", len);

    return 0;
}




