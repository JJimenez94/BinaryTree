#include <iostream>
#include <memory>
#include "src/Controller.h"

using namespace std;

int main(int, char **)
{
    Controller mainController;
    mainController.Start();

    cout << "Press any key to exit." << std::endl;
    string line;
    getline(cin, line);

    mainController.Stop();
}
