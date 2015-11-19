template<typename T>
auto JsonLoad::getValue(std::string name) -> std::vector<T>
{
	std::fstream file("./assets/json/"+ fileName);
	std::string 	line;
	std::string 	type;
	std::vector<T> 	vecVal;
	T 				val;

	while (std::getline(file, line))
	{
		if (line.size() > 0)
		{
			std::stringstream line_stream(line);
			line_stream >> type;	
			if (type == name)
			{
				line_stream >> val;
				vecVal.push_back(val);
			}
		}
	}
	return vecVal;
}

