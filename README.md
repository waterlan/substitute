# Substitute

Regex string replacement tool.

## Description

Substitute is a regex string replacement tool for text files.
It is handy for doing multiple replacements on multiple files
in one go.

* Multiple files
* Multiple replacements
* Regular expressions
* Creates backup files
* Verbose option
* Can show differences on modified files

## Changes

[ChangeLog](ChangeLog.txt)

## Usage

```text
./S [options] 'replacement1' for 'pattern1' ['replacement..' for 'pattern..'].. in filename_list
   options:
   -v    : verbose, report also when nothing is matched
   -diff : do a diff on modified files
   -i    : ignore case
```

## WWW

[Substitute on GitHub](https://github.com/waterlan/substitute)

## Authors

Ondrej Popp

Erwin Waterlander <waterlan@xs4all.nl>

## Copyright

The Substitute package is distributed under GNU GPL V2 license.
See [COPYING](COPYING.txt)
