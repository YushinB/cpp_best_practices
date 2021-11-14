# C++ Idiom.
## Move semantic
The key idea of move semantic is quite simple: use cheap move operations instead of expensive copy operations for big objects.
The different between Copy and move semantic is move semantic move the rerource element from one to another instead copy all resource data. 
* Copy semantic. 
```cpp
std::string1("ABCDEF");
std::string str2;
str2 = str1;
std::cout << "str1 = " << str1 << std::endl;
std::cout << "str2 = " << str2 << std::endl;
```
output.
```
ABCDEF
ABCDEF
```
![image](https://user-images.githubusercontent.com/34083808/141681550-2d922820-b01b-4d7d-9045-4ce82a2f47e8.png)

* Move semantic. 

```cpp
std::string1("ABCDEF");
std::string str3;
str3 = std::move(str1);
std::cout << "str1 = " << str1 << std::endl;
std::cout << "str2 = " << str2 << std::endl;
```
output.
```

ABCDEF
```
![image](https://user-images.githubusercontent.com/34083808/141681677-cf5b1c02-dddb-43ac-8ebe-4d11dab4f55d.png)

