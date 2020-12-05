# Component

This is a directory for components which can be omitted if not used.

1. Every file must have include guard (`#pragma once`)

2. Every component should have two files - `{component}_header.h` (declaration) and `{component}.h` (definition)

3. Definition file must include `{component}_header.h`

4. Make sure that components can be omitted safely (project can successfully compile)
