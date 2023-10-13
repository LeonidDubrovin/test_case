#include "ProgramOne.h"
//#include "ProgramOne.h"

int main() {
    ProgramOne * poPtr = new ProgramOne();
    std::thread t1(&ProgramOne::readStringThread, poPtr);
    std::thread t2(&ProgramOne::exportStringThread, poPtr);

    t1.join();
    t2.join();

    delete poPtr;

    return EXIT_SUCCESS;
}
