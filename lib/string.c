#include <types.h>

void *memcpy(void *dst, const void *src, size_t n)
{
	void *dstaddr = dst;
	void *max = dst + n;

	if (((u_long)src & 3) != ((u_long)dst & 3))
	{
		while (dst < max)
		{
			*(char *)dst++ = *(char *)src++;
		}
		return dstaddr;
	}

	while (((u_long)dst & 3) && dst < max)
	{
		*(char *)dst++ = *(char *)src++;
	}

	// copy machine words while possible
	while (dst + 4 <= max)
	{
		*(uint32_t *)dst = *(uint32_t *)src;
		dst += 4;
		src += 4;
	}

	// finish the remaining 0-3 bytes
	while (dst < max)
	{
		*(char *)dst++ = *(char *)src++;
	}
	return dstaddr;
}

void *memset(void *dst, int c, size_t n)
{
	void *dstaddr = dst;
	void *max = dst + n;
	u_char byte = c & 0xff;
	uint32_t word = byte | byte << 8 | byte << 16 | byte << 24;

	while (((u_long)dst & 3) && dst < max)
	{
		*(u_char *)dst++ = byte;
	}

	// fill machine words while possible
	while (dst + 4 <= max)
	{
		*(uint32_t *)dst = word;
		dst += 4;
	}

	// finish the remaining 0-3 bytes
	while (dst < max)
	{
		*(u_char *)dst++ = byte;
	}
	return dstaddr;
}

size_t strlen(const char *s)
{
	int n;

	for (n = 0; *s; s++)
	{
		n++;
	}

	return n;
}

char *strcpy(char *dst, const char *src)
{
	char *ret = dst;

	while ((*dst++ = *src++) != 0)
	{
	}

	return ret;
}

const char *strchr(const char *s, int c)
{
	for (; *s; s++)
	{
		if (*s == c)
		{
			return s;
		}
	}
	return 0;
}

int strcmp(const char *p, const char *q)
{
	while (*p && *p == *q)
	{
		p++, q++;
	}

	if ((u_int)*p < (u_int)*q)
	{
		return -1;
	}

	if ((u_int)*p > (u_int)*q)
	{
		return 1;
	}

	return 0;
}

void strcat(char *src, char *target)
{
	while (*src)
	{
		src++;
	}
	while (*target)
	{
		*src = *target;
		src++;
		target++;
	}
	*src = 0;
}
int strncmp(const char *s1, const char *s2, size_t len)
{

	while (len--)
	{
		if (*s1 == 0 || *s1 != *s2)
			return *s1 - *s2;
		s1++;
		s2++;
	}
	return 0;
}

void insert(char *str, int i, char *s, int len)
{
	int slen = strlen(str); // 原字符串长度
	int j;
	if (i < 0 || i > slen)
	{
		// printf("Error: invalid index %d\n", i);
		return;
	}
	// 把插入位置之后的字符依次向后移动len个位置
	for (j = slen; j >= i; j--)
	{
		str[j + len] = str[j];
	}
	// 在插入位置处插入字符串s
	for (j = 0; j < len; j++)
	{
		str[i + j] = s[j];
	}
}

void delete(char *str, int i, int len)
{
	if (str == NULL || i < 0 || i >= strlen(str))
	{
		return;
	}
	char *p = str + i; // 删除位置的指针
	char *q = p + len; // 删除位置后len个字符的指针
	while (*q != '\0')
	{
		*p = *q; // 把后面的字符依次向前移动len个位置
		p++;
		q++;
	}
	*p = '\0'; // 在字符串末尾添加空字符
}

char *
strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';

	return dest;
}

void replace(char *src, char *obj, int len_obj, char *rep)
{
	int len_src = strlen(src); // 源字符串长度
	int len_rep = strlen(rep); // 替换字符串长度
	int i, j, k;
	char temp[100];
	memset(temp, 0, sizeof temp);
	i = j = k = 0;
	while (src[i] != '\0')
	{
		if (strncmp(src + i, obj, len_obj) == 0)
		{						   // 如果找到了目标字符串
			strcpy(temp + j, rep); // 把替换字符串复制到临时字符串中
			j += len_rep;		   // 更新临时字符串的位置
			i += len_obj;		   // 更新源字符串的位置，跳过目标字符串
		}
		else
		{					  // 如果没有找到目标字符串
			temp[j] = src[i]; // 把源字符串的当前字符复制到临时字符串中
			j++;			  // 更新临时字符串的位置
			i++;			  // 更新源字符串的位置
		}
	}
	temp[j] = '\0';	   // 在临时字符串末尾添加空字符
	strcpy(src, temp); // 把临时字符串复制回源字符串
}
