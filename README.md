# xconfig2

  A set of configuration persistence libraries that support registry, ini, XML and JSON formats



## Code EXample

```c++
XConfig cfg;
LoadConfig<IniStorage>("config.ini", cfg);  //load config from ini file

SaveConfig<XmlStorage>("config.xml", cfg);  //save config to xml file
```

