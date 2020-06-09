#include "GeneticBot.h"
#include "GeneticBotJNI.h"
#include <vector>
#include <iostream>

extern "C" {
	std::vector<int> builCopyOfArrayList(JNIEnv* env, jobject list) {
		jclass listClass = env->FindClass("java/util/ArrayList");
		jmethodID listGetId = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
		jmethodID listSizeId = env->GetMethodID(listClass, "size", "()I");
		std::vector<int> res;
		int pointCount = static_cast<int>(env->CallIntMethod(list, listSizeId));
		for (int i = 0; i < pointCount; i++) {
			int temp = static_cast<int>(env->CallIntMethod(list, listGetId, i));
			res.push_back(temp);
		}
		return res;
	}

	#pragma warning(disable:4100)
	JNIEXPORT jlong JNICALL Java_GeneticBotJNI_nativeNew(JNIEnv* env, jobject obj, jobject list) {
		pns::GeneticBot* p = new pns::GeneticBot(builCopyOfArrayList(env, list));
		std::cout << "coucou l asticot " << std::endl;
		return reinterpret_cast<jlong>(p);
		#pragma warning(default:4100)
	}

	JNIEXPORT jobject JNICALL Java_GeneticBotJNI_getValuesUnder(
		JNIEnv*, jobject, jobject, jint) {
		return nullptr;
	}

}