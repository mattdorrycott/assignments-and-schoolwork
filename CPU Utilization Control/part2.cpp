#include <iostream>
#include <fstream>
#include <unistd.h>
using namespace std;

struct stats {
	unsigned long user, nice, system, idle, iowait, irq, softirq, steal;
};

void getStats(struct stats *st, int cpunum) {
	FILE *fp = fopen("/proc/stat", "r");
	int lskip = cpunum+1;
	int line = 0;
	char ch;
	while((line < lskip) && ((ch = getc(fp)) != EOF)) {
		if(ch == '\n') { line++; }
	}
	char cpun[255];
	fscanf(fp, "%s %d %d %d %d %d %d %d %d", cpun, &(st->user), &(st->nice),
		&(st->system), &(st->idle), &(st->iowait), &(st->irq), &(st->softirq), &(st->steal));
	fclose(fp);
	return;
}

void printStats(struct stats st, string name) {
	cout << name << ": " << st.user << " " << st.nice << " " << st.system << " "
			<< st.idle << " " << st.iowait << " "<< st.irq << " " <<
			st.softirq << " " << st.steal << endl;
}

unsigned long findUsage(struct stats st) {
	unsigned long total, idle, usage;
	total = st.user + st.nice + st.system + st.idle + st.iowait + st.irq +
			st.softirq +st.steal;
	idle = st.idle + st.iowait;
	usage = total- idle;
	return usage;
}

unsigned long findTotal(struct stats st) {
	unsigned long total, idle;
	total = st.user + st.nice + st.system + st.idle + st.iowait + st.irq +
			st.softirq +st.steal;
	return total;
}

double calcUtil(unsigned long u1, unsigned long u2, unsigned long t1, unsigned long t2) {
	unsigned long du, dt;
	du = u2-u1;
	dt = t2-t1;
	double util = ((double)du/(double)dt *100);
	return util;
}

int main()
{
	struct stats cpu_1, cpu_2;
	struct stats core0_1, core0_2, core1_1, core1_2, core2_1, core2_2, core3_1, core3_2;
	double u1, u2, t1, t2, u1_0, u2_0, t1_0, t2_0, u1_1, u2_1, t1_1, t2_1;
	double u1_2, u2_2, t1_2, t2_2, u1_3, u2_3, t1_3, t2_3;
	double  util, util0, util1, util2, util3;
	while(true) {
		getStats(&cpu_1, -1);
		//printStats(cpu_1, "cpu");
		getStats(&core0_1, 0);
		//printStats(core0_1, "core0");
		getStats(&core1_1, 1);
		//printStats(core1_1, "core1");
		getStats(&core2_1, 2);
		//printStats(core2_1, "core2");
		getStats(&core3_1, 3);
		//printStats(core3_1, "core3");
		sleep(1);
		getStats(&cpu_2, -1);
		//printStats(cpu_2, "cpu");
		getStats(&core0_2, 0);
		//printStats(core0_2, "core0");
		getStats(&core1_2, 1);
		//printStats(core1_2, "core1");
		getStats(&core2_2, 2);
		//printStats(core2_2, "core2");
		getStats(&core3_2, 3);
		//printStats(core3_2, "core1");
		util = calcUtil(findUsage(cpu_1), findUsage(cpu_2), findTotal(cpu_1), findTotal(cpu_2));
		util0 = calcUtil(findUsage(core0_1), findUsage(core0_2), findTotal(core0_1), findTotal(core0_2));
		util1 = calcUtil(findUsage(core1_1), findUsage(core1_2), findTotal(core1_1), findTotal(core1_2));
		util2 = calcUtil(findUsage(core2_1), findUsage(core2_2), findTotal(core2_1), findTotal(core2_2));
		util3 = calcUtil(findUsage(core3_1), findUsage(core3_2), findTotal(core3_1), findTotal(core3_2));
		cout << "TOTAL CPU UTILIZATION: " << util << "%" << endl;
		//cout << "CORE 0 UTILIZATION: " << util0 << "%" << endl;
		//cout << "CORE 1 UTILIZATION: " << util1 << "%" << endl;
		//cout << "CORE 2 UTILIZATION: " << util2 << "%" << endl;
		//cout << "CORE 3 UTILIZATION: " << util3 << "%" << endl;
		double maxUtil = util0;
		if(maxUtil > util1) {
			if(maxUtil > util2) {
				if(maxUtil > util3) {
					cout << "Core 0 Utilization: " << maxUtil << "%" << endl;
				}
				else {
					maxUtil = util3;
					cout << "Core 3 Utilization: " << maxUtil << "%" << endl;
				}
			}
		}
		else if(util1 > util2) {
			if(util1 > util3) {
				maxUtil = util1;
				cout << "Core 1 Utilization: "<< maxUtil << "%" << endl;
			}
			else {
				maxUtil = util3;
				cout << "Core 3 Utilization: " << maxUtil << "%" << endl;
			}
		}
		else if(util2 > util3) {
			maxUtil = util2;
			cout << "Core 2 Utilization: " << maxUtil << "%" << endl;
		}
		else {
			maxUtil = util3;
			cout << "Core 3 Utilization: " << maxUtil << "%" << endl;
		}
		double desired_freq = 1.25*1500000* maxUtil / 100;
		cout << desired_freq << endl;
		ofstream setspeed;
		setspeed.open("/sys/devices/system/cpu/cpufreq/policy0/scaling_setspeed");
		setspeed << (long int) desired_freq;
		setspeed.close();
		
		sleep(1);
	}
	
	return 0;
}

