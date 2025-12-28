#include "statemachine_template.h"
#include <iostream>

int main() {
    StateMachine sm;
    sm.run();

    std::cout << "END reached" << std::endl;
    return 0;
}
