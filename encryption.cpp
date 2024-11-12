#include <Security/Security.h>
#include <iostream>
#include <vector>
#include <cmath> 
#include <string>

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
 
unsigned long long gcd(unsigned long long a, unsigned long long b) {
    if (a == 0 || b == 0) {
        return a;
    }
    if (a == b)  
        return a;  

    return gcd(b, a % b);
}

bool areCoprime(unsigned long long a, unsigned long long b) {
    return gcd(a, b) == 1;
}


unsigned long long find_d(unsigned long long A, unsigned long long M) {
    unsigned long long m0 = M;
    unsigned long long y = 0, x = 1;

    if (M == 1) {
        return 0; // No modular inverse exists if M == 1
    }

    while (A > 1) {
        // q is quotient
        unsigned long long q = A / M;
        unsigned long long t = M;

        // Apply Euclid's algorithm
        M = A % M;
        A = t;
        t = y;

        // Update y and x
        y = x - q * y;
        x = t;
    }

    // Make x positive if necessary
    if (x < 0) {
        x += m0;
    }

    return x;
}

long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod){
    unsigned long long result =1 ; 
    unsigned long long prev = base % mod;
    do{
        if( (exp&1) == 1){
            
            result = (result * prev) % mod;
        }
        exp= exp >> 1;
        prev = (prev*prev) % mod;


    }while(exp > 0);

    return (result%mod);

}



std::vector<unsigned long long> encrypt(std::string str,unsigned long long e, unsigned long long n){
    std::vector<unsigned long long > c; 
    for(auto i = str.begin(); i != str.end(); i++){

        c.push_back(mod_exp(*i, e, n));
       
    }
    return c; 
}

std::vector<unsigned long long> decrypt(std::vector<unsigned long long> crypted,unsigned long long d, unsigned long long n){
    std::vector<unsigned long long > c; 
    for(auto i = 0; i < crypted.size(); i++){

        c.push_back(mod_exp(crypted[i], d, n));
       
    }
    return c; 
}


void generating_primes(unsigned long long& p, unsigned long long&q, size_t length){
    p = generate_secure_random_bytes(length);
    while(!isPrime(p)){
        p = generate_secure_random_bytes(length);
    }
    // std::cout <<p << " ";
    q = generate_secure_random_bytes(length);
    while(!isPrime(q) || p==q){
        q = generate_secure_random_bytes(length);
    }

}

void find_e(unsigned long long& e, const unsigned long long phi, size_t length){
    e = 3;
    while(!areCoprime(phi,e) || e > phi ){
        e  = generate_secure_random_bytes(length/2);
    }

}


int main(int argc, char* argv[]) {
    size_t length = 1; 
    unsigned long long p;
    unsigned long long q; 
    generating_primes(p, q, length);


    unsigned long long n = (p*q); 
    unsigned long long phi = (p-1)*(q-1);
    std::cout << "phi is " << phi << "\n";


    unsigned long long e;
    
    find_e(e, phi, length);
    unsigned long long d = find_d(e,phi);

    std::cout << "Public key in format(e, n) is (" << e  << ", " << n << ")\n"; 
    std::cout << "secret key in format(d, n) is (" << d  << ", " << n << ")\n"; 




    for(int i =1; i< argc; i++){
        auto c = encrypt(argv[i], e, n);
        auto m = decrypt(c, d, n);
        std::cout << "Encryption of \"" << argv[i] << "\" is: ";
        for(auto l: c){
            std::cout << l << " "; 
        }
        std::cout << "\nM size is " << m.size() << "\n";
        for(auto l: m){
            std::cout <<l << " "; 
        }
        c.clear();
        std::cout << "\n"; 
    
    }

    std::cout << std::dec << std::endl;
    
 
    return 0;
}
