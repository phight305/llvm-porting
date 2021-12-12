include "TOYInstrFormats.td"

def immSExt16 : PatLeaf<(imm), [{ return isInt<16>(N->getSExtValue()); }]>;

// Addressing modes.
def ADDRrr : ComplexPattern<i32, 2, "SelectADDRrr", [], []>;

// Address operands
def MEMrr : Operand<i32> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GRRegs, GRRegs);
  let EncoderMethod = "getMemEncoding";
}

// Call instruction
def SDT_TOYCall : SDTypeProfile<0, -1, [SDTCisVT<0, i32>]>;
def call : SDNode<"TOYISD::CALL", SDT_TOYCall,
                  [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue, SDNPVariadic]>;

def calltarget : Operand<i32>;

let isCall = 1, isBarrier = 1, Defs = [LR, R0], Uses = [SP] in {
  def CALL :
    InstTOY<(outs), (ins calltarget:$dst, variable_ops),
            "call $dst",
            [(call tglobaladdr:$dst)]> {
    bits<16> dst;
    let Inst{31-29} = 0;
    let Inst{28-24} = 0b01000; // Opcode
    let Inst{16-23} = 0;
    let Inst{15-0} = dst;
  }
}

// Return instruction
def SDT_SPRet     : SDTypeProfile<0, 1, [SDTCisVT<0, i32>]>;
def retflag       : SDNode<"TOYISD::RET_FLAG", SDT_SPRet,
                           [SDNPHasChain, SDNPOptInGlue]>;

let isReturn = 1, isTerminator = 1, isBarrier = 1 in {
  def RET :
    InstTOY<(outs), (ins GRRegs:$ra),
            "ret $ra",
            [(retflag (i32 GRRegs:$ra))]> {
    bits<4> ra;
    let Inst{31-29} = 0;
    let Inst{28-24} = 0b00111; // Opcode
    let Inst{23-4} = 0;
    let Inst{3-0} = ra;
  }
}

// ALU instructions
def ADDrr :
  InstTOY<(outs GRRegs:$dst), (ins GRRegs:$src1, GRRegs:$src2),
          "add $dst, $src1, $src2",
          [(set (i32 GRRegs:$dst), (add (i32 GRRegs:$src1), (i32 GRRegs:$src2)))]> {
  bits<4> dst;
  bits<4> src1;
  bits<4> src2;
  let Inst{31-29} = 0;
  let Inst{28-24} = 0b00001; // Opcode
  let Inst{11-8} = dst;
  let Inst{7-4} = src1;
  let Inst{3-0} = src2;
}

def ADDri :
  InstTOY<(outs GRRegs:$dst), (ins GRRegs:$src1, i32imm:$src2),
          "addi $dst, $src1, $src2",
          [(set (i32 GRRegs:$dst), (add (i32 GRRegs:$src1), (i32 imm:$src2)))]> {
  bits<4> src1;
  bits<16> src2;
  bits<4> dst;
  let Inst{31-29} = 0;
  let Inst{28-24} = 0b00010; // Opcode
  let Inst{23-20} = dst;
  let Inst{19-16} = src1;
  let Inst{15-0} = src2;
}

def SUBri :
  InstTOY<(outs GRRegs:$dst), (ins GRRegs:$src1, i32imm:$src2),
          "subi $dst, $src1, $src2",
          [(set (i32 GRRegs:$dst), (sub (i32 GRRegs:$src1), (i32 imm:$src2)))]> {
  bits<4> src1;
  bits<16> src2;
  bits<4> dst;
  let Inst{31-29} = 0;
  let Inst{28-24} = 0b00011; // Opcode
  let Inst{23-20} = dst;
  let Inst{19-16} = src1;
  let Inst{15-0} = src2;
}

// Load/Store instructions
def STORErr :
  InstTOY<(outs), (ins GRRegs:$src, MEMrr:$addr),
          "store $src, $addr",
          [(store GRRegs:$src, ADDRrr:$addr)]> {
  bits<4> src;
  bits<8> addr;
  let Inst{31-29} = 0;
  let Inst{28-24} = 0b00101; // Opcode
  let Inst{23-12} = 0;
  let Inst{11-4} = addr;
  let Inst{3-0} = src;
}

