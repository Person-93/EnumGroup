# EnumGroup
The goal of this project is to make a group of enum-like objects that can be used interchangeably.

If you want to make an enum for the days of the week, you might do something like this:
```c++
enum class Days {SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY}
```

This works pretty well for most cases, but what happens if you have some function that can only take workdays or only weekends?

This is what this project aims to solve.

To declare the enum-like classes you can use the following code
```c++
#include "EnumGroup.h"
ENUM_GROUP_START( Days )
    ADD_ENUM( Workdays, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY )
    ADD_ENUM( Weekend, SATURDAY, SUNDAY )
ENUM_GROUP_END()
```

The include statement includes the macro definitions. It also includes the class `EnumGroup::Item`.  
This class does not do anything by itself, but all of the Enum classes will extend from it.

The `ENUM_GROUP_START` and `ENUM_GROUP_END` macros are necessary to start and end the macro.  
All of the Enums must be in between these two macros and
 <b>THERE SHOULD BE NO OTHER CODE IN BETWEEN THOSE TWO CALLS</b>.

IMPORTANT NOTE: The generated classes are not actually enums. If you use the stl type traits to see if it is an enum, it will say that it is not.  
Instead, you should check if it extends `EnumGroup::Item`.

## Dependencies
This project depends on cmake and Boost.  
Boost used to generate human readable type names for the error messages.  
In the future, I plan to make this optional.  
If the option is off, the error messages will be compiler-specific and might be indecipherable.

When you run cmake for the first time, it will download boost for you. Make sure to include the boost headers when
linking into your project.  
If you don't want to run cmake, just install boost on your machine yourself.

Boost is also necessary to run the test cases, but you don't need to do that unless you plan on making changes to this project.  

## Details
#### Outer Namespace 
This will add the namespace `Days`. This namespace will contain:
* Item: A class called `Item`
* Inner Namespaces: A namespace for each enum group. In our example that will be `Weekdays` and `Weekend`
* Constants: A constant of type `Item` for every member of every enum. In our example, that will be seven constants: once for each day of the week. 
* Exception: A class `Days::Error` which extends `std::runtime_error`.

##### Item
Variables of this type can be assigned any value from any of the enum groups.

##### Inner Namespaces
The inner namespaces (`Weekdays` and `Weekend`) will have a constant of type `GroupName::EnumName::Item` for each member of the enum.   
In our example that would be `Days::Weekdays::Item` and `Days::Weekend::Item` respectively.

The inner namespaces (`Weekdays` and `Weekend`) contain:
* Item: A class called `Item`. Note that this is not the same class as the `Item` class in the outer namespace. 
* Constants: A constant of type `Item` for every member of the enum.  
 In our example, the `Weedays` namespace will have a constant for each day Mon-Fri, and the `Weekend` constant will have one for Saturday and one for Sunday.  

##### Constants
There will be a constant reference to every constant that is declared in every inner namespace.

This means that you can each constant can be accessed in two ways:
```c++
bool isEqual = Days::SUNDAY == Days::Weekend::SUNDAY; // true
```

This will help if you want to use IntelliSense for places that accept all variables and for places that accept only a specific enum.

##### Exception
There will be class `Days::Error` which extends `std::runtime_error`.
This exception will be thrown in the following circumstances:
```c++
Days::Weekend::Item weekend = Days::MONDAY; // this will throw because MONDAY is not in the Weekend enum
Days::Item item = Days::MONDAY; // this is perfectly fine. Included becuase it's used in the next line
Days::Weekend::Item weekend1 = item; // this will also throw
```