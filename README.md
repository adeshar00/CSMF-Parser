# About

Provides a function to read CSMF format files (as generated by the [Blender Addon](https://github.com/adeshar00/BlenderAddon)) and generate arrays of vertices and triangles.  See the example folder for an example of it's use.

# CSMF Format

The data is stored as a series of fixed-point numbers and unsigned integers, each number being represented with two bytes.  Fixed-point numbers can represent real numbers within the range of -128 to 127+(255/256) with a precision of 1/256; unsigned integers can represent any integer within the range of 0 to ~65k.  Both types are little-endian

First 2 bytes are a uint for the object count  
Per object:  
&nbsp;&nbsp;2 byte uint for the vertex count   
&nbsp;&nbsp;2 byte uint for the triangle count  
&nbsp;&nbsp;6 bytes for object translations (2 byte fixed-point number per x, y, and z)  
&nbsp;&nbsp;6 bytes for object rotation (2 byte fixed-point number per pitch, yaw, roll)  
&nbsp;&nbsp;6 bytes for object scale (2 byte fixed-point number per x, y, and z)  
&nbsp;&nbsp;Per vertex:  
&nbsp;&nbsp;&nbsp;&nbsp;2 byte fixed-point number for x coordinate  
&nbsp;&nbsp;&nbsp;&nbsp;2 byte fixed-point number for y coordinate  
&nbsp;&nbsp;&nbsp;&nbsp;2 byte fixed-point number for z coordinate  
&nbsp;&nbsp;Per triangle:  
&nbsp;&nbsp;&nbsp;&nbsp;2 byte uint for index of first vertex  
&nbsp;&nbsp;&nbsp;&nbsp;2 byte uint for index of second vertex  
&nbsp;&nbsp;&nbsp;&nbsp;2 byte uint for index of third vertex  
