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

    /*struct stat s;
    if (stat("/etc/sysconfig/network-scripts/ifcfg-lo", &s)) pushButtonLo->setEnabled(FALSE);
    if (stat("/etc/sysconfig/network-scripts/ifcfg-eth0", &s)) pushButtonEth0->setEnabled(FALSE);
    if (stat("/etc/sysconfig/network-scripts/ifcfg-eth1", &s)) pushButtonEth1->setEnabled(FALSE);
    if (stat("/etc/sysconfig/network-scripts/ifcfg-wlan0", &s)) pushButtonWlan0->setEnabled(FALSE);*/

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
	free | grep Mem: | awk '{print $2}' >> /tmp/BerryCC.tmp\n\
	free | grep cache: | awk '{print $4}' >> /tmp/BerryCC.tmp\n\
	cat /proc/cpuinfo | grep \"cache size\" | sed 's/cache size\t: //' >> /tmp/BerryCC.tmp\n\
	cat /proc/cpuinfo | grep \"flags\" | sed 's/flags\t: //' >> /tmp/BerryCC.tmp\n\
	cat /proc/cpuinfo | grep \"bogomips\" | sed 's/bogomips\t: //' >> /tmp/BerryCC.tmp\n\
	");
    f.open("/tmp/BerryCC.tmp");
    if (!f.fail()) {
	// type
	f.getline(buff, 256);
	textLabelCpu->setText(QString::fromUtf8(buff));
	// speed
	f.getline(buff, 256);
	strncat(buff, " MHz", 256);
	textLabelCpuMHz->setText(QString::fromUtf8(buff));
	// memory
	int mem, mfree, cache;
	f.getline(buff, 256);
	mem = atoi(buff);
	f.getline(buff, 256);
	mfree = atoi(buff);
	f.getline(buff, 256);
	cache = atoi(buff);
	sprintf(buff, "Mem %d%% Use / Cache %d KB", 100-mfree*100/mem, cache);
	textLabelCpuCache->setText(QString::fromUtf8(buff));
	// flag
	f.getline(buff, 256);
	textLabelCpuFlags->setText(QString::fromUtf8(buff));
	// bogomips
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
    unlink("/tmp/BerryCC.tmp");
    // Computer Name
    lineEditCName->setText(QString::fromUtf8(buff));
    // WORKGROUP for samba
    lineEditWGROUP->setText(QString::fromUtf8(workgroup));

    // Network Interfaces
//    FILE *pp=popen("cat /proc/net/dev | grep ':' | grep -v lo | grep -v sit | cut -d ':' -f 1 | tr -d ' '", "r");
    FILE *pp=popen("cat /proc/net/dev | grep ':' | grep -v sit | cut -d ':' -f 1 | tr -d ' '", "r");
    if (pp) {
//        while ((i=fread(buff, sizeof(char), 256, pp)) > 0) {
//	    buff[i-1]=0;
        while (fgets(buff, 256, pp)) {
	    buff[strlen(buff)-1]=0;
	    comboBoxNDev->insertItem(QString::fromUtf8(buff));
        }
        pclose(pp);
    }
    netChangeDev();
    // DNS
    pp=popen("cat /etc/resolv.conf | grep nameserver | cut -d ' ' -f 2 | tail -n 2 | head -n 1", "r");
    if (pp) {
	i=fread(buff, sizeof(char), 256, pp);
	buff[i-1]=0;
	lineEditDNS->setText(QString::fromUtf8(buff));
	pclose(pp);
    }
    pp=popen("cat /etc/resolv.conf | grep nameserver | cut -d ' ' -f 2 | tail -n 1", "r");
    if (pp) {
	i=fread(buff, sizeof(char), 256, pp);
	buff[i-1]=0;
	lineEditDNS2->setText(QString::fromUtf8(buff));
	pclose(pp);
    }
}

void Berry_Control_Centre::cnameModify()
{
    QString buff;
    buff = "perl -pi -e 's/[^#]workgroup.*=.*/workgroup = " + lineEditWGROUP->text() + "/' /etc/samba/smb.conf\n/etc/init.d/smb restart";
    system(buff);
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

void Berry_Control_Centre::netChangeDev()
{
    int n;
    char buff[256];
    // IP Address
    FILE *pp=popen("/sbin/ifconfig "+comboBoxNDev->currentText()+" |egrep -o 'addr:[0-9.]+' | cut -b 6-", "r");
    if (pp) {
	n=fread(buff, sizeof(char), 256, pp);
	buff[n-1]=0;
	lineEditIP->setText(QString::fromUtf8(buff));
	pclose(pp);
    }
    // Netmask
    pp=popen("/sbin/ifconfig "+comboBoxNDev->currentText()+" |egrep -o Mask:[0-9.]+ | cut -b 6-", "r");
    if (pp) {
	n=fread(buff, sizeof(char), 256, pp);
	buff[n-1]=0;
	lineEditMask->setText(QString::fromUtf8(buff));
	pclose(pp);
    }
    // Gateway
    pp=popen("route -n |grep "+comboBoxNDev->currentText()+" |grep UG | tr -s \" \" |cut -d \" \" -f 2", "r");
    if (pp) {
	n=fread(buff, sizeof(char), 256, pp);
	buff[n-1]=0;
	lineEditGw->setText(QString::fromUtf8(buff));
	pclose(pp);
    }
}


void Berry_Control_Centre::netUp()
{
	system("killall dhcpcd; ifconfig "+comboBoxNDev->currentText()+" down;"\
		"ifconfig "+comboBoxNDev->currentText()+" "+lineEditIP->text()+" netmask "+lineEditMask->text()+";"\
		"route add default gateway "+lineEditGw->text()+" "+comboBoxNDev->currentText());
}

void Berry_Control_Centre::yumCheckUpdate()
{
    int n;
    char buff[256];
    FILE *pp=popen("yum check-update | grep updates-released", "r");
    if (pp) {
	listBoxYum->clear();
	while (fgets(buff, 255, pp)) {
	    buff[strlen(buff)-1]=0;
	    //textEditYum->insert(QString::fromUtf8(buff)+"\n");
	    listBoxYum->insertItem(QString::fromUtf8(buff));
	}
	pclose(pp);
    }
}

void Berry_Control_Centre::yumUpdate()
{
    int n;
    char buff[256];
    FILE *pp=popen("yum update", "r");
    if (pp) {
	listBoxYum->clear();
	while (fgets(buff, 255, pp)) {
	    buff[strlen(buff)-1]=0;
	    //textEditYum->insert(QString::fromUtf8(buff)+"\n");
	    listBoxYum->insertItem(QString::fromUtf8(buff));
	}
	pclose(pp);
    }
}

void Berry_Control_Centre::yumClean()
{
    int n;
    char buff[256];
    FILE *pp=popen("yum clean all", "r");
    if (pp) {
	listBoxYum->clear();
	while (fgets(buff, 255, pp)) {
	    buff[strlen(buff)-1]=0;
	    //textEditYum->insert(QString::fromUtf8(buff)+"\n");
	    listBoxYum->insertItem(QString::fromUtf8(buff));
	}
	pclose(pp);
    }
}

void Berry_Control_Centre::yumInstall()
{
    int n;
    char buff[256];
    QString s = listBoxYum->currentText();
    n = s.find(' ');
    FILE *pp=popen("yum -y install "+s.left(n), "r");
    if (pp) {
	listBoxYum->clear();
	while (fgets(buff, 255, pp)) {
	    buff[strlen(buff)-1]=0;
	    listBoxYum->insertItem(QString::fromUtf8(buff));
	}
	pclose(pp);
    }
}
