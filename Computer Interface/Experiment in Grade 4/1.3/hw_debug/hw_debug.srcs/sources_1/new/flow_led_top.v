`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/09/07 11:32:54
// Design Name: 
// Module Name: flow_led_top
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module flow_led_top
(
	input clk,		// 100Mhz
	output [15:0] led
);

wire clk_pulse;

clk_div clk_div
(
	.clk(clk),
	.clk_pulse(clk_pulse)	// 1Hz
);

flow_led flow_led
(
	.clk(clk),
	.clk_pulse(clk_pulse),
	.led_r(led)
);
endmodule
