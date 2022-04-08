#include <iostream>
#include <collections/vector.h>
#include <graphics/gwindow.h>
#include <io/tokenscanner.h>
#include <io/console.h>
#include <collections/set.h>

int main() {
    Vector<int> tt;
    TokenScanner tsc(std::cin);
    GWindow t;
    Set<int> mm {};
    t.setSize(2000, 2000);
    t.setWindowTitle("123");
    t.drawLine(0, 0, 500, 800);
    int a = tsc.getChar();
    mm.insert(123);
    for(auto i : mm) {
        std::cout << i << std::endl;
    }
    std::cout << a << std::endl;
    return 0;
}
