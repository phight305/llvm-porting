//===-- TOYISelLowering.cpp - TOY DAG Lowering Implementation ---------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the interfaces that Sparc uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"

#include "TOYISelLowering.h"
#include "TOYTargetMachine.h"
#include "llvm/DerivedTypes.h"
#include "llvm/Function.h"
#include "llvm/Module.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/Support/ErrorHandling.h"
using namespace llvm;


//===----------------------------------------------------------------------===//
// Calling Convention Implementation
//===----------------------------------------------------------------------===//
// #include "TOYGenCallingConv.inc"

SDValue
TOYTargetLowering::LowerReturn(SDValue Chain,
                               CallingConv::ID CallConv, bool isVarArg,
                               const SmallVectorImpl<ISD::OutputArg> &Outs,
                               const SmallVectorImpl<SDValue> &OutVals,
                               DebugLoc dl, SelectionDAG &DAG) const {
  llvm_unreachable("LowerReturn has not benn implemented yet");
}

SDValue
TOYTargetLowering::LowerFormalArguments(SDValue Chain,
                                        CallingConv::ID CallConv, bool isVarArg,
                                        const SmallVectorImpl<ISD::InputArg> &Ins,
                                        DebugLoc dl, SelectionDAG &DAG,
                                        SmallVectorImpl<SDValue> &InVals) const {
  llvm_unreachable("LowerFormalArguments has not benn implemented yet");
}

SDValue
TOYTargetLowering::LowerCall(TargetLowering::CallLoweringInfo &CLI,
                             SmallVectorImpl<SDValue> &InVals) const {
  llvm_unreachable("LowerCall has not benn implemented yet");
}

//===----------------------------------------------------------------------===//
// TargetLowering Implementation
//===----------------------------------------------------------------------===//

TOYTargetLowering::TOYTargetLowering(TargetMachine &TM)
  : TargetLowering(TM, new TargetLoweringObjectFileELF()) {
  // Set up the register classes.
}


SDValue TOYTargetLowering::
LowerOperation(SDValue Op, SelectionDAG &DAG) const {
  llvm_unreachable("LowerOperation has not benn implemented yet");
}
