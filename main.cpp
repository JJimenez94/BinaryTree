#include <iostream>
#include <memory>
#include "src/BinaryTree.h"
#include "src/Controller.h"

using namespace std;

int main(int, char **)
{
    std::cout << "Hello, world!\n";

    BinaryTree test;
    test.InsertNode(5);
    test.InsertNode(4);
    test.InsertNode(9);
    test.InsertNode(12);
    test.InsertNode(15);
    test.InsertNode(27);
    test.InsertNode(30);
    test.InsertNode(35);
    test.InsertNode(26);
    cout << test.Traverse() << endl;
    test.InsertNode(20);
    test.InsertNode(18);
    test.InsertNode(31);
    cout << test.Traverse() << endl;
    cout << " ================= ANCESTORS ============================ " << endl;
    cout << "(4, 26): " << test.FindCommonAncestor(4, 26) << endl;
    cout << "(4, 9): " << test.FindCommonAncestor(4, 9) << endl;
    cout << "(4, 5): " << test.FindCommonAncestor(4, 5) << endl;
    cout << "(5, 26): " << test.FindCommonAncestor(5, 26) << endl;
    cout << "(5, 30): " << test.FindCommonAncestor(5, 30) << endl;
    cout << "(15, 35): " << test.FindCommonAncestor(15, 35) << endl;

    cout << " ================= END ANCESTORS ============================ " << endl;

    cout << " ================= PLAYING WEB ============================ " << endl;
    Controller theControl;
    theControl.Start();

    cout << "Press any key to exit." << std::endl;
    string line;
    getline(cin, line);

    theControl.Stop();
}
