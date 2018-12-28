package com.github.barismeral.ports;

/**
 * @author Barış Meral
 * @see java.lang.Enum
 * @version 1.0.0
 * @since 2018.12.28
 */

/**
 * Parity Enum
 */
public enum Parity {
    NONE(0),
    ODD(1),
    EVEN(2),
    MARK(3),
    SPACE(4);

int value;

    Parity(int i) {

        value = i;
    }
}
