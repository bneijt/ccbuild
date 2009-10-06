#include "String.ih"
std::string String::replace(char from, char to) const
{
				std::string copy(*this);
			__foreach(c, copy)
				if(*c == from)
					*c = to;
			return copy;

}
std::string String::replace(std::string const &from, std::string const &to) const
{
				std::string copy(*this);
			while(true)
			{
			  std::string::size_type pos = copy.find(from);
			  if(pos == std::string::npos)
			    break;
			  copy.replace(pos, from.size(), to);
			}
			return copy;

}
