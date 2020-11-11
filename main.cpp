#include <iostream>
#include <chrono>

//#include "SimpleMatrixV.h"
#include "SimpleMatrixT.h"

using namespace std;

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock_t> m_beg;

public:
    Timer() : m_beg(clock_t::now()) { }

    void reset() { m_beg = clock_t::now(); }

    double elapsed() const { return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count(); }
};

int main() {

    // SimpleMatrixV creation
//    auto a = SimpleMatrix(3,4, {1,2,3,4,5,6,7,8,9,10,11,12});
//    auto b = SimpleMatrix(3,4, {21,22,23,24,25,26,27,28,29,30,31,32});
//    auto e = SimpleMatrix(100000,1000);

    // SimpleMatrixT creation
    auto a = SimpleMatrix<3, 4, int>({1,2,3,4,5,6,7,8,9,10,11,12});
    auto b = SimpleMatrix<3, 4, int>({21,22,23,24,25,26,27,28,29,30,31,32});
    auto e = SimpleMatrix<100000, 1000, int>();

    auto c = b;

    cout << "A" << endl << a;
    cout << "B" << endl << b;
    cout << "C" << endl << c;

    // operators test
    cout << ((c == b) ? "C == B" : "C != B") << endl;
    cout << "A + B" << endl << (a + b);
    cout << "A | B" << endl << (a | b);

    // copy/ move test
    Timer t;
    auto f = e;
    cout << " copy: " << t.elapsed() << endl;
    t.reset();
    auto g = std::move(e);
    cout << " move: " << t.elapsed() << endl;

    //cout << e; // -- this should raise error

    return 0;
}
