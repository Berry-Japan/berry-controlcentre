/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/


#include <sys/stat.h>

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int net_stat[5];
char workgroup[256];

void Berry_Control_Centre::init()
{
    int i;
    for (i=0; i<5; i++) net_stat[i]=1;

    struct stat s;
    if (stat("/etc/sysconfig/network-scripts/ifcfg-lo", &s)) pushButtonLo->setEnabled(FALSE);
    if (stat("/etc/sysconfig/network-scripts/ifcfg-eth0", &s)) pushButtonEth0->setEnabled(FALSE);
    if (stat("/etc/sysconfig/network-scripts/ifcfg-eth1", &s)) pushButtonEth1->setEnabled(FALSE);
    if (stat("/etc/sysconfig/network-scripts/ifcfg-wlan0", &s)) pushButtonWlan0->setEnabled(FALSE);

    ifstream f;
    char buff[256];

    // Berry Linux Version
    f.open("/etc/berry-release");
    if (!f.fail()) {
	f.getline(buff, 256);
	textLabelBerry->setText(QString::fromUtf8(buff));
    }
    f.close();

    // CPU info
    system("cat /proc/cpuinfo | grep \"model name\" | sed 's/model name\t: //' > /tmp/BerryCC.tmp\n\
	cat /proc/cpuinfo | grep \"cpu MHz\" | sed 's/cpu MHz.*: //' >> /tmp/BerryCC.tmp\n\
	cat /proc/cpuinfo | grep \"cache size\" | sed 's/cache size\t: //' >> /tmp/BerryCC.tmp\n\
	cat /proc/cpuinfo | grep \"flags\" | sed 's/flags\t: //' >> /tmp/BerryCC.tmp\n\
	cat /proc/cpuinfo | grep \"bogomips\" | sed 's/bogomips\t: //' >> /tmp/BerryCC.tmp\n\
	");
    f.open("/tmp/BerryCC.tmp");
    if (!f.fail()) {
	f.getline(buff, 256);
	textLabelCpu->setText(QString::fromUtf8(buff));
	f.getline(buff, 256);
	strncat(buff, " MHz", 256);
	textLabelCpuMHz->setText(QString::fromUtf8(buff));
	f.getline(buff, 256);
	textLabelCpuCache->setText(QString::fromUtf8(buff));
	f.getline(buff, 256);
	textLabelCpuFlags->setText(QString::fromUtf8(buff));
	f.getline(buff, 256);
	strncat(buff, " BogoMips", 256);
	textLabelCpuBMips->setText(QString::fromUtf8(buff));
    }
    f.close();

    system("hostname > /tmp/BerryCC.tmp\n\
	   cat /etc/samba/smb.conf | grep \"^[^#].*workgroup\" | sed 's/.*workgroup.*=[ \t]//' >> /tmp/BerryCC.tmp\n\
	   ");
    f.open("/tmp/BerryCC.tmp");
    if (f.fail()) {
	qWarning("Error");
    } else {
	//i = 0;
	//while (!f.eof()) {
	f.getline(buff, 256);
	f.getline(workgroup, 256);
	    //i++;
	//}
    }
    f.close();
//    remove_file("/tmp/BerryCC.tmp", NULL);
    // Computer Name
    lineEditCName->setText(QString::fromUtf8(buff));
    // WORKGROUP for samba
    lineEditWGROUP->setText(QString::fromUtf8(workgroup));
}

void Berry_Control_Centre::netStatLo()
{
//    qWarning("Hello, World");
//    execvp("/sbin/ifdown", "ifdown", "lo", NULL);
    if (net_stat[0]) {
	net_stat[0]=0;
	system("ifdown lo");
	pushButtonLo->setText(QString::fromUtf8("Start lo"));
    } else {
	net_stat[0]=1;
	system("ifup lo");
	pushButtonLo->setText(QString::fromUtf8("Stop lo"));
    }
}

void Berry_Control_Centre::netStatEth0()
{
    if (net_stat[1]) {
	net_stat[1]=0;
	system("ifdown eth0");
	pushButtonEth0->setText(QString::fromUtf8("Start eth0"));
    } else {
	net_stat[1]=1;
	system("ifup eth0");
	pushButtonEth0->setText(QString::fromUtf8("Stop eth0"));
    }
}

void Berry_Control_Centre::netStatEth1()
{
    if (net_stat[2]) {
	net_stat[2]=0;
	system("ifdown eth1");
	pushButtonEth1->setText(QString::fromUtf8("Start eth1"));
    } else {
	net_stat[2]=1;
	system("ifup eth1");
	pushButtonEth1->setText(QString::fromUtf8("Stop eth1"));
    }
}

void Berry_Control_Centre::netStatWlan0()
{
    if (net_stat[4]) {
	net_stat[4]=0;
	system("ifdown wlan0");
	pushButtonWlan0->setText(QString::fromUtf8("Start wlan0"));
    } else {
	net_stat[4]=1;
	system("ifup wlan0");
	pushButtonWlan0->setText(QString::fromUtf8("Stop wlan0"));
    }
}


void Berry_Control_Centre::cnameModify()
{
    QString buff;
    buff = "perl -pi -e 's/[^#]workgroup.*=.*/workgroup = " + lineEditWGROUP->text() + "/' /etc/samba/smb.conf\n/etc/init.d/smb restart";
    system(buff);
}
