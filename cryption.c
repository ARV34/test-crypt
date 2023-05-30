/**
 * @file cryption.c
 * @brief
 * @author Arestov Roman <arv34@mail.ru>
 */

#include <openssl/aes.h>
#include <openssl/rand.h>
#include "cryption.h"

static const uint8_t fixed_key[32] = {
    0x01, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    0x0A, 0x01, 0x02, 0x03, 0x04, 0xc5, 0x06, 0x07,
    0x08, 0xA9, 0x0a, 0xfb, 0x0c, 0xAd, 0x0e, 0x0f
};

void Crypt_GenerateKey(int key_size, uint8_t *key)
{
	RAND_bytes(key, key_size / 8);
}

void Crypt_Encrypt(const uint8_t *in, int size, const uint8_t *key, 
    int len_key, uint8_t *out) 
{
    AES_KEY aes_key;
    AES_set_encrypt_key(key, len_key, &aes_key);

    int offset = 0;
    while(size > offset) {
        AES_encrypt(in + offset, out + offset, &aes_key);
        offset += AES_BLOCK_SIZE;
    }
}

void Crypt_Decrypt(const uint8_t *in, int size, const uint8_t *key, 
    int len_key, uint8_t *out) 
{
    AES_KEY aes_key;
    AES_set_decrypt_key(key, len_key, &aes_key);

    int offset = 0;
    while(size > offset) {
        AES_decrypt(in + offset, out + offset, &aes_key);
        offset += AES_BLOCK_SIZE;
    }
}

void Crypt_EncryptFixedKey(const uint8_t *in, int size, uint8_t *out) 
{
    Crypt_Encrypt(in, size, fixed_key, sizeof(fixed_key) * 8, out);
}

void Crypt_DecryptFixedKey(const uint8_t *in, int size, uint8_t *out) 
{
    Crypt_Decrypt(in, size, fixed_key, sizeof(fixed_key) * 8, out);
}