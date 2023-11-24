#include <iostream>
#include <base.h>
#include <sha.h>

using namespace std;
using namespace shiny;

int main(int argc, const char* argv[])
{

    std::string str = (argc > 1 ? argv[1] : "");

    SHA0 sha0;
    sha0.init(str);
    sha0.compute();
    cout << "SHA0: ";
    for(uint32_t h : sha0.getDisgest())
        cout << hexadecimal.decodeN(h, 8);
    cout << endl;

    SHA1 sha1;
    sha1.init(str);
    sha1.compute();
    cout << "SHA1: ";
    for(uint32_t h : sha1.getDisgest())
        cout << hexadecimal.decodeN(h, 8);
    cout << endl;

    SHA224 sha224;
    sha224.init(str);
    sha224.compute();
    cout << "SHA224: ";
    for(uint32_t h : sha224.getDisgest())
        cout << hexadecimal.decodeN(h, 8);
    cout << endl;

    SHA256 sha256;
    sha256.init(str);
    sha256.compute();
    cout << "SHA256: ";
    for(uint32_t h : sha256.getDisgest())
        cout << hexadecimal.decodeN(h, 8);
    cout << endl;

    return 0;
}