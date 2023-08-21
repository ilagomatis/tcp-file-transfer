#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

/*

this function gets as input a string and and a separator
character and returns an array of strings. This array contais 
the words in the string, separated by a specific character. For 
example:

int size;
split("hello_world", '_', &size) -> ["hello", "world"]

'size' will contain the number of words.

*/

char** split(char *string, char separator, int* size);


/*

reads a binary file and returns a pointer on the buffer 
that the content were written. 'bytes' will contain the 
number of bytes.
*/
unsigned char* getBinaryContent(char* path, int* bytes);

#endif /* __STRING_UTILS_H__ */