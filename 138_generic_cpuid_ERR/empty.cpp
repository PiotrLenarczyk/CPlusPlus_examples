//Internet-based program
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#else
	#include <linux/hdreg.h>
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <sys/ioctl.h>
       #include <errno.h>
#endif

//only cpu family type based!
void getPSN(char *PSN)
{
    int varEAX, varEBX, varECX, varEDX;
    char str[9];
    //%eax=1 gives most significant 32 bits in eax 
    __asm__ __volatile__ ("cpuid"   : "=a" (varEAX), "=b" (varEBX), "=c" (varECX), "=d" (varEDX) : "a" (1));
    sprintf(str, "%08X", varEAX); //i.e. XXXX-XXXX-xxxx-xxxx-xxxx-xxxx
    sprintf(PSN, "%C%C%C%C-%C%C%C%C", str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
    //%eax=3 gives least significant 64 bits in edx and ecx [if PN is enabled]
    __asm__ __volatile__ ("cpuid"   : "=a" (varEAX), "=b" (varEBX), "=c" (varECX), "=d" (varEDX) : "a" (3));
    sprintf(str, "%08X", varEDX); //i.e. xxxx-xxxx-XXXX-XXXX-xxxx-xxxx
    sprintf(PSN, "%s-%C%C%C%C-%C%C%C%C", PSN, str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
    sprintf(str, "%08X", varECX); //i.e. xxxx-xxxx-xxxx-xxxx-XXXX-XXXX
    sprintf(PSN, "%s-%C%C%C%C-%C%C%C%C", PSN, str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
}

 static void getCpuid( unsigned int* p, unsigned int ax )       
 {         
    __asm __volatile         
    (   "movl %%ebx, %%esi\n\t"               
        "cpuid\n\t"          
        "xchgl %%ebx, %%esi" 
        : "=a" (p[0]), "=S" (p[1]),           
          "=c" (p[2]), "=d" (p[3])            
        : "0" (ax)           
    );     
 } 

#ifdef _WIN32
void hddId( char* hdd )
{ 
	system("wmic path win32_physicalmedia get SerialNumber");
};
#else
void hddId( char* hdd )
{	char buf[100];
	int st;
	sprintf(buf,"sudo hdparm -i %s | grep -i serial", hdd );
	printf( "====\n%s:\n", buf );
	st = system( buf );
};
#endif

int main()
{
     char PSN[30]; //24 Hex digits, 5 '-' separators, and a '\0'
     getPSN(PSN);
    printf("%s\n", PSN); //compare with: lshw | grep serial:
    
    unsigned int cpuinfo[4] = { 0, 0, 0, 0 };          
    getCpuid( cpuinfo, 0 );  
    for (int i = 0x0; i < 4; i++)
		printf( "[%i] : 0x%08X\n", i, cpuinfo[i] );
		
	hddId( (char*)"/dev/sr0" );
	hddId( (char*)"/dev/cdrom" );
	hddId( (char*)"/dev/hda" );
	hddId( (char*)"/dev/sda" );
     return 0;
}

