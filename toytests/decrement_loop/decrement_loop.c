int main()
{
    int *a = (int*)0x1234;
    int b = -20;
    int d = 50;
    for (int i = 0; i > b; i--) {
        d += 1;
    }
    *a = d;
}
