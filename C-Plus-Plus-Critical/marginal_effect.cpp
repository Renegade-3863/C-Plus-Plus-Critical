#include "marginal_effect.h"

void Testing_MGNL() {

    float ans = MGNL / 2;
    std::cout << "We are trying to do something like dividing MGNL by 2\n\n";
    std::cout << "If should be equal to 2.5, but it actually is: " << ans << std::endl << std::endl;
    std::cout << "We believe the problem lies in this is that MGNL is simply replaced by 3+2\n\n";
    std::cout << "Then the expression we used for MGNL / 2 is actually 3 + 2 / 2, which results in 4\n\n";
    
}

void Testing_MIN() {

    int num1 = 2, num2 = 3, b = 10;
    std::cout << "In Testing_MIN(), we try to get the expression of the following expression:\n\n";
    std::cout << "printf(\"%d\\n\", b + MIN(num1,num2));\n\n";
    std::cout << "While num1 = 2, num2 = 3, b = 10\n\n";
    std::cout << "The result turns out to be: " << (b + MIN(num1, num2)) << std::endl << std::endl;
    std::cout << "Which is totally incorrect.\n\n";
    std::cout << "We believe this is because we are actually calculating b + num1 < num2 ? num1 : num2\n\n";
    std::cout << "The result to this expression is definitely the smaller one between num1 and num2, but we treated b as nonsense!!\n\n";
    
}