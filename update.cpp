/*
 * update.cpp
 *
 *  Created on: 2012-11-1
 *      Author: zhangbo
 */

#include <windows.h>
#include <cpputils/ThreadCreator.h>
#include <cpputils/Util.h>
#include <stdio.h>
#include <iostream>
#include <cpputils/Properties.h>
#include "Updater.h"

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmdline, int show) {
	TCHAR exePath[MAX_PATH];
	char filepath[MAX_PATH];
	if (Util::ProcessCount("update.exe") <= 1) {
		Updater* pUpdater = new Updater();
		GetModuleFileName(NULL, exePath, MAX_PATH);
		(strrchr(exePath, '\\'))[0] = 0;
		sprintf(filepath, "%s\\config.txt", exePath);
		sprintf(exePath, "%s\\", exePath);
		pUpdater->SetPath(exePath);
		Properties properties;
		properties.SafeLoad(filepath);
		pUpdater->SetHost(properties.GetString("host", "192.168.1.115"));
		pUpdater->SetIpPort(properties.GetInteger("port", 8888));
		pUpdater->SetInterval(
				properties.GetInteger("interval", 1000 * 60 * 30));
		pUpdater->SetUrl(properties.GetString("url", "/bank/client"));
		pUpdater->SetApplication("terminal.exe");
		void* handle = ThreadCreator::StartThread(pUpdater);
		WaitForSingleObject(handle, INFINITE);
	}
	return 0;
}

