#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>

int main(int argc, char *argv[]) {
    if (argc<4) {
        printf("Too few arguments. You must input the public key, name of the file, and the name of the output (encrypted) file as inputs.\n");
        exit(1);
    }
    else
        printf("----> Received the file names.\n");

    //reading public.pem
    FILE *public = fopen(argv[1], "r");
    if (public == NULL) {
        printf("Cannot open public key file.\n");
        exit(1);
    }

    RSA* rsa = PEM_read_RSA_PUBKEY(public, NULL, NULL, NULL);
    if(rsa==NULL){
        printf("Cannot open public key.\n");
        exit(1);
    }
    else
        printf("----> Public key read successfully.\n");

    //reading input.txt
    FILE *input = fopen(argv[2], "r");
    if (input == NULL) {
        printf("Cannot open the file that is to be encrypted.\n");
        exit(1);
    }

    //getting the size of input.txt so that we can encrypt that many bytes
    char *text;
    fseek(input, 0, SEEK_END);
    int size = ftell(input);
    fseek(input, 0, SEEK_SET);
    text = (char *)malloc(size*sizeof(char));
    fread(text, sizeof(char), size, input);
    fclose(input);

    //1024 is the maximum size, 41 is the padding at the end. hence size(input.txt) <= maxSize - paddedSize 
    char encrypted[1024];
    if (strlen(text) >= RSA_size(rsa) - 41){
        printf("Cannot encrypt (1).\n");
        exit(1);
    }
    
    fclose(public);

    //encryption
    int len_encrypted = RSA_public_encrypt(size, text, encrypted, rsa, RSA_PKCS1_PADDING);
    if (len_encrypted == -1) {
        printf("Cannot encrypt (2).\n");
        exit(1);
    }
    else
        printf("----> Successfully encrypted! Storing it in output file.\n");
    

    //storing encrypted data in a file
    FILE *output = fopen(argv[3], "w");
    if (output != NULL) {
        fwrite(encrypted, len_encrypted, 1, output);
        fclose(output);
        printf("----> Stored successfully.\n");
    }

    return 0;

}

