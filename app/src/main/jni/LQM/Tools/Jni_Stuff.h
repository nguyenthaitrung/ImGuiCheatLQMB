#pragma once


#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_android.h"
#include "StrEnc.h"

#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <android/input.h>
#include <android/keycodes.h>
#include <queue>
#include <cstdio>
std::queue<int> unicodeCharacterQueue;

JavaVM *jvm;

using json = nlohmann::json;
std::string g_Token, g_Auth;
bool bValid = false;
std::string thongbao;

#include "Login.h"

bool isLogin = false, logginIn = false;

bool crack = false;



static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, void *stream) {
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}



bool download_file(std::string url,std::string path){
    
  curl_global_init(CURL_GLOBAL_ALL);
    
  CURL *curl = curl_easy_init();

  if (curl) {
      
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
    
    FILE *file = fopen(path.c_str(), "wb");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    
    CURLcode result = curl_easy_perform(curl);
    
    fclose(file);
    curl_easy_cleanup(curl);

    if (result == CURLE_OK) {
      return true;
    } else {
      
        return false;
    }
    
    return false;
  }

  return false;
  curl_global_cleanup();
    
}



struct MemoryStruct {
	char *memory;
	size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *) userp;
	
	mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
		return 0;
	}
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return realsize;
}

int ShowSoftKeyboardInput() {
	jint result;
	jint flags = 0;
	
	JNIEnv *env;
	jvm->AttachCurrentThread(&env, NULL);
	
	jclass looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
	auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
	env->CallStaticVoidMethod(looperClass, prepareMethod);
	
	jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
	jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
	jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
	
	jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
	jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
	
	jclass contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
	jfieldID fieldINPUT_METHOD_SERVICE = env->GetStaticFieldID(contextClass, OBFUSCATE("INPUT_METHOD_SERVICE"), OBFUSCATE("Ljava/lang/String;"));
	jobject INPUT_METHOD_SERVICE = env->GetStaticObjectField(contextClass, fieldINPUT_METHOD_SERVICE);
	jmethodID getSystemServiceMethod = env->GetMethodID(contextClass, OBFUSCATE("getSystemService"), OBFUSCATE("(Ljava/lang/String;)Ljava/lang/Object;"));
	jobject callObjectMethod = env->CallObjectMethod(mInitialApplication, getSystemServiceMethod, INPUT_METHOD_SERVICE);
	
	jclass classInputMethodManager = env->FindClass(OBFUSCATE("android/view/inputmethod/InputMethodManager"));
    jmethodID toggleSoftInputId = env->GetMethodID(classInputMethodManager, OBFUSCATE("toggleSoftInput"), OBFUSCATE("(II)V"));
	
	if (result) {
		env->CallVoidMethod(callObjectMethod, toggleSoftInputId, 2, flags);
	} else {
		env->CallVoidMethod(callObjectMethod, toggleSoftInputId, flags, flags);
	}
	
	env->DeleteLocalRef(classInputMethodManager);
	env->DeleteLocalRef(callObjectMethod);
	env->DeleteLocalRef(contextClass);
    env->DeleteLocalRef(mInitialApplication);
    env->DeleteLocalRef(activityThreadClass);
	jvm->DetachCurrentThread();
	
	return result;
}



void HideSoftKeyboardInput() {
    JNIEnv *env;
    jvm->AttachCurrentThread(&env, NULL);
    
    jclass looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
    auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
    env->CallStaticVoidMethod(looperClass, prepareMethod);
    
    jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
    jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
    jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
    
    jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
    jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
    
    jclass contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
    jfieldID fieldINPUT_METHOD_SERVICE = env->GetStaticFieldID(contextClass, OBFUSCATE("INPUT_METHOD_SERVICE"), OBFUSCATE("Ljava/lang/String;"));
    jobject INPUT_METHOD_SERVICE = env->GetStaticObjectField(contextClass, fieldINPUT_METHOD_SERVICE);
    jmethodID getSystemServiceMethod = env->GetMethodID(contextClass, OBFUSCATE("getSystemService"), OBFUSCATE("(Ljava/lang/String;)Ljava/lang/Object;"));
    jobject callObjectMethod = env->CallObjectMethod(mInitialApplication, getSystemServiceMethod, INPUT_METHOD_SERVICE);
    
    jclass classInputMethodManager = env->FindClass(OBFUSCATE("android/view/inputmethod/InputMethodManager"));
    jmethodID hideSoftInputFromWindowId = env->GetMethodID(classInputMethodManager, OBFUSCATE("hideSoftInputFromWindow"), OBFUSCATE("(Landroid/os/IBinder;I)Z"));
    
    jobject windowToken; // Tham số của hideSoftInputFromWindow là window token của view hiện tại, bạn cần chỉnh sửa để truyền đúng window token.
    jint flags = 0;
    jboolean result = env->CallBooleanMethod(callObjectMethod, hideSoftInputFromWindowId, windowToken, flags);
    
    env->DeleteLocalRef(classInputMethodManager);
    env->DeleteLocalRef(callObjectMethod);
    env->DeleteLocalRef(contextClass);
    env->DeleteLocalRef(mInitialApplication);
    env->DeleteLocalRef(activityThreadClass);
    jvm->DetachCurrentThread();
}

