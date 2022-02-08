# Yubikey code decoder

Simple command line tool to breakdown a yubikey output into some useful information in hexadecimal format.

Information contained in yubicode:

* Key ID - 48 bits
* OTP
  * Private ID - 48 bits
  * Usage Counter - 16 bits
  * Timestamp - 24 bits
  * Session usage counter - 8 bits
  * Random number - 16 bits
  * Checksum - 16 bits

## Build

Using `Makefile` run the command `make`, or `make run`.

This will generate a binary named `yubicode-dec`.

If you want to only generate the tool, run `make compile`.

## Recommended usage

Pairing with command pipe. E.g. `echo <my_secret_code> | yubicode-dec`

When running with no pipe, depending on the setup, some yubikeys don't introduce a new line character, the tool still works but you need to introduce the new line character by pressing enter.