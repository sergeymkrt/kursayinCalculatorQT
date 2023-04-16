//
// Created by Sergey Mkrtumyan on 16.04.23.
//

#include "../Headers/HashPassword.h"
#include <string>
#include <random>
#include <vector>
#include <sstream>
#include <iomanip>

QString HashPassword::generate_salt(int length_bytes) {
    std::string salt;
    salt.reserve(length_bytes);

    //obtain a seed for the random number generator
    std::random_device rd;
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, 255); //uniform distribution between 0 and 255

    for (int i = 0; i < length_bytes; ++i) {
        salt.push_back(static_cast<char>(distrib(gen)));
    }

    return QString::fromStdString(salt);
}

void HashPassword::sha256_pad_message(std::vector<uint8_t> &message) {
    uint64_t original_length_bits = message.size() * 8;
    uint64_t message_length_bits = original_length_bits + 1 + 64;
    size_t padding_length = (512 - (message_length_bits % 512)) / 8;

    message.push_back(0x80);
    padding_length--;

    while (padding_length>0){
        message.push_back(0);
        padding_length--;
    }
    uint64_t length_be = htobe64(original_length_bits);
    uint8_t* length_bytes = reinterpret_cast<uint8_t*>(&length_be);
    for (int i = 0; i < 8; i++) {
        message.push_back(length_bytes[i]);
    }
}

uint64_t HashPassword::htobe64(uint64_t x) {
    uint64_t y;
    auto* px = reinterpret_cast<uint8_t*>(&x);
    auto* py = reinterpret_cast<uint8_t*>(&y);
    py[0] = px[7];
    py[1] = px[6];
    py[2] = px[5];
    py[3] = px[4];
    py[4] = px[3];
    py[5] = px[2];
    py[6] = px[1];
    py[7] = px[0];
    return y;
}

void HashPassword::sha256_compress(uint32_t state[], const uint8_t *block) {
    uint32_t words[64];
    uint32_t a, b, c, d, e, f, g, h, T1, T2;


    // Convert the block from bytes to words
    for (int i = 0; i < 16; i++) {
        words[i] = (block[i * 4 + 0] << 24) |
                   (block[i * 4 + 1] << 16) |
                   (block[i * 4 + 2] << 8) |
                   (block[i * 4 + 3] << 0);
    }

    // Expand the block to create 48 more words
    for (int i = 16; i < 64; i++) {
        uint32_t s0 = right_rotate(words[i-15], 7) ^ right_rotate(words[i-15], 18) ^ (words[i-15] >> 3);
        uint32_t s1 = right_rotate(words[i-2], 17) ^ right_rotate(words[i-2], 19) ^ (words[i-2] >> 10);
        words[i] = words[i-16] + s0 + words[i-7] + s1;
    }

    // Initialize the hash values
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];

    // Main loop
    for (int i = 0; i < 64; i++) {
        T1 = h + (right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25)) + ((e & f) ^ (~e & g)) + K[i] + words[i];
        T2 = (right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22)) + ((a & b) ^ (a & c) ^ (b & c));
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }

    // Update the hash values
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}

uint32_t HashPassword::right_rotate(uint32_t value, uint32_t count) {
    return (value >> count) | (value << (32 - count));
}

QString HashPassword::hash_password(const std::string& message) {
    std::vector<uint8_t> data(message.begin(), message.end());
    sha256_pad_message(data);
    const uint8_t* data_ptr = data.data();

    for (size_t i = 0; i < data.size(); i += 64) {
        sha256_compress(H, &data_ptr[i]);
    }

    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned int i : H) {
        ss << std::setw(8) << i;
    }

    return QString::fromStdString(ss.str());
}
