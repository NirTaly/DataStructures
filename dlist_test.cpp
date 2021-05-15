#include <iostream>

#include "utils.h"
#include "wet1/dlist.h"

using std::cout;
using std::endl;

using namespace DS;

int int_arr[10] = {1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 };
const char *string_arr[5] = { "Air", "Bir", "Cir", "Dir", "Nir"};

int main(void)
{
    DList<const char*> list;
    
    TEST_INT(1, list.isEmpty(), 1, "IsEmpty when empty");
    TEST_INT(2, list.size(), 0, "Size when empty");

    list.pushAfter(&string_arr[4]);
    list.pushBefore(&string_arr[3]);
    list.pushAfter(&string_arr[2]);
    list.pushBefore(&string_arr[1]);

    TEST_INT(3, list.isEmpty(), 0, "IsEmpty when not-empty");
    TEST_INT(4, list.size(), 4, "Size when not-empty");

    list.pop();
    list.pop();
    list.pop();

    TEST_INT(5, list.size(), 1, "Size after Pops");

    list.pop();
    list.pop(); // extra pop
    
    TEST_INT(6, list.size(), 0, "Size after More Pops");
}