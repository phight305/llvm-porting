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
    llvm_unreachable("applyFixup is not implemented yet");
  }

  unsigned getNumFixupKinds() const {
    llvm_unreachable("getNumFixupKinds is not implemented yet");
  }

  const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const {
    llvm_unreachable("getFixupKindInfo is not implemented yet");
  }

  /// @name Target Relaxation Interfaces
  /// @{

  /// MayNeedRelaxation - Check whether the given instruction may need
  /// relaxation.
  ///
  /// \param Inst - The instruction to test.
  bool mayNeedRelaxation(const MCInst &Inst) const {
    llvm_unreachable("mayNeedRelaxation is not implemented yet");
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
    llvm_unreachable("writeNopData is not implemented yet");
  }
}; // class TOYAsmBackend

} // namespace

// MCAsmBackend
MCAsmBackend *llvm::createTOYAsmBackend(const Target &T, StringRef TT,
                                        StringRef CPU) {
  return new TOYAsmBackend(T, Triple(TT).getOS(), /*IsLittle*/true, /*Is64Bit*/false);
}
