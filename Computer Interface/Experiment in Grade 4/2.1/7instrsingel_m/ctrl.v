module ctrl (clk,rst,op,funct,beqout,ALUctr,DMWrite,npc_sel,RegWrt,ExtOp,mux4_5sel,mux4_32sel,mux2sel);//ALUctr[1:0]
   input      	 clk,rst;
   input       	beqout;//made by alu
   input [5:0]  op,funct;
   
   //control signal out
   output [2:0] ALUctr;
   output       DMWrite;
   output [1:0] npc_sel;
   output       RegWrt;
   output [1:0] ExtOp;
   
   output [1:0] mux4_5sel;
   output [1:0] mux4_32sel;
   output mux2sel;
   
   wire Rtype,add,addiu,lw,sw,j,beq,addi;//Rtype,addu,subu,ori,lw,sw,beq,lui,addi,addiu,slt,j,jal,jr,lb,lbu,lh,lhu,sb,sh,slti;   //former
   //wire add,sub,sll,srl,sra,sllv,srlv,srav,AND,OR,XOR,NOR,andi,xori,sltiu,bne,blez,bgtz,bltz,bgez,jalr;//added
   //???
   assign Rtype = (op==6'b000000)?1:0;
   assign add   = (Rtype&&funct==6'b100000)?1:0;   	//&& ???it's better to be included in "head.v"
   assign sub   = (Rtype&&funct==6'b100010)?1:0;
   assign lw    = (op==6'b100011)?1:0;
   assign sw    = (op==6'b101011)?1:0;
   assign beq   = (op==6'b000100)?1:0;
   assign lui   = (op==6'b001111)?1:0;
   assign addiu = (op==6'b001001)?1:0;
   assign j     = (op==6'b000010)?1:0;
   assign addi  = (op==6'b001000)?1:0;		//ADDED
  

   
            //(add||addiu||lw||sw)?3'b001:(beq)?3'b010:3'b000;
   assign DMWrite = (sw)?'b1:'b0;
   assign npc_sel= (j)?2'b01:(beq&&beqout)?2'b11:2'b00;  //singular  valuebeq?11
   assign RegWrt =(add||addiu||lw||lui||addi)?'b1:'b0;//JAL???????????????		//ADDED
   assign ExtOp =(lui)?2'b00:(lw||sw||addi)?2'b10:2'b10;					//ADDED	EXTEND
   assign mux4_5sel =  (addiu||lui||lw||addi)?2'b00:2'b01;//add						//ADDED RD RT
   assign mux2sel  = (lw||sw||addiu||addi)?'b1:'b0;//beq								//ADDED ALUsrc
   assign mux4_32sel = (lui)?2'b11:(add||addiu||addi)?2'b00:(lw)?2'b01:2'b10;//??????pc+4????JAL		//ADDED MemtoReg
   
   assign ALUctr = (add||addiu||lw||sw||addi)?3'b001:(beq)?3'b010:3'b000;	//ADDED
   
endmodule  