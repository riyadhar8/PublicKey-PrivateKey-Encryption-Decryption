# PublicKey-PrivateKey-Encryption-Decryption
C program to encrypt a file using an RSA public key and decrypt it using an RSA private key.

## Step1: Download OpenSSL library  
OpenSSL can be downloaded using `sudo apt-get install libssl-dev` on the command line.  

## Step2: Generate Private Key
To generate a 1024 byte long private key, use `openssl genrsa -out private.pem`  
To generate a 4096 byte long private key, use `openssl genrsa -out private.pem 4096`  
The maximum size of input.txt possible depends upon this private key generated. My encrypt and decrypt code uses 1024 in its char array, this can be increased to 4096 if required.

## Step3: Generate Public Key
Using the private key obtained in the previous step, a public key can be generated using `openssl rsa -pubout -in private.pem -out public.pem`

## Step4: Compiling the program files
`make`

## Step5: Run encrypt.c
`./encrypt public.pem input.txt encrypted.txt`  
The executable takes the name of the public key, the name of the file that is to be encrypted and the name of the file where the encrypted data is to be stored.

## Step6: Run decrypt.c
`./decrypt private.pem encrypted.txt decrypted.txt`  
The executable takes the name of the private key, the encrypted text, and the name of the file where the decrypted data is to be stored.