std::string convertToSignatureFormat(const std::string& md5String) {
    std::ostringstream oss;
    for (size_t i = 0; i < md5String.size(); i += 2) {
        if (i > 0) {
            oss << ":";
        }
        oss << std::uppercase << md5String.substr(i, 2);
    }
    return oss.str();
}


std::string getSignatureMD5() {
    
    JNIEnv *env;
    jvm->AttachCurrentThread(&env, NULL);
    
    auto looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
    auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
    env->CallStaticVoidMethod(looperClass, prepareMethod);
    
    jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
    jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
    jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
    
    jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
    jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);

    jclass contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
    jmethodID getPackageManagerMethodID = env->GetMethodID(contextClass, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    jmethodID getPackageNameMethodID = env->GetMethodID(contextClass, "getPackageName", "()Ljava/lang/String;");
    jobject packageManagerObject = env->CallObjectMethod(mInitialApplication, getPackageManagerMethodID);

    // Lấy chữ ký của ứng dụng
    jclass packageManagerClass = env->GetObjectClass(packageManagerObject);
    jmethodID getPackageInfoMethodID = env->GetMethodID(packageManagerClass, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jstring packageNameString = static_cast<jstring>(env->CallObjectMethod(mInitialApplication, getPackageNameMethodID));
    jobject packageInfoObject = env->CallObjectMethod(packageManagerObject, getPackageInfoMethodID, packageNameString, 64);

    // Lấy mảng chữ ký
    jclass packageInfoClass = env->GetObjectClass(packageInfoObject);
    jfieldID signaturesFieldID = env->GetFieldID(packageInfoClass, "signatures", "[Landroid/content/pm/Signature;");
    jobjectArray signaturesArray = static_cast<jobjectArray>(env->GetObjectField(packageInfoObject, signaturesFieldID));
    jobject signatureObject = env->GetObjectArrayElement(signaturesArray, 0);

    // Chuyển đổi đối tượng chữ ký thành mảng byte
    jclass signatureClass = env->GetObjectClass(signatureObject);
    jmethodID toByteArrayMethodID = env->GetMethodID(signatureClass, "toByteArray", "()[B");
    jbyteArray signatureByteArray = static_cast<jbyteArray>(env->CallObjectMethod(signatureObject, toByteArrayMethodID));

    // Tính toán giá trị MD5 cho mảng byte chữ ký
    const jbyte* signatureBytes = env->GetByteArrayElements(signatureByteArray, nullptr);
    jsize signatureLength = env->GetArrayLength(signatureByteArray);
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5(reinterpret_cast<const unsigned char*>(signatureBytes), signatureLength, digest);
    
    // Chuyển đổi chuỗi MD5 thành đối tượng Java String để trả về
    char md5String[MD5_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(&md5String[i * 2], "%02x", (unsigned int)digest[i]);
    }
    std::string result(md5String, MD5_DIGEST_LENGTH * 2);
    std::string signatureFormat = convertToSignatureFormat(result);

    jvm->DetachCurrentThread();
    
    return signatureFormat;
}


int PollUnicodeChars() {
    JNIEnv *env;
    jvm->AttachCurrentThread(&env, NULL);
    
    jclass looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
    auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
    env->CallStaticVoidMethod(looperClass, prepareMethod);
    
    jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
    jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
    jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
    
    jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
    jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
    
    jclass keyEventClass = env->FindClass(OBFUSCATE("android/view/KeyEvent"));
    jmethodID getUnicodeCharMethod = env->GetMethodID(keyEventClass, OBFUSCATE("getUnicodeChar"), OBFUSCATE("(I)I"));
    
    ImGuiIO& io = ImGui::GetIO();
    
    int return_key = env->CallIntMethod(keyEventClass, getUnicodeCharMethod);
    
    env->DeleteLocalRef(keyEventClass);
    env->DeleteLocalRef(mInitialApplication);
    env->DeleteLocalRef(activityThreadClass);
    jvm->DetachCurrentThread();
    
    return return_key;
}

void ConvertToUppercase(std::string& str) {
    for (char& c : str) {
        if (c >= 'a' && c <= 'z') {
            c -= 32;
        }
    }
}

std::string trim(const std::string& str) {
    // Xác định vị trí bắt đầu và kết thúc của chuỗi sau khi đã trim
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");

    // Kiểm tra nếu chuỗi là chuỗi trống hoặc chỉ gồm khoảng trắng
    if (start == std::string::npos || end == std::string::npos) {
        return "";
    }

    // Trích xuất phần tử không có khoảng trắng từ chuỗi gốc
    return str.substr(start, end - start + 1);
}


void showAlertDialog(char* strtitle, char* strbody) {
    JNIEnv* env;
    jvm->AttachCurrentThread(&env, NULL);

    // Get the application context
    jclass activityThreadClass = env->FindClass("android/app/ActivityThread");
    jmethodID currentActivityThreadMethod = env->GetStaticMethodID(activityThreadClass, "currentActivityThread", "()Landroid/app/ActivityThread;");
    jobject activityThreadObj = env->CallStaticObjectMethod(activityThreadClass, currentActivityThreadMethod);
    jmethodID getApplicationMethod = env->GetMethodID(activityThreadClass, "getApplication", "()Landroid/app/Application;");
    jobject applicationObj = env->CallObjectMethod(activityThreadObj, getApplicationMethod);

    // Create an AlertDialog.Builder object
    jclass alertDialogClass = env->FindClass("android/app/AlertDialog$Builder");
    jmethodID alertDialogConstructor = env->GetMethodID(alertDialogClass, "<init>", "(Landroid/content/Context;)V");
    jobject alertDialogObj = env->NewObject(alertDialogClass, alertDialogConstructor, applicationObj);

    // Set the title and message
    jstring title = env->NewStringUTF(strtitle);
    jstring message = env->NewStringUTF(strbody);
    jmethodID setTitleMethod = env->GetMethodID(alertDialogClass, "setTitle", "(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;");
    jmethodID setMessageMethod = env->GetMethodID(alertDialogClass, "setMessage", "(Ljava/lang/CharSequence;)Landroid/app/AlertDialog$Builder;");
    env->CallObjectMethod(alertDialogObj, setTitleMethod, title);
    env->CallObjectMethod(alertDialogObj, setMessageMethod, message);

    // Set the positive button
    jmethodID setPositiveButtonMethod = env->GetMethodID(alertDialogClass, "setPositiveButton", "(Ljava/lang/CharSequence;Landroid/content/DialogInterface$OnClickListener;)Landroid/app/AlertDialog$Builder;");
    jstring positiveButtonLabel = env->NewStringUTF("OK");
    jobject nullObj = NULL;
    env->CallObjectMethod(alertDialogObj, setPositiveButtonMethod, positiveButtonLabel, nullObj);

    // Show the AlertDialog
    jmethodID showMethod = env->GetMethodID(alertDialogClass, "show", "()Landroid/app/AlertDialog;");
    jobject alertDialog = env->CallObjectMethod(alertDialogObj, showMethod);

    jvm->DetachCurrentThread();
}



void copy_to_clipboard(const std::string& text) {
	JNIEnv *env;
	jvm->AttachCurrentThread(&env, NULL);
	
	auto looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
	auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
	env->CallStaticVoidMethod(looperClass, prepareMethod);
	
	jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
	jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
	jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
	
	jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
	jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
	
	jclass clipboardManagerClass = env->FindClass("android/content/ClipboardManager");
    jmethodID getTextMethod = env->GetMethodID(clipboardManagerClass, "getText", "()Ljava/lang/CharSequence;");
    jmethodID setTextMethod = env->GetMethodID(clipboardManagerClass, "setText", "(Ljava/lang/CharSequence;)V");

    jclass charSequenceClass = env->FindClass("java/lang/CharSequence");
    jmethodID toStringMethod = env->GetMethodID(charSequenceClass, "toString", "()Ljava/lang/String;");

    jclass contextClass = env->FindClass("android/content/Context");
    jmethodID getSystemServiceMethod = env->GetMethodID(contextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jfieldID clipboardServiceField = env->GetStaticFieldID(contextClass, "CLIPBOARD_SERVICE", "Ljava/lang/String;");
    jobject clipboardService = env->GetStaticObjectField(contextClass, clipboardServiceField);

    jobject clipboardManager = env->CallObjectMethod(mInitialApplication, getSystemServiceMethod, clipboardService);
    jobject textObject = env->CallObjectMethod(clipboardManager, getTextMethod);
    jstring jText = static_cast<jstring>(env->CallObjectMethod(textObject, toStringMethod));

    env->CallVoidMethod(clipboardManager, setTextMethod, env->NewStringUTF(text.c_str()));

    env->DeleteLocalRef(jText);
    env->DeleteLocalRef(textObject);
    env->DeleteLocalRef(clipboardManager);
    env->DeleteLocalRef(clipboardManagerClass);
    env->DeleteLocalRef(charSequenceClass);
    env->DeleteLocalRef(contextClass);
    env->DeleteLocalRef(clipboardService);
	jvm->DetachCurrentThread();
	
}

std::string getClipboard() {
	std::string result;
	JNIEnv *env;
	
	jvm->AttachCurrentThread(&env, NULL);
	
	auto looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
	auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
	env->CallStaticVoidMethod(looperClass, prepareMethod);
	
	jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
	jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
	jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
	
	jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
	jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
	
	auto contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
	auto getSystemServiceMethod = env->GetMethodID(contextClass, OBFUSCATE("getSystemService"), OBFUSCATE("(Ljava/lang/String;)Ljava/lang/Object;"));
	
	auto str = env->NewStringUTF(OBFUSCATE("clipboard"));
	auto clipboardManager = env->CallObjectMethod(mInitialApplication, getSystemServiceMethod, str);
	env->DeleteLocalRef(str);
	
	jclass ClipboardManagerClass = env->FindClass(OBFUSCATE("android/content/ClipboardManager"));
    auto getText = env->GetMethodID(ClipboardManagerClass, OBFUSCATE("getText"), OBFUSCATE("()Ljava/lang/CharSequence;"));

    jclass CharSequenceClass = env->FindClass(OBFUSCATE("java/lang/CharSequence"));
    auto toStringMethod = env->GetMethodID(CharSequenceClass, OBFUSCATE("toString"), OBFUSCATE("()Ljava/lang/String;"));

    auto text = env->CallObjectMethod(clipboardManager, getText);
    if (text) {
        str = (jstring) env->CallObjectMethod(text, toStringMethod);
        result = env->GetStringUTFChars(str, 0);
        env->DeleteLocalRef(str);
        env->DeleteLocalRef(text);
    }
    env->DeleteLocalRef(CharSequenceClass);
    env->DeleteLocalRef(ClipboardManagerClass);
    env->DeleteLocalRef(clipboardManager);
    env->DeleteLocalRef(contextClass);
    env->DeleteLocalRef(mInitialApplication);
    env->DeleteLocalRef(activityThreadClass); 	
    jvm->DetachCurrentThread();
    return result.c_str();
}


int getSizeApp(){
    
    JNIEnv *env;
    
    jvm->AttachCurrentThread(&env, NULL);
    
    auto looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
    auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
    env->CallStaticVoidMethod(looperClass, prepareMethod);
    
    jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
    jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
    jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
    
    jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
    jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
    
    
    jclass context_class = env->GetObjectClass(mInitialApplication);
    jmethodID get_package_manager_method = env->GetMethodID(context_class, "getPackageManager", "()Landroid/content/pm/PackageManager;");
    jobject package_manager_object = env->CallObjectMethod(mInitialApplication, get_package_manager_method);

    jmethodID get_package_name_method = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");
    jstring package_name_string = (jstring) env->CallObjectMethod(mInitialApplication, get_package_name_method);
    const char *package_name = env->GetStringUTFChars(package_name_string, 0);

    jclass package_manager_class = env->GetObjectClass(package_manager_object);
    jmethodID get_package_info_method = env->GetMethodID(package_manager_class, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject package_info_object = env->CallObjectMethod(package_manager_object, get_package_info_method, env->NewStringUTF(package_name), 0);

    jclass package_info_class = env->GetObjectClass(package_info_object);
    jfieldID application_info_field = env->GetFieldID(package_info_class, "applicationInfo", "Landroid/content/pm/ApplicationInfo;");
    jobject application_info_object = env->GetObjectField(package_info_object, application_info_field);

    jclass application_info_class = env->GetObjectClass(application_info_object);
    jfieldID source_dir_field = env->GetFieldID(application_info_class, "sourceDir", "Ljava/lang/String;");
    jstring source_dir_string = (jstring) env->GetObjectField(application_info_object, source_dir_field);

    const char *source_dir = env->GetStringUTFChars(source_dir_string, 0);

    struct stat apkStat;
    stat(source_dir, &apkStat);
    
    
    env->ReleaseStringUTFChars(source_dir_string, source_dir);
    env->ReleaseStringUTFChars(package_name_string, package_name);
    
    jvm->DetachCurrentThread();
    
    return apkStat.st_size;
    
}


std::string getCacheDir(const char *fileName) {
	std::string result;
	JNIEnv *env;
	
	jvm->AttachCurrentThread(&env, NULL);
	
	auto looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
	auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
	env->CallStaticVoidMethod(looperClass, prepareMethod);
	
	jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
	jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
	jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
	
	jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
	jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);
	
	auto contextClass = env->FindClass(OBFUSCATE("android/content/Context"));
	auto getSystemServiceMethod = env->GetMethodID(contextClass, OBFUSCATE("getSystemService"), OBFUSCATE("(Ljava/lang/String;)Ljava/lang/Object;"));
	
	jmethodID getCacheDirMethod = env->GetMethodID(contextClass, "getCacheDir", "()Ljava/io/File;");
    jobject cacheDirObject = env->CallObjectMethod(mInitialApplication, getCacheDirMethod);

    // Lấy lớp File
    jclass fileClass = env->FindClass("java/io/File");
    
    // Lấy phương thức getAbsolutePath()
    jmethodID getAbsolutePathMethod = env->GetMethodID(fileClass, "getAbsolutePath", "()Ljava/lang/String;");
    jstring cacheDirPathString = (jstring) env->CallObjectMethod(cacheDirObject, getAbsolutePathMethod);
    
    // Chuyển đổi jstring thành char*
    const char* cacheDirPath = env->GetStringUTFChars(cacheDirPathString, NULL);

    // Chuyển đổi const char* thành std::string
    std::string cacheDir = cacheDirPath;
    cacheDir += "/";
    cacheDir += std::string(fileName);

    // Giải phóng bộ nhớ
    env->ReleaseStringUTFChars(cacheDirPathString, cacheDirPath);

    jvm->DetachCurrentThread();
    return cacheDir;
}


bool fileExist(const std::string& filename){
    
    std::ifstream file(std::string(getCacheDir(filename.c_str())));

    if (file) {
        return true;
    } 
    
    return false;
}

bool fileRemove(const std::string& filename){
    
    if (std::remove(getCacheDir(filename.c_str()).c_str()) == 0) {
        return true;
    } 
    
    return false;
}

bool writeStructToFile(const sConfig& data, const std::string& filename) {
    std::ofstream outFile(std::string(getCacheDir(filename.c_str())), std::ios::binary | std::ios::out);
    if (outFile) {
        outFile.write(reinterpret_cast<const char*>(&data), sizeof(data));
        outFile.close();
        return true;
    } 
    
    return false;
}

// Hàm đọc struct từ tệp tin
bool readStructFromFile(sConfig& data, const std::string& filename) {
    std::ifstream inFile(std::string(getCacheDir(filename.c_str())), std::ios::binary | std::ios::in);
    if (inFile) {
        inFile.read(reinterpret_cast<char*>(&data), sizeof(data));
        inFile.close();
        return true;
    } 
    
    return false;
}



void writeFile(const std::string& filename, std::string content, const bool enc = false)
{
	if(enc){
		content = base64_decode(content);
	}
    std::ofstream file(std::string(getCacheDir(filename.c_str())));
    if (file.is_open())
    {
        file << content;
        file.close();
    }
}



void writeFile_full_path(const std::string& filename, std::string content, const bool enc = false)
{
    if(enc){
        content = base64_decode(content);
    }
    std::ofstream file(filename.c_str());
    if (file.is_open())
    {
        file << content;
        file.close();
    }
}

std::string readFile(const std::string& filename)
{
    std::ifstream file(std::string(getCacheDir(filename.c_str())));
    if (file.is_open())
    {
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        return content;
    }
    else
    {
        return "";
    }
}



std::string Login(const char *user_key) {
    JNIEnv *env;
    jvm->AttachCurrentThread(&env, 0);
	
	auto looperClass = env->FindClass(OBFUSCATE("android/os/Looper"));
	auto prepareMethod = env->GetStaticMethodID(looperClass, OBFUSCATE("prepare"), OBFUSCATE("()V"));
	env->CallStaticVoidMethod(looperClass, prepareMethod);
	
	jclass activityThreadClass = env->FindClass(OBFUSCATE("android/app/ActivityThread"));
	jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBFUSCATE("sCurrentActivityThread"), OBFUSCATE("Landroid/app/ActivityThread;"));
	jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);
	
	jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBFUSCATE("mInitialApplication"), OBFUSCATE("Landroid/app/Application;"));
	jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);

	std::string hwid = user_key;
	
	hwid += Tools::GetAndroidID(env, mInitialApplication);
	hwid += Tools::GetDeviceModel(env);
	hwid += Tools::GetDeviceBrand(env);
	std::string UUID = Tools::GetDeviceUniqueIdentifier(env, hwid.c_str());
	jvm->DetachCurrentThread();

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    std::string errMsg;
    isLogin = false;
    bValid = false;
    g_Token = "";
    g_Auth = "";
    std::string resbase;
    
    if(isLogin || bValid){
        exit(99);
    }
    struct MemoryStruct chunk {};
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;
    
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, (urlLogin.c_str()));
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, OBFUSCATE("Content-Type: application/x-www-form-urlencoded"));

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        std::string request_id = Tools::RandomString(20);
        json dataPost = {

            {std::string(OBFUSCATE("keyname")),bdvt_encode(std::string(user_key))},
            {std::string(OBFUSCATE("device_id")),bdvt_encode(UUID)},
            {std::string(OBFUSCATE("request_id")),request_id},
            {std::string(OBFUSCATE("user_token")),bdvt_encode(owner)},
            {std::string(OBFUSCATE("project")),bdvt_encode(projectName)},
            /*{std::string(OBFUSCATE("lib_onl")),"true"},
            {std::string(OBFUSCATE("lib_name")),libName},*/
            
        };


        std::string dataPost_str = dataPost.dump();

        char dataEnc[4096];

        sprintf(dataEnc, OBFUSCATE("token=%s&enc=aes"), bdvt_encode(EncryptionAES(dataPost_str)).c_str());

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataEnc);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {

                resbase = bdvt_decode(std::string(chunk.memory));

                std::string res = DecryptionAES(resbase);

                json result = json::parse(res);
                if (result[std::string(OBFUSCATE("bool"))] == std::string(OBFUSCATE("true"))) {

                    std::string timePhp = result[std::string(OBFUSCATE("time"))].get<std::string>();

                    timePhp = bdvt_decode(timePhp);

                    std::tm time = {};
                    std::istringstream ss(timePhp);
                    ss >> std::get_time(&time, std::string(OBFUSCATE("%Y-%m-%dT%H:%M:%SZ")).c_str());

                    std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(std::mktime(&time));

                    std::chrono::duration<double> diff = tp - now;

                    std::string token = result[std::string(OBFUSCATE("token"))].get<std::string>();
                    
					std::string auth = projectName;
                    auth += std::string(OBFUSCATE("-"));
                    auth += owner;
                    auth += std::string(OBFUSCATE("-"));
                    auth += user_key;
                    auth += std::string(OBFUSCATE("-"));
                    auth += UUID;
                    auth += std::string(OBFUSCATE("-"));
                    auth += request_id;

                    std::string outputAuth = Tools::CalcMD5(auth);
                    g_Token = token;
                    g_Auth = outputAuth;
                    bValid = g_Token == g_Auth;

                    if (diff.count() >= 60) {

                        bValid = false;

                        errMsg = std::string(OBFUSCATE("Time limited"));
                    }

                    thongbao = result[std::string(OBFUSCATE("msg"))].get<std::string>();
                } else {
                    errMsg = result[std::string(OBFUSCATE("msg"))].get<std::string>();
                }
            } catch (json::exception &e) {
                errMsg = "{";
                errMsg += e.what();
                errMsg += "}\n{";
                errMsg += resbase;
                errMsg += "}";
            }
        } else {
            errMsg = std::string(OBFUSCATE(ICON_MD_SIGNAL_WIFI_STATUSBAR_CONNECTED_NO_INTERNET_4 "  Không có kết nối internet"));
        }
    }
    curl_easy_cleanup(curl);
    jvm->DetachCurrentThread();


    return bValid ? std::string(OBFUSCATE("OK")) : errMsg;
}
