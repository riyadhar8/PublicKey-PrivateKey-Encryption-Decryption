#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

int main(int argc, char *argv[]) {
    if (argc<4) {
        printf("Too few arguments. You must input the private key, name of the encrypted file, and the name of the output (decrypted) file as inputs.\n");
        exit(1);
    }
    else
        printf("----> Received the file names.\n");

    //reading the private key
    FILE *private = fopen(argv[1], "r");
    if (private == NULL) {
        printf("Cannot open private key file.\n");
        exit(1);
    }

    RSA *rsa = PEM_read_RSAPrivateKey(private, NULL, NULL, NULL);
    if (rsa == NULL) {
        printf("Cannot open private key.\n");
        exit(1); 
    }
    else
        printf("----> Private key read successfully.\n");

    fclose(private);

    //reading encrypted file
    FILE *input = fopen(argv[2], "r");
    if (input == NULL) {
        printf("Cannot open the file that is to be decrypted.\n");
        exit(1);
    }

    //getting the size of encrypted file
    char *encrypted;
    fseek(input, 0, SEEK_END);
    int len_encrypted = ftell(input);
    fseek(input, 0, SEEK_SET);
    encrypted = (char *)malloc(len_encrypted * sizeof(char));
    fread(encrypted, len_encrypted, 1, input);
    fclose(input);

    //maximum size. can be changed to 4096 in case the length of the key is 4096 bytes
    char decrypted[1024];

    //decryption and storing the decrypted data in the char array 'decrypted'	
    int len_decrypted = RSA_private_decrypt(len_encrypted, encrypted, decrypted, rsa, RSA_PKCS1_PADDING);
    if (len_decrypted == -1){
        printf("Cannot decrypt.\n");
        exit(1);
    }
    else
        printf("----> Successfully decrypted! Storing it in output file.\n");

    //storing decrypted data in a file
    FILE *output = fopen(argv[3], "w");
    if (output != NULL) {
        fwrite(decrypted, len_decrypted, 1, output);
        fclose(output);
        printf("----> Stored successfully.\n");
    }

    return 0;
}

