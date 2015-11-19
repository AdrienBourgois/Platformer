	template<typename T, typename U>
	auto JsonValue::tryParseValue(T a, U b) -> void
	{

		if (typeid(b) == typeid(bool))
		{
			if (b)
				_file << "\"" << a << "\": " << "true" << "," << std::endl;
			else
				_file << "\"" << a << "\": " << "false" << "," << std::endl;
		}
		else
			_file << "\"" << a << "\": " << b << "," << std::endl;
	}

	template<typename T>
	auto JsonValue::tryParseArray(T a) -> void
	{

		if (typeid(a) == typeid(std::string))
			_file << "\"" << a << "\",";
		else 
			_file << a << ", ";
	}
