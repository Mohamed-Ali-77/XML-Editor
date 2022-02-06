
#include "xml_formating.h"

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;

void XML_Formating::indentation(vector<string> &Spaces, int &Lineindex, int NumOfSpaces)
{
    for (int i = 0; i < NumOfSpaces; i++)
        {
            Spaces[Lineindex] = Spaces[Lineindex] + " ";
        }
        Lineindex++;
}

XML_Formating::XML_Formating(vector<string> &indentations, vector<string> &XML_Formated , unsigned int LineOfXML)
{
        char start;
        char end;
        char anotherend;
        bool flag = false;
        unsigned int LineIndex = 0;
        int Line = 0;

        string temp;
        string t;
        int Tab = 0;
        stack <string> OpenAngleStack;
        //loop untill end of file
        while (LineIndex < LineOfXML )
        {
            temp = XML_Formated[(LineIndex)];
            LineIndex++;
            // Condition of XML Version Tag
            if ((temp == "") || (((temp[1] == '?') || (temp[1] == '!')) && temp[0] == '<') || ((temp.find("<") == -1) && (temp.find(">") != -1)) || ((temp.find(">") == -1) && (temp.find("<") != -1)))
            {
                indentation(indentations, Line, Tab);
                continue;
            }

            start = temp.find("<") + 1;
            end = temp.find(">");
            if (temp[start] == '/')                         //IF Closing Tag
            {
                t = temp.substr(start, end - start);
                OpenAngleStack.pop();
                Tab = Tab - 4;

            }

            else            //If Opening Tag
            {

                if ((end!=-1) && (temp[end-1] == '/'))			// SELF CLOSING TAGS
                {
                    indentation(indentations, Line, Tab);
                    continue;
                }
                // Tags That have attributes inside like <user Name=" "  ID=" ">
                anotherend = temp.find(" ");
                if (anotherend > start && anotherend < end)
                {
                    t = temp.substr(start, anotherend - start);
                }
                else        // Normal opening Tags
                {
                    t = temp.substr(start, end - start);
                }
                //Push opening and closing tags into Stack To make Them at the same indetation
                OpenAngleStack.push(t);
                Tab = Tab + 4;      //Incremet indentation every time
                temp = temp.substr(end + 1);   // Continue

                if (temp != "") {			// Check if the closing Tag is in the same string Then pop like <id>....</id>

                    start = temp.find("<") + 1;
                    end = temp.find(">");
                    t = temp.substr(start + 1, end - (start + 1));
                    OpenAngleStack.pop();
                    Tab = Tab - 4;

                }
                else   //Normal tags ,, We start from Tab=0 then incremnted by 4 every opening tag but we need to start with no space thu dicrement Tab first to 0 then indent.
                {
                    indentation(indentations, Line, Tab - 4);
                    flag = true;
                }
            }
            if (flag == false)        //Make indentation of closing tag at the same space of it's opening tag
            {
                indentation(indentations, Line, Tab);
            }
            else
            {
                flag = false;
            }

        }
    }


