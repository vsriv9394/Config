# Configuration File Parser

This C++ header file can be used with a custom-named namespace (see test/test.cpp) to read a configuration file
on a single processor.

## Configuration File Rules

Look at test/config.cfg for an example of the configuration file. The delimiters `{`, `}`, `#` and `:` should
always be preceded and succeeded by a tab, a space or a newline character. `{` and `}` are used to define
sub-configuration scopes. `#` is used for comments. Note that commenting the opening statement of a sub-configuration
scope and leaving the corresponding closing statement uncommented can lead to run-time errors. `:` must always precede
configuration values. A configuration value can consist of one or more tokens separated by spaces. It is the user's
responsibility to use the correct datatype when accessing a configuration value. Valid types are `int`, `double`,
`std::string`, `std::vector<int>`, `std::vector<double>` and `std::vector<std::string>`.