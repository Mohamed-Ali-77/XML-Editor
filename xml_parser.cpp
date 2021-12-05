#include "xml_parser.h"


XML_Parser::XML_Parser(string file_data, vector<string> &XML_Vector, unsigned int &XML_Size)
{

        int str_start;
        int str_end;
        int file_data_index=0;
        XML_Vector.reserve(10000);
        long long vector_capacity = 10000;
        while(file_data[file_data_index] != '\0')
        {
            string line="";

            while( (file_data[file_data_index] == ' ') && (file_data[file_data_index] == '\n' ))
            {
                file_data_index++;
            }

            if(file_data[file_data_index] == '<')
                {
                    str_start = file_data_index;
                    str_end = file_data_index+1;
                    while(file_data[str_end] != '>' && file_data[str_end] != '\0')
                    {
                        str_end++;
                    }
                    if(file_data[str_end] == '\0')
                    {
                        break;
                    }
                }
                else //normal input(not tags)
                {
                    str_start = file_data_index;
                    str_end = file_data_index+1;
                    while(file_data[str_end] != '<' && file_data[str_end] != '\0' && file_data[str_end] != '\n' )
                    {
                        str_end++;
                    }
                    str_end--; //So we dont take "<" with us
                    if(file_data[str_end] == '\0' )
                    {
                        break;
                    }
                }

            if ( file_data[file_data_index] == '\n'   ) {
                file_data_index ++;
                continue;
            }

            file_data_index = str_end+1;
            XML_Vector.push_back(file_data.substr(str_start, str_end - str_start +1));
            XML_Size++;
            if(XML_Size + 20 > vector_capacity)
            {
                XML_Vector.reserve(vector_capacity + 10000);
                vector_capacity = vector_capacity + 10000;
            }
        }
    }



