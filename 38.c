#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 100
#define ALPHABET_SIZE 26

int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}

void encrypt(char *plaintext, int n, int *ciphertext, int *K, int m) {
    int i, j, sum;

    for (i = 0; i < n; i++) {
        sum = 0;
        for (j = 0; j < n; j++) {
            sum += K[i * n + j] * (plaintext[j] - 'a');
        }
        ciphertext[i] = sum % m;
    }
}

void decrypt(int *ciphertext, int n, char *decryptedtext, int *K, int m) {
    int i, j, sum, inv;

    inv = modInverse(K[0] * K[3] - K[1] * K[2], m);
    int K_inv[4] = {K[3], -K[1], -K[2], K[0]};
    for (i = 0; i < 4; i++) {
        K_inv[i] = (K_inv[i] * inv) % m;
    }

    for (i = 0; i < n; i++) {
        sum = 0;
        for (j = 0; j < n; j++) {
            sum += K_inv[i * n + j] * ciphertext[j];
        }
        decryptedtext[i] = (sum % m) + 'a';
    }
    decryptedtext[n] = '\0';
}

int main() {
    char plaintext[MAX_LEN], decryptedtext[MAX_LEN];
    int ciphertext[MAX_LEN], n, m;
    int K[4]; 

    printf("Enter the size of the key matrix (n): ");
    scanf("%d", &n);

    printf("Enter the modulo value (m): ");
    scanf("%d", &m);

    printf("Enter the key matrix K (in row-major order):\n");
    for (int i = 0; i < n * n; i++) {
        scanf("%d", &K[i]);
    }

    printf("Enter the plaintext (lowercase alphabets only): ");
    scanf("%s", plaintext);

    int len = strlen(plaintext);

    encrypt(plaintext, n, ciphertext, K, m);

    printf("Ciphertext: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", ciphertext[i]);
    }
    printf("\n");

    printf("\nPerforming chosen plaintext attack...\n");

    int chosen_ciphertext[MAX_LEN];
    char chosen_plaintext[MAX_LEN] = "attack"; 
    int chosen_len = strlen(chosen_plaintext);

    encrypt(chosen_plaintext, n, chosen_ciphertext, K, m);

    decrypt(chosen_ciphertext, n, decryptedtext, K, m);

    printf("Recovered key matrix K:\n");
    for (int i = 0; i < n * n; i++) {
        printf("%d ", K[i]);
        if ((i + 1) % n == 0) {
            printf("\n");
        }
    }

    printf("\n");

    return 0;
}
