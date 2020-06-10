#include "GeneticBot.h"
#include "GeneticBotJNI.h"
#include <vector>
#include <iostream>
using std::cout;
using std::endl;

extern "C" {

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

	jlong getNativePointer(JNIEnv* env, jobject obj) {
		jclass jclass = env->FindClass("GeneticBotJNI");
		jfieldID valId = env->GetFieldID(jclass, "nativeObjectPtr", "J");
		jlong longVal = env->GetIntField(obj, valId);
		// cout << "longVal= " << longVal << endl;
		return longVal;
	}

#pragma warning(disable:4100)
	JNIEXPORT jlong JNICALL Java_GeneticBotJNI_nativeNew(JNIEnv* env, jobject obj, jobject list) {
		pns::GeneticBot* p = new pns::GeneticBot(builCopyOfArrayList(env, list));
		return reinterpret_cast<jlong>(p);
#pragma warning(default:4100)
	}

#pragma warning(disable:4100)
	JNIEXPORT jobject JNICALL Java_GeneticBotJNI_getDecisionMap(JNIEnv* env, jobject obj) {
		// cout << "last checkpoint" << endl;
		pns::GeneticBot* bot = reinterpret_cast<pns::GeneticBot*>(getNativePointer(env, obj));
		// cout << "bot= " << bot << endl;
		// cout << "bot->decisionMap.size()= " << bot->getDecisionMap().size() << endl;
		return vectorToJavaIntegerList(env, bot->getDecisionMap());
#pragma warning(default:4100)
	}


#pragma warning(disable:4100)
	JNIEXPORT jobject JNICALL Java_GeneticBotJNI_getValuesUnder(
		JNIEnv* env, jobject obj, jobject list, jint max) {
		std::vector<int> copy = builCopyOfArrayList(env, list);
		pns::GeneticBot* bot = reinterpret_cast<pns::GeneticBot*>(getNativePointer(env, obj));
		copy = bot->getValuesUnder(copy, static_cast<int>(max));
		jobject res = vectorToJavaIntegerList(env, copy);
		return res;
#pragma warning(default:4100)
	}

}