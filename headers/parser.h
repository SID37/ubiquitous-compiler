#pragma once
#include <string>
#include <cstring>
#include <exception>
#include <vector>
#include <algorithm>
#include <queue>

#include <iostream>

namespace Slime
{
    class Slarray
    {
        enum SlarrayType {
            NUMBER,
            STRING,
            ARRAY,
        } type;

        struct Array
        {
            Slarray* data;
            int length;
        };

        struct String
        {
            char* data;
            int length;
        };

        union Sldata
        {
            Array array;
            String string;
            int number;
        } data;

        void NumToString()
        {
            if (type != NUMBER)
                throw std::bad_typeid();
            int len = data.number;
            type = STRING;
            data.string.length = len;
            data.string.data = new char[std::abs(len) + 1];
            std::fill_n(data.string.data, std::abs(len) + 1, 0);
        }

        void NumToArray()
        {
            if (type != NUMBER)
                throw std::bad_typeid();
            int len = data.number;
            type = ARRAY;
            data.array.length = len;
            data.array.data = new Slarray[len];
        }

        void StringToArray()
        {
            if (type != STRING)
                throw std::bad_typeid();
            int len = data.string.length;
            char* str = data.string.data;
            type = ARRAY;
            data.array.length = len;
            data.array.data = new Slarray[len + 1];
            for (int i = 0; i < len; ++i) {
                data.array.data[i] = str[i];
            }
            delete[] str;
        }

    public:
        Slarray()
        {
            type = NUMBER;
            data.number = 0;
        }

        Slarray(const std::string& s)
        {
            type = STRING;
            data.string.length = s.size();
            data.string.data = new char[data.string.length + 1];
            std::strcpy(data.string.data, s.data());
        }

        Slarray(int num)
        {
            type = NUMBER;
            data.number = num;
        }

        Slarray(const std::vector<Slarray>& arr)
        {
            type = ARRAY;
            data.array.length = arr.size();
            data.array.data = new Slarray[data.array.length];
            std::copy_n(arr.cbegin(), arr.size(), data.array.data);
        }

        int GetNumber()
        {
            switch (type) {
                case NUMBER: return data.number;
                case STRING: return data.string.length;
                case ARRAY:  return data.array.length;
                default: throw std::bad_typeid();
            }
        }

        int Length()
        {
            return GetNumber();
        }

        Slarray& operator[](int i)
        {
            switch (type) {
                case NUMBER: {
                    NumToArray();
                    return (*this)[i];
                }
                case STRING:  {
                    StringToArray();
                    return (*this)[i];
                }
                case ARRAY:  return data.array.data[i];
                default: throw std::bad_typeid();
            }
        }

        std::string PrettyPrint(const std::string spaces = "")
        {
            std::string result;
            switch (type) {
                case NUMBER: {
                    result += spaces + std::to_string(data.number);
                    break;
                }
                case STRING: {
                    result += spaces + data.string.data;
                    break;
                }
                case ARRAY: {
                    result += spaces + "{\n";
                    int len = std::abs(data.array.length);
                    for (int i = 0 ; i < len; ++i) {
                        result += data.array.data[i].PrettyPrint(spaces + "\t");
                        result += i == len - 1 ? "\n" : ",\n";
                    }
                    result += spaces + '}';
                    break;
                }
                default: throw std::bad_typeid();
            }
            return result;
        }

        ~Slarray() {
            switch (type) {
                case NUMBER: return;
                case STRING: {
                    delete[] data.string.data;
                    return;
                }
                case ARRAY: {
                    delete[] data.array.data;
                    return;
                }
            }
        }
    };

    class Parser
    {
        enum LineType {
            COMMAND,
            POP_CONTEXT,
            PUSH_CONTEXT,
        };

        struct CommandLine
        {
            LineType type;
            Slarray data;
        };

        std::string line;
        std::queue<CommandLine> queue;

        Slarray Parse(const std::string& s)
        {
            return 0;   // TODO: parser
        }

        Slarray RunLine(const CommandLine& command)
        {
            return 0;   // TODO: line execute
        }

    public:
        Parser(const std::string& line):
            line(line)
        { }

        void Run(const std::string& input)
        {
            Slarray program = Parse(line);
            int programLen =  program.Length();
            for (int i = 0; i < programLen; ++i)
                queue.push({COMMAND, program[i]});

            while (!queue.empty()) {
                RunLine(queue.front());
                queue.pop();
            }
        }
    };
}
