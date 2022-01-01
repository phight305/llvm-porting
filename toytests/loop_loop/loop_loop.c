int main()
{
    int *a = (int*)0x1234;
    int b = 20;
    int c = 30;
    int d = 50;
    for (int i = 0; i < b; i++) {
        for (int j = 0; j < c; j++) {
            d += 1;
        }
    }
    *a = d;
}
