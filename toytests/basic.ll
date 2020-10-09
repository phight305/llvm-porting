target triple = "toy"

define i32 @basic(i32 %m, i32 %n, i32 %p, i32 %q) nounwind uwtable {
entry:
  %m.addr = alloca i32, align 4
  %n.addr = alloca i32, align 4
  %p.addr = alloca i32, align 4
  %q.addr = alloca i32, align 4
  store i32 %m, i32* %m.addr, align 4
  store i32 %n, i32* %n.addr, align 4
  store i32 %p, i32* %p.addr, align 4
  store i32 %q, i32* %p.addr, align 4
  ret i32 %m
}
