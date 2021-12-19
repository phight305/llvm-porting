int main()
{
    int *a = (int*)0x1234;
    int b = 20;
    int c = 30;
    for (int i = 0; i < b; i++) {
        c += 1;
    }
    *a = c;
}
