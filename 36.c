#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int is_coprime(int a) {
    return gcd(a, 26) == 1;
}

int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  
}

char affine_encrypt_char(char p, int a, int b) {
    if (isalpha(p)) {
        char base = isupper(p) ? 'A' : 'a';
        return (a * (p - base) + b) % 26 + base;
    }
    return p;
}

char affine_decrypt_char(char c, int a, int b) {
    if (isalpha(c)) {
        char base = isupper(c) ? 'A' : 'a';
        int a_inv = mod_inverse(a, 26);
        return (a_inv * ((c - base - b + 26) % 26)) % 26 + base;
    }
    return c;
}

void affine_encrypt(char* plaintext, char* ciphertext, int a, int b) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = affine_encrypt_char(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void affine_decrypt(char* ciphertext, char* plaintext, int a, int b) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        plaintext[i] = affine_decrypt_char(ciphertext[i], a, b);
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    int a, b;
    char plaintext[256];
    char ciphertext[256];
    char decryptedtext[256];

    printf("Enter values for a and b: ");
    scanf("%d %d", &a, &b);

    if (!is_coprime(a)) {
        printf("Error: a must be coprime with 26.\n");
        return 1;
    }

    printf("Enter plaintext: ");
    scanf(" %[^\n]s", plaintext);

    affine_encrypt(plaintext, ciphertext, a, b);
    printf("Encrypted text: %s\n", ciphertext);

    affine_decrypt(ciphertext, decryptedtext, a, b);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
