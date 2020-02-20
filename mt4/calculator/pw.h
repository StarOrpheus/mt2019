#pragma once

static inline int pw(int x, int y)
{
    if (y == 0)
        return 1;
    if (y == 1)
        return x;

    return (y % 2 == 0) ? pw(x * x, y / 2) : pw(x * x, y / 2) * x;
}
