#ifndef _GET_RESOURCE_PATH
#define _GET_RESOURCE_PATH


#ifdef _WIN32 
#include <shlwapi.h>
#include <Shlobj.h>
#include <Shlobj_core.h>
#include <string>

char* GetConfigPath(const char* CompanyName, const char* ProductName, const char* FileName = "")
{
	char* spacer = "\\";
	char* szPath = std::getenv("APPDATA");
	char* result = new char[1024];
	if(szPath != nullptr)
	{
		strcpy(result, szPath);
		strcat(result, spacer);
		strcat(result, CompanyName);
		strcat(result, spacer);
		strcat(result, ProductName);

		if(!PathFileExistsA(result))
		{
			if(!SHCreateDirectoryEx(NULL, result, NULL) == ERROR_SUCCESS)
			{
				fprintf(stderr, "Failed to create config directory.");
			}
		}

		if (FileName[0] != '\0')
		{
			strcat(result, spacer);
			strcat(result, FileName);
		}
		
		return result;
	}

	fprintf(stderr, "Failed to find config directory.");
	return result;
}

#elif __linux__

wchar_t* GetConfigPath()
{
	// TODO: implement for platform
	return nullptr;
}

#elif __APPLE__

wchar_t* GetConfigPath()
{
	// TODO: implement for platform
	return nullptr;
}

#endif


#endif 