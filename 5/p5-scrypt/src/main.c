/*
 * scrypt/src/main.c --
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "scrypt.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

static void
printhex(char *prefix, unsigned char *s, size_t len)
{
    size_t i;
    int printable = 1;
    
    printf("%s", prefix);
    for (i = 0; i < len; i++) {
        printf("%02x", s[i]);
        printable = (printable && isprint(s[i]));
    }
    if (printable) {
        printf(" \"%.*s\"", (int) len, s);
    }
    puts("");
}

static void
test_ecb(unsigned char *m, uint32_t k)
{
    uint32_t nk = htonl(k);
    size_t len = strlen((char*) m);
    unsigned char c[len];
    unsigned char d[len];

    sc_enc_ecb(m, c, len, k);
    sc_dec_ecb(c, d, len, k);

    printf("b: ecb\n");
    printhex("k: 0x", (unsigned char *) &nk, 4);
    printhex("m: 0x", m, len);
    printhex("c: 0x", c, len);
    printhex("d: 0x", d, len);
}

static void
test_cbc(unsigned char *m, uint32_t k, uint8_t iv)
{
    uint32_t nk = htonl(k);
    size_t len = strlen((char *) m);
    unsigned char c[len];
    unsigned char d[len];
    
    sc_enc_cbc(m, c, len, k, iv);
    sc_dec_cbc(c, d, len, k, iv);

    printf("b: cbc\n");
    printhex("k: 0x", (unsigned char *) &nk, 4);
    printhex("i: 0x", (unsigned char *) &iv, 1);
    printhex("m: 0x", m, len);
    printhex("c: 0x", c, len);
    printhex("d: 0x", d, len);
}

static long
getlong_or_die(char *s)
{
    long l;
    char *end;

    l = strtol(optarg, &end, 0);
    if (!end || *end != 0) {
	fprintf(stderr, "scrypt: invalid number '%s'\n", optarg);
	exit(EXIT_FAILURE);
    }
    return l;
}

int main(int argc, char *argv[])
{
    uint32_t k = 0x98267351;
    uint8_t iv = 0x42;
    int i;
    char c;

    while ((c = getopt(argc, argv, "i:k:h")) != -1) {
	switch (c) {
	case 'i':
	    iv = getlong_or_die(optarg);
	    break;
	case 'k':
	    k = getlong_or_die(optarg);
	    break;
	case 'h':
	default:
	    printf("usage: scrypt [-i iv] [-k key]\n");
	    break;
	}
    }
    argc -= optind;
    argv += optind;

    for (i = 0; i < argc; i++) {
        test_ecb((unsigned char *) argv[i], k);
        puts("");
    }

    for	(i = 0; i < argc; i++) {
        test_cbc((unsigned char *) argv[i], k, iv);
        puts("");
    }
    
    unsigned char cipher[] = {0xc6, 0x5e, 0x05, 0x94, 0x6b, 0x86, 0xeb, 0x2e, 0x33, 0xf5, 0x8f, 0xda, 0xff, 0x0f, 0x42};
    int len = strlen((char *) cipher);
    unsigned char e[len];
    sc_dec_cbc(cipher, e, len, k, iv);
    
    for(int i = 0; i < len; i++) fprintf(stderr, "%x", cipher[i]);
    fprintf(stderr, " = %s\n\n", e);
    return EXIT_SUCCESS;
}
