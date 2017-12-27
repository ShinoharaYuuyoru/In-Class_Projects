onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -radix hexadecimal /testbench/my_mips/U_PC/PC
add wave -noupdate -radix hexadecimal /testbench/my_mips/instr
add wave -noupdate /testbench/my_mips/clk
add wave -noupdate /testbench/my_mips/rst
add wave -noupdate /testbench/my_mips/U_RF/CLK_I
add wave -noupdate -radix unsigned /testbench/my_mips/U_RF/RS1_I
add wave -noupdate -radix unsigned /testbench/my_mips/U_RF/RS2_I
add wave -noupdate -radix unsigned /testbench/my_mips/U_RF/RD_I
add wave -noupdate /testbench/my_mips/U_RF/RegWr_I
add wave -noupdate -radix hexadecimal /testbench/my_mips/U_RF/WData_I
add wave -noupdate -radix hexadecimal /testbench/my_mips/U_RF/RS1_O
add wave -noupdate -radix hexadecimal /testbench/my_mips/U_RF/RS2_O
add wave -noupdate -radix hexadecimal -childformat {{{/testbench/my_mips/U_RF/gpr[31]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[30]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[29]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[28]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[27]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[26]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[25]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[24]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[23]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[22]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[21]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[20]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[19]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[18]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[17]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[16]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[15]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[14]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[13]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[12]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[11]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[10]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[9]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[8]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[7]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[6]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[5]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[4]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[3]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[2]} -radix hexadecimal} {{/testbench/my_mips/U_RF/gpr[1]} -radix hexadecimal}} -expand -subitemconfig {{/testbench/my_mips/U_RF/gpr[31]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[30]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[29]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[28]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[27]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[26]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[25]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[24]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[23]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[22]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[21]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[20]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[19]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[18]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[17]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[16]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[15]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[14]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[13]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[12]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[11]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[10]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[9]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[8]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[7]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[6]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[5]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[4]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[3]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[2]} {-height 15 -radix hexadecimal} {/testbench/my_mips/U_RF/gpr[1]} {-height 15 -radix hexadecimal}} /testbench/my_mips/U_RF/gpr
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {6585036 ns} 0}
quietly wave cursor active 1
configure wave -namecolwidth 283
configure wave -valuecolwidth 146
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
WaveRestoreZoom {6585651 ns} {6585831 ns}
