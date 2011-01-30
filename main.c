#include "sha256.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int hash_file(const char *path);
static const char *prompt_file(void);
static char *showDigest(unsigned char *digest, int len, char *out);
static void chomp(char *str);

int main(int argc, char *argv[])
{
	int status = EXIT_SUCCESS;
	
	if (argc > 1) {
		int i;
		
		fprintf(stderr, "Hashing...\n");
		
		for (i = 1; i < argc; i++) {
			if (hash_file(argv[i]) != 0)
				status = EXIT_FAILURE;
		}
	} else {
		const char *path = prompt_file();
		
		fprintf(stderr, "Hashing %s\n", path);
		
		if (hash_file(path) != 0)
			status = EXIT_FAILURE;
	}
	
	return status;
}

static int hash_file(const char *path)
{
	unsigned char digest[SHA256_HASH_SIZE];
	char buffer[sizeof(digest) * 2 + 1];
	
	if (SHA256File(path, digest) != 0) {
		perror(path);
		return -1;
	}
	
	printf("%s\n    %s\n", showDigest(digest, sizeof(digest), buffer), path);
	return 0;
}

static const char *prompt_file(void)
{
	static char buffer[1024];
	
	printf("File: ");
	if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
		fprintf(stderr, "No file path given\n");
		exit(EXIT_FAILURE);
	}
	
	chomp(buffer);
	return buffer;
}

static char *showDigest(unsigned char *digest, int len, char *out)
{
	static const char hex[16] = "0123456789abcdef";
	char *ret = out;
	
	while (len--) {
		unsigned char b = *digest++;
		*out++ = hex[b >> 4];
		*out++ = hex[b & 0xF];
	}
	*out = 0;
	
	return ret;
}

static void chomp(char *str)
{
	char *end = strchr(str, '\0');
	
	if (end > str && end[-1] == '\n')
		end[-1] = '\0';
}