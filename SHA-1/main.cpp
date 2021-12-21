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
    compare(instance.get_sha1(), "a459b3ba6ce23c42d8badcfe5032547603d2e1f0");

    cout << endl;
    cout << "Test:     abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq" << endl;
    instance.add_message("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
    compare(instance.get_sha1(), "216e447369f6ccfb18badcfe9032547643d2e1f0");


    cout << endl;
    cout << "Test:     abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmno" << endl;
    instance.add_message("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmno");
    compare(instance.get_sha1(), "b922514b51e7a09518badcfe9032547643d2e1f0");

	return 0;
}
