//===-- TOYISelLowering.h - TOY DAG Lowering Interface ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that Sparc uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#ifndef TOY_ISELLOWERING_H
#define TOY_ISELLOWERING_H

#include "TOY.h"
#include "llvm/Target/TargetLowering.h"

namespace llvm {

  namespace TOYISD {
    enum {
      FIRST_NUMBER = ISD::BUILTIN_OP_END,
      CALL,      // A call instruction.
      RET_FLAG   // A return instruction.
    };
  }

  class TOYTargetLowering : public TargetLowering {
  public:
    TOYTargetLowering(TargetMachine &TM);
    virtual SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const;

    virtual SDValue
      LowerFormalArguments(SDValue Chain,
                           CallingConv::ID CallConv,
                           bool isVarArg,
                           const SmallVectorImpl<ISD::InputArg> &Ins,
                           DebugLoc dl, SelectionDAG &DAG,
                           SmallVectorImpl<SDValue> &InVals) const;

    virtual SDValue
      LowerCall(TargetLowering::CallLoweringInfo &CLI,
                SmallVectorImpl<SDValue> &InVals) const;

    virtual SDValue
      LowerReturn(SDValue Chain,
                  CallingConv::ID CallConv, bool isVarArg,
                  const SmallVectorImpl<ISD::OutputArg> &Outs,
                  const SmallVectorImpl<SDValue> &OutVals,
                  DebugLoc dl, SelectionDAG &DAG) const;

    virtual const char *getTargetNodeName(unsigned Opcode) const;
  };
} // end namespace llvm

#endif // TOY_ISELLOWERING_H
