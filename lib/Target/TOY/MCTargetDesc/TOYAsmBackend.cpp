//===-- TOYASMBackend.cpp - TOY Asm Backend  ----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the TOYAsmBackend and TOYELFObjectWriter classes.
//
//===----------------------------------------------------------------------===//
//

#include "MCTargetDesc/TOYMCTargetDesc.h"
#include "MCTargetDesc/TOYFixupKinds.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// Prepare value for the target space for it
static unsigned adjustFixupValue(unsigned Kind, uint64_t Value) {
  llvm_unreachable("adjustFixupValue is not implemented yet");
}

namespace {
class TOYAsmBackend : public MCAsmBackend {

  Triple::OSType OSType;
  bool IsLittle;
  bool Is64Bit;

public:
  TOYAsmBackend(const Target &T, Triple::OSType _OSType, bool _isLittle, bool _is64Bit)
    :MCAsmBackend(), OSType(_OSType), IsLittle(_isLittle), Is64Bit(_is64Bit) {}

  MCObjectWriter *createObjectWriter(raw_ostream &OS) const {
    return createTOYELFObjectWriter(OS,
      MCELFObjectTargetWriter::getOSABI(OSType), IsLittle, Is64Bit);
  }

  /// ApplyFixup - Apply the \p Value for given \p Fixup into the provided
  /// data fragment, at the offset specified by the fixup and following the
  /// fixup kind as appropriate.
  void applyFixup(const MCFixup &Fixup, char *Data, unsigned DataSize,
                  uint64_t Value) const {
    unsigned Offset = Fixup.getOffset();
    MCFixupKind Kind = Fixup.getKind();
    unsigned NumBytes = (getFixupKindInfo(Kind).TargetSize + 7) / 8;

    // Write out the fixed up bytes back to the code/data bits.
    for (unsigned i = 0; i != NumBytes; ++i) {
      Data[Offset + i] = (uint8_t)((Value >> (i*8)) & 0xff);
    }
  }

  unsigned getNumFixupKinds() const {
    return TOY::NumTargetFixupKinds;
  }

  const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const {
    const static MCFixupKindInfo Infos[TOY::NumTargetFixupKinds] = {
      // This table *must* be in same the order of fixup_* kinds in
      // TOYFixupKinds.h.
      //
      // name             offset bits flags
      { "fixup_TOY_CALL", 0,     16,  MCFixupKindInfo::FKF_IsPCRel },
      { "fixup_TOY_BR",   0,     16,  MCFixupKindInfo::FKF_IsPCRel },
    };

    if (Kind < FirstTargetFixupKind)
      return MCAsmBackend::getFixupKindInfo(Kind);

    assert(unsigned(Kind - FirstTargetFixupKind) < getNumFixupKinds() &&
           "Invalid kind!");
    return Infos[Kind - FirstTargetFixupKind];
  }

  void processFixupValue(const MCAssembler &Asm,
                         const MCAsmLayout &Layout,
			 const MCFixup &Fixup,
			 const MCFragment *DF,
			 MCValue &Target, uint64_t &Value,
			 bool &IsResolved) {
    switch (Fixup.getKind()) {
    case TOY::fixup_TOY_CALL:
    case TOY::fixup_TOY_BR: {
        if (Value != 0) { // The symbol is defined in the same section
          IsResolved = true;
        }
    }
    break;
    }
  }

  /// @name Target Relaxation Interfaces
  /// @{

  /// MayNeedRelaxation - Check whether the given instruction may need
  /// relaxation.
  ///
  /// \param Inst - The instruction to test.
  bool mayNeedRelaxation(const MCInst &Inst) const {
    return false;
  }

  /// fixupNeedsRelaxation - Target specific predicate for whether a given
  /// fixup requires the associated instruction to be relaxed.
  bool fixupNeedsRelaxation(const MCFixup &Fixup,
                            uint64_t Value,
                            const MCInstFragment *DF,
                            const MCAsmLayout &Layout) const {
    llvm_unreachable("RelaxInstruction() is not implemented yet");
  }

  /// RelaxInstruction - Relax the instruction in the given fragment
  /// to the next wider instruction.
  ///
  /// \param Inst - The instruction to relax, which may be the same
  /// as the output.
  /// \param [out] Res On return, the relaxed instruction.
  void relaxInstruction(const MCInst &Inst, MCInst &Res) const {
    llvm_unreachable("relaxInstruction is not implemented yet");
  }

  /// @}

  /// WriteNopData - Write an (optimal) nop sequence of Count bytes
  /// to the given output. If the target cannot generate such a sequence,
  /// it should return an error.
  ///
  /// \return - True on success.
  bool writeNopData(uint64_t Count, MCObjectWriter *OW) const {
    // All instructions are 32 bits, so it is not required to insert nop to do alignment
    return true;
  }
}; // class TOYAsmBackend

} // namespace

// MCAsmBackend
MCAsmBackend *llvm::createTOYAsmBackend(const Target &T, StringRef TT,
                                        StringRef CPU) {
  return new TOYAsmBackend(T, Triple(TT).getOS(), /*IsLittle*/true, /*Is64Bit*/false);
}
