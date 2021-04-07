bool isLrgel(char operation[])
{
    int num = 0;
    for(int i =0;num>= 0 && operation[i] != '';i++)
    {
        if(operation[i]=='I')
            num++;
        if(operation[i]=='O')
            num--;
    }
    if(num == 0)
        return true;
    else
        return false;
}
