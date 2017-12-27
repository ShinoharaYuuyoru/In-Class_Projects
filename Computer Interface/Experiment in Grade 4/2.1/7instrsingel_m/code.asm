#MIPS-C2: addiu，add，ori，lw，sw，beq，lui

    # test lui
    lui     $16, 0xABCD             # $16 = 0xABCD0000装入立即数到高16位
    
    # test addiu
    addiu   $16, $0, 0x1234         # $16 = 0x1234   addiu 格式 op rt rs  immediate 完成 rs+immediate =》rt
    addiu   $17, $16,2              # $17 = 0x1236
    addiu   $18, $16, -2            # $18 = 0x1232
    addiu   $19, $17, -2            # $19 = 0x1234
    
    # test add
    addiu   $16, $0, 1              # $16 = 1
    add     $17, $16, $16           # $17 = 2
    addiu   $17, $0, -1             # $17 = 0xFFFFFFFF
    addiu   $18, $0, 0x55AA         # $18 = 0x55AA
    add     $18, $16, $17           # $18 = 0
    
   
    # test sw, lw
    addiu   $22, $0, 0,             # $22 --> 0
    lui     $16, 0xEFAB
    sw      $16, 0($22)             # *$22 = 0xEFAB0000
    lw      $17, 0($22)             #装入字格式 lw rt offset（base）
    addiu   $16, $16, 0x5678
    sw      $16, 4($22)             # *$22 = 0xEFAB5678
    lw      $17, 4($22)
    
    # test beq
    addiu   $22, $0, 0,             # $22 --> 0
    
    lui     $16, 0xABCD
    addiu   $17, $0, 1
    addiu   $18, $0, 7
    addiu   $19, $0, 9
    
   
L_Begin :
    beq     $18, $19, L_End
    add     $16, $16, $17
    sw      $16, 0($22)
    addiu   $18, $18, 1
    addiu   $22, $22, 4
   j L_Begin
    
L_End :
    j L_End     
