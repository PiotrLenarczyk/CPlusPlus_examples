#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define VERBOSE

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <phys_addr> <offset>\n", argv[0]);
        return 0;
    };

    off_t offset = strtoul(argv[1], NULL, 0);
    size_t len = strtoul(argv[2], NULL, 0);
    if ( (len % 4) != 0 )
    {
        printf( "Access not aligned to 0x4!, Defaulting to 0x%08X\n", (len >> 2) << 2 );
        len = (len >> 2) << 2;
    };

    // Truncate offset to a multiple of the page size, or mmap will fail.
    size_t pagesize = sysconf( _SC_PAGE_SIZE );
    off_t page_base = (offset / pagesize) * pagesize;
    off_t page_offset = offset - page_base;

    int fd = open("/dev/mem",  O_RDWR | O_SYNC);
#ifdef VERBOSE
    printf( "offset : 0x%08X\n", offset );
    printf( "len : 0x%08X\n\n", len );
    printf( "fd : 0x%08X\n", fd );
    printf( "page_offset : 0x%08X\n", page_offset );
    printf( "page_base : 0x%08X\n", page_base );
#endif
    if (fd < 0)
    {
        perror( "Program can't open /dev/mem!" );
        return -1;
    };

    volatile unsigned int *mem = (unsigned int*)mmap(NULL, page_offset + len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, page_base);
    if (mem == MAP_FAILED)
    {
        perror("Program can't map memory");
        return -1;
    };

    size_t i;
    printf( "@0x%08X:\n", offset );
    for (i = 0; i < (len >> 2); ++i)
        printf("%08x ", (int)mem[(page_offset + i) >> 2]);
    puts( "" );

    munmap( (void*)mem, page_offset + len );
    close( fd );

    return 0;
};
