// recursive implementation of factorial that computes
//   its result "on the way down",
//   and throws the answer back up the stack

#include <iostream>
#include <iomanip>

using namespace std;

void factR(int n, int result)
{
    if (n <= 1)
        throw result;
    else
        factR(n - 1, result * n);
}

int fact(int n)
{
    try {
        factR(n, 1);
    } catch (int result) {
        return result;
    }
    return -1;
}

int main(int argc, char **argv)
{
    int     n(argc > 1 ? atoi(argv[1]) : -1);
    int     f;

    if (n < 0) {
        cout << "one positive numeric argument is required" << endl;
        return -1;
        }

    f = fact(n);

    cout << "fact(" << n <<") = " << setw(6) << f << endl;
    return 0;
}
