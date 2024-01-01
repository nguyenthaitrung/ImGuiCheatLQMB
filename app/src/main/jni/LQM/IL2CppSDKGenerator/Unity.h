#ifndef IMGUIANDROID_UNITY_H
#define IMGUIANDROID_UNITY_H

#include <codecvt>

#include <string>
#include <iostream>


typedef struct _monoString
{
    void *klass;
    void *monitor;
    int length;
    char chars[1];

    int getLength()
    {
        return length;
    }

    char *getRawChars()
    {
        return chars;
    }

    std::string getString()
    {
        std::u16string u16string(reinterpret_cast<const char16_t *>(chars));
        std::wstring wstring(u16string.begin(), u16string.end());
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;

        return convert.to_bytes(wstring);
    }

    const char *getChars()
    {
        return getString().c_str();
    }
}monoString;


//MONOARRAY
template <typename T>
struct monoArray
{
    void* klass;
    void* monitor;
    void* bounds;
    int   max_length;
    void* vector [1];
    int getLength()
    {
        return max_length;
    }
    T getPointer()
    {
        return (T)vector;
    }
};

//MONOLIST
template <typename T>
struct monoList {
	void *unk0;
	void *unk1;
	monoArray<T> *items;
	int size;
	int version;
	
	T getItems(){
		return items->getPointer();
	}
	
	int getSize(){
		return size;
	}
	
	int getVersion(){
		return version;
	}
};

//MONODICTIONARY
template <typename K, typename V>
struct monoDictionary {
	void *unk0;
	void *unk1;
	monoArray<int **> *table;
	monoArray<void **> *linkSlots;
	monoArray<K> *keys;
	monoArray<V> *values;
	int touchedSlots;
	int emptySlot;
	int size;
	
	K getKeys(){
		return keys->getPointer();
	}
	
	V getValues(){
		return values->getPointer();
	}
	
	int getNumKeys(){
		return keys->getLength();
	}
	
	int getNumValues(){
		return values->getLength();
	}
	
	int getSize(){
		return size;
	}
};

monoString *CreateIl2cppString(const char *str)
{
    dlerror();
    auto handle = dlopen("libil2cpp.so", RTLD_LAZY);
    const char* openerror = dlerror();
    if(openerror)
    {
        LOGE(OBFUSCATE("Error Opening Lib: %s"), openerror);

        return nullptr;
    }
        const char* symerror = dlerror();
        if(symerror)
        {
            LOGE(OBFUSCATE("Error Finding Symbol: %s"), symerror);
            return nullptr;
        }
        monoString *(*il2cpp_string_new)(const char *) = (monoString *(*)(const char *))dlsym(handle, OBFUSCATE("il2cpp_string_new"));
        return il2cpp_string_new(str);
}

int GetObscuredIntValue(uint64_t location){
    int cryptoKey = *(int *)location;
    int obfuscatedValue = *(int *)(location + 0x4);

    return obfuscatedValue ^ cryptoKey;
}
bool GetObscuredBoolValue(uint64_t location){
    int cryptoKey = *(int *)location;
    int obfuscatedValue = *(int *)(location + 0x4);

    return (bool)obfuscatedValue ^ cryptoKey;
}
/*
Set the real value of an ObscuredInt.
Parameters:
	- location: the location of the ObscuredInt
	- value: the value we're setting the ObscuredInt to
*/
void SetObscuredIntValue(uint64_t location, int value){
    int cryptoKey = *(int *)location;

    *(int *)(location + 0x4) = value ^ cryptoKey;
}
void SetObscuredBoolValue(uint64_t location, bool value){
    int cryptoKey = *(int *)location;

    *(int *)(location + 0x4) = value ^ cryptoKey;
}
/*
Get the real value of an ObscuredFloat.
Parameters:
	- location: the location of the ObscuredFloat
*/
float GetObscuredFloatValue(uint64_t location)
{
    int cryptoKey = *(int *) location;
    int obfuscatedValue = *(int *) (location + 0x4);

    union intfloat
    {
        int i;
        float f;
    };

    /* use this intfloat to set the integer representation of our parameter value, which will also set the float value */
    intfloat IF;
    IF.i = obfuscatedValue ^ cryptoKey;

    return IF.f;
}

/*
Set the real value of an ObscuredFloat.
Parameters:
	- location: the location of the ObscuredFloat
	- value: the value we're setting the ObscuredFloat to
*/
void SetObscuredFloatValue(uint64_t location, float value)
{
    int cryptoKey = *(int *) location;

    union intfloat
    {
        int i;
        float f;
    };

    /* use this intfloat to get the integer representation of our parameter value */
    intfloat IF;
    IF.f = value;

    /* use this intfloat to generate our hacked ObscuredFloat */
    intfloat IF2;
    IF2.i = IF.i ^ cryptoKey;

    *(float *) (location + 0x4) = IF2.f;
}
#endif IMGUIANDROID_UNITY_H
