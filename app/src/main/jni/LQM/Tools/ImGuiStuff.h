#pragma once


#include <android/input.h>
#include <map>
#include <queue>
#include <cstdint>
#include <vector>
#include <map>
#include <android/input.h>
#include <android/keycodes.h>
#include <queue>

ImVec2 menuRectSize; // Lấy kích thước của menu
ImVec2 menuRectPos;    // Lấy vị trí của menu hiện tại trong cửa sổ
bool isCaps;
std::vector<int> kdata;

bool isInsideRect(ImVec2 point, ImVec2 rectMin, ImVec2 rectMax) {
    return (point.x >= rectMin.x && point.x <= rectMax.x &&
            point.y >= rectMin.y && point.y <= rectMax.y);
}


void (*origInput)(...);
void myInput(void *inputConsumer, void *motionEvent, const void *inputMessage) {
    origInput(inputConsumer, motionEvent, inputMessage);
	ImGui_ImplAndroid_HandleInputEvent((AInputEvent *)inputConsumer, {(float) screenWidth / (float) glWidth, (float) screenHeight / (float) glHeight});
    return;
}



int32_t (*orig_ANativeWindow_getWidth)(ANativeWindow* window);
int32_t _ANativeWindow_getWidth(ANativeWindow* window) {
	screenWidth = orig_ANativeWindow_getWidth(window);
	return orig_ANativeWindow_getWidth(window);
}

int32_t (*orig_ANativeWindow_getHeight)(ANativeWindow* window);
int32_t _ANativeWindow_getHeight(ANativeWindow* window) {
	screenHeight = orig_ANativeWindow_getHeight(window);
	return orig_ANativeWindow_getHeight(window);
}

int32_t (*orig_AConfiguration_getDensity)(ANativeWindow* config);
int32_t _AConfiguration_getDensity(ANativeWindow* config) {
	density = orig_AConfiguration_getDensity(config);
	return orig_AConfiguration_getDensity(config);
}


jboolean (*orig_unity__nativeInjectEvent)(JNIEnv *env, jobject object, jobject inputEvent);
jboolean unity_nativeInjectEvent(JNIEnv *env, jobject object, jobject inputEvent) {
	ImGuiIO &io = ImGui::GetIO();
	
	jclass motionEventClass = env->FindClass(OBFUSCATE("android/view/MotionEvent"));
	
	if (env->IsInstanceOf(inputEvent, motionEventClass)) {
		
        #if defined(TOUCH_IL2CPP)
        
        #else
        
        jmethodID getActionMethod = env->GetMethodID(motionEventClass, OBFUSCATE("getActionMasked"), OBFUSCATE("()I"));
		jint getAction = env->CallIntMethod(inputEvent, getActionMethod);
		
		jmethodID getXMethod = env->GetMethodID(motionEventClass, OBFUSCATE("getX"), OBFUSCATE("()F"));
		jfloat getX = env->CallFloatMethod(inputEvent, getXMethod);
		
		jmethodID getYMethod = env->GetMethodID(motionEventClass, OBFUSCATE("getY"), OBFUSCATE("()F"));
		jfloat getY = env->CallFloatMethod(inputEvent, getYMethod);
		
		jmethodID getPointerCountMethod = env->GetMethodID(motionEventClass, OBFUSCATE("getPointerCount"), OBFUSCATE("()I"));
		jint getPointerCount = env->CallIntMethod(inputEvent, getPointerCountMethod);
		
        
        float x_egl= getX;
        float y_egl = getY;
        if(screenWidth > 0 && screenHeight > 0){
            
        
            x_egl = getX * scaleX;
            y_egl = getY * scaleY;

        }
        
        
        
        if(Config.InitImGui.initImGui){
            
            io.MousePos = ImVec2(x_egl, y_egl);
            
            ImGui_ImplAndroid_HandleInputEvent(getAction,x_egl,y_egl,getPointerCount);
        
            if (!ImGui::GetIO().MouseDownOwnedUnlessPopupClose[0]){
                
                
                return orig_unity__nativeInjectEvent(env, object, inputEvent);
            }
        return false;
        
        }
        
        
        #endif
        
       	}
	
	
	
	jclass KeyEventClass = env->FindClass(OBFUSCATE("android/view/KeyEvent"));
	if (env->IsInstanceOf(inputEvent, KeyEventClass)) {
		jmethodID getActionMethod = env->GetMethodID(KeyEventClass, OBFUSCATE("getAction"), OBFUSCATE("()I"));
		if (env->CallIntMethod(inputEvent, getActionMethod) == 0) {
			jmethodID getKeyCodeMethod = env->GetMethodID(KeyEventClass, OBFUSCATE("getKeyCode"), OBFUSCATE("()I"));
			jmethodID getUnicodeCharMethod = env->GetMethodID(KeyEventClass, OBFUSCATE("getUnicodeChar"), OBFUSCATE("(I)I"));
			jmethodID getMetaStateMethod = env->GetMethodID(KeyEventClass, OBFUSCATE("getMetaState"), OBFUSCATE("()I"));
			
            jmethodID getCharacters = env->GetMethodID(KeyEventClass, OBFUSCATE("getCharacters"), OBFUSCATE("()Ljava/lang/String;"));
			
            jint keyCode = env->CallIntMethod(inputEvent, getKeyCodeMethod);
            
            jint metaState = env->CallIntMethod(inputEvent, getMetaStateMethod);
			
            jstring characters =  (jstring)env->CallObjectMethod(inputEvent, getCharacters);
            
            jint unicodeChar = env->CallIntMethod(inputEvent, getUnicodeCharMethod, metaState);
			
            kdata.push_back(unicodeChar);
            
			ImGui_ImplAndroid_Addkeyboard(keyCode, unicodeChar);
            
            
            
		}
	}

	return orig_unity__nativeInjectEvent(env, object, inputEvent);
}



jint (*old_RegisterNatives)(JNIEnv*, jclass, const JNINativeMethod*, jint);
jint hook_RegisterNatives(JNIEnv* env, jclass klazz, const JNINativeMethod* methods, jint methodcount) {
	for (int i = 0; i < methodcount; ++i) {
		auto method = methods[i];
		
		if (strcmp(method.name, OBFUSCATE("nativeInjectEvent")) == 0) {
            Tools::Hook((void *) method.fnPtr, (void *) unity_nativeInjectEvent, (void **) &orig_unity__nativeInjectEvent);
		}
	}
	return old_RegisterNatives(env, klazz, methods, methodcount);
}
