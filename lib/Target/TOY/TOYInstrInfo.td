include "TOYInstrFormats.td"

def immSExt16 : PatLeaf<(imm), [{ return isInt<16>(N->getSExtValue()); }]>;

// Addressing modes.
def ADDRrr : ComplexPattern<i32, 2, "SelectADDRrr", [], []>;

// Address operands
def MEMrr : Operand<i32> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GRRegs, GRRegs);
}

// ALU instructions
def ADDrr :
  InstTOY<(outs GRRegs:$dst), (ins GRRegs:$src1, GRRegs:$src2),
          "add $dst, $src1,z$src2",
          [(set (i32 GRRegs:$dst), (add (i32 GRRegs:$src1), (i32 GRRegs:$src2)))]>;

// Load/Store instructions
def STORErr :
  InstTOY<(outs), (ins GRRegs:$src, MEMrr:$addr),
          "store $src0, $addr",
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
