#include "supportLib.h"
#include <time.h>

using namespace std;

unsigned char *DoubleArrayToByteArray(vector<double> *data){
	unsigned char *out;
	size_t i;

	out = new unsigned char[data->size()];

	for(i = 0; i < data->size(); i++){
		out[i] = data->at(i);
	}

	return out;
}
//NAMING CONVENTION INCLUDED
void WriteToFile(vector<double> *data, string filename){
    unsigned char *bytes;
    bytes = DoubleArrayToByteArray(data);

    //File Timestamp
    char date[20];
    struct tm *ptr;
    time_t tm;
    tm = time(NULL);
    ptr = localtime(&tm);
    strftime(date, 20, "%d_%m_%Y@%H_%M_%S", ptr);

    //Directory Set
    string path="GRAPHS";
    string FinalFileName = path + "/" + filename + "--" + date + ".png";

	ofstream file(FinalFileName, ios::binary);

	if (!file.is_open()) {
		cerr << "Error: Unable to open file " << FinalFileName << " for writing. Error code: " << errno << endl;
		delete[] bytes;
		return; // Exit the function
	}

	file.write(reinterpret_cast<char *>(bytes), data->size());

	if (!file) {
		cerr << "Error: Failed to write data to file " << FinalFileName << "." << endl;
	}

	file.close();

	delete [] bytes;
}

vector<double> *ByteArrayToDoubleArray(vector<unsigned char> *data){
	vector<double> *out;
	size_t i;

	out = new vector<double>(data->size());

	for(i = 0; i < data->size(); i++){
		out->at(i) = data->at(i);
	}

	return out;
}
