#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define NUM_TOP_PLAINTEXTS 10

const float english_frequencies[ALPHABET_SIZE] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 
    0.0609, 0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 
    0.0751, 0.0193, 0.0009, 0.0599, 0.0633, 0.0906, 0.0276, 
    0.0098, 0.0236, 0.0015, 0.0197, 0.0007                  
};

void count_letter_frequencies(const char *text, int *freq) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        char c = toupper(text[i]);
        if (c >= 'A' && c <= 'Z') {
            freq[c - 'A']++;
        }
    }
}

int compare_freq(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

void decrypt_with_mapping(const char *ciphertext, char *plaintext, int *mapping) {
    int i;
    for (i = 0; i < strlen(ciphertext); i++) {
        char c = toupper(ciphertext[i]);
        if (c >= 'A' && c <= 'Z') {
            plaintext[i] = 'A' + mapping[c - 'A'];
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char ciphertext[1000]; 
    int freq[ALPHABET_SIZE] = {0};
    int mapping[ALPHABET_SIZE];
    char plaintext[1000];
    int i;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    count_letter_frequencies(ciphertext, freq);

    for (i = 0; i < ALPHABET_SIZE; i++) {
        mapping[i] = i;
    }

    qsort(freq, ALPHABET_SIZE, sizeof(int), compare_freq);

    for (i = 0; i < ALPHABET_SIZE; i++) {
        mapping[freq[i]] = i;
    }

    printf("\nTop possible plaintexts:\n");
    for (i = 0; i < NUM_TOP_PLAINTEXTS; i++) {
        decrypt_with_mapping(ciphertext, plaintext, mapping);
        printf("%d. %s\n", i + 1, plaintext);
        qsort(mapping, ALPHABET_SIZE, sizeof(int), compare_freq);
    }

    return 0;
}
