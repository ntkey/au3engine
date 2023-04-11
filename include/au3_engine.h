#pragma once

#include <cstdint>


#ifdef __cplusplus
extern "C" {
#endif


// error code
enum Au3EngineError
{
    SuccessNormal	    = 0x00000000,
    SuccessMoreItems,
    SuccessNomoreItem,

    ErrorUnknow		    = 0x80000000,
    ErrorInit,
    ErrorFormat,
    ErrorUnexpected,
    ErrorInvalidArg,
    ErrorInvalidHandle,
    ErrorPointer,
    ErrorFileData,
    ErrorFileOpen,
    ErrorFileRead,
    ErrorFileTooLarge,
    ErrorFileFormat,
    ErrorFilePacked,
    ErrorOutOfMemory,
    ErrorInvalidMemory,
};

// version type
enum VersionType
{
    TypeInvalid,		// not autoit file
    TypeEA03,			// EA03 [3.0.100.0 - 3.0.101.0]
    TypeEA04,			// EA04 [3.0.102.0 - 3.1.1.133]
    TypeEA05,			// EA05 [3.2.0.0 - 3.2.4.9]
    TypeEA06			// EA06 [3.2.6.0 - 3.3.8.1, 3.3.10.0 - 3.3.16.1 ...]
};

// script config
enum CharMode
{
    ConfigDefault = 0,
    ConfigUpper,
    ConfigLower,
};
typedef struct
{
    CharMode vars;
    CharMode keys;
    CharMode funcs;
    CharMode macros;
}DecompileConfig;

// basic information for script
typedef struct
{
    wchar_t version[64];            // detail version
    wchar_t pasword[64];            // password for EA03 and EA04
    VersionType type;               // version type
    int from_resource;              // is from resource, only for EA06, since 3.3.10.0 [2013.12.23]
    int compiled_script;            // decompile source, a3x or exe
    int unicode_script;             // script file is unicode
}BasicInformation;

// file information for item
typedef struct
{
    unsigned long file_index;	    // file index, begin with 0(0 is script)
    unsigned char* file_buffer;     // file buffer pointer
    unsigned long file_size;	    // file buffer size
    wchar_t install_path[512];      // install path
    wchar_t compile_path[512];      // file path when develop
}ItemInformation;


// global init
int au3engine_init(
);

// global uninit
int au3engine_uinit(
);

// open by file static mode
int au3engine_openfile_general(
    int* handle,
    BasicInformation* baseinfo,
    const wchar_t* filename,
    const DecompileConfig* config
);

// open by file advance mode
int au3engine_openfile_advance(
    int* handle,
    BasicInformation* baseinfo,
    const wchar_t* filename,
    const DecompileConfig* config
);

// next item
int au3engine_next_item(
    int handle,
    ItemInformation* iteminfo
);

// close item
int au3engine_close_item(
    int handle,
    ItemInformation* iteminfo
);

// close item
int au3engine_close_handle(
    int handle
);

#ifdef __cplusplus
}
#endif