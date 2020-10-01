add_llvm_library(LLVMTOYDesc
  TOYMCTargetDesc.cpp
  TOYMCAsmInfo.cpp
  TOYAsmBackend.cpp
)
add_dependencies(LLVMTOYDesc TOYCommonTableGen)
