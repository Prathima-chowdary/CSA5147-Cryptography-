#include <stdio.h>
#include <math.h>

int main() {
    double log2_25_factorial = 83.66;  
    double log2_effective_keys = log2_25_factorial - log2(4);
    
    printf("Approximate number of possible keys: 2^%.2f\n", log2_25_factorial);
    printf("Approximate number of effectively unique keys: 2^%.2f\n", log2_effective_keys);
    
    return 0;
}
