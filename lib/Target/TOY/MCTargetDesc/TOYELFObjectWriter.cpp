//===-- TOYELFObjectWriter.cpp - TOY ELF Writer -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/TOYMCTargetDesc.h"
#include "MCTargetDesc/TOYFixupKinds.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSection.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ErrorHandling.h"
#include <list>

using namespace llvm;

namespace {

  class TOYELFObjectWriter : public MCELFObjectTargetWriter {
  public:
    TOYELFObjectWriter(bool _is64Bit, uint8_t OSABI,
                       bool _isN64, bool IsLittleEndian);

    virtual ~TOYELFObjectWriter();

    virtual unsigned GetRelocType(const MCValue &Target, const MCFixup &Fixup,
                                  bool IsPCRel, bool IsRelocWithSymbol,
                                  int64_t Addend) const;
    virtual unsigned getEFlags() const;
    virtual const MCSymbol *ExplicitRelSym(const MCAssembler &Asm,
                                           const MCValue &Target,
                                           const MCFragment &F,
                                           const MCFixup &Fixup,
                                           bool IsPCRel) const;
    virtual void sortRelocs(const MCAssembler &Asm,
                            std::vector<ELFRelocationEntry> &Relocs);
  };
}

TOYELFObjectWriter::TOYELFObjectWriter(bool _is64Bit, uint8_t OSABI,
                                       bool _isN64, bool IsLittleEndian)
  : MCELFObjectTargetWriter(_is64Bit, OSABI, ELF::EM_TOY,
                            /*HasRelocationAddend*/ (_isN64) ? true : false,
                            /*IsN64*/ _isN64) {}

TOYELFObjectWriter::~TOYELFObjectWriter() {}

// FIXME: get the real EABI Version from the Subtarget class.
unsigned TOYELFObjectWriter::getEFlags() const {
  return ELF::EF_TOY_ARCH;
}

const MCSymbol *TOYELFObjectWriter::ExplicitRelSym(const MCAssembler &Asm,
                                                   const MCValue &Target,
                                                   const MCFragment &F,
                                                   const MCFixup &Fixup,
                                                   bool IsPCRel) const {
  llvm_unreachable("ExplicitRelSym is not implemented yet");
}

unsigned TOYELFObjectWriter::GetRelocType(const MCValue &Target,
                                          const MCFixup &Fixup,
                                          bool IsPCRel,
                                          bool IsRelocWithSymbol,
                                          int64_t Addend) const {
  // determine the type of the relocation
  unsigned Type = (unsigned)ELF::R_TOY_NONE;
  unsigned Kind = (unsigned)Fixup.getKind();

  switch (Kind) {
  default:
    llvm_unreachable("invalid fixup kind!");
  case TOY::fixup_TOY_CALL:
    Type = ELF::R_TOY_CALL;
    break;
  }
  return Type;
}

void TOYELFObjectWriter::sortRelocs(const MCAssembler &Asm,
                                    std::vector<ELFRelocationEntry> &Relocs) {
  llvm_unreachable("sortRelocs is not implemented yet");
}

MCObjectWriter *llvm::createTOYELFObjectWriter(raw_ostream &OS,
                                               uint8_t OSABI,
                                               bool IsLittleEndian,
                                               bool Is64Bit) {
  MCELFObjectTargetWriter *MOTW = new TOYELFObjectWriter(Is64Bit, OSABI,
                                                         (Is64Bit) ? true : false,
                                                         IsLittleEndian);
  return createELFObjectWriter(MOTW, OS, IsLittleEndian);
}

