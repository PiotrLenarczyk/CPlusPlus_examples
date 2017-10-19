int main ( void )
{
    for (;;)
    {
        char  line[80]; line[79] = '#';
        int   len;

        len = 80;
        if (len > 0)
        {
            for (int i = 0;  i < len;  i++)
            {
                int   ch;
                ch = line[i];
                if (ch == '#')
                    goto endFor;   // multiple nested loops / conditions "jump end" for clarity
            }
        }
        else
            return 0;
    }
    endFor:;

    return 0;
}
