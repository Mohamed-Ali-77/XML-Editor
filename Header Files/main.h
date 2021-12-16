#ifndef MAIN_H_
#define MAIN_H_


#include "XMLTree.h"
#include "xml_parser.h"
#include "compression.h"
#include "xml_formating.h"
#include "XML_Correction.h"
#include "XML_Detection.h"
#include "jsonconverter.h"




/* GLOBAL VARIABLES */
extern string ErrorLines;
extern string StringOriginalData;
extern string Comprssed_data;
extern string DeCompresseddata;
extern unsigned int sizeOfXML ;
extern unsigned int sizeOriginal;
extern unsigned int sizeCompressed;


/* GLOBAL VECTORS */

extern vector<string> XML_ReadFile;
extern vector<string> XML_Formated;
extern vector<string> XML_Decompressed;
extern vector<string> XML_Corrected;
extern vector<string> XML_JSONdata;
extern vector<string> XML_EncodedPairs;
extern vector<char> XML_CodingCharacters;
extern vector<string> Spaces;

void Output_File( const vector<string> &XML_string, int size);
void Output_File(const vector<string> &Spaces, const vector<string> &XML_string, int size, string caller);


#endif /* MAIN_H_ */
