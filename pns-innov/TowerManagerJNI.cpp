#include <iostream>
#include "TowerManagerJNI.h"
#include "TowerManager.h"
#include "OurJNILib.h"

using std::cout;
using std::endl;

extern "C" {
#pragma warning(disable:4100)
	JNIEXPORT jlong JNICALL Java_TowerManagerJNI_nativeNew(JNIEnv* env, jobject obj, 
		jobject pathVector, jobject buildableVector, jobject towersRange) {
		std::vector<int> _towersRange = builCopyOfArrayList(env, towersRange);
		std::vector<std::array<int, 2>> _pathVector = builCopyOfArrayListOfArray(
			env, pathVector);
		std::vector<std::array<int, 2>> _buildableVector = builCopyOfArrayListOfArray(
			env, buildableVector);
		/*
		cout << "_towersRange= " << endl;
		for (int i = 0; i < _towersRange.size(); i++)
			cout << _towersRange[i] << " ";
		cout << endl;
		cout << "pathVector= " << endl;
		print_debug(_pathVector);
		cout << "buildableVector= " << endl;
		print_debug(_buildableVector); */
		pns::TowerManager* p = new pns::TowerManager(_pathVector, _buildableVector, _towersRange);
		return reinterpret_cast<jlong>(p);
	}
#pragma warning(default:4100)
}