#include "OurJNILib.h"
#include <iostream>

using std::cout;
using std::endl;

void rapid_print(std::string str) {
	cout << str << endl;
}
void print_debug(std::vector<std::array<int, 2>> list) {
	for (int i = 0; i < list.size(); i++) {
		for (int j = 0; j < 2; j++)
			cout << list[i][j] << " ";
		cout << endl;
	}

}
#pragma warning(disable:4190)
std::vector<int> builCopyOfArrayList(JNIEnv* env, jobject list) {
	jclass listClass = env->FindClass("java/util/ArrayList");
	jmethodID listGetId = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
	jmethodID listSizeId = env->GetMethodID(listClass, "size", "()I");
	jclass integerClass = env->FindClass("java/lang/Integer");
	jmethodID intValueMid = env->GetMethodID(integerClass, "intValue", "()I");
	jvalue arg;
	std::vector<int> res;
	jint pointCount = env->CallBooleanMethodA(list, listSizeId, &arg);
	for (int i = 0; i < pointCount; i++) {
		arg.i = i;
		jobject temp = env->CallObjectMethodA(list, listGetId, &arg);
		int _val = env->CallIntMethodA(temp, intValueMid, &arg);
		res.push_back(_val);
	}
	return res;
#pragma warning(default:4190)
}
std::vector<std::array<int, 2>> builCopyOfArrayListOfArray(JNIEnv* env, jobject listOfArrays) {
	jclass listClass = env->FindClass("java/util/ArrayList");
	jmethodID listGet = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
	jmethodID listSize = env->GetMethodID(listClass, "size", "()I");
	//jclass integerClass = env->FindClass("java/lang/Integer");
	//jmethodID intValueMid = env->GetMethodID(integerClass, "intValue", "()I");
	//jclass arrayClass = env->FindClass("java/lang/reflect/Array");
	//jmethodID getArrayID = env->GetMethodID(arrayClass, "get", "(I)Ljava/lang/Object;");

	std::vector<std::array<int, 2>> res;
	int dim1 = env->CallIntMethod(listOfArrays, listSize);
	for (int i = 0; i < dim1; i++) {
		jintArray temp_array = static_cast<jintArray>(
			env->CallObjectMethod(listOfArrays, listGet, i));
		//jintArray bof = env->
		jint temp_sub_array[2];
		env->GetIntArrayRegion(temp_array, 0, 2, temp_sub_array);
		std::array<int, 2> sub_array = {
			static_cast<int>(temp_sub_array[0]),
			static_cast<int>(temp_sub_array[1])
		};
		res.insert(res.end(), sub_array);
	}
	return res;
}

jobject vectorToJavaIntegerList(JNIEnv* env, std::vector<int> base) {
	size_t size = base.size();
	jint element;
	jclass java_util_ArrayList = static_cast<jclass>(
		env->NewGlobalRef(env->FindClass("java/util/ArrayList")));
	jmethodID java_util_ArrayList_method = env->GetMethodID(
		java_util_ArrayList, "<init>", "(I)V");
	jmethodID java_util_ArrayList_add = env->GetMethodID(
		java_util_ArrayList, "add", "(Ljava/lang/Object;)Z");
	jclass integerClass = env->FindClass("java/lang/Integer");
	jmethodID intClassMID = env->GetMethodID(integerClass, "<init>", "(I)V");
	jobject res = env->NewObject(
		java_util_ArrayList, java_util_ArrayList_method, size);

	for (int i = 0; i < size; i++) {
		element = static_cast<jint>(base.at(i));
		jobject newObj = env->NewObject(integerClass, intClassMID, element);
		env->CallBooleanMethod(res, java_util_ArrayList_add, newObj);
	}
	return res;
}