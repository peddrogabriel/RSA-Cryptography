# RSA Cryptography in C

## Overview

This project implements the RSA (Rivest–Shamir–Adleman) cryptographic algorithm using the C programming language.

The application provides a menu-driven interface that allows users to generate RSA keys, encrypt messages, and decrypt previously encrypted messages.

This implementation was developed for educational purposes, focusing on the mathematical principles behind RSA and their practical implementation in C.

## Features

- Prime number validation.
- RSA key generation using two distinct prime numbers.
- Calculation of the public and private exponents.
- Greatest Common Divisor (GCD) calculation using the Euclidean algorithm.
- Extended Euclidean algorithm to calculate the modular multiplicative inverse.
- Efficient modular exponentiation using the binary exponentiation method.
- Modular multiplication designed to reduce integer overflow risks.
- Message encryption and decryption.
- File handling to save and retrieve keys and encrypted messages.
- Dynamic memory allocation for message processing.

## How It Works

The application follows the main mathematical steps of the RSA algorithm:

1. Two distinct prime numbers (`p` and `q`) are provided.
2. The modulus `n` and Euler's totient function `φ(n)` are calculated.
3. A public exponent `e` is selected, satisfying the required coprimality condition.
4. The private exponent `d` is calculated using the Extended Euclidean Algorithm.
5. The public key `(n, e)` is used for encryption.
6. The private exponent `d` is used for decryption.

The program converts each supported character into a numerical representation before applying the RSA modular exponentiation operation.

## Technologies

- **C**
- Standard C libraries:
  - `stdio.h`
  - `string.h`
  - `stdlib.h`
  - `limits.h`

## Project Structure

```text
01-rsa-c/
├── src/
│   └── criptografia_RSA.c
├── docs/
└── README.md

## Compilation and Execution

Make sure you have a C compiler, such as GCC, installed.

From the `01-rsa-c` directory, compile the program:

```bash
gcc src/criptografia_RSA.c -o rsa.exe
```

Run the application on Windows:

```powershell
.\rsa.exe
```

On Linux or macOS, compile and execute with:

```bash
gcc src/criptografia_RSA.c -o rsa
./rsa
```

## Message Format

The current implementation supports:

- Uppercase letters (A–Z).
- Spaces.

Lowercase letters, accented characters, punctuation, and other symbols are not supported.

## Limitations

This project is an educational implementation of RSA and is **not intended for real-world security applications**.

It uses the `long long int` data type, which imposes numerical limits on the key sizes. Additionally, the message is encrypted character by character using a simplified encoding scheme.

The implementation does not include modern cryptographic padding schemes or the security measures required by production-grade RSA systems.

## Author's Contribution

The C implementation, including the RSA mathematical functions, key generation, encryption, decryption, and file handling, was developed by the author.