onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /testbench/my_mips/clk
add wave -noupdate /testbench/my_mips/rst
add wave -noupdate /testbench/my_mips/zero
add wave -noupdate /testbench/my_mips/beqout
add wave -noupdate /testbench/my_mips/ALUctr
add wave -noupdate /testbench/my_mips/ExtOp
add wave -noupdate -radix hexadecimal /testbench/my_mips/PC_add_4
add wave -noupdate -radix unsigned /testbench/my_mips/RS
add wave -noupdate -radix unsigned /testbench/my_mips/RT
add wave -noupdate -radix unsigned /testbench/my_mips/RD
add wave -noupdate -radix unsigned /testbench/my_mips/SA
add wave -noupdate -radix hexadecimal /testbench/my_mips/imm_16
add wave -noupdate -radix hexadecimal /testbench/my_mips/imm_26
add wave -noupdate -radix unsigned /testbench/my_mips/ALUout
add wave -noupdate -radix unsigned /testbench/my_mips/RS1out
add wave -noupdate -color Red -radix hexadecimal /testbench/my_mips/instr
add wave -noupdate -radix hexadecimal /testbench/my_mips/PCout
add wave -noupdate -radix hexadecimal /testbench/my_mips/PCin
add wave -noupdate -radix hexadecimal /testbench/my_mips/DMout
add wave -noupdate -radix hexadecimal /testbench/my_mips/extout
add wave -noupdate -radix unsigned /testbench/my_mips/RS2out
add wave -noupdate /testbench/my_mips/npc_sel
add wave -noupdate /testbench/my_mips/RegWrt
add wave -noupdate /testbench/my_mips/DMWrite
add wave -noupdate /testbench/my_mips/op
add wave -noupdate /testbench/my_mips/funct
add wave -noupdate /testbench/my_mips/mux4_5out
add wave -noupdate -radix hexadecimal /testbench/my_mips/mux4_32out
add wave -noupdate -radix hexadecimal /testbench/my_mips/mux2out
add wave -noupdate /testbench/my_mips/mux4_32sel
add wave -noupdate /testbench/my_mips/mux4_5sel
add wave -noupdate -radix unsigned /testbench/my_mips/mux2sel
add wave -noupdate -radix hexadecimal /testbench/my_mips/instrout
add wave -noupdate -radix unsigned /testbench/my_mips/U_RF/RS1_I
add wave -noupdate -radix unsigned /testbench/my_mips/U_RF/RS2_I
add wave -noupdate -radix unsigned /testbench/my_mips/U_RF/RD_I
add wave -noupdate /testbench/my_mips/U_RF/RegWr_I
add wave -noupdate -radix hexadecimal /testbench/my_mips/U_RF/WData_I
add wave -noupdate -radix hexadecimal /testbench/my_mips/U_RF/RS1_O
add wave -noupdate -radix hexadecimal /testbench/my_mips/U_RF/RS2_O
add wave -noupdate -radix unsigned -childformat {{{/testbench/my_mips/U_RF/gpr[31]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[30]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[29]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[28]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[27]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[26]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[25]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[24]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[23]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[22]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[21]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[20]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[19]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[18]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[17]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[16]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[15]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[14]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[13]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[12]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[11]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[10]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[9]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[8]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[7]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[6]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[5]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[4]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[3]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[2]} -radix unsigned} {{/testbench/my_mips/U_RF/gpr[1]} -radix unsigned}} -subitemconfig {{/testbench/my_mips/U_RF/gpr[31]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[30]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[29]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[28]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[27]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[26]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[25]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[24]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[23]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[22]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[21]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[20]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[19]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[18]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[17]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[16]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[15]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[14]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[13]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[12]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[11]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[10]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[9]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[8]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[7]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[6]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[5]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[4]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[3]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[2]} {-height 15 -radix unsigned} {/testbench/my_mips/U_RF/gpr[1]} {-height 15 -radix unsigned}} /testbench/my_mips/U_RF/gpr
add wave -noupdate -radix hexadecimal /testbench/my_mips/U_ALU/A
add wave -noupdate -radix hexadecimal /testbench/my_mips/U_ALU/B
add wave -noupdate /testbench/my_mips/U_ALU/Ctrl
add wave -noupdate -radix hexadecimal /testbench/my_mips/U_ALU/C
add wave -noupdate -radix unsigned /testbench/my_mips/U_ALU/Zero
add wave -noupdate -radix unsigned /testbench/my_mips/U_ALU/beqout
add wave -noupdate -radix hexadecimal /testbench/my_mips/U_ALU/tmp_arith
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {707 ns} 0}
quietly wave cursor active 1
configure wave -namecolwidth 217
configure wave -valuecolwidth 128
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {777 ns} {883 ns}
