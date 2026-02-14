# Loader library

Library is in charge of loading all game files from the disk and making them available to the rest of the program.  Resources can be thought of as class templates.  They are immutable and can last the program lifespan, but need to be instantiated.

All resources are distinguishable by a unique (in their category) name.
Resource files are found in their respective folders:
- images for all files to be loaded as images/textures
- items for all files describing items in the game
- entities for all files describing mobs/units in the game
- components for all files describing generated structures (dungeon components)

Malformed or misplaced files will cause errors on game loading

## File Format
Items, entities, and components are in a special text file format for easy parsing.  Each line in this file is a key-value+ pair where each key can map to one or more values (depending on the key).  The format is simple:

```key:value```\
```key:value1:value2```

More information on expected keys and values can be found in `forge.hh`

## Code Format
- `loader.cc` orchestrates the loading from a high level.  Designed to operate as an independent thread with a monitoring front-end.  Caller is responsible for ensuring that loader has finished before advancing to the rest of the program.  Caller is responsible for verifying that the loader has not produced an error.
- `parser.cc` converts reads resource files to produce a map of key-value attributes
- `forge.cc` reads and checks attribute maps to build resources
- `resources.hh` (and others) describe the format of resources, including their component fields
- `forge.hh` describes the keys and values expected in the forging process