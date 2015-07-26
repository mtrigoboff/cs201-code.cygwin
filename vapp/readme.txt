This code demonstrates how to write code in the "object-oriented" style
in a non-object-oriented language. In C, there are no classes nor any
other object-oriented features. But we can still write code that works
the way object-oriented code does, by using void* pointers and an
object-oriented style.

This project manages items that can be either cars, boats, or planes.
The code acts as though there is a "parent class" named Vehicle that
has 3 subclasses: Car, Boat, and Plane.

Since the pointers used in main are void* pointers, code in main has
no way to change any of the fields in the memory that those pointers
point to. The contents of that memory is effectively "private."
Void* pointers used in this way are often referred to as "handles."

This is the style of programming that many people used in the 1980's,
when object-oriented concepts were becoming more well-known, but
object-oriented languages had not yet become common.

