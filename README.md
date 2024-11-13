# RSA Encryption Project (macOS)

This project demonstrates a simple RSA encryption and decryption example using C++ on macOS. It includes two versions of an encryption implementation: one using `unsigned long long int` for calculations, and a more optimized version using `mpz_class` from the **GMP** (GNU Multiple Precision Arithmetic) library. 

**Note**: This project is designed specifically for macOS. The `SecRandomCopyBytes` function used for secure random number generation is part of Apple's Security framework and will not work on other platforms like Linux or Windows.

## Table of Contents

- [Project Overview](#project-overview)
- [Files in Project](#files-in-project)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Compiling and Running](#compiling-and-running)
- [Usage](#usage)
- [Keywords](#keywords)

## Project Overview

The project provides two versions of RSA encryption:

1. **`encryption.cpp`**: This file uses `unsigned long long int` for modular exponentiation and a brute-force modular inverse (`find_d`) implementation. It is less efficient and should be used for educational purposes or small values only.
   
2. **`encryption_optimized.cpp`**: This file uses **GMP**'s `mpz_class` type for arbitrary-precision arithmetic, which allows for much larger numbers, making it suitable for actual cryptographic use cases. It includes optimized modular exponentiation and modular inverse calculations, leveraging the Extended Euclidean Algorithm.

## Files in Project

- **`encryption.cpp`**: Basic RSA encryption with `unsigned long long int` and brute-force modular inverse.
- **`encryption_optimized.cpp`**: Optimized RSA encryption with GMP's `mpz_class` for large number support.

## Dependencies

- **macOS**: This project relies on macOS's `SecRandomCopyBytes` for secure random byte generation.
- **GMP Library (GNU Multiple Precision Arithmetic)**: Required only for `encryption_optimized.cpp` to handle large numbers and provide optimized arithmetic functions.

## Installation

To install GMP on macOS, use **Homebrew**:

```bash
brew install gmp
```
installation is only needed to run the encryption_optimized.cpp version 

## Compiling and Running

### 1. Basic Implementation (`encryption.cpp`)

This version uses `unsigned long long int` for calculations and is compiled as follows:

```bash
clang++ -std=c++17 -framework Security -o enc encryption.cpp
```

### 2. Optimized GMP Implementation (`encryption_optimized.cpp`)

This version uses **GMP** for high-precision arithmetic. Compile with the following command:

```bash
clang++ -std=c++17 -framework Security -o enc encryption_optimized.cpp -lgmp -lgmpxx -I/opt/homebrew/include -L/opt/homebrew/lib
```

- **Note**: Adjust include and library paths (`-I/opt/homebrew/include` and `-L/opt/homebrew/lib`) if GMP is installed in a different location.

## Usage

Both versions accept a plaintext message as a command-line argument. The message will be encrypted using RSA encryption and then decrypted to show the original message.

Run the program with:

```bash
./enc YourMessageHere
```

### Example

```bash
./enc Yousef
```

## How It Works

### 1. `encryption.cpp`

- Uses `unsigned long long int` for calculations, which can only handle smaller values, making it suitable for basic or educational use.
- Implements `find_d` (modular inverse) with a brute-force algorithm, which is slower and less efficient for larger values.
- Provides basic RSA functionality: it generates random prime numbers, computes the public and private keys, and performs encryption and decryption.

### 2. `encryption_optimized.cpp`

- Uses **GMP**'s `mpz_class` for arbitrary-precision arithmetic, enabling it to handle large RSA key sizes securely.
- Includes optimized functions for modular exponentiation and modular inverse (`find_d`) using the Extended Euclidean Algorithm, which is faster and more suitable for cryptographic use cases.
- Suitable for larger messages and realistic RSA encryption due to its support for very large numbers.

## Keywords

- **RSA Encryption**: Public key cryptography algorithm used for secure data transmission.
- **macOS**: Platform dependency, uses macOS-specific `SecRandomCopyBytes`.
- **GMP**: GNU Multiple Precision Arithmetic Library, necessary for high-precision calculations.
- **Modular Arithmetic**: Key concept in cryptography, used in both modular exponentiation and modular inverse.
- **Extended Euclidean Algorithm**: Algorithm for finding the modular inverse, used in optimized version.
- **Secure Random Number Generation**: Used in cryptographic applications, specifically for generating keys.
- **Public Key Cryptography**: Encryption system where encryption and decryption use different keys.
- **High-precision Arithmetic**: Important for cryptography to handle large numbers securely.

## License

This project is open for educational purposes.

