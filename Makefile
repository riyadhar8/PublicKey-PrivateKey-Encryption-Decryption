all:	encrypt	decrypt

encrypt:	encrypt.c 
		gcc encrypt.c -o encrypt -lcrypto -lssl

decrypt:	decrypt.c 
		gcc decrypt.c -o decrypt -lcrypto -lssl

clean:		
		rm -rf encrypt decrypt
