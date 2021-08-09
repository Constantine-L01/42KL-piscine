# ft_atoi.c

```c
int ft_atoi(char* str)
{
    int i = 0;
    int sign = 1;
    int ret = 0;

    while('\t' <= str[i] && str[i] <= '\r' || str[i] == ' '){
        i++;
    }

    while(str[i] == '+' || str[i] == '-'){
        if(str[i] == '-'){
            sign *= -1;
        }
        i++;
    }

    while('0' <= str[i] && str[i] <= '9'){
        ret = ret * 10 + (str[i] - '0');
        i++;
    }

    return sign * ret;
}
```
