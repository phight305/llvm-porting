add_llvm_library(LLVMTOYDesc
  TOYMCTargetDesc.cpp
  TOYMCAsmInfo.cpp
  TOYAsmBackend.cpp
  TOYMCCodeEmitter.cpp
)
add_dependencies(LLVMTOYDesc TOYCommonTableGen)
