## File Handling
### Stream?
- Input/Output in C++ is performed using Sequence of bytes called Streams.
- Boost IOStreams can be used for:
  - _1._ Access TCP connections
  - _2._ Accessing memory-mapped files
  - _3._ file access using operating system file descriptors
  - _4._ For text filtering with regular expressions
### Stream types?
- **1. [ofstream/ostream/Write to File/Write to stdout(<<)](ofstream_ostream)** 
  - Direction of flow of bytes is from RAM to device(Eg: Monitor, File, Printer).
  - Examples: Writing to file, Writing to stdout using stream insertion operator(<<)
- **2. [ifstream/istream/Read from file/Input to file(>>)](ifstream_istream)** 
  - Direction of flow of bytes is from the device(Eg: Keyboard, File, Network) to RAM.
- **3. fstream/iostream/Bidirectional** Capable of both Input & Output.
