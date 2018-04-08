#ifndef FILE_PARSER_H
#define FILE_PARSER_H
#include <stddef.h>

/**
 * a function which loads a file containing a list of float values 
 * takes a custom function pointer to convert each line to a float
 * @param 
 * @param filename string path of the file to parse
 * @param point to size_t to retun the length of the float list
 * @return an array of floats which have been parse, NULL if there was an error
 */
float* parseFile(char* filename, float(*convert)(char*), size_t* return_len);

/**
 * takes a string, reverses it then converts to float with atof
 * @param input_str a point to a char array which will be revered then converted to float
 * @return the converted float value
 */
float reverseStringToFloat(char* input_str);

#endif