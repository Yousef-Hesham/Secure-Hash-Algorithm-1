/*
Authors : Yousef Hesham
		  Youssef Ansara
		  Eman Mohammed
*/
#include "SHA-1.h"

using namespace std;


void compare(const string& result, const string& expected)
{
	const string& state = (result == expected) ? "OK" : "Failure";
	cout << "Result:   " << result << endl;
	cout << "Expected: " << expected << "  (" << state << ")" << endl;
}

int main()
{
	cout << "Hello SHA1." << endl;
	sha1 instance;

    /* Test Vectors */
    cout << endl;
    cout << "Test:     abc" << endl;
    instance.add_message("abc");
    compare(instance.get_sha1(), "a9993e364706816aba3e25717850c26c9cd0d89d");

    cout << endl;
    cout << "Test:     abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq" << endl;
    instance.add_message("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
    compare(instance.get_sha1(), "84983e441c3bd26ebaae4aa1f95129e5e54670f1");


    cout << endl;
    cout << "Test:     abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu" << endl;
    instance.add_message("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu");
    compare(instance.get_sha1(), "a49b2446a02c645bf419f995b67091253a04a259");

	return 0;
}
