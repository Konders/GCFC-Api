# GCFC SDK
**Dependencies**
1. [gason++](https://github.com/azadkuh/gason--)


**Connection**
If you using want to use https connection, send requests to https://gcfc.ru/api/configs
or use default http connection with http://api.gcfc.ru/Configs
**API key**
You need hack api key, and user api key.
First API key you can get on your personal cabinet.
Second API key user must get on personal cabinet and put in string variable
****
**Server-side information**
Successful request returns json encoded configs array like this: 

    [{"name":"1tap cfg 4 this paste","config":"aim = 1\r\nwh = 1\r\nbhop = 1\r\n","description":"Best config for hvh legends","type":"Rage","owner":"legenden","file_type":"ini"}]

Unsuccessful request can return errors:
1. Incorrect parameters, you must send api_key and user_key
2. Invalid api_key
3. Invalid user_key
4. User banned
5. User doesn`t have configs for this hack
####Usage example



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
