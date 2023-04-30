/*
 * test the implemented truing machine using programming language.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

bool isPerfectSquare(int num)
{
    int x = (int)sqrt(num);
    return x * x == num;
}

int main()
{
    string str = "1";
    string test = "./turing ../programs/case2new.tm ";
    string ans;
    int n = 100000;
    for (int i = 0; i < n; i++)
    {
        test += str + " > a.txt";
        int ret = system("test");
        if (!ret)
        {
            cout << "run error" << endl;
            return -1;
        }
        fstream input("a.txt", ios::in);
        if (!input)
        {
            cout << "open failed" << endl;
            return 1;
        }
        input >> ans;
        bool result = isPerfectSquare(str.size());
        if (ans == "true" && !result)
        {
            cout << "error " << str << endl;
            break;
        }
        else if (ans == "false" && result)
        {
            cout << "error " << str << endl;
            break;
        }
        else
            cout << "success " << str << endl;
        str += '1';
    }
}
