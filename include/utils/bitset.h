/**
 * @file bitset.h
 * @brief Header file for a fixed-size bitset implementation.
 * 
 * This file defines the Bitset64 structure and functions for manipulating a bitset
 * of 64 bits. Each bit can be set, cleared, toggled, or tested, allowing for efficient
 * storage and manipulation of flags or binary states.
 */

#ifndef BITSET_H
#define BITSET_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

// Forward declaration of the Bitset64 structure
typedef struct Bitset64 Bitset64;

#include "utils/logger.h"

/**
 * @struct Bitset64
 * @brief A fixed-size bitset storing up to 64 bits in a 64-bit unsigned integer.
 */
struct Bitset64
{
    uint64_t bits; /** Storage for bits; each bit represents one flag (0 or 1). */
};

/**
 * @brief Sets the bit at the specified position to 1.
 * 
 * @param bs Pointer to the Bitset64 instance.
 * @param pos Bit position to set (0 to 63).
 */
void bitset64_set(Bitset64 *bs, int pos);

/**
 * @brief Clears the bit at the specified position to 0.
 * 
 * @param bs Pointer to the Bitset64 instance.
 * @param pos Bit position to clear (0 to 63).
 */
void bitset64_clear(Bitset64 *bs, int pos);

/**
 * @brief Toggles the bit at the specified position.
 * 
 * Toggles means if the bit was 1, it becomes 0; if it was 0, it becomes 1.
 * 
 * @param bs Pointer to the Bitset64 instance.
 * @param pos Bit position to toggle (0 to 63).
 */
void bitset64_toggle(Bitset64 *bs, int pos);

/**
 * @brief Tests whether the bit at the specified position is set.
 * 
 * @param bs Pointer to the Bitset64 instance.
 * @param pos Bit position to test (0 to 63).
 * @return true if the bit is set (1), false otherwise or if bs is NULL or pos out of range.
 */
bool bitset64_test(const Bitset64 *bs, int pos);

/**
 * @brief Checks if the bitset is empty (all bits are 0).
 * 
 * @param bs Pointer to the Bitset64 instance.
 * @return true if all bits are 0, false otherwise.
 */
bool bitset64_isEmpty(const Bitset64 *bs);

/**
 * @brief Prints the bitset to stdout as a sequence of 64 bits.
 * 
 * Bits are printed from the most significant bit (bit 63) to the least significant bit (bit 0),
 * grouped by 8 bits separated by spaces for readability.
 * 
 * @param bs Pointer to the Bitset64 instance.
 */
void bitset64_print(const Bitset64 *bs);

#endif // BITSET_H