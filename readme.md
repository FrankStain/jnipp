Jni++
============

**Jni++** is designed to be used in projects for Android OS.

**Jni++** shows how the JNI could looks like if it was written using C++11.

The distinctive feature of **Jni++** is delegation of mostly all service code from the library's user to metaprogramming and automatic code generation. 


Difference between JNI and **Jni++**
------------

The JNI library is designed in the that way, so while using it you have to put up with next inconveniences:
* For proper initialization of `JNINativeMethod` you have to declare three arguments, while the second one (`const char* signature`) really just duplicates the declaration of third one (`void* fnPtr`) in a in strange manner.
* The user of JNI must manually control the lifetime of Java Environment (`JNIEnv` instances) for each of native threads the user prefer to use JNI. This fact implicitly forces the C++ developers to abandon the native threads and use only Java threads. This is a huge disadvantage of JNI.
* The translation of plain types between Java and C++ type-spaces is mostly trivial and can be done by compiler. But the JNI user always have to make type translation manually.
* The string value accessors are designed in C-style, what is unsafe for C++.
* In order to get the id of field (static or dynamic), the user have to make duplication of field description, especially the type of field. The second declaration of field type is the string signature in strange manner.
* In order to get the id of method (static or dynamic), the user have to make duplication of function signature in strange manner too.

It obvious that most of duplications are widely distributed, what is the source very different bugs.
Also while solving the problem, the user have to write a lot of servicing JNI code mixed with code of problem solution. It makes difficult to reading the code and debugging process. It makes practically impossible the solution of non-trivial tasks.

The overall impression from JNI is like it designed to indirectly cause the low-level developers to resort the solving their problems using Java rather than using JNI.         


**Jni++** features
------------

**Jni++** is designed to let the user get rid of most of JNI routine, delegating it metaprogramming and compilation phase.

**Jni++** solves next JNI issues:
* Tracking the lifetime of thread-local `JNIEnv` instances for each native thread the user prefer to call Java code. Each thread-local instance of `JNIEnv` will be deleted just at finish of the thread function.
* All string signatures will be generated at compile-time using the given information about types.
* The public interface of library looks like Java reflection in C++ code. OOP and RAII extensively used. The general entities of **Jni++** are classes, objects, fields and methods from Java.
* Automatic translation of types between Java and C++ type-spaces.
* User can use only native C++ types in his code. No JNI/Java types more required.
* **Jni++** is thread-safe. It provides capabilities to call the Java code from any native thread in concurrent mode.       


Code examples
------------

#### Capturing the handle to Java class

```c++
Jni::Class string_class{ "java/lang/String" };
```
`Jni::Class` uses the global reference, which can be used across the threads.

#### Capturing the handle to Java object

```c++
jobject local_object; // reference from Java side.

Jni::Object captured_object{ local_object };
```
`Jni::Object` uses the global references as well, leaving the object valid all the time it captured.

#### Construction of object

```c++
Jni::Class string_class{ "java/lang/String" };

Jni::Object captured_object{ Jni::Object::NewObject( string_class ) };
```

#### Complex usage

```c++
// Load the class.
Jni::Class class_handle{ "java/lang/Class" };
// Capture the member-function from class.
Jni::MemberFunction<std::string> func_get_name{ class_handle, "getName" };

// Promote the class to object.
Jni::Object string_class{ Jni::Class{ "java/lang/String" } };

// Get the name of Java class. `java/lang/String` will be stored.
std::string string_class_name{ func_get_name.Call( string_class ) };
```
Lets imagine how much servicing JNI code must be written to solve this small task.


License
------------

The **Jni++** is licensed using Apache-2.0 license.

It consists of no third-party code or libraries.

The root repository of project: https://github.com/FrankStain/jnipp