def LOADrr :
  InstTOY<(outs GRRegs:$dst), (ins MEMrr:$addr),
          "load $dst, $addr",
          [(set (i32 GRRegs:$dst), (load ADDRrr:$addr))]> {
  bits<4> dst;
  bits<8> addr;
  let Inst{31-29} = 0;
  let Inst{28-24} = 0b00110; // Opcode
  let Inst{23-12} = 0;
  let Inst{11-4} = addr;
  let Inst{3-0} = dst;
}

// Data movement instructions
def MOVi :
  InstTOY<(outs GRRegs:$dst), (ins i32imm:$src),
          "mov $dst, $src",
          []> {
  bits<4> dst;
  bits<16> src;
  let Inst{31-29} = 0;
  let Inst{28-24} = 0b01001; // Opcode
  let Inst{23-20} = dst;
  let Inst{15-0} = src;
}

def : Pat<(i32 immSExt16:$in),
          (MOVi imm:$in)>;

// Unconditional branch

def jmptarget : Operand<OtherVT>;
let isBranch = 1, isTerminator = 1, isBarrier = 1, hasSideEffects = 1 in {
  def BR :
    InstTOY<(outs), (ins jmptarget:$addr),
            "br $addr", [(br bb:$addr)]> {
    bits<16> addr;
    let Inst{31-29} = 0;
    let Inst{28-24} = 0b01010; // Opcode
    let Inst{23-16} = 0;
    let Inst{15-0} = addr;
  }
}

// Conditional branch

def SDT_TOYBrCC : SDTypeProfile<0, 1, [SDTCisVT<0, OtherVT>]>;
def TOYbrcc : SDNode<"TOYISD::BR_CC", SDT_TOYBrCC,
                      [SDNPHasChain, SDNPInGlue]>;

def brtarget : Operand<OtherVT>;
let Uses = [PRED], isBranch = 1, isBarrier = 1, hasSideEffects = 1 in {
  def BRCC:
    InstTOY<(outs), (ins brtarget:$dst),
            "brcc $dst",
            [(TOYbrcc (bb:$dst))]> {
    bits<16> dst;
    let Inst{31-29} = 0;
    let Inst{28-24} = 0b01011; // Opcode
    let Inst{23-19} = 0;
    let Inst{19-16} = 0;
    let Inst{15-0}  = dst;
  }
}

// Cmp instructions

def SDT_TOYCmp : SDTypeProfile<0, 2, [SDTCisSameAs<0, 1>]>;
def TOYCmpEq : SDNode<"TOYISD::CMPEQ", SDT_TOYCmp, [SDNPOutGlue]>;
def TOYCmpNe : SDNode<"TOYISD::CMPNE", SDT_TOYCmp, [SDNPOutGlue]>;
def TOYCmpLt : SDNode<"TOYISD::CMPLT", SDT_TOYCmp, [SDNPOutGlue]>;
def TOYCmpLe : SDNode<"TOYISD::CMPLE", SDT_TOYCmp, [SDNPOutGlue]>;
def TOYCmpGt : SDNode<"TOYISD::CMPGT", SDT_TOYCmp, [SDNPOutGlue]>;
def TOYCmpGe : SDNode<"TOYISD::CMPGE", SDT_TOYCmp, [SDNPOutGlue]>;

class CMP<bits<5> opcode, string asm, SDNode opnode> :
  InstTOY<(outs), (ins GRRegs:$src1, GRRegs:$src2),
          !strconcat(asm, " $src1, $src2"),
          [(opnode (i32 GRRegs:$src1), (i32 GRRegs:$src2))]> {
  bits<4> src1;
  bits<4> src2;
  let Inst{31-29} = 0;
  let Inst{28-24} = opcode;
  let Inst{23-19} = 0;
  let Inst{7-4} = src2;
  let Inst{3-0} = src1;
}

let Defs = [PRED] in {
  def CMPEQ : CMP<0b01100, "cmp_eq", TOYCmpEq>;
  def CMPNE : CMP<0b01101, "cmp_ne", TOYCmpNe>;
  def CMPLT : CMP<0b01110, "cmp_lt", TOYCmpLt>;
  def CMPLE : CMP<0b01111, "cmp_le", TOYCmpLe>;
  def CMPGT : CMP<0b10000, "cmp_gt", TOYCmpGe>;
  def CMPGE : CMP<0b10001, "cmp_ge", TOYCmpGe>;
}
