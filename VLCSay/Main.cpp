#include <windows.h>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
#define WIN32_LEAN_AND_MEAN
#pragma comment(linker, "/EXPORT:song=_song@24")
#pragma comment(linker, "/EXPORT:creator=_creator@24")
#pragma comment(linker, "/EXPORT:version=_version@24")
#pragma comment(linker, "/EXPORT:status=_status@24")
#pragma comment(linker, "/EXPORT:control=_control@24")
using namespace std;
string title{};
int status_{ 0 };
HWND hWNd{};

char version_[] = "1.0.0";
char createdby[] = "Created by: Turbosmurfen";

//Media Control
enum Control {

	PlayPause = 917504,
	Play = 3014656,
	Pause = 3080192,
	Stop = 851968,
	NextTrack = 720896,
	PreviousTrack = 786432,
	VolumeMute = 524288

};

void readData(wstring input, HWND hWnd) {

	if (!input.empty()) {
		const wchar_t* wchar_0 = input.c_str();
		if (wcscmp(wchar_0, L"VLC media player") == 0) {
			status_ = 1;
			hWNd = hWnd;
		}
		else {
			wstring window = wstring(input).c_str();
			int count = WideCharToMultiByte(CP_UTF8, 0, window.c_str(), window.length(), NULL, 0, NULL, NULL);
			string str(count, 0);
			WideCharToMultiByte(CP_UTF8, 0, window.c_str(), -1, &str[0], count, NULL, NULL);
			string data = str.substr(0, str.find(" - VLC media player"));
			replace(data.begin(), data.end(), '\n', ' ');
			replace(data.begin(), data.end(), '\r', ' ');
			title = data;
			status_ = 2;
			hWNd = hWnd;
		}
	}
	else {
		status_ = 0;
	}
}
static BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam) {
	int length = GetWindowTextLength(hWnd);
	DWORD proc;
	GetWindowThreadProcessId(hWnd, &proc);
	wchar_t window_text[1024];
	GetWindowTextW(hWnd, window_text, length + 1);
	char* buffer0 = new char[256];
	GetClassNameA(hWnd, buffer0, 256);
	string wClass = buffer0;
	wstring window = wstring(window_text).c_str();
	if (wClass == "Qt5QWindowIcon" && window.find(L" - VLC media player") != string::npos || window.find(L"VLC media player") != string::npos) {
		readData(window_text, hWnd);
		delete[] buffer0;
		return FALSE;

	}
	else {
		delete[] buffer0;
		return TRUE;
	}
}
static void WindowRun() {

	EnumWindows(enumWindowCallback, NULL);
}

//Writes out title of the song
extern "C" int __stdcall song(HWND mWnd, HWND aWnd, CHAR * data, char* parms, BOOL show, BOOL nopause)
{
	WindowRun();
	if (title.empty()) {
		return 0;
	}
	else {
		strcpy_s(data, title.size() + 1, title.c_str());
		return 3;
	}
}



//Media Controls
extern "C" int __stdcall control(HWND mWnd, HWND aWnd, CHAR * data, char* parms, BOOL show, BOOL nopause)
{

	string cmd(data);
	if (!cmd.empty()) {
		WindowRun();

		//Track controls
		if (cmd == "playpause") {
			if (hWNd) SendMessage(hWNd, WM_APPCOMMAND, 0, Control::PlayPause);
		}
		else if (cmd == "play") {
			if (hWNd) SendMessage(hWNd, WM_APPCOMMAND, 0, Control::Play);
		}
		else if (cmd == "pause") {
			if (hWNd) SendMessage(hWNd, WM_APPCOMMAND, 0, Control::Pause);
		}
		else if (cmd == "stop") {
			if (hWNd) SendMessage(hWNd, WM_APPCOMMAND, 0, Control::Stop);
		}
		else if (cmd == "next") {
			if (hWNd) SendMessage(hWNd, WM_APPCOMMAND, 0, Control::NextTrack);
		}
		else if (cmd == "previous") {
			if (hWNd) SendMessage(hWNd, WM_APPCOMMAND, 0, Control::PreviousTrack);
		}

		//Volume Control
		else if (cmd == "volmute") {
			if (hWNd) SendMessage(hWNd, WM_APPCOMMAND, 0, Control::VolumeMute);
		}
	}
	return 0;
}

//Created By
extern "C" int __stdcall creator(HWND mWnd, HWND aWnd, CHAR * data, char* parms, BOOL show, BOOL nopause)
{
	strcpy_s(data, strlen(createdby) + 1, createdby);
	return 3;
}

//Current Version
extern "C" int __stdcall version(HWND mWnd, HWND aWnd, CHAR * data, char* parms, BOOL show, BOOL nopause)
{
	strcpy_s(data, strlen(version_) + 1, version_);
	return 3;
}

/* Check for status
* 0 - VLC is not running
* 1 - VLC is paused
* 2 - VLC is playing a song
*/
extern "C" int __stdcall status(HWND mWnd, HWND aWnd, CHAR * data, char* parms, BOOL show, BOOL nopause)
{
	WindowRun();
	strcpy_s(data, std::to_string(status_).size() + 1, std::to_string(status_).c_str());
	return 3;
}