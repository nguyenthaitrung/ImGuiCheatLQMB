#pragma once

//
// Memory Tools Internal by foxcheatsid@gmail.com
// Created on Tue Apr 4 13:03:13 2023
//

/*
* Type
*/

enum Type {
    TYPE_DWORD,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_WORD,
    TYPE_BYTE,
    TYPE_QWORD,
};

/*
* Maps, Semua hasil pencarian ada di sini 
*/
struct Maps_t {
    uintptr_t start, end;
};

/*
* List Memori Region 
*/
enum RegionType {
    ALL,
    JAVA_HEAP,
    C_HEAP,
    C_ALLOC,
    C_DATA,
    C_BSS,
    PPSSPP,
    ANONYMOUS,
    JAVA,
    STACK,
    ASHMEM,
    VIDEO,
    OTHER,
    BAD,
    CODE_APP,
    CODE_SYS
};

namespace kFox 
{
    /*
    * Mendapatkan PackageName
    */
	const char *GetPackageName();
	
    /*
    * Menghapus semua hasil pencarian memori
    */
	extern void ClearResult();
	
    /*
    * Mendapatkan semua hasil pencarian memori
    */
	extern std::vector<uintptr_t> GetResult();
	
    /*
    * Mendapatkan Semua Map Region dari proses yang sedang berjalan saat ini
    */
    extern std::vector<Maps_t> GetRegions(unsigned int regionType);
    
    /*
    * Mencari value berdasarkan Region dan Type
    */
    extern void MemorySearch(std::vector<Maps_t> regions, char* value, Type type);
	
    /*
    * Memperbaharui value dari semua hasil pencarian memori
    */
	extern void MemoryRefine(char* value, Type type, int max_result);
	
    /*
    * Menulis value ke memori
    */
	extern void MemoryWrite(char* value, Type type);
	
    /*
    * Menulis value ke memori
    */
	extern void WriteValues(uintptr_t address, void *value, ssize_t size);
}
