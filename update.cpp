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
	if (Util::ProcessCount("update.exe") <= 1) {
		Updater* pUpdater = new Updater();
		pUpdater->SetPath(Util::GetCurrentPath() + "\\");
		Properties properties;
		properties.SafeLoad(Util::GetCurrentPath() + "\\update.cfg");
		pUpdater->SetHost(properties.GetString("host", "192.168.0.100"));
		pUpdater->SetIpPort(properties.GetInteger("port", 8088));
		pUpdater->SetInterval(
				properties.GetInteger("interval", 1000 * 60 * 30));
		pUpdater->SetUrl(properties.GetString("url", "/bank/client"));
		pUpdater->SetApplication(properties.GetString("application", "mediac.exe"));
		void* handle = ThreadCreator::StartThread(pUpdater);
		WaitForSingleObject(handle, INFINITE);
	}
	return 0;
}

