include "TOYInstrFormats.td"

// Addressing modes.
def ADDRrr : ComplexPattern<i32, 2, "SelectADDRrr", [], []>;

// Address operands
def MEMrr : Operand<i32> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GRRegs, GRRegs);
}

def ADDrr :
  InstTOY<(outs GRRegs:$dst), (ins GRRegs:$src1, GRRegs:$src2),
          "add $dst, $src1,z$src2",
          [(set (i32 GRRegs:$dst), (add (i32 GRRegs:$src1), (i32 GRRegs:$src2)))]>;

def STORErr :
  InstTOY<(outs), (ins GRRegs:$src, MEMrr:$addr),
          "store $src0, $addr",
          [(store GRRegs:$src, ADDRrr:$addr)]>;

