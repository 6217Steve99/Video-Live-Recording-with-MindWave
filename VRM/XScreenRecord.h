#pragma once
#include <QThread>
#include <QMutex>

class XScreenRecord:protected QThread
{
public:
	//in
	int fps = 10;
	int outWidth = 1280;
	int outHeight = 720;

	bool Start(const char *filename);
	void Stop();
	void run();
	static XScreenRecord *Get()
	{
		static XScreenRecord ct;
		return &ct;
	}

	virtual ~XScreenRecord();
protected:
	bool isExit = false;
	QMutex mutex;
	XScreenRecord();
};

