
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <dlfcn.h>
#include <stdio.h>
#include <assert.h>

int install_hook(const char* function_name, void* jump_to_addr)
{
    assert(function_name);
    assert(jump_to_addr);

    // https://man7.org/linux/man-pages/man3/dlsym.3.html
    // There are two special pseudo-handles that may be specified in handle:
    //
    //   RTLD_DEFAULT
    //      Find the first occurrence of the desired symbol using the
    //      default shared object search order.  The search will
    //      include global symbols in the executable and its
    //      dependencies, as well as symbols in shared objects that
    //      were dynamically loaded with the RTLD_GLOBAL flag.
    void* function_addr = dlsym(RTLD_DEFAULT, function_name);
    if (function_addr == NULL)
    {
        printf("err: %s\n", dlerror());
        return -1;
    }

    uint64_t pagesize = sysconf(_SC_PAGE_SIZE);
    void* page_addr = (void*)((uint64_t)function_addr - ((uint64_t)function_addr % pagesize));
    mprotect(page_addr, pagesize, PROT_READ | PROT_WRITE | PROT_EXEC);

    // https://en.wikipedia.org/wiki/X86_calling_conventions#x86-64_calling_conventions
    // The registers RAX, RCX, RDX, R8, R9, R10, R11 are considered volatile (caller-saved).
    char jmp_instruction[13] =
    {
        0x49, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     //mov r10, addr
        0x41, 0xFF, 0xE2,                                               //jmp r10
    };

    memcpy(&jmp_instruction[2], &jump_to_addr, sizeof(jump_to_addr));
    memcpy(function_addr, jmp_instruction, 13);
    mprotect(page_addr, pagesize, PROT_READ | PROT_EXEC);

    return 0;
}