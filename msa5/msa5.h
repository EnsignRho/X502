// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MSA5_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MSA5_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MSA5_EXPORTS
#define MSA5_API __declspec(dllexport)
#else
#define MSA5_API __declspec(dllimport)
#endif

// This class is exported from the msa5.dll
class MSA5_API Cmsa5 {
public:
	Cmsa5(void);
	// TODO: add your methods here.
};

extern MSA5_API int nmsa5;

MSA5_API int fnmsa5(void);
