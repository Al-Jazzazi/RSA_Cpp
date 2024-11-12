#include <Security/Security.h>
#include <iostream>
#include <vector>

unsigned long long generate_secure_random_bytes(size_t length =8) {
    std::vector<unsigned char> buffer(length);
    if (SecRandomCopyBytes(kSecRandomDefault, length, buffer.data()) != errSecSuccess) {
        throw std::runtime_error("Failed to generate secure random bytes.");
    }

    unsigned long long number = 0; 
    for (int i = 0; i<length; i++ ) {
        number |= (static_cast<unsigned long long>(buffer[i]) << (i * 8));
        // std::cout << std::hex << (int)buffer[i] << " "; 
    }

    return number;
}

bool isPrime(unsigned long long num) {
    if (num <= 1) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;

    unsigned long long limit = static_cast<unsigned long long>(std::sqrt(num));
    for (unsigned long long i = 5; i <= limit; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    
    return true;
}


int main() {
    size_t length = 8; 
    auto p = generate_secure_random_bytes(length);

    while(!isPrime(p)){
        p = generate_secure_random_bytes(length);
    }
    std::cout <<p << " ";

    auto q = generate_secure_random_bytes(length);
    while(!isPrime(q)){
        q = generate_secure_random_bytes(length);
    }

    std::cout <<q << " ";

    unsigned long long n = p*q; 
   
    std::cout <<q << " ";

    

    


    
    std::cout << std::dec << std::endl;
    
 
    return 0;
}
