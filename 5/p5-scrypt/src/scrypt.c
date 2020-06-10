/*
 * scrypt/src/scrypt.c --
 */

#include <stdlib.h>

#include "scrypt.h"
union Nibble {
     struct { 
        unsigned int first:4;
        unsigned int second:4;
     } nibbles;
     uint8_t byte_value;
} nibble;

uint8_t
sc_dec_perm_step(uint8_t m)
{
    uint8_t res = 0;
    for (int i = 0 ;i<8;i++)
    {
        uint8_t temp = (m >> (i+2)%8)&1;

        res = res | (temp << i); 
    }
    return res;
}

uint8_t
sc_dec_sub_step(uint8_t m)
{
    uint8_t s_box_inv[] = {15, 6, 13, 4, 11, 2, 9, 0, 7, 14, 5, 12, 3, 10, 1, 8};
    nibble.byte_value = m;
    nibble.nibbles.first = s_box_inv[nibble.nibbles.first];
    nibble.nibbles.second = s_box_inv[nibble.nibbles.second];
    m = nibble.byte_value;
    return m;
}

uint8_t
sc_enc_perm_step(uint8_t m)
{
    uint8_t res = 0;
    for (int i =0 ;i<8;i++)
    {
        uint8_t temp = (m >> (i+6)%8)&1;

        res = res | (temp << i); 
    }
    return res;
}

uint8_t
sc_enc_sub_step(uint8_t m)
{
    nibble.byte_value = m;
    nibble.nibbles.first = ((nibble.nibbles.first + 1)*7)%16;
    nibble.nibbles.second = ((nibble.nibbles.second + 1)*7)%16;
    m = nibble.byte_value;
    return m;
}

uint8_t
sc_key_step(uint8_t m, uint8_t k)
{
    return m^k;
}

uint8_t
sc_enc8(uint8_t m, uint32_t k)
{
    //0 index holds the least significant bits, 3 holds the most significant
    uint8_t temp_key[4];
    for (int i =0; i<4; i++)
    {
        temp_key[i] = (uint8_t)(k>>i*8);
    }
    //1st round
    m = sc_key_step(m,temp_key[3]);
    
    //2nd round
    m = sc_enc_sub_step(m);
    m = sc_enc_perm_step(m);
    m = sc_key_step(m,temp_key[2]);

    //3rd round;
    m = sc_enc_sub_step(m);
    m = sc_enc_perm_step(m);
    m = sc_key_step(m,temp_key[1]);

    //4th round:
    m = sc_enc_sub_step(m);
    m = sc_key_step(m,temp_key[0]);
    return m;
}

uint8_t
sc_dec8(uint8_t c, uint32_t k)
{
    uint8_t temp_key[4];
    for (int i =0; i<4; i++)
    {
        temp_key[i] = (uint8_t)(k>>i*8);
    }
    //1st round
    c = sc_key_step(c,temp_key[0]);
    c = sc_dec_sub_step(c);

    
    //2nd round
    c = sc_key_step(c,temp_key[1]);
    c = sc_dec_perm_step(c);
    c = sc_dec_sub_step(c);

    //3rd round;
    c = sc_key_step(c,temp_key[2]);
    c = sc_dec_perm_step(c);
    c = sc_dec_sub_step(c);

    //4th round:
    c = sc_key_step(c,temp_key[3]);
    return c;
}

void
sc_enc_ecb(unsigned char *m, unsigned char *c, size_t len, uint32_t k)
{
    for (int i =0; i < len; i++)
    {
        c[i] = sc_enc8(m[i],k);
    }
}

void
sc_dec_ecb(unsigned char *c, unsigned char *m, size_t len, uint32_t k)
{
    for (int i =0; i < len; i++)
    {
        m[i] = sc_dec8(c[i],k);
    }
}

void
sc_enc_cbc(unsigned char *m, unsigned char *c, size_t len, uint32_t k, uint8_t iv)
{
    
    for (int i =0;i< len; i++)
    {
        if (i==0)
        {
            c[i] = sc_enc8(m[i]^iv,k);
        }
        else 
        {
            c[i] = sc_enc8(m[i]^c[i-1],k);
        }
    }
}

void
sc_dec_cbc(unsigned char *c, unsigned char *m, size_t len, uint32_t k, uint8_t iv)
{
    for (int i =0;i< len; i++)
    {
        if (i==0)
        {
            m[i] = sc_dec8(c[i],k)^iv;
        }
        else 
        {
            m[i] = sc_dec8(c[i],k)^c[i-1];
        }
    }
}

