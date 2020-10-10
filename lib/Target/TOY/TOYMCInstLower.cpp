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
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Target/Mangler.h"

using namespace llvm;

TOYMCInstLower::TOYMCInstLower(MCContext &ctx, AsmPrinter &printer)
  : Ctx(ctx), Printer(printer) {}

MCOperand TOYMCInstLower::LowerSymbolOperand(const MachineOperand &MO,
                                             MachineOperandType MOTy,
                                             unsigned Offset) const {
  const MCSymbol *Symbol;
  switch (MOTy) {
  case MachineOperand::MO_GlobalAddress:
    Symbol = Printer.Mang->getSymbol(MO.getGlobal());
    Offset += MO.getOffset();
    break;
  default: llvm_unreachable("This MOTy is not supported");
  }

  // FIXME: For now, we only handle the symbol of call instruction, so it always
  //        return VMCSymbolRefExp::rK_TOY_CALL.
  MCSymbolRefExpr::VariantKind Kind;
  switch (MO.getTargetFlags()) {
  case 0: Kind = MCSymbolRefExpr::VK_TOY_CALL; break;
  default: llvm_unreachable("This target flag is not supported");
  }

  const MCExpr *Expr = MCSymbolRefExpr::Create(Symbol, Kind, Ctx);
  return MCOperand::CreateExpr(Expr);
}

MCOperand TOYMCInstLower::LowerOperand(const MachineOperand &MO,
                                       unsigned offset) const {
  MachineOperandType MOTy = MO.getType();

  switch (MOTy) {
  default: llvm_unreachable("unknown operand type");
  case MachineOperand::MO_Register:
    // Ignore all implicit register operands.
    if (MO.isImplicit()) break;
    return MCOperand::CreateReg(MO.getReg());
  case MachineOperand::MO_Immediate:
    return MCOperand::CreateImm(MO.getImm() + offset);
  case MachineOperand::MO_GlobalAddress:
    return LowerSymbolOperand(MO, MOTy, offset);
  }

  return MCOperand();
}

void TOYMCInstLower::Lower(const MachineInstr *MI, MCInst &OutMI) const {
  OutMI.setOpcode(MI->getOpcode());

  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    const MachineOperand &MO = MI->getOperand(i);
    MCOperand MCOp = LowerOperand(MO);

    if (MCOp.isValid())
      OutMI.addOperand(MCOp);
  }
}
