; ModuleID = 'loop.c'
target triple = "toy"

define i32 @main() nounwind uwtable {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32*, align 8
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %retval
  store i32* inttoptr (i64 4660 to i32*), i32** %a, align 8
  store i32 20, i32* %b, align 4
  store i32 30, i32* %c, align 4
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32* %i, align 4
  %1 = load i32* %b, align 4
  %cmp = icmp slt i32 %0, %1
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %2 = load i32* %c, align 4
  %add = add nsw i32 %2, 1
  store i32 %add, i32* %c, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %3 = load i32* %i, align 4
  %inc = add nsw i32 %3, 1
  store i32 %inc, i32* %i, align 4
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %4 = load i32* %c, align 4
  %5 = load i32** %a, align 8
  store i32 %4, i32* %5, align 4
  %6 = load i32* %retval
  ret i32 %6
}
