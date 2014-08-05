/*
 * Updater.cpp
 *
 *  Created on: Jun 23, 2012
 *      Author: zhangbo
 */

#include "Updater.h"
#include <cpputils/Util.h>
#include <cpputils/ThreadCreator.h>
#include <windows.h>

Updater::Updater() : interval(60000), port(8088) {
	this->running = false;
}

Updater::~Updater() {
}

void Updater::SetIpPort(int port) {
	this->port = port;
}

void Updater::SetUrl(const string& url) {
	this->url = url;
}

void Updater::SetHost(const string& host) {
	this->host = host;
}

void Updater::SetPath(const string& path) {
	this->path = path;
}

void Updater::SetInterval(int interval) {
	this->interval = interval;
}

void Updater::SetApplication(const string& application) {
	this->application = application;
}

void Updater::Stop() {
	this->running = false;
}

void Updater::Run() {
	this->running = true;
	while (this->running) {
		string oldVersion = Util::ReadFile(path + "/version.txt", 40);

		string verFile(path + "version.txt");
		if (Util::Download(host, url + "/version.txt", port, verFile)) {
			string newVersion = Util::ReadFile(path + "/version.txt", 40);
			if (oldVersion != newVersion) {
				Util::Download(host, url + "/client.zip", port,
						path + "client.zip");
				Util::FilesRead(path.c_str());
				HANDLE hMutex = CreateMutex(NULL, FALSE, "terminal");
				if (GetLastError() == ERROR_ALREADY_EXISTS) {

					Util::KillProcess(application);
					Sleep(5000);
					Util::Unzip(path + "client.zip", path);

					string exe = path + application;
					Util::ShellExecuteNoWait(exe);
					CloseHandle(hMutex);
				} else {
					CloseHandle(hMutex);
					Util::Unzip(path + "client.zip", path);
				}
			}
		}

		if (Util::ProcessCount(application) == 0) {
			string exe = path + application;
			Util::ShellExecuteNoWait(exe);
		}

		Sleep(interval);
	}
}
