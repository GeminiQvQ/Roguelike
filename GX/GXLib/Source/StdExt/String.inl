namespace GX
{
	inline std::vector<std::string_view> split_string(std::string_view string, char delimiter)
	{
		std::vector<std::string_view> result;
		
		std::string_view::size_type pos0 = 0;
		std::string_view::size_type pos1 = 0;
		
		while (pos1 != std::string_view::npos)
		{
			pos1 = string.find(delimiter, pos0);
			result.emplace_back(string.substr(pos0, pos1 - pos0));
			pos0 = pos1 + 1;
		}

		return result;
	}
}