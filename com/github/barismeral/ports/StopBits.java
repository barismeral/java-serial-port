package com.github.barismeral.ports;



/**
 * @author Barış Meral
 * @see java.lang.Enum
 * @version 1.0.0
 * @since 2018.12.28
 *
 * Stop Bits Enum
 */
public enum StopBits {
    NONE(0),
    ONE(1),
    TWO(2);

    int value;

    StopBits(int i) {

        value =i;
    }
}
