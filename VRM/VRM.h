#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VRM.h"
#include <QTime>
#include <qtimer.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "thinkgear.h"
#include <fstream>


class VRM : public QMainWindow
{
	Q_OBJECT

public:
	VRM(QWidget *parent = Q_NULLPTR);

private slots:
	void on_timer_timeout();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
	Ui::VRMClass ui;
	QTimer* fTimer;
	int num = 0;

private:
	char* comPortName = "3";
	int   dllVersion = 0;
	int   connectionId = 0;
	int   packetsRead = 0;
	int   errCode = 0;

	double secondsToRun = 0;
	time_t startTime = 0;
	time_t currTime = 0;
	char* currTimeStr = NULL;
	int set_filter_flag = 0;
	int count = 0;
	std::fstream file;
};
