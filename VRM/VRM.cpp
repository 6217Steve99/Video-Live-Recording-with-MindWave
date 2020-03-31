#include "VRM.h"
#include <qdatetime.h>
#include <QString>
#include <iostream>
#include <fstream>

VRM::VRM(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	fTimer = new QTimer(this);
	fTimer->stop();
	fTimer->setInterval(5);
	connect(fTimer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
}

void VRM::on_timer_timeout()
{
    /* Read a single Packet from the connection */
    packetsRead = TG_ReadPackets(connectionId, 1);

    /* If TG_ReadPackets() was able to read a Packet of data... */
    if (packetsRead == 1) {
        //time_t current = time(&current);/*获取当前时间*/

        //char buff[26];
        //ctime_s(buff, sizeof buff, &current);
        //file << buff;

        /* If the Packet containted a new raw wave value... */
        if (TG_GetValueStatus(connectionId, TG_DATA_RAW) != 0) {
            /* Get and print out the new raw value */
            file << TG_GetValue(connectionId, TG_DATA_RAW);
        }
        file << ",";
        if (TG_GetValueStatus(connectionId, TG_DATA_ATTENTION) != 0) {
            /* Get and print out the new raw value */
            file << TG_GetValue(connectionId, TG_DATA_ATTENTION);
        }
        file << ",";
        if (TG_GetValueStatus(connectionId, TG_DATA_MEDITATION) != 0) {
            /* Get and print out the new raw value */
            file << TG_GetValue(connectionId, TG_DATA_MEDITATION);
        }
        file << ",";
        
        if (TG_GetValueStatus(connectionId, TG_DATA_DELTA) != 0) {
            file << TG_GetValue(connectionId, TG_DATA_DELTA);
        }

        file << ",";
        if (TG_GetValueStatus(connectionId, TG_DATA_THETA) != 0) {
            file << TG_GetValue(connectionId, TG_DATA_THETA);
        }
 
        file << ",";
        if (TG_GetValueStatus(connectionId, TG_DATA_ALPHA1) != 0) {
            file << TG_GetValue(connectionId, TG_DATA_ALPHA1);
        }

        file << ",";
        if (TG_GetValueStatus(connectionId, TG_DATA_ALPHA2) != 0) {
            file << TG_GetValue(connectionId, TG_DATA_ALPHA2);
        }

        file << ",";
        if (TG_GetValueStatus(connectionId, TG_DATA_BETA1) != 0) {
            file << TG_GetValue(connectionId, TG_DATA_BETA1);
        }

        file << ",";
        if (TG_GetValueStatus(connectionId, TG_DATA_BETA2) != 0) {
            file << TG_GetValue(connectionId, TG_DATA_BETA2);
        }

        file << ",";
        if (TG_GetValueStatus(connectionId, TG_DATA_GAMMA1) != 0) {
            file << TG_GetValue(connectionId, TG_DATA_GAMMA1);
        }

        file << ",";
        if (TG_GetValueStatus(connectionId, TG_DATA_GAMMA2) != 0) {
            file << TG_GetValue(connectionId, TG_DATA_GAMMA2);
        }

        file << ","<<mood<< std::endl;


        num++;
        ui.label->setText(QString::number(num));

    } /* end "If TG_ReadPackets() was able to read a Packet..." */

}

void VRM::on_pushButton_clicked()
{
	ui.label->setText("begin");
	fTimer->start();

    /* Get a connection ID handle to ThinkGear */
    connectionId = TG_GetNewConnectionId();
    if (connectionId < 0) {
        ui.label->setText("ERROR: TG_GetNewConnectionId() returned %d.");
    }

    /* Set/open stream (raw bytes) log file for connection */
    errCode = TG_SetStreamLog(connectionId, "streamLog.txt");
    if (errCode < 0) {
        ui.label->setText("ERROR: TG_SetStreamLog() returned %d.");
    }

    /* Set/open data (ThinkGear values) log file for connection */
    errCode = TG_SetDataLog(connectionId, "dataLog.txt");
    if (errCode < 0) {
        ui.label->setText("ERROR: TG_SetDataLog() returned %d.");
    }

    /* Attempt to connect the connection ID handle to serial port "COM5" */
    /* NOTE: On Windows, COM10 and higher must be preceded by \\.\, as in
     *       "\\\\.\\COM12" (must escape backslashes in strings).  COM9
     *       and lower do not require the \\.\, but are allowed to include
     *       them.  On Mac OS X, COM ports are named like
     *       "/dev/tty.MindSet-DevB-1".
     */
    comPortName = "\\\\.\\COM5";
    errCode = TG_Connect(connectionId,
        comPortName,
        TG_BAUD_57600,
        TG_STREAM_PACKETS);
    if (errCode < 0) {
        ui.label->setText("ERROR: TG_Connect() returned %d.");
    }
    file.open("data.csv", std::ios::out);
    file << "RAW,ATTENTION,MEDITATION,DELTA,THETA,ALPHA1,ALPHA2,BETA1,BETA2,GAMMA1,GAMMA2,MOOD" << std::endl;
    ui.label->setText("Begin");
}

void VRM::on_pushButton_2_clicked()
{
    fTimer->stop();
    file.close();
    ui.label->setText("Stop");
}

void VRM::on_radioButton_clicked()
{
    mood = 0;
}

void VRM::on_radioButton_2_clicked()
{
    mood = 1;
}

void VRM::on_radioButton_3_clicked()
{
    mood = 2;
}
