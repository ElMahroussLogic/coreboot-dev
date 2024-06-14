# ====================================
#
#   Zeta Electronics Corporation CoreBoot
#   (C) Zeta Electronics Corporation all rights reserved.
#
#   Purpose: Assembler API for RISC-V
#
# ====================================

.balign 4
.global mp_flush_tlb

mp_flush_tlb:
    sfence.vma

    ret

