#include <iostream>

#include <chrono>
#include "CubicBezier.h"

using namespace std;

int main() {
    CubicBezier cb1{{-200, -200},
                    {400,  200},
                    {-400, 200},
                    {200,  -200}};
    CubicBezier cb2{{-200, 200},
                    {400,  -200},
                    {-400, -200},
                    {200,  200}};

    chrono::milliseconds start = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch());

    for (int i = 0; i < 1e3; ++i) {
        cb1.intersect(cb2);
    }

    chrono::milliseconds end = chrono::duration_cast<chrono::milliseconds>(
            chrono::system_clock::now().time_since_epoch());

    cout << (end - start).count() << endl;
    cout << cb1.intersect(cb2).length();
    cin.get();
    return 0;


};