
int x = 5;

void hello();

int main()
{
    main:
    int x = 5;
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