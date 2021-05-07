# Class

This is a directory for low-level class types and its methods.

1. Every file must have include guard (`#pragma once`)

2. Every class should have two files - `{class}_header.h` (declaration) and `{class}.h` (definition)

3. Declaration file should not include anything but `_meta.h` header file

4. Declaration file can contain short (inlinable) definitions

5. Definition file must include `{class}_header.h`
