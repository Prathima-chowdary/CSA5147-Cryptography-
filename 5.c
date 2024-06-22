#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

char affineEncrypt(char p, int a, int b) {
    if (isalpha(p)) {
        int p_val = toupper(p) - 'A'; 
        return (char) (((a * p_val + b) % 26) + 'A'); 
    }
    return p;
}

char affineDecrypt(char c, int a, int b) {
    if (isalpha(c)) {
        int c_val = toupper(c) - 'A'; 
        int a_inv = modInverse(a, 26); 
        if (a_inv == -1) {
            printf("Error: a does not have a modular inverse, decryption impossible.\n");
            exit(1);
        }
        return (char) (((a_inv * (c_val - b + 26)) % 26) + 'A'); 
    }
    return c;
}

int main() {
    int a, b;
    char plaintext[100], ciphertext[100];
    
    // Input values of a and b
    printf("Enter the values of a and b: ");
    scanf("%d %d", &a, &b);

    // Input plaintext
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    // Encrypt the plaintext
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = affineEncrypt(plaintext[i], a, b);
    }
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    char decryptedtext[100];
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        decryptedtext[i] = affineDecrypt(ciphertext[i], a, b);
    }
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
