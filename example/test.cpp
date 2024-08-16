#include <base.h>
#include <iostream>
#include <sha.h>

using namespace std;
using namespace shiny;

int main(int argc, const char *argv[]) {
    std::string str = (argc > 1 ? argv[1] : "");

    SHA0 sha0;
    sha0.init(str);
    sha0.compute();
    cout << "SHA0: ";
    for (auto h : sha0.getDisgest()) cout << hexadecimal.decodeN(h, sizeof(h) * 2);
    cout << endl;

    SHA1 sha1;
    sha1.init(str);
    sha1.compute();
    cout << "SHA1: ";
    for (auto h : sha1.getDisgest()) cout << hexadecimal.decodeN(h, sizeof(h) * 2);
    cout << endl;

    SHA224 sha224;
    sha224.init(str);
    sha224.compute();
    cout << "SHA224: ";
    for (auto h : sha224.getDisgest()) cout << hexadecimal.decodeN(h, sizeof(h) * 2);
    cout << endl;

    SHA256 sha256;
    sha256.init(str);
    sha256.compute();
    cout << "SHA256: ";
    for (auto h : sha256.getDisgest()) cout << hexadecimal.decodeN(h, sizeof(h) * 2);
    cout << endl;

    SHA384 sha384;
    sha384.init(str);
    sha384.compute();
    cout << "SHA384: ";
    for (auto h : sha384.getDisgest()) cout << hexadecimal.decodeN(h, sizeof(h) * 2);
    cout << endl;

    SHA512 sha512;
    sha512.init(str);
    sha512.compute();
    cout << "SHA512: ";
    for (auto h : sha512.getDisgest()) cout << hexadecimal.decodeN(h, sizeof(h) * 2);
    cout << endl;

    return 0;
}
