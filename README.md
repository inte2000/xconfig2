# xconfig2

  A set of configuration persistence libraries that support windows registry, ini, XML and JSON formats



## Code Example

```c++
XConfig cfg;
LoadConfig<IniStorage>("config.ini", cfg);  //load config from ini file

SaveConfig<XmlStorage>("config.xml", cfg);  //save config to xml file
```

xconfig2 now support ini,xml,json,registry (windows) storage format.

## Compile

### Windows

The "msvc" folder contains the visual studio 2019 project files that compile xconfig2.

### linux

On going...

## Dependency Library

- [boost](https://www.boost.org/)
- [libIconv](http://www.gnu.org/software/*libiconv*/)
- [rapidjson](http://rapidjson.org)
- [rapidxml](http://rapidxml.sourceforge.net/)

