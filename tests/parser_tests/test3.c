
int x = 5;

void hello();

int main()
{
    int x = 5;
    main:
    x = 2;
    return 0;
}

void hello()
{
    for(;;)
    {
        if (1)
        {
            break;
        }
        else if (2)
        {
            goto main;
        }
    }
}