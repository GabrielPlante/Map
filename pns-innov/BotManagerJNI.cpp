#include "BotManagerJNI.h"
#include <iostream>
#include "OurJNILib.h"
#include <map>


using std::cout;
using std::endl;
#ifdef __cplusplus
extern "C" {
#endif
jobject hwe_Iface, snw_Iface, hge_Iface, sng_Iface, gm_Iface;
jmethodID hwe_method, snw_method, hge_method, sng_method, gm_method;
JNIEnv *big_env;

typedef bool (*bool_func)();
typedef void (*void_func)();
typedef int (*int_func)();

typedef struct _group {
    jobject Iface;
    jmethodID method;
    JNIEnv* env;
} _group;

void startNextWave_wrapper() {
    big_env->ExceptionClear();
    big_env->CallVoidMethod(snw_Iface, snw_method);
    if (big_env->ExceptionOccurred()) {
        cout << "error calling bool_func()" << endl;
        big_env->ExceptionClear();
    }
}
void startNewGame_wrapper() {
    big_env->ExceptionClear();
    big_env->CallVoidMethod(sng_Iface, sng_method);
    if (big_env->ExceptionOccurred()) {
        cout << "error calling bool_func()" << endl;
        big_env->ExceptionClear();
    }
}
bool hasWaveEnded_wrapper() {
    jboolean retval;
    big_env->ExceptionClear();
    retval = big_env->CallBooleanMethod(hwe_Iface, hwe_method);
    if (big_env->ExceptionOccurred()) {
        cout << "error calling bool_func()" << endl;
        big_env->ExceptionClear();
    }
    if (retval == true) {
        return true;
    } else {
        return false;
    }
}
bool hasGameEnded_wrapper() {
    jboolean retval;
    big_env->ExceptionClear();
    retval = big_env->CallBooleanMethod(hge_Iface, hge_method);
    if (big_env->ExceptionOccurred()) {
        cout << "error calling bool_func()" << endl;
        big_env->ExceptionClear();
    }
    if (retval == true) {
        return true;
    }
    else {
        return false;
    }
}
int getMoney_wrapper() {
    jint retval;
    big_env->ExceptionClear();
    retval = big_env->CallIntMethod(gm_Iface, gm_method);
    if (big_env->ExceptionOccurred()) {
        cout << "error calling bool_func()" << endl;
        big_env->ExceptionClear();
    }
    return static_cast<int>(retval);
}

// 2nd paramter: if does not return Bool, it returns void
void setData(jobject _interface, int type, jmethodID* methodID, jobject* iface) {
    *iface = _interface;
    jclass objclass = big_env->GetObjectClass(_interface);

    switch (type) {
    case 0:
        *methodID = big_env->GetMethodID(objclass, "func", "()V");
        break;
    case 1:
        *methodID = big_env->GetMethodID(objclass, "func", "()Z");
        break;
    case 2:
        *methodID = big_env->GetMethodID(objclass, "func", "()I");
        break;
    }
    if (*methodID == 0) {
        std::cout << "could not get method id!" << std::endl;
        return;
    } 
}

JNIEXPORT jlong JNICALL Java_BotManagerJNI_nativeNew(
	JNIEnv* env, jobject obj, 
    jobject _hasWaveEnded_func, jobject _startNextWave_func,
    jobject _hasGameEnded_func, jobject _startNewGame_func,
    jobject _getMoney_func, jobject _placeTower_func) {
    
    jclass objclass;
    big_env = env;

    setData(_hasWaveEnded_func, 1, &hwe_method, &hwe_Iface);
    bool_func hasWaveEnded = hasWaveEnded_wrapper;
    setData(_startNextWave_func, 0, &snw_method, &snw_Iface);
    void_func startNextWave = startNextWave_wrapper;
    setData(_hasGameEnded_func, 1, &hge_method, &hge_Iface);
    bool_func hasGameEnded = hasGameEnded_wrapper;
    setData(_startNewGame_func, 0, &sng_method, &sng_Iface);
    void_func startNewGame = startNewGame_wrapper;
    setData(_getMoney_func, 2, &gm_method, &gm_Iface);
    int_func getMoney = getMoney_wrapper;

    cout << "hasGameEnded()= " << hasGameEnded() << endl;

    cout << "getMoney()= " << getMoney() << endl;
    cout << "startNewGame()=> " << endl;
    startNewGame();
    cout << "startNextWave.func()=> " << endl;
    startNextWave();
    cout << "hasWaveEnded.func()= " << hasWaveEnded() << endl;
    
    /*
    cout << "----\n" <<"hasWaveEnded.func()= " << hasWaveEnded() << endl;
    cout << "startNextWave.func()=> " << endl;
    startNextWave(); */

	return 0; 
}

#ifdef __cplusplus
}
#endif