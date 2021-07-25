#include "parser.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
    std::vector<Slime::Slarray> v{0x41, 0x42, 0x43};
    Slime::Slarray data(v);
    std::cout << data.PrettyPrint() << std::endl;
}
