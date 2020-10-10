//===-- TOYAsmPrinter.cpp - TOY LLVM assembly writer ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to GAS-format TOY assembly language.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "asm-printer"
#include "TOYTargetMachine.h"
#include "TOYMCInstLower.h"

#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Target/Mangler.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/Twine.h"
#include "llvm/BasicBlock.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/InlineAsm.h"
#include "llvm/Instructions.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/Mangler.h"
#include "llvm/DataLayout.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

namespace {
  class TOYAsmPrinter : public AsmPrinter {
  public:

    explicit TOYAsmPrinter(TargetMachine &TM, MCStreamer &Streamer)
      : AsmPrinter(TM, Streamer) {}

    virtual const char *getPassName() const {
      return "TOY Assembly Printer";
    }

    void printOperand(const MachineInstr *MI, int opNum, raw_ostream &OS);
    void printMemOperand(const MachineInstr *MI, int opNum, raw_ostream &OS,
                         const char *Modifier = 0);
    void printCCOperand(const MachineInstr *MI, int opNum, raw_ostream &OS);

    virtual void EmitInstruction(const MachineInstr *MI) {
      MachineBasicBlock::const_instr_iterator I = MI;
      MachineBasicBlock::const_instr_iterator E = MI->getParent()->instr_end();

      TOYMCInstLower MCInstLowering(MI->getParent()->getParent()->getContext(), *this);
      do {
        MCInst TmpInst0;
        MCInstLowering.Lower(I++, TmpInst0);

        OutStreamer.EmitInstruction(TmpInst0);
      } while ((I != E) && I->isInsideBundle()); // Delay slot check
    }
    void printInstruction(const MachineInstr *MI, raw_ostream &OS);// autogen'd.
    static const char *getRegisterName(unsigned RegNo);

    bool PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
                         unsigned AsmVariant, const char *ExtraCode,
                         raw_ostream &O);
    bool PrintAsmMemoryOperand(const MachineInstr *MI, unsigned OpNo,
                               unsigned AsmVariant, const char *ExtraCode,
                               raw_ostream &O);

    bool printGetPCX(const MachineInstr *MI, unsigned OpNo, raw_ostream &OS);
    
    virtual bool isBlockOnlyReachableByFallthrough(const MachineBasicBlock *MBB) const;

    virtual MachineLocation getDebugValueLocation(const MachineInstr *MI) const;
  };
} // end of anonymous namespace

// #include "TOYGenAsmWriter.inc"

void TOYAsmPrinter::printOperand(const MachineInstr *MI, int opNum,
                                 raw_ostream &O) {
  llvm_unreachable("printOperand not implemented yet!\n");
}

void TOYAsmPrinter::printMemOperand(const MachineInstr *MI, int opNum,
                                    raw_ostream &O, const char *Modifier) {
  llvm_unreachable("printMemOperand not implemented yet!\n");
}

bool TOYAsmPrinter::printGetPCX(const MachineInstr *MI, unsigned opNum,
                                raw_ostream &O) {
  llvm_unreachable("printGetPCX not implemented yet!\n");
}

void TOYAsmPrinter::printCCOperand(const MachineInstr *MI, int opNum,
                                   raw_ostream &O) {
  llvm_unreachable("printCCOperand not implemented yet!\n");
}

/// PrintAsmOperand - Print out an operand for an inline asm expression.
///
bool TOYAsmPrinter::PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
                                    unsigned AsmVariant,
                                    const char *ExtraCode,
                                    raw_ostream &O) {
  llvm_unreachable("PrintAsmOperand not implemented yet!\n");
}

bool TOYAsmPrinter::PrintAsmMemoryOperand(const MachineInstr *MI,
                                          unsigned OpNo, unsigned AsmVariant,
                                          const char *ExtraCode,
                                          raw_ostream &O) {
  llvm_unreachable("PrintAsmMemoryOperand not implemented yet!\n");
}

/// isBlockOnlyReachableByFallthough - Return true if the basic block has
/// exactly one predecessor and the control transfer mechanism between
/// the predecessor and this block is a fall-through.
///
/// This overrides AsmPrinter's implementation to handle delay slots.
bool TOYAsmPrinter::
isBlockOnlyReachableByFallthrough(const MachineBasicBlock *MBB) const {
  llvm_unreachable("isBlockOnlyReachableByFallthrough not implemented yet!\n");
}

MachineLocation TOYAsmPrinter::
getDebugValueLocation(const MachineInstr *MI) const {
  llvm_unreachable("getDebugValueLocation not implemented yet!\n");
}

// Force static initialization.
extern "C" void LLVMInitializeTOYAsmPrinter() { 
  RegisterAsmPrinter<TOYAsmPrinter> X(TheTOYTarget);
}
