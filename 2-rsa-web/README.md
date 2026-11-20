# RSA Cryptography - Web Application

## Overview

This project is a web-based implementation of the RSA (Rivest–Shamir–Adleman) cryptographic algorithm, integrating C, Python, Flask, HTML, CSS, and JavaScript.

The application provides a graphical interface that allows users to generate RSA keys, encrypt messages, and decrypt previously encrypted messages.

The project combines the computational logic implemented in C with a Python backend responsible for processing requests and communicating with the frontend.

## Features

- RSA key generation.
- Message encryption and decryption.
- Prime number validation.
- Calculation of public and private exponents.
- Modular arithmetic operations implemented in C.
- Backend API developed with Python and Flask.
- Communication between Python and C using `subprocess`.
- Data exchange between frontend and backend using HTTP requests and JSON.
- Graphical interface developed with HTML, CSS, and JavaScript.

## Technologies

- **C** - RSA mathematical operations and cryptographic processing.
- **Python** - Backend development and process management.
- **Flask** - API development.
- **Flask-CORS** - Cross-Origin Resource Sharing configuration.
- **HTML** - Frontend structure.
- **CSS** - Interface styling.
- **JavaScript** - Frontend interactions and HTTP requests.

## Project Architecture

The application is divided into three main components:

### 1. C - Cryptographic Processing

The C program contains the RSA implementation and performs the main mathematical operations.

It is responsible for:

- Generating RSA keys.
- Encrypting messages using the public key.
- Decrypting messages using the private key.
- Processing the numerical representation of characters.

### 2. Python and Flask - Backend

The Python backend acts as an intermediary between the frontend and the C executable.

It is responsible for:

- Receiving HTTP requests from the frontend.
- Processing JSON data.
- Executing the C program using Python's `subprocess` module.
- Capturing the output returned by the C executable.
- Sending the results back to the frontend in JSON format.

The RSA mathematical operations remain implemented in C. Python manages the communication and execution of the cryptographic program.

### 3. Frontend - User Interface

The frontend provides the graphical interface through which users interact with the application.

It was developed using HTML, CSS, and JavaScript.

It is responsible for:

- Displaying the application interface.
- Collecting user input.
- Sending requests to the Python backend.
- Displaying generated keys and cryptographic results.

## API Endpoints

The Flask backend provides the following endpoints:

| Method | Endpoint | Description |
|---|---|---|
| GET | `/` | Root endpoint for application access or status checking. |
| POST | `/gerar-chaves` | Generates RSA keys. |
| POST | `/criptografar` | Encrypts a message. |
| POST | `/descriptografar` | Decrypts a message. |

The POST endpoints receive data in JSON format and return the results in JSON format.

## Communication Between C and Python

The communication between Python and C is performed through the `subprocess` module.

The backend executes the compiled C program, passes the required arguments through the command line, captures its standard output and error output, and processes the returned results.

This approach allows the mathematical implementation to remain in C while Python handles the API and communication with the frontend.

## Project Structure

```text
02-rsa-web/
├── backend/
│   └── app.py
│
├── frontend/
│   ├── index.html
│   ├── script.js
│   └── style.css
│
├── rsa/
│   └── criptografia_RSA.c
│
└── README.md
```

## Installation and Execution

### Requirements

Make sure the following tools are installed:

- Python 3
- GCC compiler
- pip (Python package manager)

### 1. Install Python Dependencies

Install the required packages:

```bash
pip install flask flask-cors
```

### 2. Compile the C Program

The C source code must be compiled before running the backend.

From the `02-rsa-web` directory, compile the program into the expected output directory:

```bash
gcc rsa/criptografia_RSA.c -o rsa/output/criptografia_RSA.exe
```

Make sure the `rsa/output/` directory exists before compiling.

### 3. Start the Backend

From the `02-rsa-web` directory, run:

```bash
python backend/app.py
```

### 4. Open the Frontend

Open `frontend/index.html` in a browser or use a local development server.

Make sure the Flask backend is running before interacting with the application.

## Limitations

This project is an educational implementation of RSA and is not intended for real-world security applications.

The implementation uses numerical limitations associated with the `long long int` data type and a simplified character encoding scheme.

It does not implement modern cryptographic padding schemes or the security mechanisms required for production-grade RSA systems.

## Author's Contribution

The C implementation and Python backend were developed by the author.

The frontend was developed with AI assistance, under the author's guidance and direction regarding the interface design, visual organization, functionality, and overall application structure.