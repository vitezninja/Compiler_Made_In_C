#include "utils/bitset.h"

void bitset64_set(Bitset64 *bs, int pos)
{
    if (!bs)
    {
        DEBUG_PRINT("bitset64_set: bitset is NULL\n");
        return;
    }

    if (pos < 0 || pos >= 64)
    {
        DEBUG_PRINT("bitset64_set: position %d out of range [0..63]\n", pos);
        return;
    }

    bs->bits |= (1ULL << pos);
}

void bitset64_clear(Bitset64 *bs, int pos)
{
    if (!bs)
    {
        DEBUG_PRINT("bitset64_clear: bitset is NULL\n");
        return;
    }

    if (pos < 0 || pos >= 64)
    {
        DEBUG_PRINT("bitset64_clear: position %d out of range [0..63]\n", pos);
        return;
    }

    bs->bits &= ~(1ULL << pos);
}

void bitset64_toggle(Bitset64 *bs, int pos)
{
    if (!bs)
    {
        DEBUG_PRINT("bitset64_toggle: bitset is NULL\n");
        return;
    }

    if (pos < 0 || pos >= 64)
    {
        DEBUG_PRINT("bitset64_toggle: position %d out of range [0..63]\n", pos);
        return;
    }

    bs->bits ^= (1ULL << pos);
}

bool bitset64_test(const Bitset64 *bs, int pos)
{
    if (!bs)
    {
        DEBUG_PRINT("bitset64_test: bitset is NULL\n");
        return false;
    }

    if (pos < 0 || pos >= 64)
    {
        DEBUG_PRINT("bitset64_test: position %d out of range [0..63]\n", pos);
        return false;
    }

    return (bs->bits & (1ULL << pos)) != 0;
}

bool bitset64_isEmpty(const Bitset64 *bs)
{
    if (!bs)
    {
        DEBUG_PRINT("bitset64_isEmpty: bitset is NULL\n");
        return true;
    }

    return bs->bits == 0;
}

void bitset64_print(const Bitset64 *bs)
{
    if (!bs)
    {
        DEBUG_PRINT("bitset64_print: bitset is NULL\n");
        return;
    }

    printf("Bitset64 {\n");
    printf("    bits: ");
    for (int i = 63; i >= 0; i--)
    {
        printf("%d", bitset64_test(bs, i));
        if (i % 8 == 0) printf(" ");
    }
    
    printf("\n}\n");
}