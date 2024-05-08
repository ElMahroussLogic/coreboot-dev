# ====================================
#
#   SoftwareLabs CoreBoot
#   (C) SoftwareLabs all rights reserved.
#
#   Purpose: Assembler API.
#
# ====================================

[global mp_flush_tlb]

mp_flush_tlb:
    invlpg
    ret