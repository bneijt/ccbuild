/*
	ccbuild - A strict developer's build utility
	Copyright (C) 2005  A. Bram Neijt <bneijt@gmail.com>

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "Arguments.ih"

void Arguments::outputOptions(ostream &str) const
{
	int optionIndex(0);	//Although this should be an unsigned, get_longOpts wants an int :-(
	char spacer[32];
	memset(&spacer[0], ' ', sizeof(spacer));
	spacer[sizeof(spacer) -1] = '\0';
	unsigned spacerLen = strlen(spacer);

	string flag;
	while(true)
	{
		Option const * curOption = &d_options[optionIndex];

		if(curOption->flags == 0 && curOption->value == 0 && curOption->helpText == 0)
			break;

		istringstream givenFlags(string(curOption->flags) + " ");	//Needed extra space for eof in while loop below
		bool first = true;
		unsigned alreadyOut = 0;
		while(true)
		{
			givenFlags >> flag;

			if(givenFlags.eof())
				break;

			if(flag.size() == 1)
			{
				str << (first ? " " : ", ") << "-" << flag;
				alreadyOut += (first ? 2 : 3);
			}
			else
			{
				str << (first ? " " : ", ") << "--" << flag;
				alreadyOut += (first ? 3 : 4);
			}
			alreadyOut += flag.size();
			first = false;
		}

		str << " ";
		++alreadyOut;
		if(curOption->value && strlen(curOption->value) > 0)
		{
			str << curOption->value;
			alreadyOut += strlen(curOption->value);
		}


		if(alreadyOut < spacerLen)
		{
			spacer[spacerLen - alreadyOut] = '\0';
			str << spacer;
			spacer[spacerLen - alreadyOut] = ' ';
		}



		if(curOption->helpText)
		{
			istringstream helpText(string(curOption->helpText) + " ");
			unsigned maxLen = 79 - spacerLen;
			unsigned len = 0;
			string word;
			while(true)
			{
				helpText >> word;

				if(helpText.eof())
					break;

				len += word.size();

				if(len > maxLen)
				{
					str << "\n " << spacer;
					len = 0;
				}
				else
				{
					str << " ";
					++len;
				}
				str << word;
			}
		}
		str << "\n";
		++optionIndex;
	}
}
