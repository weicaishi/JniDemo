#include "stdafx.h"
#include "java\jniDemo_JniDll.h"



typedef union
{
	unsigned long UL;
	signed long SL;
} JObjValue;
JObjValue covJObj(const char FAR *format, ...)

{
	JObjValue value;
	va_list sp;
	va_start(sp, format);
	value = va_arg(sp, JObjValue);
	va_end(sp);
	return value;
}


JNIEXPORT void JNICALL Java_jniDemo_JniDll_init
(JNIEnv *env, jobject jObj)
{
	JObjValue obj = covJObj("", *jObj);
	printf("obj init  JNIEnv:%p  jObject:%p  %d\t   jObject id:%d -- %d \r", env, jObj, *jObj, obj.UL, obj.SL);
}


JNIEXPORT void JNICALL Java_jniDemo_JniDll_put
(JNIEnv *env, jobject jObj, jbyteArray jBuf, jint jSize)
{
	JObjValue obj = covJObj("", *jObj);
	printf("obj init  JNIEnv:%p  jObject:%p  %d\t   jObject id:%d -- %d \r", env, jObj, *jObj, obj.UL, obj.SL);

	char *jBuffer = reinterpret_cast<char*>(env->GetByteArrayElements(jBuf, 0));
	printf("call put()  buffer string: %s \r", jBuffer);
}


JNIEXPORT jbyteArray JNICALL Java_jniDemo_JniDll_get
(JNIEnv *env, jobject jObj)
{
	JObjValue obj = covJObj("", *jObj);
	printf("obj init  JNIEnv:%p  jObject:%p  %d\t   jObject id:%d -- %d \r", env, jObj, *jObj, obj.UL, obj.SL);

	char *sName = "hello,world!";
	int nSize = strlen(sName) + 1;
	jbyteArray rtByte = env->NewByteArray(nSize);
	env->SetByteArrayRegion(rtByte, 0, nSize, reinterpret_cast<jbyte*>(sName));
	return rtByte;
}


JNIEXPORT void JNICALL Java_jniDemo_JniDll_callback
(JNIEnv *env, jobject jObj, jbyteArray jBuf, jint jSize)
{

	//1.get install
	jclass jcls = env->GetObjectClass(jObj);

	//2.find method id
	jmethodID jmid = env->GetMethodID(jcls, "callbackProc", "([BI)V");
	env->CallVoidMethod(jObj, jmid, jBuf, jSize);
}