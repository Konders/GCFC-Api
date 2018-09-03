#include <iostream>
#include "GCFC-SDK.hpp"
using namespace std;

void main()
{
	//Get congifs response from API
	string response = GCFC::GetResponse("", "");//if keys is empty, enable test mode(returns 1 test config)
	//Parsing json response
	vector<GCFC::Config_t> configs = GCFC::Parse(const_cast<char*>(response.c_str()));
	//Configs accessibility
	for (auto const& config : configs) {
	cout << "Name: " << config.Name << endl;
	cout << "Description: " << config.Description << endl;
	cout << "Owner: " << config.Owner << endl;
	cout << "Type: " << config.Type << endl;
	cout << "File_type: " << config.File_type << endl;
	cout << "Config: " << config.Config << endl;
	}
	//Display error if configs empty
	if (configs.size() <= 0)
		cerr << response << endl;
}