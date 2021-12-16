#pragma once

#include <iostream>

#define BLOCK_INTS 16  /* number of 32bit integers per SHA1 block */
#define BLOCK_BYTES (BLOCK_INTS*4)

class sha1 {
public:
	sha1();
	~sha1();

    void sha1::add_message(const std::string& s);
    std::string sha1::get_sha1();

private:
    uint32_t digest[5];
    std::string buffer;
    uint64_t transforms_num;


    void sha1::reset();
    uint32_t sha1::rol(const uint32_t value, const size_t bits);
    uint32_t sha1::blk(const uint32_t block[BLOCK_INTS], const size_t i);
    void sha1::buffer_to_block(const std::string& buffer, uint32_t block[BLOCK_INTS]);
    void sha1::R0(const uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t& w, const uint32_t x, const uint32_t y, uint32_t& z, const size_t i);
    void sha1::R1(uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t& w, const uint32_t x, const uint32_t y, uint32_t& z, const size_t i);
    void sha1::R2(uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t& w, const uint32_t x, const uint32_t y, uint32_t& z, const size_t i);
    void sha1::R3(uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t& w, const uint32_t x, const uint32_t y, uint32_t& z, const size_t i);
    void sha1::R4(uint32_t block[BLOCK_INTS], const uint32_t v, uint32_t& w, const uint32_t x, const uint32_t y, uint32_t& z, const size_t i);
    void sha1::perform_sha1(uint32_t digest[], uint32_t block[BLOCK_INTS], uint64_t& transforms);
};
