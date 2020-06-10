#include "../Dependencies/include/include/jni.h"
#include <vector>
#include <array>
#ifndef _Our_JNI_LIB
#define _Our_JNI_LIB
#include <string>

void print_debug(std::vector<std::array<int, 2>> list);

void rapid_print(std::string str);

// to copy Java ArrayList<Integer> into Cpp std::vector<int>
std::vector<int> builCopyOfArrayList(JNIEnv* env, jobject list);

std::vector<std::array<int, 2>> builCopyOfArrayListOfArray(JNIEnv* env, jobject listOfArrays);

jobject vectorToJavaIntegerList(JNIEnv* env, std::vector<int> base);

#endif