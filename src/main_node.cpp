#include "readPcd.h"

#define test_1

void test(){
#ifdef test_1
    readPcd rP;
    rP.run();
    //rP.print_debug();
#endif
}

int main(){

    test();

}