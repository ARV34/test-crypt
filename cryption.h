/**
 * @file cryption.h
 * @brief
 * @author Arestov Roman <arv34@mail.ru>
 */

#ifndef CRYPTION_H_
#define CRYPTION_H_

#include <stdint.h>

void Crypt_GenerateKey(int key_size, uint8_t *key);
void Crypt_Encrypt(const uint8_t *in, int size, const uint8_t *key, 
    int len_key, uint8_t *out);
void Crypt_Decrypt(const uint8_t *in, int size, const uint8_t *key, 
    int len_key, uint8_t *out);
void Crypt_EncryptFixedKey(const uint8_t *in, int size, uint8_t *out);
void Crypt_DecryptFixedKey(const uint8_t *in, int size, uint8_t *out);

#endif /* CRYPTION_H_ */
