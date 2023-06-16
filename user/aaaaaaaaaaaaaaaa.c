void readline(char *buf, u_int n)
{
    int i, r;
    int repeat;
    int isHistoryCmd = 0;
    r = 0;
    for (i = 0; i < n; i++)
    {
        if ((r = read(0, buf + i, 1)) != 1)
        {
            if (r < 0)
                writef("read error: %e", r);
            exit();
        }
        if (buf[i] == '\x7f')
        { //<----
            if (i == 0)
            {
                i--;
                continue;
            }
            i -= 2;
            fwritef(1, "\x1b[1D\x1b[K"); // back one
        }
        // writef("%c\n",*(buf+i));
        // writef("%c\n",*(buf+i));
        if (buf[i] == '\x1b')
        {
            repeat = 0;
            i++;
            if ((r = read(0, buf + i, 1)) != 1)
            {
                if (r < 0)
                    writef("read error: %e", r);
                exit();
            }
            if (buf[i] != '[')
            {
                writef("read error: %e", r);
                exit();
            }
            i++;
            if ((r = read(0, buf + i, 1)) != 1)
            {
                if (r < 0)
                    writef("read error: %e", r);
                exit();
            }
            if (buf[i] == 'A')
            {
                fwritef(1, "\x1b[1B\x1b[2K");
                //	fwritef(1, "\x1b[1B\x1b[%dD\x1b[K", i);
                getHistoryCommand(buf, 0, 1, &repeat);
                fwritef(1, "%s", buf);
            }
            else if (buf[i] == 'B')
            {
                //	fwritef(1, "\x1b[1A\x1b[2K");
                fwritef(1, "\x1b[%dD\x1b[K", i);
                getHistoryCommand(buf, 0, 0, &repeat);
                fwritef(1, "%s", buf);
            }
            i = strlen(buf) - 1;
        }
        if (buf[i] == '\b')
        {
            if (i > 0)
                i -= 2;
            else
                i = 0;
        }
        if (buf[i] == '\r' || buf[i] == '\n')
        {
            buf[i] = 0;
            getHistoryCommand(buf, 0, -1, &repeat);
            if (!repeat)
                saveCommandToHistory(buf);
            return;
        }
    }
    writef("line too long\n");
    while ((r = read(0, buf, 1)) == 1 && buf[0] != '\n')
        ;
    buf[0] = 0;
}
