/*
* 15/12/2021 SHA-1 Implementation
Authors : Yousef Hesham
		  Youssef Ansara
		  Eman Mohammed
*/

#include <iostream>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "SHA-1.h"

sha1::sha1() {
	std::cout << "A new instance was initialized..." << std::endl;

    // Set SHA1 Init Values and reset internal variables
    reset();
}

sha1::~sha1() {

}

void sha1::reset()
{
    /* SHA1 initialization constants */
    digest[0] = 0x67452301; // A
    digest[1] = 0xefcdab89; // B
    digest[2] = 0x98badcfe; // C
    digest[3] = 0x10325476; // D 
    digest[4] = 0xc3d2e1f0; // E

    /* Reset counters */
    buffer = "";
    transforms_num = 0;
}

uint32_t sha1::left_rotate(const uint32_t value, const size_t bits)
{
    return (value << bits);
}

uint32_t sha1::extend(const uint32_t block[], const size_t i)
{
    return left_rotate(block[i-3] ^ block[i-8] ^ block[i-14] ^ block[i-16], 1);
}

void sha1::perform_sha1(uint32_t digest[], uint32_t block[], uint64_t& transforms)
{
    /* Copy digest[] to working vars */
    uint32_t a = digest[0];
    uint32_t b = digest[1];
    uint32_t c = digest[2];
    uint32_t d = digest[3];
    uint32_t e = digest[4];

    /* 4 rounds of 20 operations each. */

    uint32_t f, k, temp;

    for (int i = 0; i < 80; i++)
    {
        if (0 <= i <= 19)
        {
            f = (b & c) | ((!b) & d);
            //f = d ^ (b & (c ^ d));
            k = 0x5A827999;
        }
        else if (20 <= i <= 39)
        {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        }
        else if (40 <= i <= 59)
        {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8F1BBCDC;
        }
        else if (60 <= i <= 79)
        {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }


        if (i <= 15) {
            temp = left_rotate(a,5) + f + e + k + block[i];
        }
        else {
            temp = left_rotate(a,5) + f + e + k + extend(block, i);
        }
        //temp = (a << 5) + f + e + k + blk(block, i);
        e = d;
        d = c;
        c = left_rotate(b, 30);
        b = a;
        a = temp;
    }



    /* Add the working vars back into digest[] */
    digest[0] += a;
    digest[1] += b;
    digest[2] += c;
    digest[3] += d;
    digest[4] += e;

    /* Count the number of transformations */
    transforms++;
}

void sha1::buffer_to_block(const std::string& buffer, uint32_t block[BLOCK_INTS])
{
    /* Convert the std::string (byte buffer) to a uint32_t array (MSB) */
    for (size_t i = 0; i < BLOCK_INTS; i++)
    {
        block[i] = (buffer[4 * i + 3] & 0xff)
            | (buffer[4 * i + 2] & 0xff) << 8
            | (buffer[4 * i + 1] & 0xff) << 16
            | (buffer[4 * i + 0] & 0xff) << 24;
    }
}

void sha1::add_message(const std::string& s)
{
    std::istringstream is(s);
    
    while (true)
    {
        char sbuf[BLOCK_BYTES];
        is.read(sbuf, BLOCK_BYTES - buffer.size());
        buffer.append(sbuf, (std::size_t)is.gcount());
        if (buffer.size() != BLOCK_BYTES)
        {
            return;
        }
        uint32_t block[BLOCK_INTS];
        buffer_to_block(buffer, block);
        perform_sha1(digest, block, transforms_num);
        buffer.clear();
    }
}



std::string sha1::get_sha1()
{
    /* Total number of hashed bits */
    uint64_t total_bits = (transforms_num * BLOCK_BYTES + buffer.size()) * 8;

    /* Padding */
    buffer += (char)0x80;
    size_t orig_size = buffer.size();
    while (buffer.size() < BLOCK_BYTES)
    {
        buffer += (char)0x00;
    }

    uint32_t block[BLOCK_INTS];
    buffer_to_block(buffer, block);

    if (orig_size > BLOCK_BYTES - 8)
    {
        perform_sha1(digest, block, transforms_num);
        for (size_t i = 0; i < BLOCK_INTS - 2; i++)
        {
            block[i] = 0;
        }
    }

    /* Append total_bits, split this uint64_t into two uint32_t */
    block[BLOCK_INTS - 1] = (uint32_t)total_bits;
    block[BLOCK_INTS - 2] = (uint32_t)(total_bits >> 32);
    perform_sha1(digest, block, transforms_num);

    /* Hex std::string */
    std::ostringstream result;
    for (size_t i = 0; i < sizeof(digest) / sizeof(digest[0]); i++)
    {
        result << std::hex << std::setfill('0') << std::setw(8);
        result << digest[i];
    }

    /* Reset for next run */
    reset();

    return result.str();
}
