#include <stdio.h>
#include <assert.h>

#define verify_it(condition, message)\
        if(!(condition)){
            printf(stderr, "file: %s, lint: %d, fall: %s", __FILE__, __LINE__, message);
        }
int main(){
    assert(0 && "hi");
}



