//===-- TOYMCInstLower.cpp - Convert Mips MachineInstr to MCInst ---------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains code to lower Mips MachineInstrs to their corresponding
// MCInst records.
//
//===----------------------------------------------------------------------===//
#include "TOYMCInstLower.h"
// #include "TOYAsmPrinter.h"
// #include "TOYInstrInfo.h"
// #include "MCTargetDesc/MipsBaseInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Target/Mangler.h"

using namespace llvm;

TOYMCInstLower::TOYMCInstLower() {}

MCOperand TOYMCInstLower::LowerSymbolOperand(const MachineOperand &MO,
                                              MachineOperandType MOTy,
                                              unsigned Offset) const {
  llvm_unreachable("LowerSymbolOperand not implemented\n");
}

MCOperand TOYMCInstLower::LowerOperand(const MachineOperand &MO,
                                        unsigned offset) const {
  llvm_unreachable("LowerOperand not been implemented yet!");
}

void TOYMCInstLower::Lower(const MachineInstr *MI, MCInst &OutMI) const {
  llvm_unreachable("Lower not been implemented yet!");
}
