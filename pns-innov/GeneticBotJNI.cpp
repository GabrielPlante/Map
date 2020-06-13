#include "GeneticBot.h"
#include "GeneticBotJNI.h"
#include "OurJNILib.h"
#include <vector>
#include <iostream>
using std::cout;
using std::endl;

extern "C" {
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