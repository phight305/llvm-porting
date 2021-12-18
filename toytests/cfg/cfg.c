int main()
{
    int *a = (int*)0x1234;
    int b = 20;
    int c = 30;
    if (b < c)
        *a = 5;
    else
        *a = 6;
}
