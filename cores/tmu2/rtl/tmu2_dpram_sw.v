/*
 * Milkymist VJ SoC
 * Copyright (C) 2007, 2008, 2009, 2010 Sebastien Bourdeauducq
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Double-port RAM with single write-capable port */

module tmu2_dpram_sw #(
	parameter depth = 11, /* < log2 of the capacity in words */
	parameter width = 32
) (
	input sys_clk,
	input ce,

	input [depth-1:0] a,
	input we,
	input [width-1:0] di,
	output reg [width-1:0] do,

	input [depth-1:0] a2,
	output reg [width-1:0] do2
);

reg [width-1:0] ram[0:(1 << depth)-1];

reg [width-1:0] do_tmp;
reg [width-1:0] do2_tmp;

always @(posedge sys_clk) begin
	if(ce) begin
		if(we)
			ram[a] <= di;
		do_tmp <= ram[a];
		do2_tmp <= ram[a2];
		do <= do_tmp;
		do2 <= do2_tmp;
	end
end


// synthesis translate_off

/*
 * For some reason, in Verilog the result of an undefined multiplied by zero
 * seems to be undefined.
 * This causes problems with pixels that texcache won't fetch because some fractional
 * parts are zero: the blend unit yields an undefined result on those, instead of ignoring
 * the contribution of the undefined pixel.
 * Work around this by initializing the memories.
 */

integer i;
initial begin
	for(i=0;i<(1 << depth);i=i+1)
		ram[i] = 0;
end

// synthesis translate_on

endmodule
