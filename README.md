# RSA Cryptography

## Overview

This repository contains two implementations of the RSA (Rivest–Shamir–Adleman) cryptographic algorithm, developed using the C programming language.

The project explores the mathematical principles of RSA through two different approaches: a command-line application developed in C and a web application integrating C, Python, Flask, HTML, CSS, and JavaScript.

Both implementations allow users to generate RSA keys, encrypt messages, and decrypt previously encrypted messages.

## Project Implementations

### 1. RSA in C - Command Line Application

A terminal-based implementation of the RSA cryptographic algorithm, developed entirely in C.

**Features:**
- Prime number validation.
- RSA key generation.
- Public and private exponent calculation.
- Message encryption and decryption.
- Modular arithmetic operations.
- File handling for storing keys and encrypted messages.
- Dynamic memory allocation.

**Technologies:**
- C

[View C Implementation](./01-rsa-c/)

### 2. RSA Web Application

A web-based implementation that integrates the C cryptographic program with a Python backend and a graphical frontend.

The application uses C for the RSA mathematical operations, while Python and Flask handle API requests and communication between the frontend and the C executable.

**Features:**
- Graphical interface for RSA operations.
- RSA key generation.
- Message encryption and decryption.
- Communication between Python and C using `subprocess`.
- HTTP requests and JSON data exchange.
- Integration between frontend and backend.

**Technologies:**
- C
- Python
- Flask
- Flask-CORS
- HTML
- CSS
- JavaScript

[View Web Implementation](./02-rsa-web/)

## Project Structure

```text
RSA-Cryptography/
│
├── .gitignore
│
├── 01-rsa-c/
│   ├── src/
│   ├── docs/
│   └── README.md
│
├── 02-rsa-web/
│   ├── backend/
│   ├── frontend/
│   ├── rsa/
│   └── README.md
│
└── README.md
```

## Screenshots

Screenshots of the applications will be added here.

### Command Line Application

<!-- Add terminal screenshots here -->

### Web Application

<!-- Add web application screenshots here -->

## Educational Purpose and Limitations

This project was developed for educational purposes, focusing on understanding the mathematical foundations of the RSA algorithm and its implementation.

The implementations use simplified numerical and character encoding approaches and are not intended for real-world security applications.

They do not include modern cryptographic padding schemes or the security mechanisms required for production-grade RSA systems.

## Author's Contribution

The C implementations and Python backend were developed by the author.

The frontend was developed with AI assistance, under the author's guidance and direction regarding the interface design, visual organization, functionality, and overall application structure.