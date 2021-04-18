#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <string>
#include <regex>
#include <ShObjIdl.h>
#include <iostream>
#include <sstream>

// -d="<path>"

int wmain(int argc, wchar_t** argv) {
	LPWSTR defaultpathstr = 0;
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	if (argc == 2) {
		std::wregex re(L"-d=(.*)", std::regex_constants::icase);
		std::wsmatch matches;
		std::wstring path(argv[1]);
		if (std::regex_search(path, matches, re)) {
			std::wstring str = matches[1].str();
			defaultpathstr = (LPWSTR)malloc(sizeof(wchar_t) * (str.length() + 1));
			if (defaultpathstr) wcscpy(defaultpathstr, str.c_str());
		}
	}
	else if (argc > 2) {
		std::wostringstream err;

		err << L"Usage:\n  " << argv[0] << L"\n  " << argv[0] << L" -d=\"<path>\"   //sets default folder//" << std::endl;

		MessageBoxW(0, err.str().c_str(), L"Invalid arguments!", MB_OK | MB_ICONERROR);
		return 0;
	}

	HRESULT hr = CoInitializeEx(0, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (SUCCEEDED(hr)) {
		IFileOpenDialog* fod;
		hr = CoCreateInstance(CLSID_FileOpenDialog, 0, CLSCTX_ALL, IID_IFileOpenDialog, (void**)&fod);
		if (SUCCEEDED(hr)) {
			fod->SetOptions(FOS_PICKFOLDERS);

			wchar_t locale[LOCALE_NAME_MAX_LENGTH + 1];
			GetUserDefaultLocaleName(locale, LOCALE_NAME_MAX_LENGTH);
			if (!wcscmp(locale, L"cs-CZ")) fod->SetTitle(L"Vyberte složku projektu VSCode");
			else fod->SetTitle(L"Choose a VSCode project folder");

			if (defaultpathstr) {
				IShellItem* defaultpath;
				hr = SHCreateItemFromParsingName(defaultpathstr, 0, IID_IShellItem, (void**)&defaultpath);
				if (SUCCEEDED(hr)) hr = fod->SetFolder(defaultpath);
			}
			fod->Show(0);

			IShellItem* item;
			hr = fod->GetResult(&item);
			if (SUCCEEDED(hr)) {
				PWSTR filePath;
				hr = item->GetDisplayName(SIGDN_FILESYSPATH, &filePath);
				if (SUCCEEDED(hr)) {
					std::wostringstream cmd;
					cmd << L"call \"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\Common7\\Tools\\VsDevCmd.bat\" & cd \"" << filePath << L"\" & code .\n";
					_wsystem(cmd.str().c_str());
					CoTaskMemFree(filePath);
				}
				item->Release();
			}
			fod->Release();
		}
		CoUninitialize();
	}
	if (defaultpathstr) free(defaultpathstr);
	return 0;
}