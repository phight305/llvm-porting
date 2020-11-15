//===-- TOYMCCodeEmitter.cpp - Convert TOY Code to Machine Code ---------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the TOYMCCodeEmitter class.
//
//===----------------------------------------------------------------------===//
//
#define DEBUG_TYPE "mccodeemitter"
#include "MCTargetDesc/TOYMCTargetDesc.h"
#include "MCTargetDesc/TOYFixupKinds.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
class TOYMCCodeEmitter : public MCCodeEmitter {
  TOYMCCodeEmitter(const TOYMCCodeEmitter &) LLVM_DELETED_FUNCTION;
  void operator=(const TOYMCCodeEmitter &) LLVM_DELETED_FUNCTION;
  const MCInstrInfo &MCII;
  bool IsLittleEndian;

public:
  TOYMCCodeEmitter(const MCInstrInfo &mcii, bool IsLittle) :
     MCII(mcii), IsLittleEndian(IsLittle) {}

  ~TOYMCCodeEmitter() {}

  void EmitByte(unsigned char C, raw_ostream &OS) const {
    OS << (char)C;
  }

  void EmitInstruction(uint64_t Val, unsigned Size, raw_ostream &OS) const {
    // TOY is little-edian
    for (unsigned i = 0; i < Size; ++i) {
      unsigned Shift = i * 8;
      EmitByte((Val >> Shift) & 0xff, OS);
    }
  }

  void EncodeInstruction(const MCInst &MI, raw_ostream &OS,
                         SmallVectorImpl<MCFixup> &Fixups) const;

  // getBinaryCodeForInstr - TableGen'erated function for getting the
  // binary encoding for an instruction.
  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups) const;

  // getBranchJumpOpValue - Return binary encoding of the jump
  // target operand. If the machine operand requires relocation,
  // record the relocation and return zero.
   unsigned getJumpTargetOpValue(const MCInst &MI, unsigned OpNo,
                                 SmallVectorImpl<MCFixup> &Fixups) const;

   // getBranchTargetOpValue - Return binary encoding of the branch
   // target operand. If the machine operand requires relocation,
   // record the relocation and return zero.
  unsigned getBranchTargetOpValue(const MCInst &MI, unsigned OpNo,
                                  SmallVectorImpl<MCFixup> &Fixups) const;

   // getMachineOpValue - Return binary encoding of operand. If the machin
   // operand requires relocation, record the relocation and return zero.
  unsigned getMachineOpValue(const MCInst &MI,const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups) const;

  unsigned getMemEncoding(const MCInst &MI, unsigned OpNo,
                          SmallVectorImpl<MCFixup> &Fixups) const;
  unsigned getSizeExtEncoding(const MCInst &MI, unsigned OpNo,
                              SmallVectorImpl<MCFixup> &Fixups) const;
  unsigned getSizeInsEncoding(const MCInst &MI, unsigned OpNo,
                              SmallVectorImpl<MCFixup> &Fixups) const;

}; // class TOYMCCodeEmitter
}  // namespace

MCCodeEmitter *llvm::createTOYMCCodeEmitter(const MCInstrInfo &MCII,
                                            const MCRegisterInfo &MRI,
                                            const MCSubtargetInfo &STI,
                                            MCContext &Ctx) {
  return new TOYMCCodeEmitter(MCII, true/*IsLittle*/);
}

/// EncodeInstruction - Emit the instruction.
/// Size the instruction (currently only 4 bytes
void TOYMCCodeEmitter::
EncodeInstruction(const MCInst &MI, raw_ostream &OS,
                  SmallVectorImpl<MCFixup> &Fixups) const {
  uint32_t Binary = getBinaryCodeForInstr(MI, Fixups);
  EmitInstruction(Binary, 4, OS);
}

/// getBranchTargetOpValue - Return binary encoding of the branch
/// target operand. If the machine operand requires relocation,
/// record the relocation and return zero.
unsigned TOYMCCodeEmitter::
getBranchTargetOpValue(const MCInst &MI, unsigned OpNo,
                       SmallVectorImpl<MCFixup> &Fixups) const {
  llvm_unreachable("getBranchTargetOpValue is not implemented yet");
}

/// getJumpTargetOpValue - Return binary encoding of the jump
/// target operand. If the machine operand requires relocation,
/// record the relocation and return zero.
unsigned TOYMCCodeEmitter::
getJumpTargetOpValue(const MCInst &MI, unsigned OpNo,
                     SmallVectorImpl<MCFixup> &Fixups) const {
  llvm_unreachable("getJumpTargetOpValue is not implemented yet");
}
/// getMachineOpValue - Return binary encoding of operand. If the machine
/// operand requires relocation, record the relocation and return zero.
unsigned TOYMCCodeEmitter::
getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                  SmallVectorImpl<MCFixup> &Fixups) const {
  if (MO.isReg()) {
    switch (MO.getReg()) {
    case TOY::R0:   return 0;
    case TOY::R1:   return 1;
    case TOY::R2:   return 2;
    case TOY::R3:   return 3;
    case TOY::ZERO: return 4;
    case TOY::SP:   return 5;
    case TOY::LR:   return 6;
    case TOY::TMP:  return 7;
    default: llvm_unreachable("Unable to encode MachineOperand!");
    }
  }
  else if (MO.isImm())
    return static_cast<unsigned>(MO.getImm());
  else if (MO.isExpr()) {
    const MCExpr *Expr = MO.getExpr();
    assert(Expr->getKind() == MCExpr::SymbolRef);

    TOY::Fixups FixupKind = TOY::Fixups(0);

    switch (cast<MCSymbolRefExpr>(Expr)->getKind()) {
    default: llvm_unreachable("Unknown fixup kind!");
    case MCSymbolRefExpr::VK_TOY_CALL:
      FixupKind = TOY::fixup_TOY_CALL;
      break;
    }
    Fixups.push_back(MCFixup::Create(0, MO.getExpr(), MCFixupKind(FixupKind)));
  }
  else
    llvm_unreachable("Unable to encode MachineOperand!");

  // All of the information is in the fixup.
  return 0;
}

/// getMemEncoding - Return binary encoding of memory related operand.
/// If the offset operand requires relocation, record the relocation.
unsigned
TOYMCCodeEmitter::getMemEncoding(const MCInst &MI, unsigned OpNo,
                                 SmallVectorImpl<MCFixup> &Fixups) const {
  assert(MI.getOperand(OpNo).isReg());
  unsigned RegBits = getMachineOpValue(MI, MI.getOperand(OpNo), Fixups);
  unsigned OffBits = getMachineOpValue(MI, MI.getOperand(OpNo+1), Fixups) << 4;

  return OffBits | (RegBits & 0xf);
}

unsigned
TOYMCCodeEmitter::getSizeExtEncoding(const MCInst &MI, unsigned OpNo,
                                     SmallVectorImpl<MCFixup> &Fixups) const {
  llvm_unreachable("getSizeExtEncoding is not implemented yet");
}

// FIXME: should be called getMSBEncoding
//
unsigned
TOYMCCodeEmitter::getSizeInsEncoding(const MCInst &MI, unsigned OpNo,
                                     SmallVectorImpl<MCFixup> &Fixups) const {
  llvm_unreachable("getSizeInsEncoding is not implemented yet");
}

#include "TOYGenMCCodeEmitter.inc"


