#include "Includes/obfuscate.h"
#include "Includes/Logger.h"
#include <dlfcn.h>
#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <sstream>
#include <jni.h>
#include <cstdio>
//#include "LQM/Tools/Login.h"

static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, void *stream) {
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

const char *GetPackageName() {
    char *application_id[256];
    FILE *fp = fopen("proc/self/cmdline", "r");
    if (fp) {
        fread(application_id, sizeof(application_id), 1, fp);
        fclose(fp);
    }
    return (const char *) application_id;
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




std::string file_path;
std::string file_path_dt;

void *pLibRealUnity = 0;

void *pLibOnl = 0;

typedef jint(JNICALL *CallJNI_OnLoad_t)(JavaVM *vm, void *reserved);

typedef void(JNICALL *CallJNI_OnUnload_t)(JavaVM *vm, void *reserved);

typedef jint(JNICALL *CallJNI_OnLoad_t_o)(JavaVM *vm, void *reserved);

CallJNI_OnLoad_t RealJNIOnLoad = 0;
CallJNI_OnUnload_t RealJNIOnUnload = 0;

CallJNI_OnLoad_t_o RealJNIOnLoado = 0;


JNIEXPORT jint JNICALL CallJNIOL(
        JavaVM *vm, void *reserved) {
    if (!pLibRealUnity)
        pLibRealUnity = dlopen(file_path_dt.c_str(), RTLD_NOW);
    if (!RealJNIOnLoad)
        RealJNIOnLoad = reinterpret_cast<CallJNI_OnLoad_t>(dlsym(pLibRealUnity, "JNI_OnLoad"));
        
    
    if (!pLibOnl)
        pLibOnl = dlopen(file_path.c_str(), RTLD_NOW);
    if (!RealJNIOnLoado)
        RealJNIOnLoado = reinterpret_cast<CallJNI_OnLoad_t_o>(dlsym(pLibOnl, "JNI_OnLoad"));

    RealJNIOnLoado(vm,reserved);
    return RealJNIOnLoad(vm, reserved);
}

JNIEXPORT void JNICALL CallJNIUL(
        JavaVM *vm, void *reserved) { 
    if (!pLibRealUnity)
        pLibRealUnity = dlopen(file_path_dt.c_str(), RTLD_NOW);
    if (!RealJNIOnUnload)
        RealJNIOnUnload = reinterpret_cast<CallJNI_OnUnload_t>(dlsym(pLibRealUnity,
                                                                     "JNI_OnUnload"));
    RealJNIOnUnload(vm, reserved);
}



//dùng lib onl thì thay link bên dưới và đưa libmain.so build đc vào game
JNIEXPORT jint JNICALL 
JNI_OnLoad(JavaVM *vm, void * reserved) {
	
	JNIEnv *env;
	
	vm->GetEnv((void **) &env, JNI_VERSION_1_6);
	
    
    file_path = std::string("/data/user/0/").append(GetPackageName()).append("/cache/").append("libdvt.so");
    file_path_dt = std::string("/data/user/0/").append(GetPackageName()).append("/cache/").append("libdt.so");
    
    //Link libonl.so của imgui upload lên server
   // std::string urlOnl = std::string(std::string("https://dvtruong.com/uploads/").append(owner).append("/libonl.so"));
    
    
    //link libmain.so gốc của game
 //   std::string urlMain = std::string(std::string("https://dvtruong.com/uploads/").append(owner).append("/libmain.so"));
    
    
    
 /*   if(download_file(urlOnl, file_path)){
        
        
        if(download_file(urlMain, file_path_dt)){
        
            CallJNIOL(vm, reserved);
            
            std::remove(file_path.c_str());
            std::remove(file_path_dt.c_str());
            
        }else{
            
            exit(97);
        }
    
    }else{
        
        exit(98);
    }
    */
	
	return JNI_VERSION_1_6;
}



JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {

    CallJNIUL(vm, reserved);
}
