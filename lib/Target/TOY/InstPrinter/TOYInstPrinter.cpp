//===-- TOYInstPrinter.cpp - Convert TOY MCInst to assembly syntax ------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints an TOY MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "asm-printer"
#include "TOYInstPrinter.h"
#include "TOYInstrInfo.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#include "TOYGenAsmWriter.inc"

void TOYInstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const {
  llvm_unreachable("printRegName not implemented yet");
}

void TOYInstPrinter::printInst(const MCInst *MI, raw_ostream &O,
                               StringRef Annot) {
  llvm_unreachable("printInst not implemented yet");
}

static void printExpr(const MCExpr *Expr, raw_ostream &OS) {
  llvm_unreachable("printExpr not implemented yet");
}

void TOYInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                  raw_ostream &O) {
  llvm_unreachable("printOperand not implemented yet");
}

void TOYInstPrinter::printUnsignedImm(const MCInst *MI, int opNum,
                                      raw_ostream &O) {
  llvm_unreachable("printUnsignedImm not implemented yet");
}

void TOYInstPrinter::
printMemOperand(const MCInst *MI, int opNum, raw_ostream &O) {
  llvm_unreachable("printMemOperand not implemented yet");
}

void TOYInstPrinter::
printMemOperandEA(const MCInst *MI, int opNum, raw_ostream &O) {
  llvm_unreachable("printMemOperandEA not implemented yet");
}

void TOYInstPrinter::
printFCCOperand(const MCInst *MI, int opNum, raw_ostream &O) {
  llvm_unreachable("printFCCOperand not implemented yet");
}
