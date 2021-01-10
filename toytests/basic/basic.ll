target triple = "toy"

define i32 @main() nounwind uwtable {
entry:
  %a = alloca i32*, align 8
  store i32* inttoptr (i64 4660 to i32*), i32** %a, align 8
  %0 = load i32** %a, align 8
  store i32 5, i32* %0, align 4
  ret i32 0
}
