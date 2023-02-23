#include <blib.h>

size_t strlen(const char *s) {
	// panic("please implement");
	int n = 0;
	while (*s++){
		n++;
	}
	return n;
}

char *strcpy(char *dst, const char *src) {
	// panic("please implement");
	char *res = dst;
	while (*src) {
		*dst++ = *src++;
	}
	*dst = '\0';
	return res;
}

char *strncpy(char *dst, const char *src, size_t n) {
	char *res = dst;
	while (*src && n--) {
		*dst++ = *src++;
	}
	*dst = '\0';
	return res;
}

char *strcat(char *dst, const char *src) {
	// panic("please implement");
	char *res = dst;
	dst += strlen(dst);
	while (*src){
		*dst++ = *src++; 
	}
	*dst = '\0';
	return res;
}

int strcmp(const char *s1, const char *s2) {
	// panic("please implement");
	while (*s1 || *s2){
		if (*s1 != *s2) {
			return *s1 - *s2;
		}
		s1++;
		s2++;
	}
	return 0;
	
}

int strncmp(const char *s1, const char *s2, size_t n) {
	while (n--) {
		if (*s1 != *s2) {
			return *s1 - *s2;
		}
		// ???
		if (*s1 == 0) {
			break;
		}
		s1++;
		s2++;
	}
	return 0;
}

void *memset(void *s, int c, size_t n) {
	// panic("please implement");
	void *res = s;
	char *dst = (char *)s;
	for (int i = 0; i < n; i++) {
		dst[i] = (char)c;
	}
	return res;
}

void *memcpy(void *out, const void *in, size_t n) {
	char *csrc = (char *)in;
	char *cdest = (char *)out;
	for (int i = 0; i < n; i++) {
		cdest[i] = csrc[i];
	}
	return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
	// panic("please implement");
	unsigned char *q1 = (unsigned char *)s1;
	unsigned char *q2 = (unsigned char *)s2;
	while(n--){
		if (*q1 != *q2){
			return *q1 - *q2;
		}
		q1++;
		q2++;
	}
	return 0;

}
