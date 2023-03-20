#include <asm/asm.h>


LEAF(test_mips)
.set noreorder
    nop
    nop
    nop
    nop
    nop
    addiu t1, a0, 0x5678
    
.set reorder    
    jr ra

END(test_mips)