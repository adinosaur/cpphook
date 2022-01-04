# cpphook
hook function in x86-64/linux. 

# Build
```
make clean && make
```

# Usgae
```c++
#include "cpphook.h"

install_hook("function_name_after_mangled", (void*)hook_function_address);
```
And link with `libcpphook.a` and `-ldl`.

# Noted
1. Compile your code with `-falign-functions=16`. This make sure function at least 16 bytes, so we can insert jump instrcution safely (13 bytes need).
2. Donot hook local function, because compiler maybe will optimize the calling convention for local function, Like that:
https://gcc.gnu.org/legacy-ml/gcc-help/2017-11/msg00039.html