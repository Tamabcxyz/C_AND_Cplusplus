#include <sys/sysinfo.h>
uint64 getSysUpTime(void) {
	uint64 sysUpTime;
	struct sysinfo info;
	sysinfo(&info);
	sysUpTime = (((uint64)info.uptime) * 100);
	return(sysUpTime);
}