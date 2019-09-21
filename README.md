    Working with SVG files

## Structure
The application is composed of several layers:

- **Xml** → contains classes representing XML (i.e. `Tag`, `Attribute`, …etc) and the class `Parser` which parses string and creates a
tree of `Tag` elements, preserving the structure and nesting of the SVG;
- **Core** → contains classes used to recreate the structure of an SVG file as an object (i.e. `DomElement`, `ScalableVectorGraphic`, …etc);
  - **Properties** → contains a class representation of basic properties (i.e. `Coordinate`, `Color`, `Length`, …etc); used to parse tag attribute values without loss of information (preserves the unit of the attribute);
  - **Regions** → contains classes representing circle and rectangle regions;
  - **Shapes** → contains classes representing currently supported SVG shapes `Rectangle`, `Circle` and `Line`;
  - **Utils** → contains utility classes (i.e. `FileHelper`, `SvgLoader`);
- **Engine** → introduces commands to the application; contains the classes `Engine`, `Command` and `CommandContext`;
  - **Commands** → contains concreate implementations of the `Command` class, i.e. `SaveCommand`, `PrintCommand`, `TranslateCommand`, …etc.

## List of available commands
### File-related commands:
`open <path>`  
opens the file with the specified path

`close`  
closes the file that is currently opened

`exit`  
exits the application

`save <path?>`  
writes the file to the specified path  
_if <path?> parameter is not provided - overwrites the original file_

### SVG-related commands:
`print`  
prints all supported svg shapes

`erase <id>`  
removes the shape with the specified id

`translate <id?> <horizontal> <vertical>`  
_if <id?> is provided - translates the shape with the specified id_  
_if <id?> is not provided - translates all shapes_

`create <shape>`  
creates a shape  
_supported shapes:_  
`rectangle <x> <y> <width> <height> <fill?>`  
`circle <cx> <cy> <r> <fill?>`  
`line <x1> <y1> <x2> <y2> <stroke?>`

`within <region>`  
prints shapes withing the specified region  
_supported regions:_  
`rectangle <x> <y> <width> <height>`  
`circle <cx> <cy> <radius>`

## Important classes
`ScalableVectorGraphic`  
`Engine`
