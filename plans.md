# Immolate2 Plans/Roadmap
This document serves to plan how I want to structure the development and final product of Immolate2.

## Philosophy
With Immolate, there is already a fully functional seed searcher available. However, it has heavy potential for optimization as shown by speed boosts in other projects. Immolate2 is a rebuild from the ground up that will prioritize speed over features while it is in development, so it can be highly optimized once complete.

## Planned Features
- **SIMD Support** - Using the builtin (immintrin) bindings for x86 SIMD, each CPU thread can search multiple seeds at once, resulting in up to an 8x speed improvement on some platforms. I'm not sure yet if I want the SIMD optimizations for each platform to be handled at runtime (like C#) or at compile time (like Stockfish)
- **Less Hardcoding** - Game objects will be loaded dynamically (such as from a file on startup), making it easier to adjust for game updates and add support for modded content. These objects will also contain information about more specific RNG pools/types (such as item-specific ones).
- **JSON Filters** - Currently all filters have to be written in code, and in C++ they need to be compiled. Supporting a JSON format for filters allows for most searches to be done in the browser or through a mod, rather than requiring a standalone program.
- **Modding Support** - Some system for searching for modded seeds. The best way to do this would probably be something that takes advantage of the dynamic game object system, exports that info from Balatro, and then enables some code changes for Steamodded and maybe some other large mods (like Cryptid). However those extensions would probably also ahve to be added at compile time for speed reasons.

## Release Formats
There are three release formats that Immolate currently uses, and Immolate2 should be compatible with all of them.
- **The Source Code**: By using the code itself as a library, people can compile their own filters directly, resulting in maximum performance.
- **WASM Bindings**: By compiling with [Emscripten](https://emscripten.org/) bindings, Immolate2 will also be usable in the browser, for applications such as [The Soul](https://mathisfun0.github.io/The-Soul/) and [Blueprint](https://miaklwalker.github.io/Blueprint/).
- **As a DLL**: Using some C bindings, Immolate2 will also be available as a DLL. Besides making standalone programs, it can also be used in Balatro mods like [Brainstorm](https://github.com/OceanRamen/Brainstorm).