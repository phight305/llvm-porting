include "TOYInstrFormats.td"

def immSExt16 : PatLeaf<(imm), [{ return isInt<16>(N->getSExtValue()); }]>;

// Addressing modes.
def ADDRrr : ComplexPattern<i32, 2, "SelectADDRrr", [], []>;

// Address operands
def MEMrr : Operand<i32> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GRRegs, GRRegs);
}

// Call instruction
def SDT_TOYCall : SDTypeProfile<0, -1, [SDTCisVT<0, i32>]>;
def call : SDNode<"TOYISD::CALL", SDT_TOYCall,
                  [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue, SDNPVariadic]>;

def calltarget : Operand<i32>;

let isCall = 1, isBarrier = 1, Defs = [LR], Uses = [SP] in {
  def CALL :
    InstTOY<(outs), (ins calltarget:$dst, variable_ops),
            "call $dst",
            [(call tglobaladdr:$dst)]>;
}

// Return instruction
def SDT_SPRet     : SDTypeProfile<0, 1, [SDTCisVT<0, i32>]>;
def retflag       : SDNode<"TOYISD::RET_FLAG", SDT_SPRet,
                           [SDNPHasChain, SDNPOptInGlue]>;

let isReturn = 1, isTerminator = 1, isBarrier = 1 in {
  def RET :
    InstTOY<(outs), (ins GRRegs:$ra),
            "ret $ra",
            [(retflag (i32 GRRegs:$ra))]>;
}

// ALU instructions
def ADDrr :
  InstTOY<(outs GRRegs:$dst), (ins GRRegs:$src1, GRRegs:$src2),
          "add $dst, $src1,z$src2",
          [(set (i32 GRRegs:$dst), (add (i32 GRRegs:$src1), (i32 GRRegs:$src2)))]>;

def ADDri :
  InstTOY<(outs GRRegs:$dst), (ins GRRegs:$src1, i32imm:$src2),
          "addi $dst, $src1, $src2",
          [(set (i32 GRRegs:$dst), (add (i32 GRRegs:$src1), (i32 imm:$src2)))]>;

def SUBri :
  InstTOY<(outs GRRegs:$dst), (ins GRRegs:$src1, i32imm:$src2),
          "subi $dst, $src1, $src2",
          [(set (i32 GRRegs:$dst), (sub (i32 GRRegs:$src1), (i32 imm:$src2)))]>;

// Load/Store instructions
def STORErr :
  InstTOY<(outs), (ins GRRegs:$src, MEMrr:$addr),
          "store $src, $addr",
          [(store GRRegs:$src, ADDRrr:$addr)]>;

def LOADrr :
  InstTOY<(outs GRRegs:$dst), (ins MEMrr:$addr),
          "load $dst, $addr",
          [(set (i32 GRRegs:$dst), (load ADDRrr:$addr))]>;

// Data movement instructions
def MOVi :
  InstTOY<(outs GRRegs:$dst), (ins i32imm:$src),
          "mov $dst, $src",
          []>;

def : Pat<(i32 immSExt16:$in),
          (MOVi imm:$in)>;
