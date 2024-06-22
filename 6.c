#include <stdio.h>

int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int main() {
    int a, b;
    int m = 26;
    int x1 = 4, y1 = 1; 
    int x2 = 19, y2 = 20; 

    int y_diff = (y2 - y1 + m) % m; 
    int x_diff = (x2 - x1 + m) % m; 

    a = (y_diff * modInverse(x_diff, m)) % m;

    b = (y1 - a * x1) % m;
    if (b < 0) b += m;

    printf("Key found: a = %d, b = %d\n", a, b);

    char ciphertext[] = "BUBUBU";
    char plaintext[sizeof(ciphertext)];

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            int y = ciphertext[i] - 'A';
            int x = (modInverse(a, m) * (y - b + m)) % m;
            plaintext[i] = x + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[sizeof(ciphertext) - 1] = '\0'; 

    printf("Decrypted plaintext: %s\n", plaintext);

    return 0;
}
