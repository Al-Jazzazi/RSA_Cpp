#include <Security/Security.h>
#include <iostream>
#include <vector>
#include <cmath> 
#include <gmpxx.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>


std::string generate_secure_random_bytes(size_t length = 8) {
    std::vector<unsigned char> buffer(length);
    if (SecRandomCopyBytes(kSecRandomDefault, length, buffer.data()) != errSecSuccess) {
        throw std::runtime_error("Failed to generate secure random bytes.");
    }

    // Convert each byte in buffer to a hexadecimal string
    std::ostringstream oss;
    for (size_t i = 0; i < length; i++) {
        // Convert each byte to hexadecimal and add to the output stream
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]);
    }

    std::string number = oss.str();
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
 
mpz_class gcd(mpz_class a, mpz_class b) {
    if (a == 0 || b == 0) {
        return a;
    }
    if (a == b)  
        return a;  

    return gcd(b, a % b);
}

bool areCoprime(mpz_class a, mpz_class b) {
    return gcd(a, b) == 1;
}


mpz_class mod_exp(mpz_class base, mpz_class exp, mpz_class mod){
    mpz_class result =1 ; 
    mpz_class prev = base % mod;
    do{
        if( (exp&1) == 1){
            
            result = (result * prev) % mod;
        }
        exp= exp >> 1;
        prev = (prev*prev) % mod;


    }while(exp > 0);

    return (result%mod);

}



std::vector<mpz_class> encrypt(std::string str,mpz_class e, mpz_class n){
    std::vector<mpz_class > c; 
    for(auto i = str.begin(); i != str.end(); i++){

        c.push_back(mod_exp(*i, e, n));
       
    }
    return c; 
}

std::vector<mpz_class> decrypt(std::vector<mpz_class> crypted,mpz_class d, mpz_class n){
    std::vector<mpz_class > c; 
    for(auto i = 0; i < crypted.size(); i++){

        c.push_back(mod_exp(crypted[i], d, n));
       
    }
    return c; 
}


void find_e(mpz_class& e, mpz_class phi, size_t length){
    e = 65537;
    while(!areCoprime(phi,e) || e > phi ){
        e.set_str(generate_secure_random_bytes(length/2),16);
    }

}
void find_d(mpz_class& d, mpz_class A, mpz_class M) {
    mpz_class m0 = M;
    mpz_class y = 0, x = 1;

    if (M == 1) {
        return; // No modular inverse exists if M == 1
    }

    while (A > 1) {
        // q is quotient
        mpz_class q = A / M;
        mpz_class t = M;

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

    d = x;
}


int main(int argc, char* argv[]) {
    size_t length = 64;  //512 bit security 
    // std::string s = generate_secure_random_bytes(length);
    mpz_class p(generate_secure_random_bytes(length),16);     // Generate a random 512-bit number
    mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());  // Set p to the next prime after the random number



    mpz_class q(generate_secure_random_bytes(length),16);     // Generate a random 512-bit number
    mpz_nextprime(q.get_mpz_t(), q.get_mpz_t());  // Set p to the next prime after the random number


    mpz_class n = p*q; 
    mpz_class phi =  (p-1)*(q-1);
    // std::cout << n << "\n";
    std::cout << "phi is " << phi << "\n";  

    
    mpz_class e;
    mpz_class d;
    
    find_e(e, phi, length);
    find_d(d, e,phi);

    std::cout << "Public key in format(e, n) is (" << e  << ", " << n << ")\n"; 
    std::cout << "secret key in format(d, n) is (" << d  << ", " << n << ")\n"; 




    for(int i =1; i< argc; i++){
        auto c = encrypt(argv[i], e, n);
        auto m = decrypt(c, d, n);
        std::cout << "Encryption of \"" << argv[i] << "\" is: ";
        for(auto l: c){
            std::cout << l << "\n"; 
        }
        std::cout << "\nM size is " << m.size() << "\n";
        for(auto l: m){
            std::cout << static_cast<char>(l.get_ui()) << " "; 
        }
        c.clear();
        std::cout << "\n"; 
    
    }

    // std::cout << std::dec << std::endl;
    
 
    return 0;
}
